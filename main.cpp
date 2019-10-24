#include <stdio.h>
#include <iostream>
#include <string>

//#include <stdlib.h>
using namespace std;

const int height = 15;
const int width = 53;

void currentFrame(char **screen);

void moveUp(char **&screen){
    char* temp;
    temp = screen[0];

    for (int i=0; i<height-1; i++)
        screen[i] = screen[i+1];

    screen[height-1] = temp;
}

void moveDown(char **&screen){
    char* temp;

    temp = screen[height-1];

    for (int i=height-1; i>0; i--)
        screen[i] = screen[i-1];

    screen[0] = temp;
}

void moveRight(char **&screen){
    char temp;
    for (int i=0; i<height; i++){
        temp = screen[i][width-1];
        for (int j=width-1; j>0; j--){
            screen[i][j] = screen[i][j-1];
        }
        screen[i][0] = temp;
    }
}

void moveLeft(char **&screen){
    char temp;
    for (int i=0; i<height; i++){
        temp = screen[i][0];
        for (int j=0; j<width-1; j++){
            screen[i][j] = screen[i][j+1];
        }
        screen[i][width-1] = temp;
    }
}

void screenSaver(char *corners, int &x, int &y, char **&screen){
    if (x>0){
        if(corners[2]+1 <= width-1){ 
            moveRight(screen); 
            corners[2]++;
            corners[0]++;
        }
        else{
            x = -1;
            moveLeft(screen);
            corners[0]--;
            corners[2]--;
        };
    }
    else{
        if(corners[0]-1 >= 0){ 
            moveLeft(screen);
            corners[0]--;
            corners[2]--;
        }
        else{
            x = 1;
            moveRight(screen);
            corners[0]++;
            corners[2]++;
        };
    }

    if (y>0){
        if(corners[1]-1 >= 0){ 
            moveUp(screen); 
            corners[1]--;
            corners[3]--;
        }
        else{
            y = -1;
            moveDown(screen);
            corners[1]++;
            corners[3]++;
        };
    }
    else{
        if(corners[3]+1 <= height-1){ 
            moveDown(screen);
            corners[1]++;
            corners[3]++;
        }
        else{
            y = 1;
            moveUp(screen);
            corners[1]--;
            corners[3]--;
        };
    }
}

void currentFrame(char **screen){
    string str;
    for (int i=0; i<width+2; i++) str.push_back('=');
    str.push_back('\n');
    for (int i=0; i<height; i++){
        str.push_back('|');
        for (int j=0; j<width; j++)
            str.push_back(screen[i][j]);
        str.push_back('|');
        str.push_back('\n');
    }
    for (int i=0; i<width+2; i++) str.push_back('=');
    str.push_back('\n');
    cout <<str;
}

int main(){
    char **screen = new char*[height];
    for (int i=0; i<height; i++){
        screen[i] = new char[width];
        for (int j=0; j<width; j++)
            screen[i][j] = ' ';
    };
    int x = 1, y = -1;
    char *corners = new char[4];
    corners[0] = 0;
    corners[1] = 0;
    corners[2] = 6;
    corners[3] = 1;

    screen[0][0] = 'f';
    screen[0][1] = 'u';
    screen[0][2] = 'c';
    screen[0][3] = 'k';
    screen[0][4] = 'i';
    screen[0][5] = 'n';
    screen[0][6] = 'g';

    screen[1][1] = 'c';
    screen[1][2] = 'l';
    screen[1][3] = 'o';
    screen[1][4] = 'w';
    screen[1][5] = 'n';


system("pause");
for (int i=0; i<100; i++)
 {screenSaver(corners, x, y, screen);
    currentFrame(screen);
    for (unsigned j=0; j<0x02FFFFFF; j++)
        {unsigned dum = 0xEFFFFFFF;
        dum++;}
};system("pause");
return 0;  
}