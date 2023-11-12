#include <iostream>
#include <cctype>
#include <string>
#include <graphics.h>
#include <ctime>
#include <cstdlib>  
#include<fstream>
#include <algorithm>
#include <cmath>

#define MAX_WORD_LENGTH 100
#define MAX_GUESSES 6

using namespace std;

void hold() {
	fflush(stdout);  //flushing the buffer input
    string input;
    getline(cin, input);  //waiting for the enter key
}

void convertToUnderscore(string &word, string &guessed)
{
    guessed = word;
    for (size_t i = 0; i < word.length(); i++)
    {
        if (word[i] != ' ' && word[i] != '-' && word[i] != '/' )
            guessed[i] = '_';
    }
}

string capitalized(string lower)
{
    for (int i = 0; i < lower.length(); i++)
    {
        lower[i] = toupper(lower[i]);
    }
    return lower;
}

void draw(int er)
{
    switch (er)
    {
    case 1:
        // Head
        for (int i = -2; i < 3; i++)
            circle(400, 200, 50 + i);
        break;
    case 2:
        // Body
        for (int i = -2; i < 2; i++)
            line(400 + i, 250, 400 + i, 400);
        break;
    case 3:
        // Left arm
        for (int i = -2; i < 3; i++)
            line(400 + i, 275 + i, 350 + i, 325 + i);
        break;
    case 4:
        // Right arm
        for (int i = -2; i < 3; i++)
            line(400 - i, 275 + i, 450 - i, 325 + i);
        break;
    case 5:
        // Left leg
        for (int i = -2; i < 3; i++)
            line(400 + i, 400 + i, 350 + i, 500 + i);
        break;
    case 6:
        // Right leg
        for (int i = -2; i < 3; i++)
            line(400 - i, 400 + i, 450 - i, 500 + i);
//        outtextxy(325, 80, "Game Over");
 		 settextstyle(COMPLEX_FONT, HORIZ_DIR, 3 );
         outtextxy(270, 65, "Game Over!");
//        hold();
        break;
    }
}

void displayStats(int gPlayed, int CDs)
{
    cout << "Total number of games played: " << gPlayed << endl;
    cout << "Total number of Chicken Dinner: " << CDs << endl
        << endl;
}

int displayMenu()
{
	int choice;
	cout << "-------- MENU SCREEN ------------" <<endl;
	cout << "Select Category to play hangman: "<<endl;
	cout << "1 for Country"<<endl;
	cout << "2 for Sports"<<endl;
	cout << "3 for Animals"<<endl;
	cout << "4 for Landmarks"<<endl;
	cout << "0 for Exit"<<endl;
    cout << "Enter your choice(0-4): ";
    cin >> choice;
    system("cls");
    return choice;
    
}

int getRandomNumber(){
    srand(time(NULL));
    return  (rand()*rand());
}

string getWord(int choice)
{
	string word;
    int random_number;
    int temp;
    ifstream file;
    switch (choice){
		case 0: 
    		exit(1);
		case 1:
   			file.open("countryList.txt");
   			temp = 195;
    		break;
    	case 2:
    		file.open("sports.txt");
    			temp = 151;
    		break;
    	case 3:
    		file.open("animals.txt");
    			temp = 105;
    		break;
    	case 4:
    		file.open("landmarks.txt");
    			temp = 41;
    		break;
    		
    	default:
    	clog<<"Invalid choice."<<endl;
    	exit(1);
    	
	}
	
    if (!file.is_open())
    {
        cout << "Error opening the file." << endl;
        exit(1);
    }
    
    random_number =getRandomNumber() % temp; 
    for (int i = 0; i < random_number; i++)
    {
          if (!getline(file, word))
        {
            cout << "Error reading the file." << endl;
            exit(1);
        }
//        cout<<word;
    }
    
    transform(word.begin(), word.end(), word.begin(), ::tolower);
    
    return word;
}


void replace(const string &word, string &guessed, char ch, int &num_guesses, int &er, bool isMatched)
{
    bool found = false;
    for (int i = 0; i < word.length(); i++)
    {
        if (tolower(word[i]) == tolower(ch))
        { 
            guessed[i] = ch;
            found = true;
        }
    }
    if (!found && !isMatched) 
        num_guesses++;

    er = num_guesses;
}

void displayGuessedWord(const string &guessed, int hasWon = 0)
{
    string temp = capitalized(guessed);
    if (!hasWon)
        cout << "Guessed word: " << temp << endl;
    else
        cout << "Correct word: " << temp << endl;
}

int displayEnteredCharacter(char enteredCharacter[50], int &lengthOfArray)
{
    char temp;
    cout << "Entered character: ";
    for (int i = 0; i < lengthOfArray; i++)
    {
        temp = toupper(enteredCharacter[i]);
        cout << temp << " ";
    }
    cout << endl;
}

bool updateEnteredCharacter(char enteredCharacter[50], char ec, int &len)
{
    for (int i = 0; i < len; i++)
    {
        if (ec == enteredCharacter[i])
            return true;
    }
    enteredCharacter[len++] = ec;
    return false;
}

bool mainGame(int &score, int categoryChoice)
{
    string word;
    string guessed;
    int num_guesses = 0, er = 0, lengthOfArray = 0;
    char enteredCharacter[50], ch;
    bool isMatched;
    char winStreaksString[30];
	
    word = getWord(categoryChoice);
   
    convertToUnderscore(word, guessed);

    cout << "The word to guess has " << guessed.length() << " letters." << endl;

    initwindow(650, 750);
    settextstyle(EUROPEAN_FONT, HORIZ_DIR, 2 );
	  for(int i = -1; i<2;i++){
        line( 400+i, 150, 400+i, 100);
		line( 280,100+i,400,100+i);
		line(280+i,100, 280+i, 550);
        line( 200,550+i ,500,550+i);
    }
    sprintf(winStreaksString, "Win Streaks: %d", score);
     settextstyle(COMPLEX_FONT, HORIZ_DIR, 1 );
    outtextxy(10, 10, winStreaksString);

    while (true)
    {
        displayGuessedWord(guessed);
        if (strlen(enteredCharacter) != 0)
            displayEnteredCharacter(enteredCharacter, lengthOfArray);
        cout << "Enter a character to guess: ";
        cin >> ch;
        ch = tolower(ch); 
        isMatched = updateEnteredCharacter(enteredCharacter, ch, lengthOfArray);
        replace(word, guessed, ch, num_guesses, er, isMatched);
        system("cls");
        draw(er);

        if (word == guessed)
        {
            
            hold();
            displayEnteredCharacter(enteredCharacter, lengthOfArray);
            enteredCharacter[0] = '\0';
            displayGuessedWord(guessed, 1);
            cout <<endl << "Winner Winner Chicken Dinner!!!" << endl;
            cout<<"You guessed it right."<<endl;
            score++;
//            delay(4000);
			cout<"Press enter to continue......";
			hold();
            system("cls");
//            closegraph();
            return true;
        }

        if (er >= MAX_GUESSES)
        {
            displayGuessedWord(word);
            cout << "Wrong!! You lost." << endl;
            displayEnteredCharacter(enteredCharacter, lengthOfArray);
            cout << "The correct word is: " << capitalized(word) << endl;
            cout << "Win Streaks: " << score << endl;
            hold();
//            closegraph();
            return false;
        }
    }
}
