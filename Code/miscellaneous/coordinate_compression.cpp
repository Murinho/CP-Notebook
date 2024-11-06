vi a;
map <ll,ll> mp;
int pos = 0;
sort(ALL(a));
st.erase(unique(ALL(a)),a.end());
for (auto au : a){
	mp[au] = pos;
	pos++;
}