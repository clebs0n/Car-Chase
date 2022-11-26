#include <iostream>
#include <conio.h>
#include <time.h>
#include <windows.h>

using namespace std;

typedef struct{
    int posX;
    int posY;
} obstacles;

COORD cord = {0,0};
int carPosX = 40, carPosY = 28, dir=0; // 1 = direita, 2 = esquerda
char c;
int upper = 60, lower = 15, carX, obstCounter=0, obstWidth=4, obstHeight=4, obstNum=5;
obstacles obst[5];

void gotoxy(int x, int y){
    cord.X = x;
    cord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cord);
}

void drawCanva(){
    for(int i=0; i < 32; i++){
        gotoxy(15, i);
        printf("%c", 178);
    }
    for(int i=0; i < 32; i++){
        gotoxy(65, i);
        printf("%c", 178);
    }
}

void drawCar(){
    gotoxy(carPosX, carPosY);
    printf(" # \n");
    gotoxy(carPosX, carPosY+1);
    printf("###");
    gotoxy(carPosX, carPosY+2);
    printf("###");

}

void checkColision(){
    if(carPosX == 15 || carPosX == 63){
        exit(0);
    }
}

void cleanTraces(){
    int holdX, holdY;
    holdX = cord.X;
    holdY = cord.Y;

    if(dir == 1){
        gotoxy(carPosX-1, carPosY+1);
        printf("%c", 32);
        gotoxy(carPosX-1, carPosY+2);
        printf("%c", 32);
    }else if(dir == 2){
        gotoxy(carPosX+3, carPosY+1);
        printf("%c", 32);
        gotoxy(carPosX+3, carPosY+2);
        printf("%c", 32);
    }
    gotoxy(holdX, holdY);
}

void play(){
    if(_kbhit()){
        c = _getch();

        if(c == 'd'){
            carPosX++; dir =1;
        }else if(c == 'a'){
            carPosX--; dir = 2;
        }
        drawCar();
        cleanTraces();
        checkColision();
    }
}

void obstUpdate(){
    for(int i=0; i < 5; i++){
        gotoxy(obst[i].posX, obst[i].posY-4);
        for(int j=0; j < obstWidth; j++){
            cout <<" ";
        }
        gotoxy(obst[i].posX, obst[i].posY++);
        for(int j=0; j < obstWidth; j++){
            cout <<"#";
        }
    }
    //Sleep(50);
}

void obstInitialSetup(){
    int helper = -60;
    for(int i=0; i < 5; i++){
        carX = (rand() % (upper - lower + 1)) + lower;
        obst[i].posX = carX; obst[i].posY = helper;
        helper+=10;
    }
}

void generateObstacles(int index){

    carX = (rand() % (upper - lower + 1)) + lower;
    obst[index].posX = carX; obst[index].posY = 0;
}

void obstInherit(){
    for(int i=0; i < 4; i++){
        obst[i].posX = obst[i+1].posX;
        obst[i].posY = obst[i+1].posY;
    }
    generateObstacles(4);
}


int main()
{
    srand((unsigned)time(NULL));
    drawCanva();
    drawCar();
    obstInitialSetup();

    while(1){
        obstUpdate();
        if(obst[0].posY > 25 && obst[4].posY > 5){
            obstInherit();
        }
        play();
    }
    return 0;
}
