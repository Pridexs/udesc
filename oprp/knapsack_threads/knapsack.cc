// Alexandre Maros
// pridexs.com
//
// This code was done in a rush without thinking too much
// about code cleaness and all that.
//
// This was an assignment for the Parallel Programming class
// where we had to quickly implement a problem (in this case
// the knapsack problem from a parallel programming competition)
// using threads and see the how much we could speed up the
// algorithm.

#include "knapsack.hh"
#include <algorithm>
#include <bitset>
#include <iostream>
#include <vector>
#include <cstdio>
#include <pthread.h>
using namespace std;

typedef struct {
      int tid;
      int nThreads;
      int n;
      long unsigned capacity;
      const item *items;
      vector<const item*> v;
      bitset<32768> best;
} param_t;

class comparator {
    public:
        bool operator()(const item* a,const item* b) const {
            return a->weight*b->volume>a->volume*b->weight;
        }
};

/*
 * Funcao executada por uma thread
 */
void *knapsack_worker(void *arg)
{
   param_t *p = (param_t *) arg;
   //printf("Hi! I am thread %d/%d\n", p->tid, p->nThreads-1);
   knapsack2(p->tid, p->nThreads, p->n, p->items, p->v, p->best, p->capacity);
}

void knapsack2(int tid, int nThreads, const long unsigned int n, const item *items, vector<const item*> &v, bitset<32768> &best, const long unsigned int capacity) {
    int remainder = n % nThreads;
    int aditional = 0;
    if (remainder) {
        aditional = tid % remainder;
        if (!aditional)
            aditional = tid;
    } 
    int initPos = tid * (n/nThreads) + aditional;
    int limit = initPos + (n/nThreads);
    if (tid < remainder)
        limit++;
    
    v.reserve(limit-initPos);
    printf("%d: %d->%d\n", tid, initPos, limit);
    printf("n: %d, nThreads: %d, remainder %d, aditional %d, initpos %d, limit %d\n\n", n, nThreads, remainder, aditional, initPos, limit);
    for (int i = initPos; i < limit; i++) {
        //printf("Thread %d: %d\n", tid, i);
        v.push_back(&items[i]);
    }

    sort(v.begin(),v.end(),comparator());
    vector<long unsigned int> sum;
    sum.reserve(n);
    long unsigned int s=0;
    for(vector<const item*>::reverse_iterator it=v.rbegin();it!=v.rend();++it) {
        s+=(*it)->weight;
        sum.push_back(s);
    }
    reverse(sum.begin(),sum.end());
    bitset<32768> bitsetA;

    long unsigned int bestvalue=0;
    long unsigned int weight=0;
    long unsigned int volume=0;
    int i=0;
    do {
        while(i<v.size()) {
            if(volume+v[i]->volume<=capacity&&weight+sum[i]>bestvalue) {
                bitsetA.set(i);
                weight+=v[i]->weight;
                volume+=v[i]->volume;
            }
            ++i;
        }
        if(weight>bestvalue) {
            best=bitsetA;
            bestvalue=weight;
        }
        while(!bitsetA.test(--i));
        bitsetA.reset(i);
        weight-=v[i]->weight;
        volume-=v[i]->volume;
        ++i;
    } while(bitsetA.any());
}

void knapsack(int argc,char* argv[],long unsigned int* output,const long unsigned int capacity,const long unsigned int n,const item* items, const int nThreads) {
    
    int i;
    pthread_t *threads;
    threads = (pthread_t *) malloc(nThreads * sizeof(pthread_t));
    param_t *args = (param_t *) malloc(nThreads * sizeof(param_t));

    for (i = 0; i < nThreads; i++)
    {
        args[i].tid = i;
        args[i].nThreads = nThreads;
        args[i].n = n;
        args[i].items = items;
        args[i].capacity = capacity;
        pthread_create(&threads[i], NULL, knapsack_worker, (void *) (args+i));
    }
    for (i = 0; i < nThreads; i++)
    {
        pthread_join(threads[i], NULL);
    }
    free(threads);

    vector<const item*> v;
    for (i = 0; i < nThreads; i++)
    {
        //printf("Thread %d:\n", i);
        size_t sizev = args[i].v.size();
        unsigned countb = args[i].best.count();
        cout << "v.size() " << sizev << " " << "nBitsets " << countb << endl << endl;
        for(long unsigned int j=0;j<sizev;j++) {
            if (args[i].best.test(j))
                v.push_back(args[i].v[j]);
        }
    }
    free(args);

    sort(v.begin(),v.end(),comparator());
    vector<long unsigned int> sum;
    sum.reserve(n);
    long unsigned int s=0;
    for(vector<const item*>::reverse_iterator it=v.rbegin();it!=v.rend();++it) {
        s+=(*it)->weight;
        sum.push_back(s);
    }
    reverse(sum.begin(),sum.end());
    bitset<32768> bitsetA;
    bitset<32768> best;

    long unsigned int bestvalue=0;
    long unsigned int weight=0;
    long unsigned int volume=0;
    i=0;
    size_t sizev = v.size();
    do {
        while(i<sizev) {
            if(volume+v[i]->volume<=capacity&&weight+sum[i]>bestvalue) {
                bitsetA.set(i);
                weight+=v[i]->weight;
                volume+=v[i]->volume;
            }
            ++i;
        }
        if(weight>bestvalue) {
            best=bitsetA;
            bestvalue=weight;
        }
        while(!bitsetA.test(--i));
        bitsetA.reset(i);
        weight-=v[i]->weight;
        volume-=v[i]->volume;
        ++i;
        
    } while(bitsetA.any());
    for(i=0;i<sizev;i++) {
        output[v[i]-items]=best.test(i);
//      if(best.test(i)) {
//          cout<<items[v[i]-items].volume<<endl;
//      }
    }
}

