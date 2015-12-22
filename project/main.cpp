#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<fstream>
using namespace std;

#define SIZE 200
char line[SIZE];
int Count = 0;
int main(){
    fstream fin;
    fin.open("D:/HomeWork/CG/FinalProject/project/blender_half_resampled_black.svg",ios::in);
    while(fin.getline(line,sizeof(line),'\n')){

        for(int i = 0; i < sizeof(line); i++){
                if(line[i] == 'M'){
                        printf("M:");
                    for(int j = i ; j < (i+17); j++){
                        if(isdigit(line[j]) || line[j] ==' ' || line[j] ==',' || line[j] =='.')
                        printf("%c", line[j]);
                    }
                }
                else if(line[i] == 'C' && line[i-1] == ' '){
                        printf("  C:");
                    for(int j = i ; j < (i+50); j++){
                        if(isdigit(line[j]) || line[j] ==' ' || line[j] == ',' || line[j] == '.')
                        printf("%c", line[j]);
                    }
                }

        }
        Count++;
        printf("    %d", Count);
        printf("\n");
         for(int i = 0; i < sizeof(line); i++){
            line[i] = '\0';
         }
    }


    printf("%d", Count);
    system("pause");
    return 0;
}
