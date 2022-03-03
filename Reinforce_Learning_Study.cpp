#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<ctime>
#include<cstring>
#include<cmath>
using namespace std;
{
double value_map[50][50];
int map_N;
int stra_tot=4;
int dx[4]={1,0,-1,0};
int dy[4]={0,1,0,-1};
bool if_visited[50][50]; 
double Q[50][50][4];
double val[50][50];
int best_strategy[50][50];
int training_time=1e4;
double epsilon_possibility=0.3;
double future_reward=0.8;
double studying_rate=0.02;
}
void show(bool which_mode){
	if(which_mode==1){
		for(int i=1;i<=map_N;i++){
			for(int j=1;j<=map_N;j++){
				double u=-100;
				double v=0;
				v=best_strategy[i][j];
				if(v==0)printf("下 ");
				else if(v==1)printf("右 ");
				else if(v==2)printf("上 ");
				else if(v==3)printf("左 ");
			}
			printf("\n");
		};
	}else{
			for(int i=1;i<=map_N;i++){
		for(int j=1;j<=map_N;j++){
			double u=-100;
			double v=0;
			for(int k=0;k<4;k++){
				printf("%d %d %d:%f\n",i,j,k,Q[i][j][k]);
			}
//			v=best_strategy[i][j];
			printf("\n");
//			if(v==0)printf("下 ");
//			else if(v==1)printf("右 ");
//			else if(v==2)printf("上 ");
//			else if(v==3)printf("左 ");
		}
		printf("\n");
	};
	}
	
	
} 
bool map_valid(int prex,int prey){
	if(prex<=0||prey<=0)return false;
	if(prex>map_N||prey>map_N)return false;
	return true;
} 
int epsilon_greedy_method(int b_strategy){
	int temp_pos=rand()%100000;
	if(temp_pos<=100000*epsilon_possibility){
		return rand()%stra_tot;
	}else return b_strategy;
}
int Qlearning_rew(int prex,int prey,int prestra){
	int nowx=prex+dx[prestra];
	int nowy=prey+dy[prestra];
	return val[nowx][nowy];
}
void Qlearning_simu(int nowx,int nowy){
//	printf("simu:%d %d\n",nowx,nowy);
	int temp_newx,temp_newy;
	int chosen_stra,temp_beststra;
	
	if(value_map[nowx][nowy]>0.9)return;
	if(if_visited[nowx][nowy]==1){
//		printf("exit!");
		return;
	}
	
	while(true){
		chosen_stra=epsilon_greedy_method(best_strategy[nowx][nowy]);
		temp_newx=nowx+dx[chosen_stra];
		temp_newy=nowy+dy[chosen_stra];
		temp_beststra=best_strategy[temp_newx][temp_newy];
		if(map_valid(temp_newx,temp_newy)==1)break;
	}
	
	int ins_reward=value_map[temp_newx][temp_newy];
	Q[nowx][nowy][chosen_stra]=(1-studying_rate)*Q[nowx][nowy][chosen_stra]+\
							studying_rate*(ins_reward+future_reward*Q[temp_newx][temp_newy][temp_beststra]);
//	if(Q[nowx][nowy][chosen_stra]>Q[nowx][nowy][temp_beststra])	best_strategy[temp_newx][temp_newy]=chosen_stra;
	for(int i=0;i<stra_tot;i++){
		if(Q[nowx][nowy][i]>Q[nowx][nowy][best_strategy[nowx][nowy]]&&\
			map_valid(nowx+dx[i],nowy+dy[i])==1)best_strategy[nowx][nowy]=i;
	}
//	if_visited[nowx][nowy]=1;
	Qlearning_simu(temp_newx,temp_newy);
	return;
}
void Qlearning_algo(){
	int state_x,state_y;
	for(int i=1;i<=training_time;i++){
		memset(if_visited,0,sizeof(if_visited));
//		printf("%d\n",i); 
		while(true){
			state_x=rand()%map_N+1;
			state_y=rand()%map_N+1;
			if(abs(value_map[state_x][state_y])<0.01)break;
		}
		Qlearning_simu(1,1);
//		Qlearning_simu(state_x,state_y);
	}

}

int main(){
	freopen("stdin.txt","r",stdin);
//	freopen("stdout.txt","w",stdout);
	srand(time(NULL));
	cin>>map_N;
	for(int i=1;i<=map_N;i++){
		for(int j=1;j<=map_N;j++){
//			for(int k=0;k<4;k++)Q[i][j][k]=0.1;
			while(true){
				best_strategy[i][j]=rand()%stra_tot;
				if(map_valid(i+dx[best_strategy[i][j]],j+dy[best_strategy[i][j]])==1)break;
			}
			scanf("%lf",&value_map[i][j]);
			printf("%lf ",value_map[i][j]);
		}printf("\n");
	}
	show(1);
	Qlearning_algo();
	printf("---------------------\n");
//	show(0);
	show(1);
//	Monto Carlo Method

//	fclose(stdout);
	fclose(stdin);
	return 0;
}
