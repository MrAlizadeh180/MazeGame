#include <iostream>
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <cmath>
#include <windows.h> // for windows users
#include <unistd.h> // for linux users
#include <time.h>
#include <conio.h>
#include <string> 
using namespace std;

// color definition
#define Green 0x0A
#define Red 0x0C
#define Aqua 0x0B
#define Yellow 0x0E
#define White 0x0F
#define Purple 0x0D

// Functions
unsigned char colorChoice();
char getKeyPress();
void printLevel(int);
void setMe(int);
bool isExit(int, int, int);
bool isWall(int, int, int);
int getPos(int, int&);
void update(int, int, int);
void makeSpace(int, int, int);
void ShowDirection(int x,int y, string& direction, int dir_size,int& counter);
void setcolor( unsigned char color )// this function is useful to change the color of console
{
  SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), color );
}

const char space = ' ';
const char me = '@';
unsigned char color_choice;


char lvl1[51][51] = { 
                 
					{'+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+',' ','+','+','+','+','+','+','+'},
                    {'+',' ','+',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','+',' ',' ',' ',' ',' ','+',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','+',' ',' ',' ',' ',' ',' ',' ',' ',' ','+','@',' ',' ',' ',' ',' ',' ','+'},
                    {'+',' ','+',' ','+','+','+','+','+',' ','+',' ','+',' ','+',' ','+',' ','+',' ','+',' ','+',' ','+','+','+','+','+',' ','+',' ','+',' ','+','+','+','+','+','+','+',' ','+',' ','+','+','+','+','+',' ','+'},
                    {'+',' ',' ',' ','+',' ',' ',' ','+',' ','+',' ','+',' ',' ',' ','+',' ','+',' ',' ',' ','+',' ',' ',' ','+',' ',' ',' ','+',' ','+',' ','+',' ',' ',' ',' ',' ','+',' ',' ',' ','+',' ',' ',' ',' ',' ','+'},
                    {'+','+','+','+','+',' ','+','+','+',' ','+',' ','+','+','+','+','+',' ','+','+','+','+','+',' ','+',' ','+',' ','+','+','+','+','+',' ','+',' ','+','+','+',' ','+',' ','+','+','+',' ','+','+','+','+','+'},
                    {'+',' ',' ',' ','+',' ',' ',' ',' ',' ','+',' ','+',' ',' ',' ','+',' ','+',' ',' ',' ',' ',' ','+',' ','+',' ',' ',' ','+',' ',' ',' ',' ',' ','+',' ',' ',' ','+',' ',' ',' ','+',' ',' ',' ',' ',' ','+'},
                    {'+',' ','+','+','+','+','+','+','+','+','+',' ','+',' ','+',' ','+',' ','+',' ','+','+','+','+','+',' ','+','+','+',' ','+',' ','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+',' ','+'},
                    {'+',' ',' ',' ',' ',' ','+',' ',' ',' ','+',' ','+',' ','+',' ','+',' ','+',' ','+',' ',' ',' ','+',' ',' ',' ','+',' ',' ',' ','+',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','+',' ',' ',' ',' ',' ','+'},
                    {'+','+','+','+','+',' ','+',' ','+',' ','+',' ','+',' ','+',' ','+',' ','+',' ','+',' ','+',' ','+','+','+','+','+','+','+','+','+',' ','+','+','+',' ','+','+','+','+','+',' ','+',' ','+','+','+','+','+'},
                    {'+',' ','+',' ',' ',' ',' ',' ','+',' ',' ',' ','+',' ','+',' ',' ',' ','+',' ','+',' ','+',' ','+',' ',' ',' ',' ',' ','+',' ',' ',' ','+',' ',' ',' ','+',' ',' ',' ','+',' ',' ',' ','+',' ',' ',' ','+'},
                    {'+',' ','+',' ','+','+','+','+','+','+','+',' ','+',' ','+','+','+',' ','+',' ','+',' ','+',' ','+',' ','+','+','+','+','+',' ','+',' ','+','+','+','+','+',' ','+','+','+','+','+','+','+','+','+',' ','+'},
                    {'+',' ',' ',' ','+',' ',' ',' ',' ',' ','+',' ','+',' ','+',' ',' ',' ','+',' ',' ',' ','+',' ','+',' ',' ',' ',' ',' ',' ',' ','+',' ','+',' ',' ',' ','+',' ',' ',' ',' ',' ','+',' ',' ',' ','+',' ','+'},
                    {'+','+','+','+','+',' ','+','+','+',' ','+',' ','+',' ','+',' ','+','+','+',' ','+',' ','+',' ','+','+','+','+','+','+','+','+','+','+','+',' ','+',' ','+',' ','+',' ','+',' ','+','+','+',' ','+',' ','+'},
                    {'+',' ',' ',' ',' ',' ','+',' ',' ',' ','+',' ','+',' ','+',' ','+',' ',' ',' ','+',' ','+',' ',' ',' ','+',' ',' ',' ','+',' ',' ',' ',' ',' ','+',' ','+',' ','+',' ','+',' ',' ',' ',' ',' ','+',' ','+'},
                    {'+',' ','+','+','+','+','+',' ','+','+','+',' ','+',' ','+',' ','+',' ','+','+','+',' ','+',' ','+',' ','+',' ','+',' ','+',' ','+','+','+','+','+',' ','+',' ','+',' ','+','+','+','+','+','+','+',' ','+'},
                    {'+',' ','+',' ',' ',' ',' ',' ',' ',' ',' ',' ','+',' ','+',' ','+',' ',' ',' ','+',' ','+',' ','+',' ','+',' ','+',' ','+',' ',' ',' ','+',' ',' ',' ','+',' ','+',' ',' ',' ',' ',' ',' ',' ',' ',' ','+'},
                    {'+',' ','+','+','+','+','+','+','+','+','+','+','+',' ','+',' ','+','+','+',' ','+','+','+',' ','+',' ','+',' ','+',' ','+','+','+',' ','+',' ','+','+','+',' ','+','+','+','+','+','+','+',' ','+','+','+'},
                    {'+',' ',' ',' ',' ',' ',' ',' ','+',' ',' ',' ','+',' ','+',' ',' ',' ','+',' ','+',' ',' ',' ','+',' ',' ',' ','+',' ',' ',' ',' ',' ','+',' ',' ',' ','+',' ','+',' ',' ',' ',' ',' ','+',' ',' ',' ','+'},
                    {'+','+','+','+','+','+','+','+','+',' ','+',' ','+',' ','+','+','+',' ','+','+','+',' ','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+',' ','+','+','+',' ','+',' ','+','+','+',' ','+'},
                    {'+',' ','+',' ',' ',' ',' ',' ',' ',' ','+',' ','+',' ',' ',' ','+',' ',' ',' ','+',' ',' ',' ',' ',' ',' ',' ',' ',' ','+',' ',' ',' ',' ',' ','+',' ',' ',' ','+',' ',' ',' ','+',' ',' ',' ','+',' ','+'},
                    {'+',' ','+',' ','+','+','+','+','+','+','+','+','+',' ','+','+','+','+','+',' ','+','+','+','+','+','+','+',' ','+','+','+',' ','+','+','+',' ','+',' ','+','+','+',' ','+','+','+','+','+',' ','+',' ','+'},
                    {'+',' ',' ',' ',' ',' ','+',' ',' ',' ',' ',' ',' ',' ','+',' ',' ',' ',' ',' ','+',' ',' ',' ',' ',' ','+',' ',' ',' ',' ',' ','+',' ','+',' ','+',' ',' ',' ',' ',' ','+',' ',' ',' ',' ',' ','+',' ','+'},
                    {'+','+','+','+','+',' ','+','+','+','+','+',' ','+','+','+',' ','+','+','+','+','+','+','+','+','+',' ','+','+','+','+','+',' ','+',' ','+',' ','+','+','+','+','+','+','+',' ','+','+','+','+','+',' ','+'},
                    {'+',' ',' ',' ','+',' ',' ',' ','+',' ',' ',' ','+',' ',' ',' ','+',' ',' ',' ',' ',' ',' ',' ',' ',' ','+',' ',' ',' ','+',' ',' ',' ','+',' ',' ',' ',' ',' ',' ',' ',' ',' ','+',' ','+',' ',' ',' ','+'},
                    {'+',' ','+','+','+','+','+',' ','+','+','+',' ','+','+','+','+','+',' ','+',' ','+','+','+','+','+','+','+',' ','+',' ','+','+','+','+','+',' ','+','+','+','+','+','+','+',' ','+',' ','+',' ','+',' ','+'},
                    {'+',' ',' ',' ',' ',' ',' ',' ',' ',' ','+',' ',' ',' ',' ',' ',' ',' ','+',' ',' ',' ',' ',' ',' ',' ','+',' ','+',' ','+',' ',' ',' ','+',' ',' ',' ',' ',' ',' ',' ','+',' ','+',' ',' ',' ','+',' ','+'},
                    {'+','+','+','+','+','+','+','+','+',' ','+','+','+','+','+',' ','+','+','+',' ','+',' ','+','+','+',' ','+','+','+',' ','+',' ','+',' ','+','+','+',' ','+','+','+',' ','+',' ','+','+','+','+','+','+','+'},
                    {'+',' ',' ',' ',' ',' ','+',' ',' ',' ',' ',' ',' ',' ','+',' ','+',' ',' ',' ','+',' ','+',' ','+',' ',' ',' ',' ',' ',' ',' ','+',' ',' ',' ','+',' ','+',' ',' ',' ','+',' ',' ',' ','+',' ',' ',' ','+'},
                    {'+',' ','+','+','+',' ','+','+','+','+','+','+','+',' ','+','+','+',' ','+',' ','+',' ','+',' ','+','+','+','+','+','+','+','+','+','+','+',' ','+',' ','+',' ','+','+','+','+','+',' ','+',' ','+',' ','+'},
                    {'+',' ',' ',' ','+',' ',' ',' ','+',' ',' ',' ',' ',' ',' ',' ',' ',' ','+',' ','+',' ',' ',' ','+',' ',' ',' ','+',' ',' ',' ',' ',' ',' ',' ','+',' ','+',' ',' ',' ','+',' ',' ',' ','+',' ','+',' ','+'},
                    {'+','+','+','+','+','+','+',' ','+',' ','+','+','+','+','+','+','+',' ','+',' ','+','+','+','+','+',' ','+',' ','+','+','+','+','+','+','+','+','+','+','+','+','+',' ','+',' ','+','+','+','+','+',' ','+'},
                    {'+',' ','+',' ',' ',' ',' ',' ','+',' ','+',' ',' ',' ','+',' ',' ',' ','+',' ',' ',' ',' ',' ','+',' ','+',' ',' ',' ',' ',' ','+',' ',' ',' ',' ',' ',' ',' ',' ',' ','+',' ',' ',' ','+',' ',' ',' ','+'},
                    {'+',' ','+',' ','+','+','+','+','+',' ','+',' ','+','+','+',' ','+','+','+','+','+','+','+',' ','+','+','+','+','+','+','+',' ','+',' ','+','+','+','+','+','+','+','+','+','+','+',' ','+',' ','+','+','+'},
                    {'+',' ','+',' ','+',' ',' ',' ','+',' ','+',' ',' ',' ',' ',' ','+',' ',' ',' ',' ',' ',' ',' ','+',' ',' ',' ',' ',' ',' ',' ','+',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','+',' ',' ',' ',' ',' ','+'},
                    {'+',' ','+',' ','+','+','+',' ','+',' ','+','+','+','+','+','+','+',' ','+',' ','+','+','+',' ','+',' ','+','+','+','+','+','+','+',' ','+',' ','+','+','+','+','+',' ','+','+','+','+','+','+','+','+','+'},
                    {'+',' ','+',' ',' ',' ',' ',' ','+',' ',' ',' ','+',' ',' ',' ','+',' ','+',' ','+',' ',' ',' ','+',' ',' ',' ','+',' ',' ',' ',' ',' ','+',' ',' ',' ',' ',' ','+',' ',' ',' ','+',' ',' ',' ',' ',' ','+'},
                    {'+',' ','+','+','+','+','+',' ','+','+','+','+','+',' ','+',' ','+',' ','+','+','+',' ','+','+','+','+','+',' ','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+',' ','+',' ','+',' ','+',' ','+'},
                    {'+',' ',' ',' ','+',' ','+',' ','+',' ',' ',' ',' ',' ','+',' ','+',' ',' ',' ','+',' ',' ',' ',' ',' ','+',' ',' ',' ','+',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','+',' ','+',' ','+',' ','+',' ','+'},
                    {'+','+','+',' ','+',' ','+',' ','+',' ','+','+','+','+','+',' ','+',' ','+',' ','+','+','+','+','+',' ','+','+','+',' ','+',' ','+','+','+','+','+','+','+','+','+',' ','+',' ','+',' ','+',' ','+','+','+'},
                    {'+',' ','+',' ','+',' ','+',' ',' ',' ','+',' ',' ',' ',' ',' ','+',' ','+',' ',' ',' ',' ',' ','+',' ',' ',' ','+',' ','+',' ',' ',' ',' ',' ',' ',' ','+',' ',' ',' ','+',' ',' ',' ','+',' ',' ',' ','+'},
                    {'+',' ','+',' ','+',' ','+','+','+','+','+',' ','+','+','+','+','+',' ','+','+','+',' ','+','+','+','+','+','+','+',' ','+','+','+','+','+','+','+',' ','+',' ','+','+','+','+','+','+','+','+','+',' ','+'},
                    {'+',' ',' ',' ','+',' ',' ',' ',' ',' ',' ',' ',' ',' ','+',' ','+',' ',' ',' ','+',' ',' ',' ',' ',' ',' ',' ','+',' ',' ',' ',' ',' ',' ',' ',' ',' ','+',' ',' ',' ',' ',' ',' ',' ',' ',' ','+',' ','+'},
                    {'+',' ','+','+','+','+','+','+','+','+','+','+','+',' ','+',' ','+','+','+','+','+',' ','+','+','+',' ','+',' ','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+',' ','+',' ','+'},
                    {'+',' ',' ',' ',' ',' ',' ',' ',' ',' ','+',' ',' ',' ',' ',' ','+',' ',' ',' ','+',' ',' ',' ','+',' ','+',' ','+',' ',' ',' ','+',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','+',' ','+',' ',' ',' ','+'},
                    {'+','+','+','+','+','+','+','+','+',' ','+','+','+','+','+',' ','+',' ','+',' ','+','+','+',' ','+','+','+',' ','+',' ','+',' ','+',' ','+',' ','+','+','+','+','+','+','+',' ','+',' ','+','+','+','+','+'},
                    {'+',' ',' ',' ',' ',' ',' ',' ','+',' ',' ',' ',' ',' ',' ',' ',' ',' ','+',' ','+',' ',' ',' ','+',' ',' ',' ','+',' ','+',' ',' ',' ','+',' ',' ',' ',' ',' ',' ',' ','+',' ','+',' ',' ',' ',' ',' ','+'},
                    {'+',' ','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+',' ','+','+','+','+','+',' ','+','+','+',' ','+','+','+','+','+','+','+','+','+','+','+',' ','+','+','+',' ','+','+','+',' ','+'}, 
                    {'+',' ','+',' ',' ',' ','+',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','+',' ',' ',' ','+',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','+',' ',' ',' ','+',' ',' ',' ',' ',' ',' ',' ','+',' ','+'}, 
                    {'+',' ','+',' ','+',' ','+',' ','+',' ','+','+','+','+','+','+','+',' ','+','+','+',' ','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+',' ','+',' ','+','+','+','+','+','+','+','+','+',' ','+'}, 
                    {'+',' ',' ',' ','+',' ',' ',' ','+',' ',' ',' ',' ',' ',' ',' ','+',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','+',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','+'},
                    {'+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+',' ','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+'}


                 
};

int main(void)
{
    int lvl;
    lvl=1;
    
    string direction;
    int dir_size = 5;
    int dir_counter = 0;
  
    system("CLS");
    setMe(lvl);
    printLevel(lvl);
 
    int x, y;
  
    while (true){

        char move = getKeyPress();

        switch (move){
        case 'u':
            x = getPos(lvl, y);
            if (!isWall(x - 1, y, lvl) && !isWall(x - 2, y, lvl)){
                if (isExit(x - 2, y, lvl)){
                    system("CLS");
                    cout << "You Win!" << endl;
                    Sleep(2000);
                }
                system("CLS");
                makeSpace(lvl, x, y);
                update(lvl, x - 2, y);
                ShowDirection(x-2,y,direction,dir_size,dir_counter);
            }
            else
                ShowDirection(x,y,direction,dir_size,dir_counter);//?
            break;
        case 'd':
            x = getPos(lvl, y);
            if (!isWall(x + 1, y, lvl) && !isWall(x + 2, y, lvl)){
                if (isExit(x + 2, y, lvl)){
                    system("CLS");
                    cout << "You Win!" << endl;
                    Sleep(2000);

                }
                system("CLS");
                makeSpace(lvl, x, y);
                update(lvl, x + 2, y);
                ShowDirection(x+2,y,direction,dir_size,dir_counter);
            }
            else
                ShowDirection(x,y,direction,dir_size,dir_counter);
            
            break;
        case 'l':
            x = getPos(lvl, y);
            if (!isWall(x, y - 1, lvl) && !isWall(x, y - 2, lvl)) {
                if (isExit(x, y - 2, lvl)){
                    system("CLS");
                    cout << "You Win!" << endl;
                    Sleep(2000);
                }
                system("CLS");
                makeSpace(lvl, x, y);
                update(lvl, x, y - 2);
                ShowDirection(x,y-2,direction,dir_size,dir_counter);
            }
            else
                ShowDirection(x,y,direction,dir_size,dir_counter);
            
            break;
        case 'r':
            x = getPos(lvl, y);
            if (!isWall(x, y + 1, lvl) && !isWall(x, y + 2, lvl)){
                if (isExit(x, y + 2, lvl)){
                    system("CLS");
                    cout << "You Win!" << endl;
                    Sleep(2000);
                }
                system("CLS");
                makeSpace(lvl, x, y);
                update(lvl, x, y + 2);
                ShowDirection(x,y+2,direction,dir_size,dir_counter);
            }
            else
                ShowDirection(x,y,direction,dir_size,dir_counter);            
            break;
        default:
            break;
        }
    
    }

    return 0;
}

void ShowDirection(int x,int y, string& direction, int dir_size,int& dir_counter){// this function shows the direction of player moves
	string base=" ABCDEFGHIJKLMNOPQRSTUVWXY";
	string show="";
	show=base[(x+1)/2];
	y = (y+1)/2;
    string num_str  = to_string(y);
    if(y < 10) num_str = "0"+num_str;
    if( dir_counter == dir_size ){
    	direction.erase (0,7);
    	direction += show + num_str + "==> "; 
    }
    else{
    	direction += show + num_str + "==> ";
    	dir_counter ++;
    }
        setcolor(0x0A); 
    	cout << endl << "Direction: "<<direction << endl;
        setcolor(0x07);
}

void printLevel(int lvl){ // this function prints the borad of Maze game
    cout << "\n";
    for (int i = 0; i != 51; ++i){
            cout << endl << "\t\t\t\t";
            for (int j = 0; j != 51; ++j){
                setcolor( 0x07 );  // Initial color for program
                if(lvl1[i][j] == '@')setcolor( color_choice );
                cout << lvl1[i][j] <<" ";
                setcolor( 0x07 );
            }
        } cout << endl;
}

void setMe(int lvl){
    // set palyer position
    int x, y;
    color_choice = colorChoice();
    x = getPos(lvl, y);
    lvl1[x][y] = me;




}
//got this function from a CPP forum
char getKeyPress(){
    // this function gets a key (ARROW KEY) from player and returns char : u -> UP , l -> LEFT, r -> RIGHT, d -> DWON  
    char key = 127;

    key = _getch(); // 

    if (key == 0 || key == -32){

        key = _getch();

        if (key == 72) {
            key = 'u';  //up
        } else if (key == 75){
            key = 'l';  //left
        } else if (key == 77){
            key = 'r';  //right
        } else if (key == 80){
            key = 'd';  //dwon
        }
    }
    return key;
}

bool isExit(int x, int y, int lvl){// this funvtion checks if user is in the exit of the Maze or not
   if ( x == 51 && y == 33) return true;
   return false;
}

int getPos(int lvl, int &y){ // this function is useful to find the position of player
    int xCoord;
    for (int i = 0; i != 51; ++i){
        for (int j = 0; j != 51; ++j){
            if (lvl1[i][j] == '@'){
                xCoord = i;
                y = j;
                return xCoord;
            }
        }
    }
    return 0;
}

bool isWall(int x, int y, int lvl){ // this function checks that palyer can move or not
	if(x<=0||y<=0 || lvl1[x][y] == '+'){
        setcolor(0x07);
        cout << "\n\t\tCannot move! That is a wall / boundary.";
        setcolor(0x0C);
        Sleep(700);
        system("CLS");
        printLevel(lvl);
        return true;
	}
    return false;
}

void update(int lvl, int x, int y){ // this function updates the board of the Game after receiving the position of player
        lvl1[x][y] = me;
        printLevel(lvl);

}

void makeSpace(int lvl, int x, int y){
          lvl1[x][y] = space;

}

unsigned char colorChoice(){
    string color_arr[6] = {"Aque", "Red", "Green", "White", "Yellow", "Purple"};
    unsigned char color_code_arr[6] = {0x0B, 0x0C, 0x0A, 0x0F, 0x0E, 0x0D};
    int choice;
    for(int i = 0; i < 6; i++){
        cout << i;
        setcolor(color_code_arr[i]);
        cout << ": "<< color_arr[i];
        setcolor(0x07); // white color
    }
    cin >> choice;
    if (choice <= 1 && choice <= 6)return color_code_arr[choice-1] ;
    colorChoice();
};