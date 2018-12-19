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

//Mendeklarasi array dengan ukuran sizeX x sizeY yang akan diisi dengan pixel
char arena[sizeY][sizeX];

//Mengdefine struct character
struct character{
	int type; //Menentukan apakah ini merupakan player 1 atau AI
	int hp; // HP player yang tersisa
	int armor; //Armor player yang tersisa
	int ap; //Jumlah Action (Action Point) yang tersisa
	int fireball; 
	int poison;
	int cm[2]; //Titik referensi character untuk design character
	int shape[sizeChar][2]; // bentuk character relatif terhadap titik cm
	struct magic *magic; //Linked list berisi semua objek magic pada sebuah character
};

//Mendeklarasi struct magic 
struct magic{
	int type; //Menentukan bentuk dari objek magic
	int cm[2]; ////Titik referensi character untuk design magic
	int shape[sizeMagic][2]; // bentuk magic relatif terhadap titik cm
	struct magic *next; //elemen berikutnya pada linked list
};

//mendeklarasi head linked list magic karakter 1 dan karakter 2
struct magic *headOne = NULL;
struct magic *headTwo = NULL;
//mendekalrasi karakter 1 dan karakter 2
struct character one = {1,100,50,5,20,12,{4,sizeY-4},{{0,0},{1,0},{-1,0},{0,-1},{0,1},{0,2},{-1,3},{1,3}}};
struct character two  = {2,12,75,5,20,12,{sizeX-5,sizeY-4},{{0,0},{1,0},{-1,0},{0,-1},{0,1},{0,2},{-1,3},{1,3}}};

//fungsi untuk menahan layar selama x milidetik
void delay(unsigned int milliseconds){
    clock_t start = clock();
    while((clock() - start) * 1000 / CLOCKS_PER_SEC < milliseconds);
}

//fungsi untuk mengreset dan menghapus semua isi arena
void resetArena(){
	int i,j;
	for(i=0;i<sizeX;i++){
		for(j=0;j<sizeY;j++){
			arena[j][i] = ' ';
		}
	}
}

