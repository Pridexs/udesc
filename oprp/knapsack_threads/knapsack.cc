#include "knapsack.hh"
#include <algorithm>
#include <bitset>
#include <iostream>
#include <vector>
#include <pthread.h>
using namespace std;

typedef struct {
      int tid;
      int nThreads;
      int n;
      const item *items;
      vector<const item *items> v;
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
   knapsack2(p->tid, p->nThreads, p->items, p->v, p->b);
}

void knapsack2(int tid, int nThreads, int n, const item *items, vector<const item*> &v, bitset<32768> &best) {
    for (int i = n * tid; i < (n*tid) + (n/nThreads); i++) {
        
    }
}

void knapsack(int argc,char* argv[],long unsigned int* output,const long unsigned int capacity,const long unsigned int n,const item* items, const int nThreads) {
    
    pthread_t *threads;
    threads = (pthread_t *) malloc(nThreads * sizeof(pthread_t));
    args = (param_t *) malloc(nThreads * sizeof(param_t));

    for (i = 0; i < nThreads; i++)
    {
        pthread_create(&threads[i], NULL, knapsack_worker, (void *) (args+i));
        args[i].tid = i;
        args[i].nThreads = nThreads;
        args[i].n = n;
    }

    vector<const item*> v;
    v.reserve(n);
    for(long unsigned int i=0;i<n;++i) {
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
    bitset<32768> best;

    long unsigned int bestvalue=0;
    long unsigned int weight=0;
    long unsigned int volume=0;
    int i=0;
    do {
        while(i<n) {
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
    for(i=0;i<n;i++) {
        output[v[i]-items]=best.test(i);
//      if(best.test(i)) {
//          cout<<items[v[i]-items].volume<<endl;
//      }
    }
}

