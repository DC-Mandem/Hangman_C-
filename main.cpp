/*
	Name: Hangman
	Copyright: theHuskyGang 2023
	Author: Ronish Ghimire
	Group: The Husky Gang
	Date: 10/11/23 14:30
	Description: OOP project
*/


#include <iostream>
#include<graphics.h>
using namespace std;

void hold();
int displayMenu();
bool mainGame(int &score, int categoryChoice);

int main()
{
	
	
    int score = 0;
    int categoryChoice = displayMenu();
    while (true)
    {
    	
        if (!mainGame(score, categoryChoice)){
            score = 0;
            char choice;
            cout << "Wanna play again??(Y/N): ";
            cin >> choice;
            closegraph();
            if (toupper(choice) != 'Y')
                break;
            else
            	hold();
                system("cls"); 
                categoryChoice = displayMenu();
        } 
    }
    return 0;
}

