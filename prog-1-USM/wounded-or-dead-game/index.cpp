#include <iostream>
#include <ctime>
#include <conio.h>
#include <windows.h>
#include <string>
#include <map>
#include <locale.h>
#include <fstream>
#include <sstream>


#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77


using namespace std;
// Global Scope output handle 
HANDLE output_handle = GetStdHandle(STD_OUTPUT_HANDLE);

void displayHearts(int num) {
    for (int i = 0; i < num; i++) {
        SetConsoleTextAttribute(output_handle, 4);
        cout << char(3);
    }
    for (int i = 0; i < (7 - num); i++) {
        SetConsoleTextAttribute(output_handle, 7);
        cout << char(3);
    }
    cout << endl;
}

void saveScore(const string& player, int score) {
  ofstream outfile("scores.txt", ios::app); // open file for appending
  if (outfile.is_open()) {
    outfile << player << " " << score << endl; // write player and score to file
    outfile.close(); // close file
  }

}

int floor(float num) {
    /*
    Function that returns the floor of a number
    input: a float number
    output: the floor of the number
    */

    int floor = int(num);
    // (if the number is negative, the floor is the number minus one)
    if (num < 0) {
        floor--;
    }
    return floor;
}

int randomNumberInt(int min, int max) {
    /*
    Function that generates a random int between two numbers
    input: the range of the random number in int
    output: a random int between the two numbers
    */

    // the min susbstract the max for having the real cap after adding de min
    int randomInt = min + ( rand()%(max - min + 1) );
    return randomInt;
}

int randomIntFourDiffDigit() {
    /*
    Function that generates a random int of four differents digits 
    input: none
    output: a random int of four digits having all digits diferent
    */
    
    int digits[4];
    digits[0] = randomNumberInt(1, 9); // the first digit can't be 0

    for (int i = 1; i < 4; i++) {
        // generate a random digit bewteen 0 and 9
        int potentialDigit = randomNumberInt(0, 9);

        // check if the digit was already generated
        for (int j = 0; j < i; j++) {
            if (potentialDigit == digits[j]) { 
                // if the digits was already generated, generate another digit
                // and start the loop again
                potentialDigit = randomNumberInt(0, 9);
                j = -1; 
            }
        }

        // store the digit 
        digits[i] = potentialDigit; 
    }

    // concatenate the int
    int num = (digits[0] * 1000) + (digits[1] * 100) + (digits[2] * 10) + digits[3];
    return num;
}

bool isNumberHave4DigitDifferent(int num) {
    /*
    Function that verifies if the four digits of a int are Diferent
    input: an integer number of four digits
    output: a boolean value that indicates if the digits of the int are diferent
    */
    
    // get the digits of the number
    int numDigits[4]; 
    for (int i = 0; i < 4; i++) {
        // obtains the last digit of the number
        numDigits[i] = num % 10; 
        // delete the last digit of the number
        num = floor(num / 10);
    }

    // Check if the digits are diferent
    // (no debería ser i<3?)
    for (int i = 0; i < 4; i++) {
        for (int j = i + 1; j < 4; j++) {
            // if two digits are equal, the number is not valid
            if (numDigits[i] == numDigits[j]) { 
                return false;
            }
        }
    }

    return true;
}

bool isStringOfInt(string str){
    /*
    Function that verifies if a string is a string of is characters 
    input: a string 
    output: a boolean value that indicates if the string is a string of characters
    */

    for (char characters : str) {
        if (!isdigit(characters)) {
            return false;
            break;
        }
    }

    return true; 
}

bool validRoundInput(string turn_input){
    /*
    Function that verifies all the inputs turns from the user  
    (check if the input is [int, 4 digits, all digits diferent] )
    (or if input is "0000", "stop", "exit", "quit")
    input: the string of the user input for the turn 
    output: a boolean value that indicates if the input is valid
    */

    // check if the input is "salir", "stop", "exit"
    if (turn_input == "quit" or turn_input == "stop" 
        or turn_input == "exit" or turn_input == "0000"){

        return true;
    }

    // check if the input is a string of int
    int input_int = 0;
    if(isStringOfInt(turn_input)){
        input_int = stoi(turn_input);
    }
    else {
        return false;
    }
    // check if the input is a number of 4 digits and all digits are diferent
    if (input_int < 1000 or input_int> 9999 or turn_input.length() != 4){
        return false;
    }
    else if (!isNumberHave4DigitDifferent(input_int)){
        return false;
    }

    return true;
}

