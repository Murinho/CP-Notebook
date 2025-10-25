const ll maxn = 1e6+5;
bool c[maxn];

void sieve(){
	c[1]=true;
	fore(i,1,maxn){
		if (!c[i]){
			for (int j = 2; i*j<maxn; j++){
				criba[i*j] = true;
			}
		}
	}
}
