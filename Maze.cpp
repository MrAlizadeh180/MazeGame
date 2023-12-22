#include <iostream>
#include <cmath>
#include <windows.h>
#include <conio.h>
using namespace std;
//color @ 
// update walls array 
// function -> check walls input(int i,int j,char move(w,a,s,d)) @ -> bool 
// function you won message void()
// function show direction(int i,int j(int -> char) ,char move(w,a,s,d)) a,b ==> c,d ==> h,j ==> 

const int walls[10][2] = {{0,3},{1,2},{4,1},{2,3},{2,5},{3,6},{1,4},{4,5},{5,2},{5,4}};

bool isNotWall(int x, int y) // function that checks if threre is wall on point(x,y) in array
{
    for (int i = 0; i < 10; i++)
    {
        if (walls[i][0] == x && walls[i][1] == y)
            return true;
    }
    return false;
}


int Y = 0; //players first vertical index 
int X = 3; //players first horizontal index 

int main()
{
    int num = 3;
    while (true){
        for (int i = 0; i < 2 * num + 1; i++)
        {
            for (int j = 0; j < 2 * num + 1; j++)
            {
                if( i== Y && j == X) cout << "@ ";
                else if ((i % 2 == 1 && j % 2 == 1) ||(isNotWall(i, j)))
                {
                    cout << "  ";
                }
                else cout << "+ ";
            }
            cout << endl;
        }
        sleep(0.1);
        char chr;
        cin >> chr;
        if( chr == 'w'){ // Move Up
            Y--;
        }
        else if( chr == 's'){ // Move dwon
            Y++;
        }
        else if( chr == 'a'){ // Move left
            X--;
        }
        else if( chr == 'd'){ // Move right
            X++;  
        }
        //cout << "\033[2J\033[1;1H";
        system("cls");
    }
}