int getDead(string random, string num){
    int dead = 0;
    for (int i = 0; i < random.length(); i++){
        if (random[i] == num[i]){
            dead++;
        }
    }
    return dead;
}

int getWounded(const string random, const string num) {
  // function that compares two strings that represent numbers and returns the number of equal
  // digits in different positions
  int wounded = 0; // counter for numbers in different position
  map<char, int> m; // map that saves the digits

  for (int i = 0; i < num.size(); i++) { // iterate second string
    m[num[i]] = i; // insert a digit in the map
  }

  for (int i = 0; i < random.size(); i++) { // iterate first string
    auto currentChar = m.find(random[i]); // search current char in the map
    if (currentChar != m.end()) { // if it appears in the map
      int j = currentChar->second; // get position of the current char in the second string
      if (i != j) { // if the position is different
        wounded++; // increase counter
      }
    }
  }
  return wounded; // get counter
}


// Visual, UI Code -------------------------------------------------------->
// ------------------------------------------------------------------------>
// ------------------------------------------------------------------------>
// ------------------------------------------------------------------------>

// Win and Lose Screens --------------------------------------------------->
int tiempo = 5;
void gotoxy(short a, short b) // Custom gotoxy() function
{
  COORD coordinates; // Data type of co-ordinates
  coordinates.X = a; // Assign value to X- Co-ordinate
  coordinates.Y = b; // Assign value to Y Co-ordinate

  SetConsoleCursorPosition(
      GetStdHandle(STD_OUTPUT_HANDLE), coordinates);
}

void writey(int x, int y, int cantidady)
{

  int j = y;

  while (j <= (cantidady + y))
  {

    gotoxy(x, j);
    cout << "RBRBR";

    j++;

    Sleep(tiempo);
  }
}

void writey2(int x, int y, int cantidady, int iteracion)
{

  int i = x;

  int j = y;

  while (j <= (cantidady + y))
  {

    gotoxy(i, j);
    cout << "RBRBR";

    j++;

    i = i + iteracion;

    Sleep(tiempo);
  }
}

void writex(int x, int y, int cantidadx)
{

  int i = x;

  while (i <= (cantidadx + x))
  {

    gotoxy(i, y);
    cout << "R";

    gotoxy(i, y + 1);
    cout << "B";

    i++;

    Sleep(tiempo);
  }
}

void loseScreen(){

  // Y

  writey(18, 6, 6);
Beep(523, 150);


  writey2(24, 2, 5, -1);
      Beep(494, 150);

  writey2(12, 2, 5, 1);

    Beep(466, 150);
  // o

  writey(34, 4, 6);
    Beep(440, 250);

  writey(49, 4, 6);
    Beep(392, 250);

  writex(40, 2, 7);
      Beep(349, 150);
  writex(40, 11, 7);
    Beep(329, 150);
  writey2(36, 3, 1, -1);

  writey2(47, 3, 1, 1);
    Beep(293, 150);
  writey2(36, 10, 1, 1);
    Beep(261, 150);
  writey2(47, 10, 1, -1);
  
  // u

  writey(62, 2, 8);
Beep(329, 150); // E4 negr
  writey(77, 2, 8);
  writex(68, 11, 7);
Beep(311, 150); // Eb4 negra
  writey2(64, 10, 1, 1);
  
  writey2(75, 10, 1, -1);  
    Beep(293, 150); // D4 negra
  // L
  writey(12, 15, 10);
    Beep(329, 150); // E4 negra
  writex(16, 24, 7);
  
  // o

  writey(29, 17, 6);
Beep(311, 100); // Eb4 negra
  writey(44, 17, 6);
    Beep(293, 150); // D4 negra
  writex(35, 15, 7);
    Beep(261, 150); // C4 blanca
  writex(35, 24, 7);
    Beep(466, 150); // Bb4 negra
  writey2(31, 16, 1, -1);
    Beep(369, 150); // Gb4 negra
  writey2(42, 16, 1, 1);
    Beep(349, 150); // F4 negra
  writey2(31, 23, 1, 1);
    Beep(311, 150); // Eb4 negra
  writey2(42, 23, 1, -1);
  
  // S
  
  writey(56, 15, 5);
    Beep(293, 150); // D4 blanca  
  writey(64, 19, 6);
    Beep(261, 250); // C4 redonda  
  writex(60, 15, 7);
      Beep(392, 150); // G4 negra
  writex(60, 19, 7);
    Beep(329, 150); // E4 negra
  writex(56, 24, 7);
  
  // E
  
  writey(76, 15, 10);
    Beep(311, 150); // Eb4 negra  
  writex(80, 15, 7);
    Beep(293, 150); // D4 negra  
  writex(80, 19, 7);
    Beep(261, 250); // C4 blanca
  writex(80, 24, 7);

    Beep(466, 500); // Bb4 negra
    Beep(369, 500); // Gb4 negra
    Beep(349, 500); // F4 negra
    Beep(311, 500); // Eb4 negra
    Beep(293, 1000); // D4 blanca
    Beep(0, 1000); // silencio
    Beep(261, 1500); // C4 redonda

    Sleep(500);
}

