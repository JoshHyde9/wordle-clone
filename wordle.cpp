// A terminal based Wordle clone
// https://www.nytimes.com/games/wordle/index.html

#include <iostream>
#include <fstream>
#include <string>
#include <random>

using namespace std;

const string filename = { "common.txt" };

int linenum() {
    int lines = 0;
    // imports the file
    ifstream in(filename);
    string unused;

    // while loop to get the length of the file
    while (getline(in, unused))
        lines++;

    //returns the line count
    return lines;
}

string word_select() {
    // i'm not totally  sure how this works, but it creates a random device to create a "random" number
    int linecount = linenum();
    random_device rd;
    default_random_engine eng(rd());

    // gets a random value up to linecount (2309)
    uniform_int_distribution<int> distr(1, linecount);

    // takes random number and shoves it into an int
    int randnum = distr(eng);
    
    string word;
    ifstream in(filename);

    // starts a loop to get the word that corrisponds to the number
    for (int i = 1; i <= randnum; i++)
        std::getline(in, word);

    return word;
}

bool check_guess(string user_guess, string word) 
{
    int letter_position[5] = { 0, 0, 0, 0, 0 }; // Init array length of 5 

    // Iterate over the length of the user's guess 
    for (int i = 0; i < user_guess.length(); i++)
    {
        // If the guessed word is not 5 characters long
        if (user_guess.length() != word.length())
        {
            cout << "Must guess a 5 letter word!" << endl;
            return false;
        }

        // If the guessed word is the same as the word to guess
        if (user_guess.compare(word) == 0)
        {
            return true;
        }

        // Check if position i character is the same as position i in the word to guess
        if (user_guess[i] == word[i])
        {
            // Increment value to 1
            letter_position[i] = 1;

            // If position i in array is equal to 1, print out the character is in the correct position.
            if (letter_position[i] == 1)
            {
                 cout << "Letter " << i + 1 << " is in the correct position." << endl;
                 continue; // breaks one iteration of the loop and jumps back up to the top of the loop
            }
        }
        // If character (i) exists in user's guess print out if there is a match 
        // npos is typically used to indicate there are no matches (so we check if there is NOT no matches)
        // https://www.cplusplus.com/reference/string/string/npos/
        if (word.find(user_guess[i]) != string::npos)
        {
            cout << "Letter exists in word." << endl;
        }
        else
        {
            cout << "Letter does not exist in word." << endl;
        }
    }

    return false;
}

int main()
{
    string word = word_select();

    cout << "I am thinking of a 5 letter word. What's your guess faggot?\n";
    for (int guesses = 0; guesses < 5; guesses++)
    {
        string guess;
        cin >> guess;

        // Assign return value from function into a variable 
        bool correct_guess = check_guess(guess, word);

        // If word is correctly guessed, break the loop and outpout a nice message
        if (correct_guess)
        {
            cout << "You guessed the word I was thinking of!" << endl; 
            break; 
        }

        cout << "You have " << 4 - guesses << " guesses left." << '\n';
    }
    
    return 0;
};