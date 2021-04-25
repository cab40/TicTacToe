/* program steps
1. display the board on the terminal
2. allow each player to input their X/O in the desired location
3. display the X/O in the appropriate location on the board
3. alternate players to input their X/O
4. check for a winner if:
  a) a vertical combination of 4 X's or O's is achieved
  b) a horizontal combination of 4 X's or O's is achieved
  c) a diagonal combination of 4 X's or O's is achieved
5. Track the scores of each player
6. if no winner, determine when it's a tie (board is filled and no winning cases is achieved)
7. Display the results and a statement corresponding to the outcome
8. ask if the player would like to play again
9. if yes, reset the board and alternate starting players
10. if no, exit the game

test values/outputs
to test the program, I ran various scenarios
  1) filling the board with no winning cases 
    output: displayed the filled board, a statement indicating it's a tie, asks if we would like to play again
  2) vertical/horizontal/diagonal combination win
    output: displayed the board with the combination, a statement indicating player X/O won as soon as 
    winning case is acheived, asks if we would like to play again 
  3) multiple rounds
    output: displays the correct score for each player (includes previous rounds' scores)
  4) exiting the game
    ouput: ends the game/exits the code
  5) playing again
    output: clears X's and O's and asks the alternate player
all outputs have been verified

limitations:
players can only play on a 4 by 4 grid space, entering numbers less than 1 or greater than 16 will not result anything
*/

#include <iostream>
#include <iomanip>

// declaring functions that simulate the Tic Tac Toe game
void output(int board[4][4]);     
bool check_win(int board[4][4]); 
bool check_tie(int board[4][4]);  
void replace_values(int board[4][4], bool player, int location);  
void game_play(bool turn, int board[4][4], int *playerX_score, int *playerO_score); // 
void game(int board[4][4]);

// a function that displays the board
//  INPUT: no input
//  PARAMETERS: the elements in the 'board' array
//  OUTPUT: displays integers 1 - 16 in a 4 by 4 grid, does not return anything
void output(int board[4][4]){
  std::cout.setf(std::ios::fixed); //set fixed precision
  std::cout.setf(std::ios::showpoint); //always show the point

  for (int row = 0; row<4; row++){
    for (int col = 0; col<4; col++){
      if (board[row][col] > 16){
        std::cout<< std::setw(5)<<char(board[row][col]); //casts to char
      }
      else std::cout << std::setw(5)<<board[row][col];
    }
    std::cout<<std::endl;
  }
}

// a function that checks for a winner (vertical, horizontal or diagonal combination of 4 X's or 4 O's)
//  INPUT: no input
//  PARAMETERS: the elements in the 'board' array
//  OUTPUT: returns a boolean value to the function
bool check_win(int board[4][4]){ 
  bool diagonal_1 = (board[0][0] == board[1][1] && board[0][0] == board[2][2] && board[0][0] == board[3][3]);   //diagonal cases
  bool diagonal_2 =  (board[0][3] == board[1][2] && board[0][3] == board[2][1] && board[0][3] == board[3][0]);
  
  for (int i = 0; i < 4; i++){  
    if (board[i][0] == board[i][1] && board[i][0] == board[i][2] && board[i][0] == board[i][3]){    //check rows
      return true;
    }
    else if (board[0][i] == board[1][i] && board[0][i] == board[2][i] && board[0][i] == board[3][i]){ //check columns
      return true;
    }
  } 
  if (diagonal_1 || diagonal_2) return true; // check diagonals
  return false;
}

// a function that checks for tie (board filled with no winner)
//  INPUT: no input
//  PARAMETERS: the elements in the 'board' array
//  OUTPUT: returns a boolean value to the function
bool check_tie(int board[4][4]){
  int match = 0;

  for (int row = 0; row < 4; row++){  
    for (int col = 0; col < 4; col++){
      if (board[row][col] == 'X' || board[row][col] == 'O') match += 1;   //checks each element in the array if it's an X or O
    } 
  }
  if (match == 16) return true; // all elements are X's or O's
  return false;
}

// a function that enables the players to place their X's and O's in the desired location
//  INPUT: no input
//  PARAMETERS: the elements in the 'board' array, the corresponding player, the integer location on the board
//  OUTPUT: does not return or ouput anything
void replace_values(int board[4][4], bool player, int location){
  const int X = int('X');
  const int O = int('O'); //for readability (can type in X instead of 88 or O instead of 79)
  for (int row = 0; row<4; row++){
    for (int col = 0; col<4; col++){    //find the location of the value and assign it X or O
      if (board[row][col]==location){    
        if (player == 1) board[row][col] = O;
        else board[row][col] = X; 
      } //when outputting, check that if the value is over 16, then cast to char.
    }
  }
}

// a function that enables the players to play the game and monitor the results 
//  INPUT: integer - board location
//  PARAMETERS: alternating turns by using a boolean, the elements in the 'board' array, each players score
//  OUTPUT: displays a statement correlating to the outcome and the overall score for each player, does not return anything
void game_play(bool turn, int board[4][4], int *playerX_score, int *playerO_score){
  int location;
  char player;

  // repeatedly asks each player to input their X/O until the board is filled
  do{   
    if (turn == 1) player = 'O';
    else if(turn == 0)player = 'X';
    output(board);
    std::cout<<"Player "<<player<<" , please enter the value of where you'd like to play: ";
    std::cin>>location;
    replace_values(board, turn, location);
    turn = !turn; //swaps player

    // displays when a tie occurs
    if (check_tie(board)){
      output(board);
      std::cout << "It's a tie! No Winner this time.\n";
    }
  } while(check_win(board)==false && check_tie(board)==false);

  // displays when a win occurs and tracks each players result after each round
  if (check_win(board)==true){
    turn = !turn;
    if (turn == 0) {
      player = 'X';
      *playerX_score +=1 ;
    }
    else if(turn == 1){
      player = 'O';
      *playerO_score += 1;
    }
    output(board);
    std::cout << "Congratulations, player " << player << " wins!"<< std::endl;
  }
  // displays the result of each player
  std::cout<<"Player X wins: " << *playerX_score << "\nPlayer O wins: " << *playerO_score <<std::endl;
}

// a function that enables players to play again (reseting the game) and alternates starting players
//  INPUT: character - yes or no to playing again
//  PARAMETERS:  the elements in the 'board' array
//  OUTPUT: displays a question regarding playing again, does not return anything
void game(int board[4][4]){
  int game_num = 0;
  char ans;
  bool play_again = true;
  bool pO = 1;
  bool pX = 0;
  int playerX_score = 0;
  int playerO_score = 0;

  while (play_again){
    int value = 1;
    game_num++;
    if (game_num%2 == 0) game_play(pO, board, &playerX_score, &playerO_score); //these set the starter player for each game
    else game_play(pX, board, &playerX_score, &playerO_score);

    std::cout << "Would you like to play again? (Y/N)" << std::endl;
    std::cin >> ans;
    if (ans=='N') play_again = false;
    //clear board for next game
    for (int row = 0; row < 4; row++){
      for (int col = 0; col < 4; col++){
      board[row][col] = value++;
      }
    }
  }
}

// stores the 'board' array and executes the game function
int main() {
  
  int board[4][4] = {{1,2,3,4},{5,6,7,8},{9,10,11,12},{13,14,15,16}}; //values will be changed to their ascii codes (X=88, O=79) then cast to chars for output

  game(board);

  return 0;
}

