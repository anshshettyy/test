/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <iostream>
#include <stdlib.h>
using namespace std;
int num=0, col = 8, row = 8;
int permutationTable[12][12] ;
int compressionPermutationTable[48] = {  20,17,11,24,1,5,3,28,15,6,21,10,23,19,12,4,26,8,16,7,27,58,113,2,41,52,31,37,47,55,30,40,51,45,33,48,44,49,39,56,34,53,36,42,50,36,29,32 };
int key48bit[48];
void partShift(int rowMin,int rowMax, int colMin, int colMax, int round)
{
        int shiftIndex = 2;
        if(round == 1 || round == 2 ||round == 9 ||round == 15) {
            shiftIndex = 1;
        }

        int Part[28];
        int index = 0;
        for(int j = rowMin; j < rowMax; j++) {
            for(int k = 0; k < colMax; k++) {
                Part[index] = permutationTable[j][k];
                index++;
            }
        }
        int temp = Part[0];
        for(int shift = 0; shift < shiftIndex; shift++) {
            temp = Part[0];
            for(int index = 0;  index < 28;  index++) {
                if(index == 27) {
                    Part[index] = temp;
                } else {
                    Part[index] = Part[index+1];
                }
            }
        }
        cout<<endl;
        index = 0;
        for(int j = rowMin; j < rowMax; j++) {
            for(int k = 0; k < colMax; k++) {
                permutationTable[j][k] = Part[index];
                index++;
            }
        }
}
int main()
{
    for(int i = 0; i  < row; i ++){
        for(int j = 0; j < col; j++) {
            num = rand() % 2;
            permutationTable[i][j] = num;
            cout<<"["<<permutationTable[i][j]<<"] ";
        }
        cout<<endl;
    }

    // removing the last 8 column
    cout<<"_______________________________"<<endl;
    cout<<"Removing the last 8 column\n";
    cout<<"_______________________________"<<endl;
    col --;
    for(int i = 0; i  < row; i ++){
        for(int j = 0; j < col; j++) {
            cout<<"["<<permutationTable[i][j]<<"] ";
        }
        cout<<endl;
    }
    for(int i = 1; i  < 17;  i ++)  // Key generation rounds
    {
        cout<<"_______________"<<endl;
        cout<<"Shifting: "<<endl;
        int leftRow = row/2 - row/2, leftCol = col;
        int rightRow = row/2, rightCol = col;

        cout<<"After Left Part Shifting: \n";
        partShift(leftRow,rightRow,0,leftCol,i);

        for(int j = leftRow; j < rightRow; j++) {
            for(int k = 0; k < leftCol; k++) {
                cout<<"["<<permutationTable[j][k]<<"] ";
            }
            cout<<endl;
        }

        cout<<"After Right Part Shifting: \n";
        partShift(rightRow,8,0,leftCol,1);

        for(int j = rightRow; j < 8; j++) {
            for(int k = 0; k < leftCol; k++) {
                cout<<"["<<permutationTable[j][k]<<"] ";
            }
            cout<<endl;
        }


        cout<<"56 Bit Key "<<i<<" \n";
        int oneDimKey[56];
        int index = 0;
        for(int i = 0; i  < row; i ++){
            for(int j = 0; j < col; j++) {
                oneDimKey[index] = permutationTable[i][j];
                cout<<"["<<permutationTable[i][j]<<"] ";
                index++;
            }
            cout<<endl;
        }

        cout<<"48 Bit Key "<<" \n";
        for(int i = 0; i  < 48; i ++){
                key48bit[i] = oneDimKey[compressionPermutationTable[i]-1];
                cout<<key48bit[i]<<",";
        }
        cout<<endl;
}
}

