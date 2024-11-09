/**
* ENGG1110 24R1 Problem Solving by Programming
 *
 * Course Project
 *
 * I declare that the project here submitted is original
 * except for source material explicitly acknowledged,
 * and that the same or closely related material has not been
 * previously submitted for another course.
 * I also acknowledge that I am aware of University policy a nd
 * regulations on honesty in academic work, and of the disciplinary
 * guidelines and procedures applicable to breaches of such
 * policy and regulations, as contained in the website.
 *
 * University Guideline on Academic Honesty:
 *   https://www.cuhk.edu.hk/policy/academichonesty/
 *
 * Student Name  : Chau Sze Kan
 * Student ID    : 1155234640
 * Class/Section : ENGG1110D
 * Date          : 6/11/2024
 */

/****************************************/
/* Header File Declaration */
#include <stdio.h>
#include <stdlib.h>
/* NO other header files are allowed */
/****************************************/
/****************************************/
/* Given Global Variables and Definition */
#define H 6  // height
#define W 6  // width

char candies[] = {'*', '#', '@', '%'};
/* NO other global variables are allowed */
/****************************************/

/****************************************/

/* Part I Functions */
void initGameBoard(int board[][W], int board_sample[][W]);
void printGameBoard(int board[][W]);
int askForSwap(int board[][W]);
void swap(int board[][6], int row1, int col1, int row2, int col2) ;
int findAndRemoveMatch(int board[][W], int row, int col);
int isMatching(int board[6][6], int row, int col);
/* Part II Functions */
int initGameBoardFromFile(int board[][W], int stacks[]);
void applyGravity(int board[][W]);
int fillEmpty(int board[][W], int stacks[], int current, int numCandies);
int cascade(int board[][6], int stacks[], int current, int numCandies);

/****************************************/
// Function Definitions/

/**
 * Main() will call this function in the beginning.
 * initGameBoard() load the game board with the pre-defined board_sample array
 * @param board The gameboard the game is using
 * @param board_sample The given game board sample values
 */
void initGameBoard(int board[H][W], int board_sample[][W]) {
  for(int i=0;i<H ;i++){
    for (int j=0;j<W;j++){
      board[i][j]=candies[board_sample[i][j]];
    }
  }
}

/**
 * [Part II]
 * Main() will call this function in the beginning.
 * initGameBoardFromFile will load the file "board.txt" to load two information:
 * (1) Game Board ; (2) Candy Stacks
 * If the file loading is unsuccessful, quit the program with the error message.
 * @param board The Game board the program is using.
 * @param stacks The stack array to store candies. It will be inititalized from the file.
 * @return The number of candies in the stack.
 */
int initGameBoardFromFile(int board[][W], int stacks[]) {

}

/**
 * Various functions will call this.
 * printGameBoard() will print the current game board in the specified format
 * @param board The game board the game is using
 */
void printGameBoard(int board[][W]) {
  printf("=====\n");
  printf(" | 0 | 1 | 2 | 3 | 4 | 5 |\n");
  for(int i=0;i<H ;i++){
    printf("%d",i);
    for (int j=0;j<W;j++){
      printf("| %c ",board[i][j]);
    }
    printf("|\n");
  }
}

/**
 * Main() will call this function.
 * askForSwap() will perform the major game logic by (1) asking the users which candy to swap
 * (2)Validate whether the swapping can be done (3) Perform the swapping
 * @param board The game board the game is using.
 * @return 0 if the error is encountered (e.g. Coordinates out of bound);
 * 1 if swapping is successfully
 */