void winScreen(){
  
  // Y

  writey(18, 6, 6);
  Beep(130, 100);
  writey2(24, 2, 5, -1);
  Beep(262, 100);
  writey2(12, 2, 5, 1);
  Beep(330, 100);


  // o

  writey(34, 4, 6);
  Beep(392, 100);
  writey(49, 4, 6);
  Beep(523, 100);
  writex(40, 2, 7);
  Beep(660, 100);
  writex(40, 11, 7);
  Beep(784, 300);
  writey2(36, 3, 1, -1);
  Beep(660, 300);
  writey2(47, 3, 1, 1);
  Beep(146, 100);
  writey2(36, 10, 1, 1);
  Beep(262, 100);
  writey2(47, 10, 1, -1);
  Beep(311, 100);  
  
  // u

  writey(62, 2, 8);
  Beep(415, 100);
  writey(77, 2, 8);
  Beep(523, 100);
  writex(68, 11, 7);
  Beep(622, 100);
  writey2(64, 10, 1, 1);
  Beep(831, 300);
  writey2(75, 10, 1, -1);
  Beep(622, 300);   
  
  // W

  writey2(12, 16, 9, 1);
  Beep(155, 100);
  writey2(28, 18, 7, -1);
  Beep(294, 100);
  writey2(29, 18, 7, 1);
  Beep(349, 100);
  writey2(45, 16, 9, -1);
  Beep(466, 100);
      
  // i
  writey(54, 16, 9);
  Beep(588, 100);

  // n

  writey(64, 16, 9);
  Beep(699, 100);
  writey2(66, 16, 9, 1);
  Beep(933, 300);
  writey(76, 16, 9);
  Beep(933, 100);
  Beep(933, 100);
  Beep(933, 100);
  Beep(1047, 400);

    Sleep(500);
}



// ------------------------------------------------------------------------>
// ------------------------------------------------------------------------>
// ------------------------------------------------------------------------>

void clearConsole() {
    /*
    Function that clears the console
    input: none
    output: clear the console
    */

    // cout << "\033[2J\033[1;1H";
    system("cls");
}

string getPaddingToCenter(int text_width, int line_width = 80){
    /*
    Function that returns a string with the padding to center the text
    input: text_width, line_width
    output: string with the padding
    */

    int left_margin = floor( (line_width - text_width) / 2 );
    string margin = "";
    for(int i = 1; i <= left_margin; i++){
        margin += " ";
    }

    return margin;
}

void printTitle(){
    /*
    Function that prints the title of the game 
    input: none
    output: print the title of the game
    */

    string title_header  = "---------------------";
    string title_muertos = "-     MUERTOS Y     -";
    string title_heridos = "-      HERIDOS      -";
    string title_footer  = "---------------------";

    // 29 and 30 spaces, because the title has 21 characters
    string leftMargin  = "*                            ";
    string rightMargin = "                             *";

    // 4 is the color red in the text 
    SetConsoleTextAttribute(output_handle, 4);
    cout << leftMargin << title_header << rightMargin << "\n";
    cout << leftMargin << title_muertos << rightMargin << "\n";
    cout << leftMargin << title_heridos << rightMargin << "\n";
    cout << leftMargin << title_footer << rightMargin << "\n";

    // 7 is the color white in the text
    SetConsoleTextAttribute(output_handle, 7);
    cout << "\n\n";
}

