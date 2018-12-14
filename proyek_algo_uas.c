#include <stdio.h>
#include <time.h> 
#include <dos.h>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#include <math.h>
#define sizeX 60
#define sizeY 10
#define block 219
#define shapeMax 30
#define sizeChar 20
#define sizeMagic 10

char arena[sizeY][sizeX];

struct character{
	int type;
	int hp;
	int armor;
	int ap;
	int fireball;
	int poison;
	int cm[2];
	int shape[sizeChar][2];
	struct magic *magic;
};

struct magic{
	int type;
	int cm[2];
	int shape[sizeMagic][2];
	struct magic *next;
};

struct magic *headOne = NULL;
struct magic *headTwo = NULL;
struct character one = {1,100,50,5,20,12,{4,sizeY-4},{{0,0},{1,0},{-1,0},{0,-1},{0,1},{0,2},{-1,3},{1,3}}};
struct character two  = {2,12,75,5,20,12,{sizeX-5,sizeY-4},{{0,0},{1,0},{-1,0},{0,-1},{0,1},{0,2},{-1,3},{1,3}}};

void delay(unsigned int milliseconds){
    clock_t start = clock();
    while((clock() - start) * 1000 / CLOCKS_PER_SEC < milliseconds);
}

void resetArena(){
	int i,j;
	for(i=0;i<sizeX;i++){
		for(j=0;j<sizeY;j++){
			arena[j][i] = ' ';
		}
	}
}

void fillArena(struct character character){
	int i,tempX,tempY;
	for(i=0;i<sizeChar;i++){
		tempX = character.cm[0] + character.shape[i][0];
		tempY = character.cm[1] + character.shape[i][1];
		arena[tempY][tempX] = block;
	}
	struct magic *temp = (struct magic*) malloc(sizeof(struct magic));
	if(character.type == 1){
		temp = headOne;	
	}
	else{
		temp = headTwo;
	}
	while(temp != NULL){
		for(i=0;i<5;i++){
			tempX = temp->cm[0] + temp->shape[i][0];
			tempY = temp->cm[1] + temp->shape[i][1];
			arena[tempY][tempX] = block;
		}
		temp = temp->next;
	}
	printf("\n");
}

void deleteAll(){
	struct magic *current;
	struct magic *next;
	current = headOne;
	while(current != NULL){
		next = current->next; 
       	free(current); 
       	current = next;
	}
	headOne = current;
	current = headTwo;
	while(current != NULL){
		next = current->next; 
       	free(current); 
       	current = next;
	}
	headTwo = current;
}