int askForSwap(int board[][W]) {
  int x=0,y=0;
  char dir=' ';
  printf("Enter the coordinate (row, column) of the candy:");
  scanf("%d%d",&y,&x);
  while (getchar() != '\n');
  if(x<0 || y<0||y>=H||x>=W){
    printf("Coordinates Out of Bound.\n");
    return 0;
  }
  printf("Enter the direction to swap (U for Up, D for Down, L for Left, R for Right):");
  scanf(" %c",&dir);
  if (dir!='U'&&dir!='D'&&dir!='L'&&dir!='R'){
    printf("Wrong Direction Input.\n");
    return 0;
  }
  int newx=x,newy=y;
  if (dir=='U'){
    newy--;
  }
  else if (dir=='D'){
    newy++;
  }
  else if (dir=='L'){
    newx--;
  }
  else if (dir=='R'){
    newx++;
  }
  if(dir=='U'&&(newy)<0||dir=='D'&&(newy)>=H||dir=='L'&&(newx)<0||dir=='R'&&(newx)>=W){
    printf("Move Out of Bound.\n");
    return 0;
  }
  if(board[newy][newx]==' '){
    printf("Empty Cell Selected.\n");
    return 0;
  }
  swap(board,y,x,newy,newx);
  if (!(findAndRemoveMatch(board,y,x)||findAndRemoveMatch(board,newy,newx))){
    swap(board,newy,newx,y,x);
    printGameBoard(board);
    printf("No Match Found\n");
    return 0;
  }
  return 1;
}

/**
 * Various functions will call this
 * swap() will perform value swapping of two cells,
 * with the given source and destination coordinates respectively.
 * @param board the game board the game is using
 * @param row1 The row number of the source cell
 * @param col1 The column number of the source cell
 * @param row2 The row number of the destination cell
 * @param col2 The column number of the destination cell
 */
void swap(int board[][6], int row1, int col1, int row2, int col2) {
    int temp= board[row1][col1];
    board[row1][col1]=board[row2][col2];
    board[row2][col2]=temp;
}

/**
 * Various functions will call this.
 * findAndRemoveMatch() will find possible matches at the given coordinates (row,col)
 * for all four directions (Up, Down, Left, Right).
 * If found, turn the cell to ASCII 32 (' ').
 *
 * @param board The game board the game is using
 * @param row The row number of the given coordinate
 * @param col The column number of the given coordinate
 * @return 1 if there is a match in the board, 0 if there is not.
 */
int findAndRemoveMatch(int board[][W], int row, int col){
  for (int i=col-2;i<=col;i++){
    if(i >= 0 && i + 2 < W){
      if(board[row][i]==board[row][i+1]&&board[row][i]==board[row][i+2]){
          printf("Horizontal Match found at row %d!\n",row);
          board[row][i]=' ';
          board[row][i+1]=' ';
          board[row][i+2]=' ';
          return 1;
        }
      }
  }
  for (int i=row-2;i<=row;i++){
    if(i >= 0 && i + 2 < H){
      if(board[i][col]==board[i+1][col]&&board[i][col]==board[i+2][col]){
        printf("Vertical Match found at column %d!\n",col);
        board[i][col]=' ';
        board[i+1][col]=' ';
        board[i+2][col]=' ';
        return 1;
      }
    }
  }
    return 0;
}
/**
 * Main() function will call this.
 * isGameOver() is to check whether there exists a game over situation, i.e.
 * no more match can be made under the current board scenerio.
 *
 * @param board The game board the game is using.
 * @return 1 if it is game over; 0 if it isn't .
 */
int isGameOver(int board[][W]) {
  for (int i=0;i<H;i++){
    for (int j=0;j<W;j++){
      if(isMatching(board,i,j)){
        
        return 0;
      }
    }
  }
  return 1;
}

/**
 * isGameOver() will call this function.
 * isMatching will check if there is at least 1 match-three at the given coordinate (row,col)
 * for four directions (Top,Down,Left,Right).
 * @param board The game board the game is using.
 * @param row The row number of the target cell
 * @param col The column number of the target cell
 * @return 1 if there is at least 1 match in any direction; 0 if there is not.
 */
