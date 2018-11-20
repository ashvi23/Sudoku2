#include<stdio.h>
#include<stdlib.h>

int inrow(int**, int, int); // num to check, row 
int incol(int**, int, int); // num to check, col
int insub(int**, int, int, int); // num to check, row start, col start
int islegal(int**, int, int, int); // num to check, row start, column start
int possibilities(int**, int, int); // i, j  checks how many posibilities at position
int dashesexist(int**);
int solver(int**, int, int);
int posibilities(int** sudoku, int row, int col){
	int counter=0;
	for(int i =1; i<= 9; i++){
		int legality = islegal(sudoku, i, row, col);
		if(legality == 1){
		counter++;
		}
	}
	return counter;
}
int dashesexist (int** sudoku){
int dashes =0;
	for (int i = 0; i< 9; i++){
		for(int j =0; j< 9; j++){
			if (sudoku[i][j] == 0){
				//printf("i:%d j:%d \n", i, j );
				dashes = 1;
			}
		}
	}
return dashes;
}

int solver(int** sudoku, int i, int j){
	// base case - no more dashes
	if(dashesexist(sudoku) == 0){
		return 1;
	}
	if(dashesexist(sudoku)==1){
if(sudoku[i][j] !=0){
//int result ;
if(j<8){
j++;
 solver(sudoku, i, j);
}
if(j==8&& i<8){
solver(sudoku, i+1 , 0);
}
if(j== 8 && i==8){
solver(sudoku, i , j);
}}
			if (sudoku[i][j] == 0){
				for(int n=1; n<=9; n++){
					if(islegal(sudoku, n, i, j) == 1){
int pos = posibilities(sudoku, i, j);
							sudoku[i][j] = n;
							
							pos--;
							int result;
							if(j<8){
							result = solver(sudoku, i, j+1);

							}
							if(j==8 && i<8){
							result = solver(sudoku, i+1 , 0);

							}
							if(j== 8 && i==8){
							result = solver(sudoku, i , j);
							}
							//int result = solver(sudoku, i, j);
							if(result == 1){
							return 1;
							}
							if(dashesexist(sudoku) == 0){ 
							return 1;}
							
							sudoku[i][j] = 0;
							if(pos == 0){
							return 0;
							}
					}// islegal

					} // n
return 0;
							//return 0;
				}// if sudoku == 0
	
	}
if(dashesexist(sudoku)== 1){
return 0;
}
else{
return 1;
}
}
int inrow(int** sudoku, int target, int row){
	int exists = 0;
		for(int j =0; j< 9; j++){
			if (sudoku[row][j] == target){
				exists = 1;
			}
		}
	return exists;
}
int incol(int** sudoku, int target, int col){
	int exists = 0;
		for(int i =0; i< 9; i++){
			if (sudoku[i][col] == target){
				exists = 1;
			}
		}
	return exists;

}
int insub(int** sudoku, int target, int rowstart, int colstart){
	int exists = 0;
	for (int i = rowstart; i< rowstart+3; i++){
		for(int j =colstart; j< colstart+3; j++){
			if (sudoku[i][j] == target){
				exists = 1;
			}
		}
	}
	return exists;
}

int islegal(int** sudoku, int target, int row, int col){
	int legality = 0;
	int rowexist = inrow(sudoku, target, row);
	int colexist = incol(sudoku, target, col);
int trow = row%3;
int tcol = col%3;
int subrow = row- trow;
int subcol = col - tcol;
	int subexist = insub(sudoku, target, subrow, subcol);

	if(rowexist == 0 && colexist == 0 && subexist == 0){
	legality = 1;
	}
	return legality;
}


int main (int argc, char**argv){
FILE* fp;
int** sudoku;
char input;
int enterval; 
sudoku = (int**) malloc(9 * sizeof(int*));
	for (int i=0; i< 9; i++){
		sudoku[i] = (int*) malloc(9 * sizeof(int));
	}
	for(int i =0; i< 9; i++){
			for(int j =0; j< 9; j++){
			sudoku[i][j] = 0;
			}
	}

		if (argc!= 2){
		//printf("not enough arguments");
		return 0;
		}
		fp = fopen(argv[1], "r");
		if(fp == NULL){
			//printf("Error, no input");
			return 0;
		}
	for (int i=0; i< 9; i++){
		for (int j=0;j< 9; j++){
			fscanf(fp, "%c\t\n", &input);
			if(input == '-'){
				enterval = 0;				
				sudoku[i][j] = enterval;
			}
			else if(input == '1' ||input == '2' ||input == '3' ||input == '4' ||input == '5' ||input == '6' ||input == '7' ||input == '8' ||input == '9') {
				enterval = input-'0';
				sudoku[i][j] = enterval;
			}			
		}
	}

int solved = solver(sudoku, 0, 0);
if(dashesexist(sudoku)==1){
printf("no-solution");
return 0;
}
int* countarr;
countarr = (int*)malloc(9*sizeof(int));
for(int n = 0; n<9;n++){
countarr[n] = 0;
}


if(solved ==1){

for (int i = 0; i< 9; i++){
	for(int j =0; j< 9; j++){
		int val = sudoku[i][j];
		val = val-1;
		int curcount = countarr[val];
		countarr[val]= curcount +1;
	}

}

for (int i = 0; i< 9; i++){
	if(countarr[i] != 9){
	printf("no-solution");
	return 0;
	}
}


for (int i = 0; i< 9; i++){
		for(int j =0; j< 9; j++){
			
			if(j+1 !=9){
				printf("%d\t", sudoku[i][j]);
			}
			else if (j+1 == 9){
				printf("%d", sudoku[i][j]);
			}
		}
		if(i+1 !=9){
		printf("\n");
		}
	}
}
free(countarr);
for(int i=0; i< 9; i++){
	free(sudoku[i]);
}
fclose(fp);

return 0;
}
