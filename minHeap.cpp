#include <bits/stdc++.h>
#define ll long long
#define pb push_back

using namespace std;

class BHeap {
   private:
   vector <int> heap;
   int l(int parent);
   int r(int parent);
   int par(int child);
   void heapifyup(int index);
   void heapifydown(int index);
   public:
      BHeap() {}
      void insert(int element);
      void extractMin();
      void showHeap();
      int showSize();
      int getMin();
      bool isEmpty();
};

bool BHeap::isEmpty(){
    if (heap.size() == 0) return true;
    return false;
}

int BHeap::showSize() {
   return heap.size();
}
void BHeap::insert(int ele) {
   heap.push_back(ele);
   heapifyup(heap.size() -1);
}
void BHeap::extractMin() {
   if (heap.size() == 0) {
      cout<<"Heap is Empty"<<endl;
      return;
   }
   heap[0] = heap.at(heap.size() - 1);
   heap.pop_back();
   heapifydown(0);
   cout<<"Element Deleted"<<endl;
}
int BHeap::getMin() {
   if (heap.size() == 0) {
      return -1;
   }
   else
   return heap.front();
}
void BHeap::showHeap() {
   cout<<"Heap --> ";
   for (auto elem : heap) cout<<elem<<" ";
   cout<<"\n";
}
int BHeap::l(int parent) {
   int l = 2 * parent + 1;
   if (l < heap.size())
      return l;
   else
      return -1;
}
int BHeap::r(int parent) {
   int r = 2 * parent + 2;
   if (r < heap.size())
      return r;
   else
      return -1;
}
int BHeap::par(int child) {
   int p = (child - 1)/2;
   if (child == 0)
      return -1;
   else
      return p;
}
void BHeap::heapifyup(int in) {
   if (in >= 0 && par(in) >= 0 && heap[par(in)] > heap[in]) {
      int temp = heap[in];
      heap[in] = heap[par(in)];
      heap[par(in)] = temp;
      heapifyup(par(in));
   }
}
void BHeap::heapifydown(int in) {
   int child = l(in);
   int child1 = r(in);
   if (child >= 0 && child1 >= 0 && heap[child] > heap[child1]) {
      child = child1;
   }
   if (child > 0 && heap[in] > heap[child]) {
      int t = heap[in];
      heap[in] = heap[child];
      heap[child] = t;
      heapifydown(child);
   }
}


int main() {
    vector <ll> a;
    BHeap pq;
    pq.insert(10);
    pq.insert(1020);
    pq.insert(600);
    pq.insert(500);
    pq.insert(777);
    pq.insert(550);
    pq.showHeap();
    while(!pq.isEmpty()){
        ll aux = pq.getMin();
        pq.extractMin();
        a.pb(aux);
    }
    for (int i = 0; i<a.size(); i++) cout<<a[i]<<" ";
    cout<<endl;
    return 0;
}