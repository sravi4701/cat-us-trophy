const int N = 100 * 1000 + 10;
char str[N]; bool bh[N], b2h[N];
int rank[N], pos[N], cnt[N], next[N], lcp[N];
bool smaller(int a, int b) { return str[a]<str[b];}
void suffix_array(int n) {
    REP(i,n)pos[i]=i, b2h[i]=false;
    sort(pos,pos+n,smaller);
    REP(i,n) bh[i]=!i||str[pos[i]] != str[pos[i-1]];
    for(int h=1;h<n;h*=2) {
        int buckets=0;
        for(int i=0,j; i<n; i=j) {
            j=i+1;
            while(j<n && !bh[j])j++;
            next[i]=j;
            buckets++;
        }
        if(buckets==n)break;
        for(int i=0;i<n;i=next[i]) {
            cnt[i] = 0;
            FOR(j, i, next[i]-1) rank[pos[j]]=i;
        }
        cnt[rank[n-h]]++;
        b2h[rank[n-h]]=true;
        for(int i=0;i<n;i=next[i]) {
            FOR(j, i, next[i]-1) {
                int s = pos[j]-h;
                if(s>=0){
                    rank[s] = rank[s] + cnt[rank[s]]++;
                    b2h[rank[s]]=true;
            }   }
            FOR(j, i, next[i]-1) {
                int s = pos[j]-h;
                if(s>=0 && b2h[rank[s]])
                    for(int k=rank[s]+1;!bh[k] && b2h[k]; k++) b2h[k]=false;
        }   }
        REP(i,n) pos[rank[i]]=i, bh[i]|=b2h[i];
    }
    REP(i,n) pos[rank[i]]=i;
}
void get_lcp(int n) {
    lcp[0]=0;
    int h=0;
    REP(i,n) if(rank[i]) {
        int j=pos[rank[i]-1];
        while(i+h<n && j+h<n && str[i+h] == str[j+h]) h++;
        lcp[rank[i]]=h;
        if(h)h--;
}   }
//slower version of SA, also works with get_lcp
struct data {
int nr[2], p;
bool operator<(const data &v)const{ return nr[0] < v.nr[0] || ...;}
bool operator==(const data &v)const{return nr[1]==v.nr[1]&&nr[0]==v.nr[0];}
} L[MAXN];
int P[MAXLG+2][MAXN], pos[MAXN], rank[MAXN];
int suffix_array(char *A, int N)
{
    int step,cnt;
    REP(i,N) P[0][i] = A[i];
    for(step=1,cnt=1;cnt/2<N;cnt*=2,step++) {
        REP(i,N) L[i]=(data){P[step-1][i],(i+cnt<N)?P[step-1][i+cnt]:-1,i};
        sort(L,L+N);
        REP(i,N) P[step][L[i].p] = i && L[i]==L[i-1]? P[step][L[i-1].p]:i;
    }
    REP(i,N) rank[L[i].p]=i;
    REP(i,N) pos[rank[i]]=i;
    return step-1;
}