int isMatching(int board[6][6], int row, int col) {
  if(board[row][col]!=' '){
    int nwrow=row+1,nwcol=col;
    swap(board,row,col,nwrow,nwcol);
    if(board[nwrow][nwcol]!=' '&&(nwrow>=0 &&nwrow<H)&&(nwcol>=0 &&nwcol<W)){
      for (int i=nwcol-2;i<=nwcol;i++){
        if(i >= 0 && i + 2 < W){
          if(board[nwrow][i]==board[nwrow][i+1]&&board[nwrow][i]==board[nwrow][i+2]){
              
              swap(board,nwrow,nwcol,row,col);
              return 1;
            }
          }
      }
      for (int i=nwrow-2;i<=nwrow;i++){
        if(i >= 0 && i + 2 < H){
          if(board[i][nwcol]==board[i+1][nwcol]&&board[i][nwcol]==board[i+2][nwcol]){
            
            swap(board,nwrow,nwcol,row,col);
            return 1;
          }
        }
      }
    }
    swap(board,nwrow,nwcol,row,col);
    nwrow=row-1,nwcol=col;
    swap(board,row,col,nwrow,nwcol);
    if(board[nwrow][nwcol]!=' '&&(nwrow>=0 &&nwrow<H)&&(nwcol>=0 &&nwcol<W)){
      for (int i=nwcol-2;i<=nwcol;i++){
        if(i >= 0 && i + 2 < W){
          if(board[nwrow][i]==board[nwrow][i+1]&&board[nwrow][i]==board[nwrow][i+2]){
              
              swap(board,nwrow,nwcol,row,col);
              return 1;
            }
          }
      }
      for (int i=nwrow-2;i<=nwrow;i++){
        if(i >= 0 && i + 2 < H){
          if(board[i][nwcol]==board[i+1][nwcol]&&board[i][nwcol]==board[i+2][nwcol]){
            
            swap(board,nwrow,nwcol,row,col);
            return 1;
          }
        }
      }
    }
    swap(board,nwrow,nwcol,row,col);
    nwrow=row,nwcol=col+1;
    swap(board,row,col,nwrow,nwcol);
    if(board[nwrow][nwcol]!=' '&&(nwrow>=0 &&nwrow<H)&&(nwcol>=0 &&nwcol<W)){
      for (int i=nwcol-2;i<=nwcol;i++){
        if(i >= 0 && i + 2 < W){
          if(board[nwrow][i]==board[nwrow][i+1]&&board[nwrow][i]==board[nwrow][i+2]){
              
              swap(board,nwrow,nwcol,row,col);
              return 1;
            }
          }
      }
      for (int i=nwrow-2;i<=nwrow;i++){
        if(i >= 0 && i + 2 < H){
          if(board[i][nwcol]==board[i+1][nwcol]&&board[i][nwcol]==board[i+2][nwcol]){
            
            swap(board,nwrow,nwcol,row,col);
            return 1;
          }
        }
      }
    }
    swap(board,nwrow,nwcol,row,col);
    nwrow=row,nwcol=col-1;
    swap(board,row,col,nwrow,nwcol);
    
    if(board[nwrow][nwcol]!=' '&&(nwrow>=0 &&nwrow<H)&&(nwcol>=0 &&nwcol<W)){
      for (int i=nwcol-2;i<=nwcol;i++){
        if(i >= 0 && i + 2 < W){
          if(board[nwrow][i]==board[nwrow][i+1]&&board[nwrow][i]==board[nwrow][i+2]){
          
              swap(board,nwrow,nwcol,row,col); 
              return 1;
            }
          }
      }
      for (int i=nwrow-2;i<=nwrow;i++){
        if(i >= 0 && i + 2 < H){
          if(board[i][nwcol]==board[i+1][nwcol]&&board[i][nwcol]==board[i+2][nwcol]){
            
            swap(board,nwrow,nwcol,row,col);
            return 1;
          }
        }
      }
    }
    swap(board,nwrow,nwcol,row,col);
  }
  return 0;
}

