const int maxn = 1e5+5;
int arr[maxn];

struct Fen{
	// Sum of values. (1-indexed).
	void add(int x, int v){
		while (x <= maxn-5){
			arr[x] += v;
			x += lsb(x);
		}
	}
	// Getting to whole prefix [1,x]
	int get(int x){ 
		int freq = 0;
		while (x > 0){
			freq += arr[x];
			x -= lsb(x);
		}
		return freq;
	}
}; // To simulate add range updates [l,r,x], add +x in position l, and -x in position r+1