//Fungsi untuk mengisi arena dengan pixel karakter dan objek magic character tersebut
void fillArena(struct character character){
	int i,tempX,tempY;
	//Mengisi arena dengan pixel character
	for(i=0;i<sizeChar;i++){
		tempX = character.cm[0] + character.shape[i][0];
		tempY = character.cm[1] + character.shape[i][1];
		arena[tempY][tempX] = block;
	}
	//Mengisi arena dengan semua objek magic dari objek character yang dimasukkan
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

//Menghapus semua isi pada linked list
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

//Menanmpilkan Informasi(HP,Armor,AP) yang tersisa
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

//Mengerakkan objek karakter dengan mengubah titik relatif/cm input character
struct character move(int moveX,int moveY,struct character character){
	character.cm[0] = character.cm[0] + moveX;
	character.cm[1] = character.cm[1] + moveY;
	return character;
}

//Mengerakkan objek magic dengan mengubah titik relatif/cm input magic
void moveMagic(struct character character){
	struct magic *temp = (struct magic*) malloc(sizeof(struct magic));
	//Menentukan head linked list yang sesuai dengan input character
	if(character.type == 1){
		temp = headOne;	
	}
	else{
		temp = headTwo;
	}
	//Memindahkan posisi CM dari setiap link pada linked list magic
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

//Menambahkan objek magic pada linked list magic
struct character createMagic(struct character character,struct character opponent,int type){
	struct magic *magic = (struct magic*) malloc(sizeof(struct magic));
	//Menentukan head linked list yang sesuai dengan input character
	if(character.type == 1){
		//Menambahkan objek magic pada linked list karakter 1 dengan bentuk firebolt
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
			//Menambahkan objek magic pada linked list karakter 1 dengan bentuk lightning 
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
			//Menambahkan objek magic pada linked list karakter 2 dengan bentuk firebolt
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
			//Menambahkan objek magic pada linked list karakter 2 dengan bentuk lightning 
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

//Mencari jarak antar dua titik (x1,y1) dan (x2,y2)
int getDistance(int x1,int y1,int x2,int y2){
	int ans = sqrt(pow(x1-x2,2)+pow(y1-y2,2));
	return ans;
};

//Fungsi yang mengembalikan 1 jika ada elemen dari kedua character yang bertabrakan (posisi pixel sama)
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

//Fungsi untuk mengreset arena dan mengisi arena dengan semua elemen karakter 1 dan karakter 2
void reset(struct character one, struct character two){
	resetArena();
	fillArena(one);
	fillArena(two);
	printArena(one,two);
	getTrigger(one,two);
}

//Fungsi yang menampilkan pesan ketika HP karakter lawan <= 0
void winscreen(){ 
	printf("\nEnemy HP is 0!");
	printf("\nYou have won the battle!\n");
	printf("See you next time, grand magus!\n");
	exit(0);
}

//Fungsi yang menampilkan pesan ketika HP karakter pemain <= 0
void losescreen(){ 
	printf("Your HP is 0!\n");
	printf("\nYou have lost the battle!\n");
	printf("See you next time, Good Luck!\n");
	exit(0);
}

//Fungsi interface utama untuk pemain
void turn(int x){
	int choice,i; 
	int seed = time(NULL);
	//mengseed rand dengan bilangan random agar diperoleh bilangan random yang berbeda setiap iterasi
	srand(seed);
	//variabel x menunjukkan urutan giliran pemain atau AI
	if(x%2==1){
		//Ulangi iterasi sampai action point pemain <= 0
		while(one.ap!=0){
			//jika HP lawan <= 0
			if(two.hp<=0){
				winscreen(); 
			}
			//Menampilkan pilihan pada user
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
			//Jika user memilih fireball
			if(choice==1){
				//Jika action point untuk melakukan tindakan tersebut tidak cukup
				if((one.ap-3<0)){
					printf("Not enough AP, choose a different action.");
					delay(2000);
					reset(one,two);
				}
				else{
					one.ap-=3; //Mengurangi action point user
					//Mengecek apakah lawan masih memiliki armor
					if(two.armor!=0){		
						//Mengurangi armor jika lawan masih memiliki armor
						if(two.armor>=one.fireball){
							two.armor=two.armor-one.fireball;
						}
						//Jika besar damage > armor, kurangi selisihnya dari HP user
						else{
							int excess=one.fireball-two.armor;
							two.armor=0;
							two.hp-=excess;
						}
					}
					//Jika lawan tidak memiliki armor kurangi damage dari HP user
					else{
						two.hp-=one.fireball;
					}
					one = createMagic(one,two,1);	//Menginisialisasi objek fireball untuk character 1
					for(i=0;i<8;i++){
						Beep(800,120); 	//menghasilkan sound effect ketika objek magic berpindah posisi
						reset(one,two); //Mengreset arena agar objek magic bisa bergerak
						delay(1); 		
						system("cls");	//Membersihkan command screen 
						moveMagic(one);	//Menggerakkan objek magic
					}
					if(one.fireball>20){
						one.fireball=20; //Jika damage fireball != 20 akibat dari efek charge,kembalikan ke nilai awal
						printf("\nFireball damage has returned to it's original value \n");
						delay(2000);
					}
					deleteAll(); //Menghapus semua objek magic pada linked list magic pada karakter 1 dan 2
					reset(one,two); //Mengreset arena
				}
			}
			//Jika user memilih poison
			if(choice==2){
				//Jika action point yang dimiliki tidak mencukupi
				if((one.ap-3<0)){
					printf("Not enough AP, choose a different action.");
					delay(2000);
					reset(one,two);
				}
				//Mengruangi HP lawan 
				else{
					one.ap-=3;
					two.hp-=one.poison;
					reset(one,two);
				}
				//Jika damage poison != 12 akibat dari efek charge,kembalikan ke nilai awal
				if(one.poison>12){
					one.poison=12;
					printf("\nPoison damage has returned to it's original value \n");
					delay(2000);
				}
				reset(one,two);
			}
			//Jika user memilih lightning
			if(choice==3){
				//Jika action point yang dimiliki tidak mencukupi
				if((one.ap-1<0)){
					printf("Not enough AP, choose a different action.");
					delay(2000);
					reset(one,two);
				}
				else{ 
					one.ap-=1;	//Mengurangi action point user
					two.ap-=1;	//mengurangi action point lawan
					one = createMagic(one,two,2);	//Menginisialisasi objek lightning pada linked list
					for(i=0;i<4;i++){
						Beep(600,120); 	//Sound effect ketika objek magic bergerak
						reset(one,two);	//Mengreset arena agar objek magic bisa bergerak
						delay(100);		//menghasilkan delay 100 ms
						system("cls"); //Mengreset display 
						moveMagic(one);	//menggerakkan objek magic
					}
					deleteAll(); 	//Menghapus semua isi pada linked list
				}
				reset(one,two);	//Mengreset arena
			}
			//Jika user memilih charge fireball
			if(choice==4){
				//Jika Action point yang dimiliki tidak mencukupi
				if((one.ap-2<0)){
					printf("Not enough AP, choose a different action.");
					delay(2000);
					reset(one,two);
				}
				else{
					one.ap-=2;	//Mengurangi action point user
					one.fireball+=20;	//Menambah damage fireball user
					reset(one,two);	//Mengreset arena
				}
			}
			//Jika user memilih charge poison
			if(choice==5){
				//Jika Action point yang dimiliki tidak mencukupi
				if((one.ap-2<0)){
					printf("Not enough AP, choose a different action.");
					delay(2000);
					reset(one,two);
				}
				else{
					one.ap-=2;	//Mengurangi action point user
					one.poison+=10;	//Menambah damage fireball user
				}
				reset(one,two);	//Mengreset arena
			}
			//Jika user memilih untuk menambah armor
			if(choice==6){
				//Jika Action point yang dimiliki tidak mencukupi
				if((one.ap-1<0)){
					printf("Not enough AP, choose a different action.");
					delay(2000);
					reset(one,two);
				}
				else{
					one.ap-=1;	//Mengurangi AP user
					one.armor+=30;	//Menambah armor user
				}
				reset(one,two);	//Mengreset arena
			}
			//Jika user mengakhiri giliran mereka
			if(choice==7){
				break; //Keluar dari loop
			}
		}
	}
		x+=1;	//Menambah x agar menjadi giliran lawan
		one.ap+=5;	//Menambah action point user 
		reset(one,two);	//Mengreset arena
	}
	/**
	AI memiliki fungsi yang identik dengan user tetapi tidak dapat memilih tindakan yang dilakukan pada giliran
	berikutnya. Pemilihan tindakan AI menggunakan fungsi rand() yang akan mengenerasikan bilangan acak dari 1-7 
	setiap giliran dan memilih tindakan berdasarkan bilangan acak yang dihasilkan.
	**/
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
