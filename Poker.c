#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define max 52
void shuttle(int card[],int player[][5]){
	srand(time(NULL));
	int i=0,j=0,temp,count;
	char rank,suit;
	for(count=0;count<4*5;){
		temp = rand()%max;
		if(card[temp]==0){
			card[temp] = 1;
			player[i][j++] = temp;
			if(j==5){
				i++;
				j=0;
			}
			count++;
		}
	}
	for(i=0;i<4;i++){
		printf("P%d : ",i+1);
		for(j=0;j<5;j++){
			if(player[i][j]%4==0)suit = 'c';
			else if(player[i][j]%4==1)suit = 'd';
			else if(player[i][j]%4==2)suit = 'h';
			else if(player[i][j]%4==3)suit = 's';
			
			if(player[i][j]/4==0)rank = 'a';
			else if(player[i][j]/4==9)rank = 't';
			else if(player[i][j]/4==10)rank = 'j';
			else if(player[i][j]/4==11)rank = 'q';
			else if(player[i][j]/4==12)rank = 'k';
			else rank = player[i][j]/4+1+'0';
			printf("%c%c  ",rank,suit);
		}
		printf("\n");
	}
}
void printresult(int i,int j)
{
	if (i==8) printf("Winner : P%d    Straight flush",j+1);
	else if (i==7)printf("Winner : P%d    Four of a kind",j+1);
	else if (i==6)printf("Winner : P%d    Full house",j+1);
	else if (i==5)printf("Winner : P%d    Flush",j+1);
	else if (i==4)printf("Winner : P%d    Straight",j+1);
	else if (i==3)printf("Winner : P%d    Three of a kind",j+1);
	else if (i==2)printf("Winner : P%d    Two pairs",j+1);
	else if (i==1)printf("Winner : P%d    Pair",j+1);
	else          printf("Winner : P%d    High card",j+1);
  printf("\n\n");
}
void compare(int player[][5]){
	int i,j,k,temp,count=0,n;
	int   straight[4] = {0}, flush[4] = {0},four[4] = {0}, three[4] = {0} ,pairs[4] = {0};
	int twopairs[4][2] = {0},point[4]={0},exist[9]={0},arr[4]={0};
	
	for(i=0;i<4;i++)
		for(j=0;j<5;j++)
			for(k=j+1;k<5;k++)
				if(player[i][k]>player[i][j]){
					temp = player[i][k];
					player[i][k] = player[i][j];
					player[i][j] = temp;
				}
		
/*	player[0][0] = 17;
	player[0][1] = 14;
	player[0][2] = 10;
	player[0][3] = 6;
	player[0][4] = 4;
	player[1][0] = 18;
	player[1][1] = 15;
	player[1][2] = 11;
	player[1][3] = 7;
	player[1][4] = 3;*/ 
/*	player[2][0] = 33;
	player[2][1] = 14;
	player[2][2] = 12;
	player[2][3] = 9;
	player[2][4] = 8;
*/
	for(i=0;i<4;i++){
		j=0;
		count = 0;
		for(k=j+1;k<5;k++){
			if(player[i][k]%4!=player[i][j]%4)break;
			count++;
			j++;
		}
		if(count==4)flush[i] = 1;
	}
	for(i=0;i<4;i++){
		j=0;
		count = 0;
		for(k=j+1;k<5;k++){
			if((player[i][j]/4-1)!=player[i][k]/4)break;
			count++;
			j++;
		}
		if(player[i][0]/4==12&&player[i][4]/4==0&&count==3)straight[i]= 1;
		else if(count==4)straight[i] = 1;
	}
	
	for(i=0;i<4;i++){
		n=0;
		j=0;
		count = 0;
		for(k=j+1;k<5;k++){
			if(player[i][k]/4==player[i][j]/4){
				count++;
			}else if(count==3){
				four[i] = player[i][j]+1;
				if(player[i][j]/4==0)four[i] = 53;
				count = 0;
			}else if(count==2){
				three[i] = player[i][j]+1;
				if(player[i][j]/4==0)three[i] = 53;
				count = 0;
			}else if(count==1){
				pairs[i]++;
				twopairs[i][n] = player[i][j]+1;
				if(player[i][j]/4==0)twopairs[i][0] = 53+player[i][3];
				n++;
				count = 0;
			}else count = 0;
			j++;
		}
		if(player[i][j-1]/4==player[i][j]/4&&j==4){
			if(count==3){
				four[i] = player[i][j]+1;
				if(player[i][j]/4==0)four[i] = 53;
				count = 0;
			}else if(count==2){
				three[i] = player[i][j]+1;
				if(player[i][j]/4==0)three[i] = 53;
				count = 0;
			}else if(count==1){
				pairs[i]++;
				twopairs[i][n] = player[i][j]+1;
				if(player[i][j]/4==0)twopairs[i][0] = 53+player[i][3];
				count = 0;
			}else count = 0;
		}
	}
	for(i=0;i<4;i++){
		if(straight[i] && flush[i])point[i] = 8;
		else if(four[i])point[i] = 7;
		else if (three[i] &&pairs[i] == 1)point[i] = 6;
		else if (flush[i])point[i] = 5;
		else if (straight[i])point[i] = 4;
		else if (three[i])point[i] = 3;
		else if (pairs[i] == 2)point[i] = 2;
		else if (pairs[i] == 1)point[i] = 1;
		else point[i] = 0;
	}
	for(i=0;i<4;i++){
		exist[point[i]]++;
	}
	
	for(i=0;i<4;i++){
		for(j=0;j<5;j++)
			if(player[i][j]/4==0)player[i][j] = player[i][j]+53;
	}
	for(i=0;i<4;i++)
		for(j=0;j<5;j++)
			for(k=j+1;k<5;k++)
				if(player[i][k]>player[i][j]){
					temp = player[i][k];
					player[i][k] = player[i][j];
					player[i][j] = temp;
				}
				
	for(i=8;i>=0;i--){
		if(exist[i]){
			if(exist[i]==1){
				for(j=0;j<4;j++){
					if(point[j]==i)break;
				}
				printresult(i,j);
			}else if(exist[i]==2){
				k=0;
				for(j=0;j<4;j++)
					if(point[j]==i){
						arr[k] = j;
						k++;
					}
				if(i==8){
					if(player[arr[0]][4]>player[arr[1]][4])printresult(i,arr[0]);
					else printresult(i,arr[1]);
				}else if(i==7){
					if(four[arr[0]]>four[arr[1]])printresult(i,arr[0]);
					else printresult(i,arr[1]);
				}else if(i==6){
					if(three[arr[0]]>three[arr[1]])printresult(i,arr[0]);
					else printresult(i,arr[1]);
				}else if(i==5){
					if(player[arr[0]][0]>player[arr[1]][0])printresult(i,arr[0]);
					else printresult(i,arr[1]);
				}else if(i==4){
					if(player[arr[0]][4]>player[arr[1]][4])printresult(i,arr[0]);
					else printresult(i,arr[1]);
				}else if(i==3){
					if(three[arr[0]]>three[arr[1]])printresult(i,arr[0]);
					else printresult(i,arr[1]);
				}else if(i==2){
					if(twopairs[arr[0]][0]>twopairs[arr[1]][0])printresult(i,arr[0]);
					else printresult(i,arr[1]);
				}else if(i==1){
					if(twopairs[arr[0]][0]>twopairs[arr[1]][0])printresult(i,arr[0]);
					else printresult(i,arr[1]);
				}else if(player[arr[0]][0]>player[arr[1]][0])printresult(i,arr[0]);
					else printresult(i,arr[1]);
			}else if(exist[i]==3){
				k=0;
				for(j=0;j<4;j++)
					if(point[j]==i){
						arr[k] = j;
						k++;
					}
				if(i==8){
					if(player[arr[0]][4]>player[arr[1]][4]&&player[arr[0]][4]>player[arr[2]][4])printresult(i,arr[0]);
					else if(player[arr[1]][4]>player[arr[0]][4]&&player[arr[1]][4]>player[arr[2]][4])printresult(i,arr[1]);
					else printresult(i,arr[2]);
				}else if(i==7){
					if(four[arr[0]]>four[arr[1]]&&four[arr[0]]>four[arr[2]])printresult(i,arr[0]);
					else if(four[arr[1]]>four[arr[0]]&&four[arr[1]]>four[arr[2]])printresult(i,arr[1]);
					else printresult(i,arr[2]);
				}else if(i==6){
					if(three[arr[0]]>three[arr[1]]&&three[arr[0]]>three[arr[2]])printresult(i,arr[0]);
					else if(three[arr[1]]>three[arr[0]]&&three[arr[1]]>three[arr[2]])printresult(i,arr[1]);
					else printresult(i,arr[2]);
				}else if(i==5){
					if(player[arr[0]][0]>player[arr[1]][0]&&player[arr[0]][0]>player[arr[2]][0])printresult(i,arr[0]);
					else if(player[arr[1]][0]>player[arr[0]][0]&&player[arr[1]][0]>player[arr[2]][0])printresult(i,arr[1]);
					else printresult(i,arr[2]);
				}else if(i==4){
					if(player[arr[0]][4]>player[arr[1]][4]&&player[arr[0]][4]>player[arr[2]][4])printresult(i,arr[0]);
					else if(player[arr[1]][4]>player[arr[0]][4]&&player[arr[1]][4]>player[arr[2]][4])printresult(i,arr[1]);
					else printresult(i,arr[2]);
				}else if(i==3){
					if(three[arr[0]]>three[arr[1]]&&three[arr[0]]>three[arr[2]])printresult(i,arr[0]);
					else if(three[arr[1]]>three[arr[0]]&&three[arr[1]]>three[arr[2]])printresult(i,arr[1]);
					else printresult(i,arr[2]);
				}else if(i==2){
					if(twopairs[arr[0]][0]>twopairs[arr[1]][0]&&twopairs[arr[0]][0]>twopairs[arr[2]][0])printresult(i,arr[0]);
					else if(twopairs[arr[1]][0]>twopairs[arr[0]][0]&&twopairs[arr[1]][0]>twopairs[arr[2]][0])printresult(i,arr[1]);
					else printresult(i,arr[2]);
				}else if(i==1){
					if(twopairs[arr[0]][0]>twopairs[arr[1]][0]&&twopairs[arr[0]][0]>twopairs[arr[2]][0])printresult(i,arr[0]);
					else if(twopairs[arr[1]][0]>twopairs[arr[0]][0]&&twopairs[arr[1]][0]>twopairs[arr[2]][0])printresult(i,arr[1]);
					else printresult(i,arr[2]);
				}else if(player[arr[0]][0]>player[arr[1]][0]&&player[arr[0]][0]>player[arr[2]][0])printresult(i,arr[0]);
					else if(player[arr[1]][0]>player[arr[0]][0]&&player[arr[1]][0]>player[arr[2]][0])printresult(i,arr[1]);
					else printresult(i,arr[2]);
			}else{
				k=0;
				for(j=0;j<4;j++)
					if(point[j]==i){
						arr[k] = j;
						k++;
					}
				if(i==8){
					if(player[arr[0]][4]>player[arr[1]][4]&&player[arr[0]][4]>player[arr[2]][4]&&player[arr[0]][4]>player[arr[3]][4])printresult(i,arr[0]);
					else if(player[arr[1]][4]>player[arr[0]][4]&&player[arr[1]][4]>player[arr[2]][4]&&player[arr[1]][4]>player[arr[3]][4])printresult(i,arr[1]);
					else if(player[arr[2]][4]>player[arr[0]][4]&&player[arr[2]][4]>player[arr[1]][4]&&player[arr[2]][4]>player[arr[3]][4])printresult(i,arr[2]);
					else printresult(i,arr[3]);
				}else if(i==7){
					if(four[arr[0]]>four[arr[1]]&&four[arr[0]]>four[arr[2]]&&four[arr[0]]>four[arr[3]])printresult(i,arr[0]);
					else if(four[arr[1]]>four[arr[0]]&&four[arr[1]]>four[arr[2]]&&four[arr[1]]>four[arr[3]])printresult(i,arr[1]);
					else if(four[arr[2]]>four[arr[0]]&&four[arr[2]]>four[arr[1]]&&four[arr[2]]>four[arr[3]])printresult(i,arr[2]);
					else printresult(i,arr[3]);
				}else if(i==6){
					if(three[arr[0]]>three[arr[1]]&&three[arr[0]]>three[arr[2]]&&three[arr[0]]>three[arr[3]])printresult(i,arr[0]);
					else if(three[arr[1]]>three[arr[0]]&&three[arr[1]]>three[arr[2]]&&three[arr[1]]>three[arr[3]])printresult(i,arr[1]);
					else if(three[arr[2]]>three[arr[0]]&&three[arr[2]]>three[arr[1]]&&three[arr[2]]>three[arr[3]])printresult(i,arr[2]);
					else printresult(i,arr[3]);
				}else if(i==5){
					if(player[arr[0]][0]>player[arr[1]][0]&&player[arr[0]][0]>player[arr[2]][0]&&player[arr[0]][0]>player[arr[3]][0])printresult(i,arr[0]);
					else if(player[arr[1]][0]>player[arr[0]][0]&&player[arr[1]][0]>player[arr[2]][0]&&player[arr[1]][0]>player[arr[3]][0])printresult(i,arr[1]);
					else if(player[arr[2]][0]>player[arr[0]][0]&&player[arr[2]][0]>player[arr[1]][0]&&player[arr[2]][0]>player[arr[3]][0])printresult(i,arr[2]);
					else printresult(i,arr[3]);
				}else if(i==4){
					if(player[arr[0]][4]>player[arr[1]][4]&&player[arr[0]][4]>player[arr[2]][4]&&player[arr[0]][4]>player[arr[3]][4])printresult(i,arr[0]);
					else if(player[arr[1]][4]>player[arr[0]][4]&&player[arr[1]][4]>player[arr[2]][4]&&player[arr[1]][4]>player[arr[3]][4])printresult(i,arr[1]);
					else if(player[arr[2]][4]>player[arr[0]][4]&&player[arr[2]][4]>player[arr[1]][4]&&player[arr[2]][4]>player[arr[3]][4])printresult(i,arr[2]);
					else printresult(i,arr[3]);
				}else if(i==3){
					if(three[arr[0]]>three[arr[1]]&&three[arr[0]]>three[arr[2]]&&three[arr[0]]>three[arr[3]])printresult(i,arr[0]);
					else if(three[arr[1]]>three[arr[0]]&&three[arr[1]]>three[arr[2]]&&three[arr[1]]>three[arr[3]])printresult(i,arr[1]);
					else if(three[arr[2]]>three[arr[0]]&&three[arr[2]]>three[arr[1]]&&three[arr[2]]>three[arr[3]])printresult(i,arr[2]);
					else printresult(i,arr[3]);
				}else if(i==2){
					if(twopairs[arr[0]][0]>twopairs[arr[1]][0]&&twopairs[arr[0]][0]>twopairs[arr[2]][0]&&twopairs[arr[0]][0]>twopairs[arr[3]][0])printresult(i,arr[0]);
					else if(twopairs[arr[1]][0]>twopairs[arr[0]][0]&&twopairs[arr[1]][0]>twopairs[arr[2]][0]&&twopairs[arr[1]][0]>twopairs[arr[3]][0])printresult(i,arr[1]);
					else if(twopairs[arr[2]][0]>twopairs[arr[0]][0]&&twopairs[arr[2]][0]>twopairs[arr[1]][0]&&twopairs[arr[2]][0]>twopairs[arr[3]][0])printresult(i,arr[2]);
					else printresult(i,arr[3]);
				}else if(i==1){
					if(twopairs[arr[0]][0]>twopairs[arr[1]][0]&&twopairs[arr[0]][0]>twopairs[arr[2]][0]&&twopairs[arr[0]][0]>twopairs[arr[3]][0])printresult(i,arr[0]);
					else if(twopairs[arr[1]][0]>twopairs[arr[0]][0]&&twopairs[arr[1]][0]>twopairs[arr[2]][0]&&twopairs[arr[1]][0]>twopairs[arr[3]][0])printresult(i,arr[1]);
					else if(twopairs[arr[2]][0]>twopairs[arr[0]][0]&&twopairs[arr[2]][0]>twopairs[arr[1]][0]&&twopairs[arr[2]][0]>twopairs[arr[3]][0])printresult(i,arr[2]);
					else printresult(i,arr[3]);
				}else if(player[arr[0]][0]>player[arr[1]][0]&&player[arr[0]][0]>player[arr[2]][0]&&player[arr[0]][0]>player[arr[3]][0])printresult(i,arr[0]);
					else if(player[arr[1]][0]>player[arr[0]][0]&&player[arr[1]][0]>player[arr[2]][0]&&player[arr[1]][0]>player[arr[3]][0])printresult(i,arr[1]);
					else if(player[arr[2]][0]>player[arr[0]][0]&&player[arr[2]][0]>player[arr[1]][0]&&player[arr[2]][0]>player[arr[3]][0])printresult(i,arr[2]);
					else printresult(i,arr[3]);
			}
			return;
		}
	}
}
int main(){
	int card[max]={0};
	int player[4][5]={0};
	shuttle(card,player);
	compare(player);
}
