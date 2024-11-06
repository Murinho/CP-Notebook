const int maxn = 1e5+5;
int arr[maxn];

// Sum of values. (1-indexed).
void add(int x, int v){
    while (x <= maxn-5){
        arr[x] += v;
        x += lsb(x);
    }
}
// Getting to whole prefix.
int get(int x){ 
    int freq = 0;
    while (x > 0){
        freq += arr[x];
        x -= lsb(x);
    }
    return freq;
}
