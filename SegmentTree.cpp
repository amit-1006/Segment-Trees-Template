#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
#define f first
#define s second
#define mod 1000000007
#define vll vector<ll>
#define pll vector<pair<ll,ll>>
#define pqmax priority_queue<ll>
#define pqmin priority_queue<ll,vll,greater<ll>>

const ll N=1e6+1;

ll seg[4*N],lazy[4*N];
ll arr[N];

ll n;

//call as (1,0,n-1)
void build(ll node,ll ss,ll se){
    if(ss==se){
        seg[node]=arr[ss];
        return;
    }
    ll mid=(ss+se)/2;
    build(node*2+1,ss,mid);
    build(node*2+2,mid+1,se);
}

//call as (1,0,n-1,l,r)
ll queryRange(ll node,ll ss,ll se,ll l,ll r){
    if(ss>=l && se<=r){
        return seg[node];
    }

    if(ss>r || se<l) return 0;
    ll mid=(l+r)/2;
    ll p1=queryRange(node*2+1,ss,mid,l,r);
    ll p2=queryRange(node*2+2,mid+1,se,l,r);
    return p1+p2;
}

// call as (1,0,n01,ind,val)
void updatePoint(ll node,ll ss,ll se,ll ind,ll val){
    if(se==se){
        seg[node]+=val;
        return;
    }
    ll mid=(se+ss)/2;
    if(ind<=mid && ind>=ss){
        updatePoint(node*2+1,ss,mid,ind,val);
    }
    else updatePoint(node*2+2,mid+1,se,ind,val);
    seg[node]=seg[node*2+1]+seg[node*2+2];

}

// call as (1,0,n-1,l,r,val)
//l and r are 0 indexed
void updateRange(ll node,ll ss,ll se,ll l, ll r,ll val){
    if(lazy[node]!=0){
        seg[node]+=(se-ss+1)*lazy[node];
        if(ss!=se){
            lazy[2*node+1]+=lazy[node];
            lazy[2*node+2]+=lazy[node];
        }
        lazy[node]=0;
    }

    if(ss>r || se<l || ss>se) return;

    if(ss>=l && se<=r){
        seg[node]+=(se-ss+1)*val;
        if(ss!=se){
            lazy[2*node+1]+=val;
            lazy[2*node+2]+=val;
        }
        return;
    }
    ll mid=(ss+se)/2;
    updateRange(node*2+1,ss,mid,l,r,val);
    updateRange(node*2+2,mid+1,se,l,r,val);
    seg[node]=seg[node*2+1]+seg[node*2+2];
}

//call as (1,0,n-1,l,r)
// l and r 0 indexed
ll queryLazy(ll node,ll ss,ll se,ll l,ll r){

     if(lazy[node]!=0){
        seg[node]+=(se-ss+1)*lazy[node];
        if(ss!=se){
            lazy[2*node+1]+=lazy[node];
            lazy[2*node+2]+=lazy[node];
        }
        lazy[node]=0;
    }

    if(ss>r || se<l || ss>se) return 0;

    if(ss>=l && se<=r){
        return seg[node];
    }

     ll mid=(ss+se)/2;
    ll p1=queryLazy(node*2+1,ss,mid,l,r);
    ll p2=queryLazy(node*2+2,mid+1,se,l,r);
    return p1+p2;

}


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	ll t;
	t=1;
	cin>>t;
	start:
	while(t--){
            ll q;
            cin>>n>>q;

            for(ll i=0;i<4*n;i++){
                seg[i]=0;
                lazy[i]=0;
            }

            while(q--){
                ll type;
                cin>>type;
                if(type==0){
                    ll a,b,d;
                    cin>>a>>b>>d;
                    a--;b--;
                    updateRange(1,0,n-1,a,b,d);
                }
                else{
                    ll a,b;
                    cin>>a>>b;
                    a--;b--;
                    cout<<queryLazy(1,0,n-1,a,b)<<endl;
                }
            }

	}
	return 0;
}
