struct mint {
	const static int M = 998244353;
	ll v = 0;
	mint() {}
	mint(ll v) { this->v = (v % M + M) % M; }
	mint operator+(const mint &o) const { return v + o.v; }
	mint &operator+=(const mint &o) {
		v = (v + o.v) % M;
		return *this;
	}
	mint operator*(const mint &o) const { return v * o.v; }
	mint operator-(const mint &o) const { return v - o.v; }
	mint &operator-=(const mint &o) {
		mint t = v - o.v;
		v = t.v;
		return *this;
	}
	mint operator^(int y) const {
		mint r = 1, x = v;
		for (y <<= 1; y >>= 1; x = x * x)
			if (y & 1) r = r * x;
		return r;
	}
	mint inv() const {
		assert(v);
		return *this ^ M - 2;
	}
	friend istream &operator>>(istream &s, mint &v) {
		return s >> v.v;
		return s;
	}
	friend ostream &operator<<(ostream &s, const mint &v) { return s << v.v; }
	mint operator/(mint o) { return *this * o.inv(); }
};