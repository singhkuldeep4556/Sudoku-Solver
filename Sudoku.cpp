//sky is the limit
// backtracking
#include<bits/stdc++.h>
using namespace std;
class Board{
	int grid[9][9];
	public:
		Board();
		void getBoard();
		bool valid();
		bool checkRow(int,int);
		bool checkCol(int,int);
		bool checkSubgrid(int,int,int);
		bool isSafe(int,int,int );
		bool findUnassignedLocation(int& ,int&);
		void printBoard();
		bool solveSudoku();
};
Board :: Board(){ //constructs an empty board
	for(int i = 0;i<9;i++){
		for(int j = 0;j<9;j++)
			grid[i][j] = 0;
	}
}
void Board :: getBoard(){ //takes board as an input from user
	cout<<"Enter Sudoku Values : (0 -->for Empty Cell) \n";
	for(int i=0;i<9;i++){
		for(int j = 0;j<9;j++)
			cin>>grid[i][j];
	}
}
bool Board :: valid(){ //checks whether a given board is valid or not
	for(int i = 0;i<9;i++){
		for(int j = 0;j<9;j++){
			int num = grid[i][j];
			grid[i][j] = 0;
			if(num && !(isSafe(i,j,num))){
				return false;
			}
			grid[i][j] = num;
		}
	}
	return true;
}
bool Board :: checkRow(int row,int num){ // checks validity for row
	for(int i = 0;i<9;i++){
		if(grid[row][i] == num)
			return false;
	}
	return true;
}
bool Board :: checkCol(int col,int num){ //checks validity for column
	for(int i = 0;i<9;i++){
		if(grid[i][col] == num)
			return false;
	}
	return true;
}
bool Board :: checkSubgrid(int row,int col,int num){ //checks validity for current subgrid(3*3)
	row = row - row%3;
	col = col - col%3;
	for(int i = 0 ;i<3;i++){
		for(int j = 0;j<3;j++){
			if(grid[row+i][col+j] == num)
				return false;
		}
	}
	return true;
}
bool Board :: isSafe(int r,int c,int num){ //checks whether a cell is safe
	if(checkRow(r,num) && checkCol(c,num) && checkSubgrid(r,c,num))
		return true;
	return false;
}
bool Board :: findUnassignedLocation(int &row,int &col){ // finds any unassigned cell
	for(int i = 0;i<9;i++){
		for(int j = 0;j<9;j++){
			if(grid[i][j] == 0){
				row = i;
				col = j;
				return true;
			}
		}
	}
	return false;
}
void Board :: printBoard(){ // prints the Suduko Board
	for(int i=0;i<9;i++){
		for(int j = 0;j<9;j++)
			cout<<grid[i][j]<<" ";
		cout<<"\n";
	}
}
bool Board :: solveSudoku(){ // solves Sudoku
	int row,col;
	if(!findUnassignedLocation(row,col)){
		return true; // Solution is found
	}
	for(int num = 1;num<=9; num++){
		if(isSafe(row,col,num)){ // is it safe to assign this val
			grid[row][col] = num; //assign it
			if(solveSudoku())// check whether this assignment leads to solution
				return true;  // success
			grid[row][col] = 0; // failure so free this cell
		}
	}
	return false;//triggers backtracking
}

int main(){
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	Board b;
	b.getBoard();
	if(b.valid()){
		if(b.solveSudoku()){
			cout<<"The Solution for the given Sudoku is:\n";
			b.printBoard();
		}
		else{
			cout<<"No Solution exists for the entered Sudoku";
		}
	}
	else cout<<"Invalid Sudoku Board";
	return 0;
}
