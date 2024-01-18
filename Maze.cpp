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
const string alphabets=" ABCDEFGHIJKLMNOPQRSTUVWXY";
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
    time_t start, ending;
    time(&start);
    while (true){

        char move = getKeyPress();

        int x_move = 0;
        int y_move = 0;

        switch (move){
        case 'u':
            x_move = -1;
            y_move = 0;
            break;
        case 'd':
            x_move = 1;
            y_move = 0;
            break;
        case 'l':
            y_move = -1;
            x_move = 0;
            break;
        case 'r':
            y_move = 1;  
            x_move = 0;      
            break;
        default:
            break;
        }

        x = getPos(lvl, y);
        if (!isWall(x + x_move, y + y_move, lvl) && !isWall(x + 2*x_move, y + 2*y_move, lvl)){
            if (isExit(x + 2*x_move, y + 2*y_move, lvl)){
                system("CLS");
                cout << "You Win!" << endl;// need change
                time(&ending);
                cout << "You won the Game in: ";
                setcolor(Green);
                cout << difftime(ending, start);
                setcolor(0x07);
                cout << " seconds " << endl;
                Sleep(2000);
                break;
            }
            system("CLS");
            makeSpace(lvl, x, y);
            update(lvl, x + 2*x_move, y + 2*y_move);
            ShowDirection(x+2*x_move,y+2*y_move,direction,dir_size,dir_counter);
        }
        else
            ShowDirection(x,y,direction,dir_size,dir_counter);
    }
    return 0;
}

void ShowDirection(int x,int y, string& direction, int dir_size,int& dir_counter){// this function shows the direction of player moves
	string show="";
	show=alphabets[(x+1)/2];
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
    cout << endl << "Direction: ";
    setcolor(0x0A); 
    cout <<direction << endl;
    setcolor(0x07);
}

void printLevel(int lvl){ // this function prints the borad of Maze game
    cout << "\n";
    for (int i = 0; i != 51; ++i){
            cout << endl << "\t\t\t\t";
            for (int j = 0; j != 51; ++j){
                if(j == 0 && i%2 != 0){
                    cout << alphabets[(i+1)/2];
                }
                else cout <<" ";                
                setcolor( 0x07 );  // Initial color for program
                if(lvl1[i][j] == '@')setcolor( color_choice );
                cout << lvl1[i][j] <<" ";
                setcolor( 0x07 );
            }
        } cout << endl;
    cout << endl << "\t\t\t\t" << "   1   2   3   4   5  6  7  8  9  10  11  12  13  14  15  16  17  18  19  20  21  22  23  24  25" << endl;
}

void setMe(int lvl){
    // set palyer position and color
    int x, y;
    color_choice = colorChoice();
    system("CLS");

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
        setcolor(Red);
        cout << "\n\t\tCannot move! That is a wall / boundary.";
        setcolor(0x0C);
        Sleep(1200);
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
    cout << "Please choose a color for playing the game " << endl;
    for(int i = 1; i <= 6; i++){
        cout << i;
        setcolor(color_code_arr[i-1]);
        cout << ": "<< color_arr[i-1] << endl;
        setcolor(0x07); // white color
    }
    cout << "Your choice: ";
    cin >> choice;
    if (1 <= choice && choice <= 6)return color_code_arr[choice-1];
    system("CLS");
    colorChoice();
}
