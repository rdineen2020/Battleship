//Ronan Dineen 120300896@umail.ucc.ie 09/12/2020 - Battleship #include<stdio.h>
#include<time.h>


#define MINBATTLEZONEHEIGHT 6
#define MINBATTLEZONEWIDTH 6
#define MAXBATTLEZONEHEIGHT 20
#define MAXBATTLEZONEWIDTH 20
#define MINFLEETSIZE 1



#define SEA '~' 
#define MISS '#'
#define COMPUTERSHIP 'K'
#define COMPUTERDESTROYED '0'
#define USERSHIP 'X'
#define USERDESTROYED '*' 
#define COMPUTERMISS '='

int zoneWidth;
int zoneHeight;

char battleZone[MAXBATTLEZONEWIDTH][MAXBATTLEZONEHEIGHT] = {0};
char botShotsTracker[MAXBATTLEZONEWIDTH][MAXBATTLEZONEHEIGHT] = {0};


int fleetSize;
int shipsDestroyed = 0;
int playerDestroyed = 0;

void help(){

printf("\nSea = '%c'\n", SEA); 
printf("Miss = '%c'\n", MISS);
printf("Computer Miss = '%c'\n", COMPUTERMISS); 
printf("Computer Ship = '%c'\n", COMPUTERSHIP);
printf("Computer Ship Destroyed = '%c'\n", COMPUTERDESTROYED); 
printf("User Ship = '%c'\n", USERSHIP);
printf("User Ship Destroyed = '%c'\n", USERDESTROYED);
}


int random_n(lower, upper){ int num; srand(time(NULL));
num = rand()%((upper+1)-lower)+lower;


return(num);
}


int getIntInRange(int bot, int top){
//Get an Integer from the input and return it,
//if it is in the range bot to top inclusive


int val;


printf("\n(%d - %d) > : ",bot, top);
scanf("%d", &val);

while(val < bot || val > top){
printf("\nOut of Range, Try again\n> : "); 
scanf("%d", &val);
}

return val;
}


int initBattleZoneWidth(){
//Ask the user to enter the width of the BattleZone
//Check that it is valid
//Set a global variable (zoneWidth) to this valid width



printf("Enter Valid Battle Zone Width"); 
return(getIntInRange(MINBATTLEZONEWIDTH, MAXBATTLEZONEWIDTH));

}


int initBattleZoneHeight(){
//Ask the user to enter the height of the BattleZone
//check that it is valid
//Set a global variable (zoneHeight) to this valid height

printf("\nEnter Valid Battle Zone Height"); 
return(getIntInRange(MINBATTLEZONEHEIGHT, MAXBATTLEZONEHEIGHT));
}


int initFleetSize(int max){ 
int size;
printf("\nEnter Valid Fleet Size");
size = getIntInRange(MINFLEETSIZE, max);
return(size);
}

void setUp(){
//Initialize Battlezone


//Initialize Fleet size


//Initialize BattleZone with "empty sea" 
zoneWidth = initBattleZoneWidth(); 
zoneHeight = initBattleZoneHeight();
fleetSize = initFleetSize((zoneWidth*zoneHeight)/2);
}


void printBattleZone(){
	int i; 
	int j;
	printf("\n\n");
	printf("  "); 
	for(i=0;i<zoneWidth;i++){
	printf("  %d", i);
	}
	for(j=0;j<zoneHeight;j++){ printf("\n%2d", j); 
		for(i=0;i<zoneWidth;i++){
			if(battleZone[i][j]==0){
				printf("  %c", SEA);
			}else if(battleZone[i][j]==1){
				printf("  %c", USERSHIP);
			}else if(battleZone[i][j]==2){
				printf("  %c", USERDESTROYED);
			}else if(battleZone[i][j]==3){
				printf("  %c", COMPUTERSHIP);

			}else if(battleZone[i][j]==4){
				printf("  %c", COMPUTERDESTROYED);
			}else if(battleZone[i][j]==5){
				printf("  %c", MISS);

			}else{



//if(battleZone[i][j] == 6){
				printf("  %c", COMPUTERMISS);

			}
		}
	}
printf("\n");
}


void place(){
int i; 
int x; 
int y;
printf("\n"); 
for(i=0;i<fleetSize;){
printf("Enter ship %d co-ordinates: ", i); 
printf("\nx:");
x = getIntInRange(0, zoneWidth - 1); 
printf("\ny:");
y = getIntInRange(0, zoneHeight - 1);


if(battleZone[x][y]==0){
battleZone[x][y] = 1; 
i++;
}

}
printBattleZone();
}


void placeBots(){ 
int i;
int x; 
int y;
for(i=0;i<fleetSize;){



x = random_n(0, zoneWidth - 1); 
y = random_n(0, zoneHeight - 1);

if(battleZone[x][y]==0){
battleZone[x][y] = 3; 
i++;
}


}
printBattleZone();
}


void shoot(){
int x; 
int y;
int valid = 0;


while(valid == 0){ printf("\nShoot them!");

	printf("\nx:");
	x = getIntInRange(0, zoneWidth - 1); 
	printf("\ny:");
	y = getIntInRange(0, zoneHeight - 1);


	if(battleZone[x][y] == 1 ||battleZone[x][y]==2){ 
	printf("You cannot shoot your own ship\n");


	}else{

	valid = 1; 
	}
}



if(battleZone[x][y] == 3){ 
	printf("Hit!"); 
	battleZone[x][y]  = 4;
	shipsDestroyed  += 1;
	}else{
	battleZone[x][y] = 5;
	printf("Miss!");
	}


}


void botShoot(){
int x; 
int y;
int valid = 0;


while(valid == 0){


x = random_n(0, zoneWidth - 1);

y = random_n(0, zoneHeight - 1);


while(botShotsTracker[x][y] == 1){
x = random_n(0, zoneWidth - 1);
y = random_n(0, zoneHeight - 1);
}
botShotsTracker[x][y] = 1;


if(battleZone[x][y] == 3 || battleZone[x][y] == 4){ 
valid = 0;

}else{

valid = 1;

}
}






if(battleZone[x][y] == 1){
printf("One of your ships has been hit!"); battleZone[x][y] = 2;
playerDestroyed += 1;
}else{
battleZone[x][y] = 6;
}


}


void game(){
while(shipsDestroyed < fleetSize && playerDestroyed < fleetSize){ 
	shoot();
	botShoot(); 
	printBattleZone();
	

	}
}


void winCheck(){
if(shipsDestroyed == fleetSize){ printf("\nYou Win!");
}else{
printf("\nYou Lose! Better luck next time!");
}
}


int main(){
setUp();
help();
printBattleZone();
place(); 
placeBots(); 
game(); 
winCheck();
printf("\nENTER SOMETHING TO QUIT: ");
scanf(" ");
return(0);
}
