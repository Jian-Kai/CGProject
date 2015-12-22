#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<string>
#include<fstream>
using namespace std;

#define SIZE 200
char line[SIZE];
int Count = 0;
string layer;
double point;
int main(){
    fstream fin;
    fin.open("D:/HomeWork/CG/FinalProject/project/blender_half_resampled_black.svg",ios::in);
    while(fin.getline(line,sizeof(line),'\n')){

        for(int i = 0; i < sizeof(line); i++){
                if(line[i] == 'l' && line[i + 4] == 'r'){
                    for(int j = i ; j < (i + 6); j++){
                        layer = layer + line[j];
                    }
                      cout<< layer ;
                      layer = "";
                }
                else if(line[i] == 'M'){
                        printf("M:");
                    for(int j = i; j <= (i+17); j++){
                        if(isdigit(line[j]) || line[j] =='.'){
                            layer = layer + line[j];
                        }
                        else if(line[j] == ' ' || line[j] == ','){
                            if(layer != ""){
                                point = atof(layer.c_str());
                                printf("%.3f", point);
                                layer = "";
                                if(line[j] == ','){
                                    printf(", ");
                                }
                            }
                        }
                    }
                }
                else if(line[i] == 'C' && line[i-1] == ' '){
                        printf("  C:");
                    for(int j = i ; j < (i+50); j++){
                        if(isdigit(line[j]) || line[j] =='.'){
                            layer = layer + line[j];
                        }
                        else if(line[j] == ' ' || line[j] == ',' || line[j] == '"'){
                            if(layer != ""){
                                point = atof(layer.c_str());
                                printf("%.3f", point);
                                layer = "";
                                if(line[j] == ','){
                                    printf(",");
                                }
                                else if(line[j] == ' '){
                                    printf(" ");
                                }
                            }
                        }
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