int mainMenu(){
    /*
    Function that prints the main menu of the game 
    input: none
    output: print the main menu of the game and return the option selected by the user
    */

    char input_user = ' '; 
    int user_actual_option = 1;

    // margin of 29 blank spaces, the same as title
    string margin_options = "                             ";

    bool user_not_has_selected_option = true;
    while(user_not_has_selected_option){
        // print the title
        printTitle();

        // set the menu options 
        string play_option_text1 =         "  1. Jugar           ";
        string instructions_option_text2 = "  2. Instrucciones   ";
        string exit_option_text3 =         "  4. Salir           ";
        string leaderboard_option_text4 =  "  3. Ranking         ";
        int last_index_options = play_option_text1.length() - 1;
        int options_amount = 4;

        // highlight the actual option 
        if(user_actual_option == 1){
            play_option_text1[0] = '>';
            play_option_text1[last_index_options] = '<';
        }
        else if(user_actual_option == 2){
            instructions_option_text2[0] = '>';
            instructions_option_text2[last_index_options] = '<';
        }
        else if(user_actual_option == 3){
            leaderboard_option_text4[0] = '>';
            leaderboard_option_text4[last_index_options] = '<';
        }
        else if(user_actual_option == 4){
            exit_option_text3[0] = '>';
            exit_option_text3[last_index_options] = '<';
        }

        // print the menu options 
        // 12 = light_red
        if(user_actual_option == 1){
            SetConsoleTextAttribute(output_handle, 12);
            cout << margin_options << play_option_text1 << "\n";
            SetConsoleTextAttribute(output_handle, 7);

            cout << margin_options << instructions_option_text2 << "\n";
            cout << margin_options << leaderboard_option_text4 << "\n";
            cout << margin_options << exit_option_text3 << "\n";
        }
        else if(user_actual_option == 2){
            cout << margin_options << play_option_text1 << "\n";

            SetConsoleTextAttribute(output_handle, 12);
            cout << margin_options << instructions_option_text2 << "\n";
            SetConsoleTextAttribute(output_handle, 7);

            cout << margin_options << leaderboard_option_text4 << "\n";
            cout << margin_options << exit_option_text3 << "\n";
        }
        else if(user_actual_option == 3){
            cout << margin_options << play_option_text1 << "\n";
            cout << margin_options << instructions_option_text2 << "\n";

            SetConsoleTextAttribute(output_handle, 12);
            cout << margin_options << leaderboard_option_text4 << "\n";
            SetConsoleTextAttribute(output_handle, 7);

            cout << margin_options << exit_option_text3 << "\n";
        }
        else if(user_actual_option == 4){
            cout << margin_options << play_option_text1 << "\n";
            cout << margin_options << instructions_option_text2 << "\n";
            cout << margin_options << leaderboard_option_text4 << "\n";

            SetConsoleTextAttribute(output_handle, 12);
            cout << margin_options << exit_option_text3 << "\n";
            SetConsoleTextAttribute(output_handle, 7);
        }
       
        // get the user input 
        input_user = getch();

        // move the cursor based on the input, w is up, s is down
        if(input_user == KEY_UP or input_user == 'k' or
            input_user == 'w'){

            if(user_actual_option > 1){
                user_actual_option -= 1;
            }
            else if(user_actual_option == 1){
                user_actual_option = options_amount;
            }
        }
        else if(input_user == KEY_DOWN or input_user == 'j'
            or input_user == 's'){

            if(user_actual_option < options_amount){
                user_actual_option += 1;
            }
            else if(user_actual_option == options_amount){
                user_actual_option = 1;
            }
        }
        else if(input_user == '\r' or input_user == 'e'
                or input_user == '\n' or input_user == KEY_RIGHT
                or input_user == 'd' or input_user == 'l'
                or input_user == ' '){

            user_not_has_selected_option = false;
        };

        if(input_user == '1'){
            user_actual_option = 1;
            user_not_has_selected_option = false;
        }
        else if(input_user == '2'){
            user_actual_option = 2;
            user_not_has_selected_option = false;
        }
        else if(input_user == '3'){
            user_actual_option = 3;
            user_not_has_selected_option = false;
        }
        else if(input_user == '4'){
            user_actual_option = 4;
            user_not_has_selected_option = false;
        }

        clearConsole();
    }

    return user_actual_option;
}

