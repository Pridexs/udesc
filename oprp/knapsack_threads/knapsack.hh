#include <vector>
#include <bitset>

typedef struct {
	long unsigned int weight;
	long unsigned int volume;
} item;
/**
 * @param argc the argc
 * @param argv the argv
 * @param output The output array of item quantities
 * @param capacity The knapsack capacity
 * @param n The number of available items
 * @param items The array of n available items
 */
void knapsack(int argc,char* argv[],long unsigned int* output,const long unsigned int capacity,const long unsigned int n,const item* items, const int nThreads);
void knapsack2(int tid, int nThreads, const long unsigned int n, const item *items, std::vector<const item*> &v_complete, std::bitset<32768> &best, const long unsigned int capacity);
void *knapsack_worker(void *arg);