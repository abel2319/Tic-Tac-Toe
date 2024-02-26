// Author: Abel KPOHINTO
// Github account: abel2319

#include<iostream>
using namespace std;


void _help_(){

  cout<<"To put or deplace a pawn you must choose between 0 and 8 like you can see below\n\n";
  cout<<"        0 | 1 | 2    \n";
  cout<<"       ---|---|---   \n";
  cout<<"        3 | 4 | 5    \n";
  cout<<"       ---|---|---   \n";
  cout<<"        6 | 7 | 8    \n";
  cout<<"\nWhen you already have 3 pawns, to move it, you must specify its old location (0-8) and its new location just like that old_loc -> new_loc\n";
  cout<<"Example: To move a pawn from 0 to 5 you write : 0 -> 5\n";
  cout<<"Good game then...\n";
}

void displayGrid(char space[3][3]){
  cout<<"     "<<space[0][0]<<" | "<<space[0][1]<<" | "<< space[0][2]<<"       \n";
  cout<<"    ---|---|---      \n";
  cout<<"     "<<space[1][0]<<" | "<<space[1][1]<<" | "<< space[1][2]<<"       \n";
  cout<<"    ---|---|---      \n";
  cout<<"     "<<space[2][0]<<" | "<<space[2][1]<<" | "<< space[2][2]<<"       \n";

}

bool wins(char space[3][3]){
  for (int i = 0; i < 3; i++) {
    if((space[i][0] == space[i][1] && space[i][0] == space[i][2]) ||
        (space[0][i] == space [1][i] && space[0][i] == space[2][i]))
      return true;
  }
  if((space[0][0] == space[1][1] && space[0][0] == space[2][2]) ||
      (space[0][2] == space [1][1] && space[0][2] == space[2][0]))
    return true;

  return false;
}


/*
 * Check if loc is between 0 and 8
 */
bool checkLoc(int loc){
  if(loc < 0 || loc > 8)
    return true;

  return false;
}

/*
 * Check if a positon on the board is empty
 *Args:
 *   space(char **): board
 *   loc (int): position
 *
 * return true or false
 */
bool checkEmptyPlace(char space[3][3], int loc){
  if(space[loc / 3][loc % 3] == 'x' ||
      space[loc / 3][loc % 3] == 'o')
    return false;

  return true;
}

/*
 * Place a pawn to the board
 * Args:
 *  space (char **): board
 *  loc (int): position
 *  sw (int): 0 if player1, 1 if player2
 */
void placement(char space[3][3], int loc, int sw)
{
  if(sw == 0)
    space[loc / 3][loc % 3] = 'x';
  else
    space[loc / 3][loc % 3] = 'o';
}

bool checkOldPlace(char space[3][3], int old_loc,int sw)
{
  if(sw == 0){
    if(space[old_loc / 3][old_loc % 3] == 'x')
      return true;
  }
  else
    if(space[old_loc / 3][old_loc % 3] == 'o')
      return true;

  return false;
}

void movePawn(char space[3][3], int old_loc, int new_loc, int sw)
{
  if(sw == 0){
    space[old_loc / 3][old_loc % 3] = ' ';
    space[new_loc / 3][new_loc % 3] = 'x';
  }
  else {
    space[old_loc / 3][old_loc % 3] = '.';
    space[new_loc / 3][new_loc % 3] = 'o';
  }
}

int main(){

  string player1 ="", player2="";
  char space[3][3] = {
    {' ', '.', ' '},
    {'.', '.', ' '},
    {' ', ' ', '.'},
  };
  int sw = 0; //switch input from players
  int ctl = 0; //check if players have already 3 pawns

  int loc = 0; //location of a pawn
  string s_loc = "";
  int new_loc = 0, old_loc = 0;
  
  _help_();

  cout<<"Enter the name of the first player : ";
  getline(cin, player1);
  cout<<"Enter the name of the second player : ";
  getline(cin, player2);

  cout<<"\nOkay!! Welcome "<< player1 << " and "<< player2<<" ...\n";
  cout<<player1<<" plays with X and "<< player2 << " with O \n";

  while(!wins(space))
  {
    if (ctl < 6) {
      
      if (sw == 0)
        cout<<"Choose a place "<<player1<<" : ";
      else
        cout<<"Choose a place "<<player2<<" : ";

      cin >> loc;
      while(checkLoc(loc) && checkEmptyPlace(space, loc))
      {
        cout<<"Your choice is out of the range (0-8), or the position is already taken.\nMake another one : ";
        cin>>loc;
      }
      ctl++;
      getchar(); //tae the enter character
      placement(space, loc, sw); //place a pawn to the position chosen
    }
    else {
      //if each player has 3 pawns on the board
      //He must change position of one of them
      //we need the old position and the new position
      //let code it
      if(sw == 0)
        cout<<player1<<" moves a pawn (old -> new) : ";
      else
        cout<<player2<<" moves a pawn (old -> new) : ";

      getline(cin, s_loc);
      new_loc = s_loc.back() - '0';
      old_loc = s_loc[0] - '0';

      //We need to chaeck if old place contain the right pawn 
      //and if the new place is empty
      while(checkLoc(old_loc) ||
          checkLoc(new_loc) ||
          !checkOldPlace(space, old_loc, sw) ||
          !checkEmptyPlace(space, new_loc))
      {
        cout<<"Your choice is out of the range (0-8), or the place is already taken.\nMake another one (old -> new) : ";
        getline(cin, s_loc);
        new_loc = s_loc.back() - '0';
        old_loc = s_loc[0] - '0';
        cout<<old_loc<<" "<<new_loc<<"\n";
      }
      //We need a function to move a pawn
      movePawn(space, old_loc, new_loc, sw);
    }

    displayGrid(space);
    sw = (sw + 1) % 2;
  }

  if (sw == 0)
    cout<<"\n"<<player2<<" wins !!! Congratulation ... <3 ... ^_^\n";
  else
    cout<<"\n"<<player1<<" wins !!! Congratulation ... <3 ... ^_^\n";

  //Good

  return 0;
}