void printInstructions(){
    /*
    Function that prints the instructions of the game 
    input: none
    output: print the instructions of the game and wait for the user key to continue
    */

    string instructions_text[] = {
        "Instrucciones:",
        "El juego consiste en adivinar un numero de 4 digitos distintos.",
        "El jugador dispondrá de 7 intentos para adivinar el numero.    ",
        "En cada intento el jugador ingresará un numero de 4 digitos,   ",
        "y el juego le indicará cuantos muertos y cuantos heridos tiene.",
        "Un muerto es un digito que esta en la posicion correcta.       ",
        "Un herido es un digito que esta en la posicion incorrecta.     ",
        "Si el jugador adivina el numero antes de los 7 intentos, gana. ",
        "                                                               ",
        "Ejemplo:                                                       ",
        "Número a adivinar: 1234                                        ",
        "Intento 1: 5678                                                ",
        "Resultado: 0 muertos y 0 heridos                               ",
        "Intento 2: 1234                                                ",
        "Resultado: !Ganaste¡                                           ",
        "                                                               ",
        "Comandos Especiales: stop, exit, quit, 0000 (backdoor)         ",
        "                                                               ",
        "   ¡Presiona cualquier tecla para volver al menu principal!    ",
    };
  
    // Get padding to center instructions
    string paddingInstructions = getPaddingToCenter(instructions_text[1].length() - 6);

    // print the title 
    printTitle();

    // print the instructions 
    int instructions_text_lenght = sizeof(instructions_text)/sizeof(instructions_text[0]);
    // print the instructions title in light_yellow(14) and return to white(7)
    SetConsoleTextAttribute(output_handle, 14);
    cout << paddingInstructions << instructions_text[0] << "\n";
    SetConsoleTextAttribute(output_handle, 7);

    for (int i = 1; i < (instructions_text_lenght - 1); i++) {
        cout << paddingInstructions << instructions_text[i] << "\n";
    }

    // print the last line in light_yellow(14) and return to white(7)
    SetConsoleTextAttribute(output_handle, 14);
    cout << paddingInstructions << instructions_text[instructions_text_lenght - 1] << "\n";
    SetConsoleTextAttribute(output_handle, 7);


    getch();
}

void displayScores() {
    /*
    Function that displays the leaderboard of the game 
    input: none
    output: print the scores of the game and wait for the user input
    */
    map<int, string> scoresMap;
    printTitle();
    string leaderboard_header = "Puntajes";
    // 6 is the color code for yellow
    SetConsoleTextAttribute(output_handle, 6);
    cout << getPaddingToCenter(leaderboard_header.length() + 2) << leaderboard_header << endl << endl;
    
    ifstream infile("scores.txt");
    if (infile.is_open()) {
        string line;
        // 14 is the color code for light yellow
        SetConsoleTextAttribute(output_handle, 14);
        while (getline(infile, line)) {
            string name;
            int score;
            istringstream iss(line);
            if (iss >> name >> score) {
                scoresMap[score] = name;
            }
        }
        infile.close();
        for (const auto& pair : scoresMap) {
            SetConsoleTextAttribute(output_handle, 6);
            cout << getPaddingToCenter(leaderboard_header.length() + 2) << pair.second << ": " << pair.first << endl;
        }
        // return to white
        SetConsoleTextAttribute(output_handle, 7);

        string leaderboard_footer = "Presiona cualquier tecla para volver al menu principal";
        cout << endl << getPaddingToCenter(leaderboard_footer.length()) << leaderboard_footer << endl;
        getch();
    }
}

