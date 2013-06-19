#include<cstdio>
#include<vector>
#define nmax 100001
#define min(a,b) (a)<=(b)?(a):(b)
using namespace std;

struct etc {

	int node,level;

}eulerv[nmax*10];

vector<int> list[nmax];
int log[1000010];
int mat[1000010][26];

int father[nmax], k, n, dist[nmax], poz[nmax];
void rmq() {
	int i,j,p;
	for(i=0;i<=k;++i)
		mat[i][0]=i;
	for(j=1;1<<j<=k;++j)
		for(i=0;i+(1<<j)-1<=k;++i)
			if(eulerv[mat[i][j-1]].level<eulerv[mat[i+(1<<(j-1))][j-1]].level)
				mat[i][j]=mat[i][j-1];
			else
				mat[i][j]=mat[i+(1<<(j-1))][j-1];
	log[0]=0;
	p=1;
	for(i=1;i<=k;++i)
		if(p*2<=i) log[i]=log[i-1]+1,p*=2;
		else log[i]=log[i-1];
}

void euler(int nod){
	int i;
	if(!list[nod].size()){
		eulerv[++k].node=nod;
		if(!poz[nod])
			poz[nod]=k;
	}
	else{
		eulerv[++k].node=nod;
		if(!poz[nod]) poz[nod]=k;
		for(i=0;i<list[nod].size();++i){
			euler(list[nod][i]);
			eulerv[++k].node=nod;
		}
	}
}
int search(int x,int y){
	/*int i,min=nmax,minpos=0;
	if(poz[x]<=poz[y]){
		for(i=poz[x];i<=poz[y];++i)
			if(min>eulerv[i].level){
				min=eulerv[i].level;
				minpos=i;
			}
	}
	else
		for(i=poz[y];i<=poz[x];++i)
			if(min>eulerv[i].level){
				min=eulerv[i].level;
				minpos=i;
			}
	return eulerv[minpos].node;
	*/
	int aux;
	if(poz[x]<poz[y]){
		x=poz[x]; y=poz[y];
	}
	else{
		aux=poz[x]; x=poz[y]; y=aux; 
	}
	if(eulerv[mat[x][log[y-x+1]]].level<eulerv[mat[y-(1<<log[y-x+1])+1][log[y-x+1]]].level)
		return eulerv[mat[x][log[y-x+1]]].node;
	else
		return eulerv[mat[y-(1<<log[y-x+1])+1][log[y-x+1]]].node;
};
int main(){
	int i,no_qr,x,y;
	freopen("lca.in","r",stdin);
	freopen("lca.out","w",stdout);
	scanf("%d%d",&n,&no_qr);
	for(i=2;i<=n;++i){
		scanf("%d",father+i);
		list[father[i]].push_back(i);
	}
	for(i=2;i<=n;++i)
		dist[i]=dist[father[i]]+1;
	euler(1);
	for(i=1;i<=k;++i)
		eulerv[i].level=dist[eulerv[i].node];
	/*for(i=1;i<=k;++i)
		printf("%d ",eulerv[i].level);
	printf("\n");
	for(i=1;i<=k;++i)
		printf("%d ",eulerv[i].node);*/
	rmq();
	for(i=1;i<=no_qr;++i){
		scanf("%d%d",&x,&y);
		printf("%d\n",search(x,y));
	}
	return 0;
}