/**
 * [Part II]
 * askForSwap() and cascade() will call this function
 * applyGravity() will scan the all columns from left to right, and
 * if there are empty cells, it will move down the candy. Lastly, print the
 * gameboard.
 * @param board The game board the game is using
 */
void applyGravity(int board[][6]) {

}

/**
 * [Part II]
 * askForSwap() and cascade() will call this.
 * fillEmpty() will scan the columns from left to right. If there are empty cells,
 * it will fill them with candies got from the stacks, in bottom-to-top manner. Lastly,
 * print the gameboard.
 * @param board the game board the game is using
 * @param stacks the 1D array containing the candies
 * @param current the counter of the next candy location in stacks array
 * @param numCandies the total number of candies in the stacks
 * @return the updated current value, i.e. the updated counter pointing to the next
 * available candy
 */
int fillEmpty(int board[][W], int stacks[], int current, int numCandies) {
   
}

/**
 * [Part II]
 * main() function will call this
 * cascade() will continously check the board to see if there is any matches
 * and perform removal until no further matches can be found.
 * First, you can apply the gravity and fill in the empty cells.
 * Then, for each cells on the board and if it is not empty, try to call
 * findAndRemoveMatch() to remove matches if any. If there is a match,
 * print the specified message.
 * Remember to collect the return value of current in fillEmpty() such that
 * you return to the main function to update the variable.
 * @param board the game board the game is using
 * @param stacks the 1D array containing the candies
 * @param current the counter of the next candy location in stacks array
 * @param numCandies the total number of candies in the stacks
* @return the updated current value, i.e. the updated counter pointing to the next
 * available candy
 */
int cascade(int board[][6], int stacks[], int current, int numCandies) {

}
/* Main Function */
/**
 * The main function will hold the game loop and hold the game logic.
 * main() will call various functions to accompolish various tasks such as
 * initializing the game board, asking for Input, and etc.
 * It will hold an infinite loop to repeatly hold the game. If it is a game over status,
 * i.e. isGameOver() returns one (1), then it will break out of the loop and the program
 * finishes.
 *
 * @return 0
 */
int main(void) {
 // This is the variable holding a sample board value
 int board_sample[6][6] = {
  {1,3,2,0,1,0},
  {2,2,0,1,1,3},
  {1,3,3,2,3,0},
  {3,0,2,1,0,2},
  {1,0,2,3,3,2},
  {3,2,1,0,3,3}
 };

 int board[H][W] = {0}; // The game board, initialized to 0
 int stacks[100] = {0}; // Stacks array containing candy, Maximum capacity 100
 int numCandies = 0; // Number of candies in the stacks
 int current = 0; // the counter pointing to the next available candy
// You may declare more variables if needed.

 // 1. First, you may initialize the board first
 // For part 1, you may use initGameBoard() while for part 2, initGameBoardFromFile()
  
  // printf for your reference
  //printf("=====\n");
  //printf("New Round:\n");

 // Print the board using printGameBoard()

  // Call askForSwap() to ask which candy to swap and perform swapping if successful.
  // If not, print error message, shown for your reference

  // printf("Please try again.\n");

  // Otherwise, continue the game logic by applying gravity and filling empty cells
  // For part II, you may replace the above two to cascade(), as cascade() will be
  // responsible to call at that moment.

 // Check if it is a game over status. If yes, print the message and break the loop
 // printf is left for your reference.

  // printf("Game Over! No more possible moves.\n");

// Hope you enjoy the game : )
  initGameBoard(board,board_sample);
  while(1){
    printf("=====\nNew Round:\n");
    printGameBoard(board);
    if (askForSwap(board)){
      printGameBoard(board);
    }
    else {
      printf("Please try again.\n");
    }
    if(isGameOver(board)){
      printf("Game Over! No more possible moves.\n");
      break;
    }
  }
 return 0;

}