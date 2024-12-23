// initially have a user input a string
// have next user input only single characters at a time (handle errors/invalid inputs)

#include <iostream>
#include <vector>
#include <string>
#include <termios.h>
#include <unistd.h> // For STDIN_FILENO
#include <thread>  // For sleep_for
#include <chrono>

using namespace std;

// func to hide input from second user.
string getHiddenInput() {
    struct termios oldt, newt;
    std::string input;

    // Get current terminal settings
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;

    // Disable echoing
    newt.c_lflag &= ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    // Get the input
    std::cout << "Enter the word (hidden): ";
    std::cin >> input;

    // Restore original settings
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    std::cout << "\n";

    return input;
}

void print(string &curr_guess, string guessed) {
    cout << "Current correct letters: " << curr_guess << endl;
    cout << endl;
    cout << "Guess letters: " << guessed << endl;
}

bool isValidGuess(string &ans, char letter, string &curr_guess) {
    size_t pos = ans.find(letter);
    vector<size_t> positions;

    while (pos != string::npos) { // search for all occurances of letter
        positions.push_back(pos);
        pos = ans.find(letter, pos + 1);
    }

    if (!positions.empty()) {
        // add letters to curr_guess and return true
        for (size_t index : positions) {curr_guess[index] = letter; }
        return true;
    } else {
        return false;
    }
}

void guessLetter(string &ans, string &curr_guess, string &guessed) {
    cout << "Pick a character to guess: ";
    char letter;
    cin >> letter;

    // check if letter was guessed already
    size_t pos = guessed.find(letter);

    vector<size_t> positions;
    if (pos != string::npos) {
        cout << "Character already guessed! Try again." << endl;
    } else {
        guessed += letter;
        // check if letter is in the word chosen
        if (isValidGuess(ans, letter, curr_guess)) {
            cout << "Valid guess" << endl;
            print(curr_guess, guessed);
        } else {
            cout << "Incorrect guess" << endl;
        }
        
    }
}



void guess(string &guessed, string &ans) {}

int main() {
    // have first user pick a word.
    string ans = getHiddenInput();

    string curr_guess = "";

    // create a vector that will be printed after each letter guess.
    // hold " _ " for spaces not picked yet.
    // this all initializes the game
    vector<string> guesses;
    for (int i = 0; i < ans.length(); i++) {
        guesses.push_back("_");
        curr_guess += guesses[i];
    }

    // work picked and placeholders set up

    string guessed = ""; // cache to store already guessed letters.

    bool seen = false;
    while (!seen) {


        // create both choices:

        cout << "Choose an option" << endl;
        this_thread::sleep_for(chrono::seconds(1));
        cout << "Guess letter (1)" << endl;
        cout << "Guess answer (2)" << endl;

        int choice;
        cin >> choice;

        if (choice == 1) {
            // guess letter logic
        } else if (choice == 2){
            // guess answer logic
        } else {
            cout << "Invalid. Choose 1 or 2." << endl;
        }

        /* cout << "Pick a character to guess: ";
        char letter;
        cin >> letter;

        // check if letter was guessed already
        size_t pos = guessed.find(letter);

        vector<size_t> positions;
        if (pos != string::npos) {
            cout << "Character already guessed! Try again." << endl;
        } else {
            guessed += letter;
            // check if letter is in the word chosen
            if (isValidGuess(ans, letter, curr_guess)) {
                cout << "Valid guess" << endl;
                print(curr_guess, guessed);
            } else {
                cout << "Incorrect guess" << endl;
            }
            
        } */
    }




    return 0;
}