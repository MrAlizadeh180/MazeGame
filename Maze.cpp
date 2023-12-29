#include <iostream>
#include <cmath>
#include <windows.h> // for windows users
#include <unistd.h> // for linux users
#include <time.h>
#include <conio.h>
#include <string> 
using namespace std;

// Functions
char getKeyPress();
void printLevel(int);
void setMe(int);
bool isExit(int, int, int);
bool isWall(int, int, int);
int getPos(int, int&);
void update(int, int, int);
void makeSpace(int, int, int);
void ShowPos(int ,int);

const char space = ' ';
const char me = '@';
const int lanes[][2] = {
    {0,43},{1, 4}, {1,6}, {1,8}, {1,10},{1,12},{1,16},{1,18},{1,22},{1,24},{1,26},{1,28},{1,30}
    ,{1, 34},{1,36},{1,38},{1,40},{1,44},{1,46},{1,48},{2,1},{2,3},{2,9},{2,11},{2,13},{2,15},{2,17}
    ,{2,19},{2,21},{2,23},{2,29},{2,31},{2,33},{2,41},{2,43},{2,49},{3,2},{3,6},{3,14},{3,20},{3,24}
    ,{3,28},{3,36},{3,38},{3,42},{3,46},{3,48},{4,5},{4,9},{4,11},{4,17},{4,23},{4,25},{4,27},{4,33}
    ,{4,35},{4,39},{4,41},{4,45},{5,48},{5,2},{5,6},{5,8},{5,14},{5,32},{5,20},{5,22},{5,28},{5,34}
    ,{5,38},{5,42},{5,46},{6,1},{6,11},{6,13},{6,15},{6,17},{6,19},{6, 25},{6,29},{6,31},{6,49}
    ,{7,2},{7,4},{7,8},{7,22},{7,26},{7,30},{7,34},{7,36},{7,38},{7,40},{7,42},{7,46},{7,48}      
    ,{8,5},{8,7},{8,9},{8,11},{8,13},{8,15},{8,17},{8,19},{8,21},{8,23},{8,33},{8,37},{8,43},{8,45} 
    ,{9,4},{9,6},{9,10},{9,16},{9,26},{9,28},{9,32},{9,36},{9,40},{9,44},{9,48},{10,1},{10,3},{10,11}
    ,{10,13},{10,17},{10,19},{10,21},{10,23},{10,25},{10,31},{10,33},{10,39},{10,49}
    ,{11,2},{11,6},{11,8},{11,16},{11,20},{11,26},{11,28},{11,30},{11,36},{11,40},{11,42},{11,46}
    ,{12,5},{12,9},{12,11},{12,13},{12,15},{12,19},{12,21},{12,23},{12,35},{12,37},{12,39},{12,41}
    ,{12,43},{12,47},{12,49},{13,2},{13,4},{13,8},{13,18},{13,24},{13,28},{13,32},{13,34},{13,44},{13,46}
    ,{14,1},{14,7},{14,11},{14,13},{14,15},{14,17},{14,19},{14,21},{14,23},{14,25},{14,27},{14,29},{14,37},{14,39}
    ,{14,41},{14,49},{15,4},{15,6},{15,8},{15,10},{15,18},{15,32},{15,36},{15,42},{15,44},{15,46},{15,48}
    ,{16,1},{16,13},{16, 15},{16,19},{16,23},{16,25},{16,27},{16,29},{16,33},{16,35},{16,39},{16,47}
    ,{17,2},{17,4},{17,6},{17,10},{17,16},{17,22},{17,26},{17,30},{17,32},{17,36},{17,42},{17,44},{17,48}
    ,{18,9},{18,11},{18,13},{18,17},{18,21},{18,39},{18,43},{18,45},{18,49},{19,4},{19,6},{19,8}
    ,{19,14},{19,18},{19,22},{19,24},{19,26},{19,28},{19,32},{19,34},{19,38},{19,42},{19,46}
    ,{20,1},{20,3},{20,13},{20,19},{20,27},{20,31},{20,35},{20,37},{20,41},{20,47},{20,49}
    ,{21,2},{21,4},{21,8},{21,10},{21,12},{21,16},{21,18},{21,22},{21,24},{21,28},{21,30},{21,38}
    ,{21,40},{21,44},{21,46},{22,5},{22,11},{22,15},{22,25},{22,31},{22,33},{22,35},{22,43},{22,49},{23,2},{23,6},{23,10}
    ,{23,14},{23,18},{23,20},{23,22},{23,24},{23,28},{23,32},{23,36},{23,38},{23,40},{23,42},{23,48},{24,1},{24,7},{24,11}
    ,{24,17},{24,19},{24,27},{24,29},{24,35},{24,43},{24,45},{24,47},{24,49},{25,2},{25,4},{25,6},{25,8},{25,12}
    ,{25,14},{25,16},{25,20},{25,22},{25,24},{25,32},{25,36},{25,38},{25,40},{25,46},{26, 9},{26,15},{26, 19},{26,21}
    ,{26, 25},{26, 29},{26,31},{26,33},{26,37},{26,41},{26,43},{27,2},{27,4},{27,8},{27,10},{27,12},{27,18},{27,26}
    ,{27,28},{27,30},{27,34},{27,40},{27,44},{27,48},{28,1},{28,5},{28,13},{28,17},{28,19},{28,21},{28,23}
    ,{28,35},{28,37},{28,39},{28,45},{28,47},{28,49},{29,2},{29,6},{29,10},{29,12},{29,14},{29,16},{29,22}
    ,{29,26},{29,30},{29,32},{29,34},{29,40},{29,44},{30,7},{30,9},{30,17},{30,19},{30,25},{30,27},{30,41}
    ,{30,43},{30,49},{31,4},{31,6},{31,12},{31,16},{31,20},{31,22},{31,28},{31,30},{31,34},{31,36},{31,38}
    ,{31,40},{31,44},{31,48},{32,1},{32,3},{32,9},{32,11},{32,15},{32,23},{32,31},{32,33},{32,45},{32,47}
    ,{33,6},{33,12},{33,14},{33,18},{33,20},{33,22},{33,26},{33,28},{33,30},{33,34},{33,36},{33,38},{33,40}
    ,{33,42},{33, 46},{33,48},{34,1},{34,3},{34,7},{34,9},{34,17},{34,19},{34,23},{34,25},{34,33},{34,35},{34,41}
    ,{35,4},{35,6},{35,10},{35,14},{35,22},{35,26},{35,30},{35,32},{35,36},{35,38},{35,42},{35,46},{35,48}
    ,{36,1},{36,7},{36,13},{36,15},{36,17},{36,21},{36,27},{36,43},{36,45},{36,47},{36,49},{37,2},{37,10}
    ,{37,12},{37,18},{37,22},{37,24},{37,28},{37,32},{37,34},{37,36},{37,38},{37,40},{38,3},{38,5},{38,7}
    ,{38,9},{38,15},{38,17},{38,19},{38,25},{38,29},{38,31},{38,41},{38,43},{38,45},{38,47},{39,8},{39,12}
    ,{39,14},{39,20},{39,22},{39,26},{39,32},{39,34},{39,36},{39,40},{39,44},{39,48},{40,1},{40,3},{40,5}
    ,{40,11},{40,17},{40,21},{40, 29},{40,37},{40,39},{40,49},{41,2},{41,6},{41,8},{41,10},{41,12},{41,18}
    ,{41,22},{41,24},{41,26},{41,30},{41,32},{41,34},{41,36},{41,40},{41,42},{41,44},{41,46},{42,1},{42,13}
    ,{42,15},{42,21},{42,25},{42,27},{42,47},{42,49},{43,2},{43,4},{43,6},{43,8},{43,12},{43,14},{43,18}
    ,{43,22},{43,30},{43,34},{43,36},{43,38},{43,40},{43,42},{43,48},{44,9},{44,15},{44,17},{44,19},{44,23}
    ,{44,27},{44,29},{44,31},{44,33},{44,35},{44,43},{44,45},{45,2},{45,4},{45,6},{45,10},{45,12},{45,14}
    ,{45,16},{45,22},{45,26},{45,32},{45,36},{45,38},{45,40},{45,46},{45,48},{46,1},{46,19},{46,25},{46,29}
    ,{46,41},{46,45},{46,49},{47,4},{47,8},{47,10},{47,12},{47,14},{47,16},{47,20},{47,24},{47,26},{47,28}
    ,{47,30},{47,32},{47,34},{47,38},{47,42},{47,44},{47,46},{48,1},{48,3},{48,5},{48,7},{48,9},{48,17},{48,21}
    ,{48,37},{48,39},{48,49},{49,2},{49,6},{49,10},{49,12},{49,14},{49,18},{49,20},{49,22},{49,24},{49,26}
    ,{49,28},{49,30},{49,32},{49,34},{49,36},{49,40},{49,42},{49,44},{49,46},{49,48},{50,33}
};
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
                    {'+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','o','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+'}


                 
};