void printArena(struct character one,struct character two){
	int i,j;
	for(i=0;i<sizeY;i++){
		for(j=0;j<sizeX;j++){
			printf("%c",arena[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	printf("Player 1  					Player 2\n");
	printf("HP : %d 					HP : %d \n",one.hp,two.hp);
	printf("Armor : %d 					Armor : %d \n",one.armor,two.armor);
	printf("Action Point : %d 				Action Point : %d \n",one.ap,two.ap);
	return;
}

struct character move(int moveX,int moveY,struct character character){
	character.cm[0] = character.cm[0] + moveX;
	character.cm[1] = character.cm[1] + moveY;
	return character;
}

void moveMagic(struct character character){
	struct magic *temp = (struct magic*) malloc(sizeof(struct magic));
	if(character.type == 1){
		temp = headOne;	
	}
	else{
		temp = headTwo;
	}
	while(temp != NULL){
		if(temp->type == 1){
			if(character.type == 1){
				temp->cm[0] = temp->cm[0] + 6;
				temp->cm[1] = temp->cm[1] + 0;
				temp = temp->next;
			}
			else{
				temp->cm[0] = temp->cm[0] - 6;
				temp->cm[1] = temp->cm[1] + 0;
				temp = temp->next;	
			}
		}
		else if(temp->type == 2){
			temp->cm[0] = temp->cm[0] + 0;
			temp->cm[1] = temp->cm[1] + 4;
			temp = temp->next;
		}
	}
	return;
}

struct character createMagic(struct character character,struct character opponent,int type){
	struct magic *magic = (struct magic*) malloc(sizeof(struct magic));
	if(character.type == 1){
		if(type == 1){
			magic->cm[0] = character.cm[0] + 5;
			magic->cm[1] = character.cm[1];
			magic->shape[0][0] = 0;
			magic->shape[0][1] = 0;
			magic->shape[1][0] = -1;
			magic->shape[1][1] = 0;
			magic->shape[2][0] = 1;
			magic->shape[2][1] = 0;
			magic->shape[3][0] = 0;
			magic->shape[3][1] = 1;
			magic->shape[4][0] = 0;
			magic->shape[4][1] = -1;
			magic->next = headOne;
			magic->type = 1;
			headOne = magic;
			character.magic = headOne;
		}
		else if(type == 2){
			magic->cm[0] = opponent.cm[0];
			magic->cm[1] = opponent.cm[1] - 12;
			magic->shape[0][0] = 0;
			magic->shape[0][1] = 0;
			magic->shape[1][0] = -1;
			magic->shape[1][1] = -1;
			magic->shape[2][0] = 0;
			magic->shape[2][1] = -2;
			magic->shape[3][0] = -1;
			magic->shape[3][1] = -1;
			magic->shape[4][0] = 0;
			magic->shape[4][1] = -2;
			magic->type = 2;
			magic->next = headOne;
			headOne = magic;
			character.magic = headOne;	
		}
	}
	else{
		if(type == 1){
			magic->cm[0] = character.cm[0] + 5;
			magic->cm[1] = character.cm[1];
			magic->shape[0][0] = 0;
			magic->shape[0][1] = 0;
			magic->shape[1][0] = -1;
			magic->shape[1][1] = 0;
			magic->shape[2][0] = 1;
			magic->shape[2][1] = 0;
			magic->shape[3][0] = 0;
			magic->shape[3][1] = 1;
			magic->shape[4][0] = 0;
			magic->shape[4][1] = -1;
			magic->next = headTwo;
			magic->type = 1;
			headTwo = magic;
			character.magic = headTwo;
		}
		else if(type == 2){
			magic->cm[0] = opponent.cm[0];
			magic->cm[1] = opponent.cm[1] - 12;
			magic->shape[0][0] = 0;
			magic->shape[0][1] = 0;
			magic->shape[1][0] = -1;
			magic->shape[1][1] = -1;
			magic->shape[2][0] = 0;
			magic->shape[2][1] = -2;
			magic->shape[3][0] = -1;
			magic->shape[3][1] = -1;
			magic->shape[4][0] = 0;
			magic->shape[4][1] = -2;
			magic->type = 2;
			magic->next = headTwo;
			headTwo = magic;
			character.magic = headTwo;	
		}
	}
	return character;
}

int getDistance(int x1,int y1,int x2,int y2){
	int ans = sqrt(pow(x1-x2,2)+pow(y1-y2,2));
	return ans;
};

int getTrigger(struct character one,struct character two){
	struct magic *temp1 = one.magic;
	struct magic *temp2 = two.magic;
	while(temp1 != NULL){
		while(temp2 != NULL && temp1 != NULL){
			if(getDistance(temp1->cm[0],temp1->cm[1],two.cm[0],two.cm[1]) <= 2){
				printf("");
				return 1;
			}
			temp2 = temp2->next;
		}
		temp2 = headTwo;
		temp1 = temp1->next;
	}
	return 0;
}

void reset(struct character one, struct character two){
	resetArena();
	fillArena(one);
	fillArena(two);
	printArena(one,two);
	getTrigger(one,two);
}

void winscreen(){ 
	printf("\nEnemy HP is 0!");
	printf("\nYou have won the battle!\n");
	printf("See you next time, grand magus!\n");
	exit(0);
}

void losescreen(){ 
	printf("Your HP is 0!\n");
	printf("\nYou have lost the battle!\n");
	printf("See you next time, Good Luck!\n");
	exit(0);
}

void turn(int x){
	int choice,i;
	int seed = time(NULL);
	srand(seed);
	if(x%2==1){
		while(one.ap!=0){
			if(two.hp<=0){
				winscreen(); //new
			}
			else{
			printf("\n1.Fireball, does %d damage blocked by armour, 3 AP",one.fireball);
			printf("\n2.Poison, does %d damage that pierces armour, 3 AP",one.poison);
			printf("\n3.Lightning, removes 1 AP from enemy, 1 AP");
			printf("\n4.Charge Fireball, adds +20 fireball damage,2 AP");
			printf("\n5.Charge Poison, adds +10 poison damage,2 AP");
			printf("\n6.Defend, adds 30 armour, 1 AP");
			printf("\n7.End Turn");
			printf("\n\nPick an action:");
			scanf("%d",&choice);
			
			if(choice==1){
				if((one.ap-3<0)){
					printf("Not enough AP, choose a different action.");
					delay(2000);
					reset(one,two);
				}
				else{
					one.ap-=3;
					if(two.armor!=0){
						if(two.armor>=one.fireball){
							two.armor=two.armor-one.fireball;
						}
						else{
							int excess=one.fireball-two.armor;
							two.armor=0;
							two.hp-=excess;
						}
					}
					else{
						two.hp-=one.fireball;
					}
					one = createMagic(one,two,1);
					for(i=0;i<8;i++){
						Beep(800,120);
						reset(one,two);
						delay(1);
						system("cls");
						moveMagic(one);
					}
					if(one.fireball>20){
						one.fireball=20;
						printf("\nFireball damage has returned to it's original value \n");
						delay(2000);
					}
					deleteAll();
					reset(one,two);
				}
			}
			
			if(choice==2){
				if((one.ap-3<0)){
					printf("Not enough AP, choose a different action.");
					delay(2000);
					reset(one,two);
				}
				else{
					one.ap-=3;
					two.hp-=one.poison;
					reset(one,two);
				}
				if(one.poison>12){
					one.poison=12;
					printf("\nPoison damage has returned to it's original value \n");
					delay(2000);
				}
				reset(one,two);
			}
			
			if(choice==3){
				if((one.ap-1<0)){
					printf("Not enough AP, choose a different action.");
					delay(2000);
					reset(one,two);
				}
				else{
					one.ap-=1;
					two.ap-=1;
					one = createMagic(one,two,2);
					for(i=0;i<4;i++){
						Beep(600,120);
						reset(one,two);
						delay(100);
						system("cls");
						moveMagic(one);
					}
					deleteAll();
				}
				reset(one,two);
			}
			
			if(choice==4){
				if((one.ap-2<0)){
					printf("Not enough AP, choose a different action.");
					delay(2000);
					reset(one,two);
				}
				else{
					one.ap-=2;
					one.fireball+=20;
					reset(one,two);
				}
			}

			if(choice==5){
				if((one.ap-2<0)){
					printf("Not enough AP, choose a different action.");
					delay(2000);
					reset(one,two);
				}
				else{
					one.ap-=2;
					one.poison+=10;
				}
				reset(one,two);
			}
			
			if(choice==6){
				if((one.ap-1<0)){
					printf("Not enough AP, choose a different action.");
					delay(2000);
					reset(one,two);
				}
				else{
					one.ap-=1;
					one.armor+=30;
				}
				reset(one,two);
			}
			
			if(choice==7){
				break;
			}
		}
	}
		x+=1;
		one.ap+=5;
		reset(one,two);
	}
	else
	{
		printf("AI's turn.'");
		int choice2;
		int state = 1;
		while(two.ap > 0 && state == 1){
			if(one.hp<=0){
				losescreen(); //new
			}
			else{
				int choice2;
    			choice2 = rand()%6+1;
			if(choice2==1){
				if((two.ap-3<0)){
					printf("AI doesn't have enough AP.\n");
					delay(400);
					//reset(one,two);
				}
				else{
					two.ap-=3;
					printf("\nAI used Fireball!");
					delay(2000);
					if(one.armor!=0){
						if(one.armor>=two.fireball){
							one.armor=one.armor-two.fireball;
						}
						else{
							int excess2=two.fireball-one.armor;
							one.armor=0;
							one.hp-=excess2;
						}
					}
					else{
						one.hp-=two.fireball;
					}
					two = createMagic(two,one,1);
					for(i=0;i<8;i++){
						Beep(800,120);
						reset(one,two);
						delay(1);
						system("cls");
						moveMagic(two);
					}
					if(two.fireball>25){
						two.fireball=25;
						printf("\nFireball damage has returned to it's original value \n");
						delay(2000);
					}
					deleteAll();
					reset(one,two);
				}
			}
			else if(choice2==2){
				if((two.ap-3<0)){
					printf("AI doesn't have enough AP.");
					delay(400);
					//reset(one,two);
				}
				else{
					printf("\nAI used Poison!");
					delay(2000);
					two.ap-=3;
					one.hp-=two.poison;
					reset(one,two);
				}
				if(two.poison>12){
					two.poison=12;
					printf("\nPoison damage has returned to it's original value \n");
					delay(2000);
				}
				reset(one,two);
			}
			else if(choice2==3){
				if((two.ap-1<0)){
					printf("AI doesn't have enough AP.\n");
					delay(400);
					//reset(one,two);
				}
				else{
					one.ap-=1;
					two.ap-=1;
					printf("\nAI used Lightning!");
					delay(500);
					two = createMagic(two,one,2);
					for(i=0;i<4;i++){
						Beep(600,120);
						reset(one,two);
						delay(100);
						system("cls");
						moveMagic(two);
					}
					deleteAll();
				}
				reset(one,two);
			}
			else if(choice2==4){
				if((two.ap-2<0)){
					printf("AI doesn't have enough AP.\n");
					delay(400);
					//reset(one,two);
				}
				else{
					two.ap-=2;
					two.fireball+=20;
					printf("\nAI used Charge Fireball!");
					delay(2000);
					reset(one,two);
				}
			}
			else if(choice2==5){
				if((two.ap-2<0)){
					printf("AI doesn't have enough AP.\n");
					delay(400);
					//reset(one,two);
				}
				else{
					printf("\nAI used Charge Poison!");
					two.ap-=2;
					two.poison+=10;
					delay(2000);
				}
				reset(one,two);
			}
			else if(choice2==6){
				if((one.ap-1<0)){
					printf("AI doesn't have enough AP.\n");
					delay(400);
					//reset(one,two);
				}
				else{
					two.ap-=1;
					two.armor+=30;
					printf("\nAI used Defend!");
					delay(2000);
				}
				reset(one,two);
			}
			else if(choice2==7){
				printf("\nAI ended their turn!");
				state = 0;
				delay(400);
				break;
			}
		}
	}
		x+=1;
		two.ap+=5;
		reset(one,two);
	}
}
void intro(){
	printf("\n|-------------------------------------------|");
	printf("\n|              WANDS AND SANDALS            |");
	printf("\n|             Definitive Edition            |");
	printf("\n|           Game of the Year 2018           |");
	printf("\n|-------------------------------------------|");
}
int main(){
	intro();
	one.magic = headOne;
	two.magic = headTwo;
	int temp=1;
	
	//one = createMagic(two,one,1);
	//two = createMagic(two);
	int i;
	while(temp<10){
		//reset(one,two);
		resetArena();
		fillArena(one);
		fillArena(two);
		printArena(one,two);
		getTrigger(one,two);
		delay(200);
		turn(temp);
		temp++;
		system("cls");
	}
	return 0;
}