map<string, string> startGame(){
    /*
    Function that starts the game 
    input: none
    output: start the game and return if the user won or not
    */

    // basic variables of the game
    int number_of_rounds = 7;
    string rng_game_number_str = to_string( randomIntFourDiffDigit());
    map<string, string> game_variables = {
        {"state", "not won"},
        {"score", "0"},
        {"player", ""},
    }; 

    string welcome_text[] = {
        " ¡Bienvenido al juego de los muertos y heridos!",
        " El numero a adivinar es de 4 digitos distintos. ",
    };
    string welcome_margin = getPaddingToCenter(welcome_text[0].length() + 2 );
    string round_margin   = getPaddingToCenter(30);

    // variables to store the user input 
    string user_input = " ";

    // print the title and introduction 
    printTitle();
    for (string welcome : welcome_text) {
       cout << welcome_margin << welcome << "\n"; 
    }
    cout << "\n";
    // start the game
    for(int actual_round = 1; (actual_round <= number_of_rounds) and (game_variables["state"] == "not won"); actual_round++){
        // round template
        cout << round_margin;
        displayHearts( 8 - actual_round);
        SetConsoleTextAttribute(output_handle, 7);
        cout << round_margin << "Turno " << actual_round << ": ";
        // get the user input
        cin >> user_input;
        cin.ignore();
        while(validRoundInput(user_input) == false){
            cout << round_margin << "Número Incorrecto: ";
            Beep(350,100);
            Beep(350,100);
            cin >> user_input;
            cin.ignore();
        }
        
        // check if the user input is the same as the number of the game
        if(user_input == rng_game_number_str){
            // user has won
            game_variables["state"] = "win";
            game_variables["score"] = to_string(actual_round);
        }
        else if(user_input == "0000"){
            // run backdoor
            cout << "                                  " <<rng_game_number_str;
            Sleep(1000);
            cout << "\b \r                                                                        \r";
            actual_round -= 1;
        }
        else if(user_input == "exit" or user_input == "quit" or user_input == "stop"){
            // exit the game 
            game_variables["state"] = "exit";
        }
        else{ 
            // get the number of deads and wounded
            int deads = getDead(user_input, rng_game_number_str);
            int wounded = getWounded(user_input, rng_game_number_str);

            // print the number of deads and wounded
            // light_red(12), 
            int report_text_color = 12;

            if(deads == 3 or wounded == 3){
                // light_yellow(14)
                report_text_color = 14;
            }
            else if(wounded == 4){
                // light_green(10)
                report_text_color = 10;
            }

            // print the number of deads and wounded
            SetConsoleTextAttribute(output_handle, report_text_color);
            cout << round_margin << "Muertos: " << deads << "        Heridos: " << wounded << "\n";
            // return to white(7)
            SetConsoleTextAttribute(output_handle, 7);
        }

        cout << "\n";
    }

    if(game_variables["state"] == "win"){
        // green(2), white(7)
        SetConsoleTextAttribute(output_handle, 2);
        cout << round_margin << "¡Ganaste! Introduce tu nombre (sin espacios): ";
        cin >> game_variables["player"];
        cin.ignore();
        SetConsoleTextAttribute(output_handle, 7);

        Sleep(1000);
    }
    else if(game_variables["state"] == "not won"){
        // red(4), white(7)
        SetConsoleTextAttribute(output_handle, 4);
        cout << round_margin << "Perdiste, el número era " 
            << rng_game_number_str << '\n';
        SetConsoleTextAttribute(output_handle, 7);

        Sleep(2000);
    }
    
    return game_variables;
}

int main(){
    // resize console
    HANDLE wHnd = GetStdHandle(STD_OUTPUT_HANDLE);
    SMALL_RECT windowSize = {0, 0, 79, 50};
    SetConsoleWindowInfo(wHnd, 1, &windowSize);
    // set random source
    srand(time(NULL)); 
    // set language
    setlocale(LC_ALL, "es_ES.UTF-8");
    // resize console


    // set console output handle
    string round_margin   = getPaddingToCenter(30);


    // start the game
    bool game_running = true;
    while(game_running){
        clearConsole();
        int menu_user_option = mainMenu();
        clearConsole();
    
        // start the game
        if(menu_user_option == 1){
            map<string, string> game_result = startGame();
            clearConsole();

            // Colors: 2 = green, 4 = red, 7 = white
            if(game_result["state"] == "win"){
            	
                SMALL_RECT windowSize = {0, 0, 100, 30};
                SetConsoleWindowInfo(wHnd, 1, &windowSize);
            	
                SetConsoleTextAttribute(output_handle, 2);
                int scoreInt = stoi(game_result["score"]);
                saveScore(game_result["player"], scoreInt);
                winScreen();
                SetConsoleTextAttribute(output_handle, 7);
            }
            else if(game_result["state"] == "not won"){
            	
                SMALL_RECT windowSize = {0, 0, 100, 30};
                SetConsoleWindowInfo(wHnd, 1, &windowSize);            	

                SetConsoleTextAttribute(output_handle, 4);
                loseScreen();
                SetConsoleTextAttribute(output_handle, 7);
            }
            clearConsole();
        }
        // show the instructions
        else if(menu_user_option == 2){
            // show the instructions and wait for the user press key to continue
            printInstructions();
        }
        // show leaderboard 
        else if(menu_user_option == 3){
            // show the leaderboard and wait for the user press key to continue
            displayScores();
        }
        // exit the game
        else if(menu_user_option == 4){
            game_running = false;
        }
    }

    return 0;
}