bool isNotWall(int x, int y)
{
    if ( x > 25){
        for (int i = 626; i >= 300 ;i--){
            if (lanes[i][0] == x && lanes[i][1] == y)
               return true;
         } 
        return false;
    }
    else {
        for (int i = 0; i <= 340 ;i++){
            if (lanes[i][0] == x && lanes[i][1] == y)
               return true;
        }
        return false;
    }
}

int main(void)
{
    int lvl;
    lvl=1;
   
    int Y = 0; //players first vertical index 
    int X = 43; //players first horizontal index 
    int num = 25;
    int x1,y1; 
  
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
                ShowPos(x-2,y);
            }
            else
                ShowPos(x,y);
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
                ShowPos(x+2,y);
            }
            else
                ShowPos(x,y);
            
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
                ShowPos(x,y-2);
            }
            else
                ShowPos(x,y);
            
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
                ShowPos(x,y+2);
            }
            else
                ShowPos(x,y);            
            break;
        default:
            break;
        }
    
    }

    return 0;
}

void ShowPos(int x,int y){// needs change
	string base=" ABCDEFGHIJKLMNOPQRSTUVWXY";
	string show="";
	show=base[(x+1)/2];
	y = (y+1)/2;

    show = show+to_string(y);	
	cout<<endl;
	cout<<show;
	
}

void printLevel(int lvl){ // this function prints the borad of Maze game
    cout << "\n";
    for (int i = 0; i != 51; ++i){
            cout << endl << "\t\t\t\t";
            for (int j = 0; j != 51; ++j){
                cout << lvl1[i][j] <<" ";
            }
        } cout << endl;
}

void setMe(int lvl){
    // set palyer position
    int x, y;
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
   if (lvl1[x][y] == 'O'){
        return true;
   }
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
	if(x<0||y<0){
	    	return true;
	}
    else  if (lvl1[x][y] == '+'){
            cout << "\n\t\t\tCannot move! That is a wall / boundary.";
            Sleep(400);
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
