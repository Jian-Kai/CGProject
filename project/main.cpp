#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<string>
#include <time.h>
#include<fstream>
#include<math.h>
#include<windows.h>
#include<GL/glut.h>
#include<GL/glu.h>

using namespace std;

#define SIZE 200
char line[SIZE];
int Count = 0;
string layer;
double point;

struct pathline{
    double SpointX;
    double EpointX;
    double Scontrol_pointX;
    double Econtrol_pointX;
    double SpointY;
    double EpointY;
    double Scontrol_pointY;
    double Econtrol_pointY;
    double SpointZ;
    double EpointZ;
    double Scontrol_pointZ;
    double Econtrol_pointZ;
};

struct points {
    double x;
    double y;
    double z;
};

static int slices = 1;


bool col0, col1;
pathline Pp[1000];
points Gp[1000];
//////////////////////////////////////////////////////////////
points graph[1000];
pathline path[1000];
//////////////////////////////////////////////////////////////
double e = 2.71828;
int pathcount = 1;
int pointcount = 1;
int space = 0;
int layercount = 0;
double Xmax, Xmin, Ymax, Ymin;
double PXmax, PXmin, PYmax, PYmin, PZmax, PZmin;

points storeP[15000][1000][5];
int repeat, enter;



void fidelity(){

    int cheak = 0;
    int time = 1;
    double E, V, F, A;
    double tem,  gap, gapp;
    double store, tempA;
    while(time <= 15000){
            printf("%d\n", time);
            for(int i = 1; i < pointcount; i++){
                Gp[i].x = (rand()%1000)+1;
                Gp[i].y = (rand()%1000)+1;
                Gp[i].z = (rand()%1000)+1;
            }
            for(int i = 1; i < pathcount; i++){
                Pp[i].SpointX = (rand()%1000)+1;
                Pp[i].SpointY = (rand()%1000)+1;
                Pp[i].SpointZ = (rand()%1000)+1;
                Pp[i].EpointX = (rand()%1000)+1;
                Pp[i].EpointY = (rand()%1000)+1;
                Pp[i].EpointZ = (rand()%1000)+1;
            }
           /* for(int i = 1; i < pathcount; i++){
                for(int j = 1; j < pointcount; j++){
                    if(path[i].SpointX == graph[j].x && path[i].SpointY == graph[j].y){
                        Pp[i].SpointX = Gp[j].x;
                        Pp[i].SpointY = Gp[j].y;
                        Pp[i].SpointZ = Gp[j].z;
                    }

                   else if(path[i].EpointX == graph[j].x && path[i].EpointY == graph[j].y){
                        Pp[i].EpointX = Gp[j].x;
                        Pp[i].EpointY = Gp[j].y;
                        Pp[i].EpointZ = Gp[j].z;
                    }
                }
            }*/

             for(int i = 1; i < pathcount; i++){
                Pp[i].SpointX = path[i].SpointX;
                Pp[i].SpointY = path[i].SpointY;
                Pp[i].EpointX = path[i].EpointX;
                Pp[i].EpointY = path[i].EpointY;
            }

            for(int k = 1; k < pathcount; k++){
                tem = abs(Pp[k].SpointX - Pp[k].EpointX)/2;
                gap = min(Pp[k].SpointX, Pp[k].EpointX);
                gapp = (Pp[k].SpointX + Pp[k].EpointX)/2;
            if(tem!=0){
                Pp[k].Scontrol_pointX = (rand()%(int)tem);
                Pp[k].Econtrol_pointX = (rand()%(int)tem);
                if(gap == Pp[k].SpointX){
                    Pp[k].Scontrol_pointX = gap + Pp[k].Scontrol_pointX ;
                    Pp[k].Econtrol_pointX = gapp + Pp[k].Econtrol_pointX;
                }
                else{
                    Pp[k].Scontrol_pointX = gapp + Pp[k].Scontrol_pointX ;
                    Pp[k].Econtrol_pointX = gap + Pp[k].Econtrol_pointX;
                }
            }
            else {
                Pp[k].Scontrol_pointX = Pp[k].SpointX;
                Pp[k].Econtrol_pointX = Pp[k].SpointX;
            }

                tem = abs(Pp[k].SpointY - Pp[k].EpointY)/2;
                gap = min(Pp[k].SpointY, Pp[k].EpointY);
                gapp = (Pp[k].SpointY + Pp[k].EpointY)/2;
            if(tem!=0){
                Pp[k].Scontrol_pointY = (rand()%(int)tem);
                Pp[k].Econtrol_pointY = (rand()%(int)tem);
                if(gap == Pp[k].SpointY){
                    Pp[k].Scontrol_pointY = gap + Pp[k].Scontrol_pointY ;
                    Pp[k].Econtrol_pointY = gapp + Pp[k].Econtrol_pointY;
                }
                else{
                    Pp[k].Scontrol_pointY = gapp + Pp[k].Scontrol_pointY ;
                    Pp[k].Econtrol_pointY = gap + Pp[k].Econtrol_pointY;
                }
            }
            else {
                Pp[k].Scontrol_pointY = Pp[k].SpointY;
                Pp[k].Econtrol_pointY = Pp[k].SpointY;
            }

                tem = abs(Pp[k].SpointZ - Pp[k].EpointZ)/2;
                gap = min(Pp[k].SpointZ, Pp[k].EpointZ);
                gapp = (Pp[k].SpointZ + Pp[k].EpointZ)/2;
                if(tem!=0){
                Pp[k].Scontrol_pointZ = (rand()%(int)tem);
                Pp[k].Econtrol_pointZ = (rand()%(int)tem);
                if(gap == Pp[k].SpointZ){
                    Pp[k].Scontrol_pointZ = gap + Pp[k].Scontrol_pointZ ;
                    Pp[k].Econtrol_pointZ = gapp + Pp[k].Econtrol_pointZ;
                }
                else{
                    Pp[k].Scontrol_pointZ = gapp + Pp[k].Scontrol_pointZ;
                    Pp[k].Econtrol_pointZ = gap + Pp[k].Econtrol_pointZ;
                }
            }
            else {
                Pp[k].Scontrol_pointZ = Pp[k].SpointZ;
                Pp[k].Econtrol_pointZ = Pp[k].SpointZ;
            }
            }
   /*        for(int k = 1; k < time; k++){
                for(int j = 1; j < pathcount; j++){
                    if(Pp[j].Scontrol_pointX == storeP[k][j][1].x && Pp[j].Scontrol_pointY == storeP[k][j][1].y && Pp[j].Scontrol_pointZ == storeP[k][j][1].z){
                        repeat++;
                    }
                    if(Pp[j].Econtrol_pointX == storeP[k][j][2].x && Pp[j].Econtrol_pointY == storeP[k][j][2].y && Pp[j].Econtrol_pointZ == storeP[k][j][2].z){
                        repeat++;
                    }
                }

                 for(int j = 1; j < pointcount; j++){
                    if(Gp[j].z == storeP[k][j][4].z && Gp[j].y == storeP[k][j][4].y && Gp[j].x == storeP[k][j][4].x){
                        repeat++;
                    }
                }

                if(repeat == (2*(pathcount-1)+(pointcount-1))){
                    for(int i= 1; i < pointcount; i++){
                        Gp[i].x = (rand()%100);
                        Gp[i].y = (rand()%100);
                        Gp[i].z = (rand()%100);
                    }
                    k = 1;
                    repeat = 0;
                }
            }*/



            for(int i = 1; i < pathcount; i++){
                Pp[i].SpointX = Pp[i].SpointX / 5 - 10;
                Pp[i].Scontrol_pointX = Pp[i].Scontrol_pointX / 5 - 10;
                Pp[i].Econtrol_pointX = Pp[i].Econtrol_pointX / 5 - 10;
                Pp[i].EpointX = Pp[i].EpointX / 5 - 10;


                Pp[i].SpointY = Pp[i].SpointY / 5 - 10;
                Pp[i].Scontrol_pointY = Pp[i].Scontrol_pointY / 5 - 10;
                Pp[i].Econtrol_pointY = Pp[i].Econtrol_pointY / 5 - 10;
                Pp[i].EpointY = Pp[i].EpointY / 5 - 10;

                Pp[i].SpointZ = Pp[i].SpointZ / 5 - 10;
                Pp[i].Scontrol_pointZ = Pp[i].Scontrol_pointZ / 5 - 10;
                Pp[i].Econtrol_pointZ = Pp[i].Econtrol_pointZ / 5 - 10;
                Pp[i].EpointZ = Pp[i].EpointZ / 5 - 10;

            }


            for(int i= 1; i < pathcount; i++){
                storeP[time][i][0].x = Pp[i].SpointX;
                storeP[time][i][1].x = Pp[i].Scontrol_pointX;
                storeP[time][i][2].x = Pp[i].Econtrol_pointX;
                storeP[time][i][3].x = Pp[i].EpointX;

                storeP[time][i][0].y = Pp[i].SpointY;
                storeP[time][i][1].y = Pp[i].Scontrol_pointY;
                storeP[time][i][2].y = Pp[i].Econtrol_pointY;
                storeP[time][i][3].y = Pp[i].EpointY;

                storeP[time][i][0].z = Pp[i].SpointZ;
                storeP[time][i][1].z = Pp[i].Scontrol_pointZ;
                storeP[time][i][2].z = Pp[i].Econtrol_pointZ;
                storeP[time][i][3].z = Pp[i].EpointZ;
            }



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            for(int i = 1; i < pathcount; i++){

                double matrix[3][4];
                matrix[0][0]=1;
                matrix[0][1]=1;
                matrix[0][2]=1;
                matrix[0][3]=1;

                matrix[1][0]=path[i].SpointX;
                matrix[1][1]=path[i].Scontrol_pointX;
                matrix[1][2]=path[i].Econtrol_pointX;
                matrix[1][3]=path[i].EpointX;

                matrix[2][0]=path[i].SpointY;
                matrix[2][1]=path[i].Scontrol_pointY;
                matrix[2][2]=path[i].Econtrol_pointY;
                matrix[2][3]=path[i].EpointY;

                double temp = matrix[1][0];

                for(int m = 0; m<4;m++){
                    matrix[1][m] = matrix[1][m] - (matrix[0][m]*(temp));
                }

                temp = matrix[2][0];

                for(int m = 0; m<4;m++){
                    matrix[2][m] = matrix[2][m] - (matrix[0][m]*(temp));
                }

                temp = matrix[2][1]/matrix[1][1];

                for(int m = 0; m<4;m++){
                    matrix[2][m] = matrix[2][m] - (matrix[1][m]*(temp));
                }

                matrix[2][3] = matrix[2][3] / matrix[2][2];

                matrix[1][3] = (matrix[1][3]-(matrix[1][2]*matrix[2][3]))/matrix[1][1];

                matrix[0][3] = matrix[0][3] - matrix[1][3] - matrix[2][3];

                //printf("%f  %f  %f  %f    %d\n", matrix[0][3],matrix[1][3],matrix[2][3], matrix[0][3]+matrix[1][3]+matrix[2][3], i);


                double q0,q1,q2,t0,t1;
                double wdv;
                double wdf;
                double wda;

                q0=matrix[0][3];
                q1=matrix[1][3];
                q2=matrix[2][3];
             // printf("q0 %f q1 %f q2 %f  %f\n",q0,q1,q2, q0+q1+q2);

                //quadruplet
                    temp = 0;
                    temp = (path[i].Scontrol_pointX-path[i].SpointX)*(path[i].Scontrol_pointX-path[i].SpointX)+(path[i].Scontrol_pointY-path[i].SpointY)*(path[i].Scontrol_pointY-path[i].SpointY);
                    if(temp < ((path[i].Econtrol_pointX-path[i].Scontrol_pointX)*(path[i].Econtrol_pointX-path[i].Scontrol_pointX)+(path[i].Econtrol_pointY-path[i].Scontrol_pointY)*(path[i].Econtrol_pointY-path[i].Scontrol_pointY)))
                        temp = ((path[i].Econtrol_pointX-path[i].Scontrol_pointX)*(path[i].Econtrol_pointX-path[i].Scontrol_pointX)+(path[i].Econtrol_pointY-path[i].Scontrol_pointY)*(path[i].Econtrol_pointY-path[i].Scontrol_pointY));
                    if(temp < ((path[i].EpointX-path[i].Econtrol_pointX)*(path[i].EpointX-path[i].Econtrol_pointX)+(path[i].EpointY-path[i].Econtrol_pointY)*(path[i].EpointY-path[i].Econtrol_pointY)))
                        temp = ((path[i].EpointX-path[i].Econtrol_pointX)*(path[i].EpointX-path[i].Econtrol_pointX)+(path[i].EpointY-path[i].Econtrol_pointY)*(path[i].EpointY-path[i].Econtrol_pointY));
                    if(temp < ((path[i].Econtrol_pointX-path[i].SpointX)*(path[i].Econtrol_pointX-path[i].SpointX)+(path[i].Econtrol_pointY-path[i].SpointY)*(path[i].Econtrol_pointY-path[i].SpointY)))
                        temp = ((path[i].Econtrol_pointX-path[i].SpointX)*(path[i].Econtrol_pointX-path[i].SpointX)+(path[i].Econtrol_pointY-path[i].SpointY)*(path[i].Econtrol_pointY-path[i].SpointY));
                    if(temp < ((path[i].Econtrol_pointX-path[i].Scontrol_pointX)*(path[i].Econtrol_pointX-path[i].Scontrol_pointX)+(path[i].Econtrol_pointY-path[i].Scontrol_pointY)*(path[i].Econtrol_pointY-path[i].Scontrol_pointY)))
                        temp = ((path[i].Econtrol_pointX-path[i].Scontrol_pointX)*(path[i].Econtrol_pointX-path[i].Scontrol_pointX)+(path[i].Econtrol_pointY-path[i].Scontrol_pointY)*(path[i].Econtrol_pointY-path[i].Scontrol_pointY));
                    if(temp < (((path[i].EpointX-path[i].SpointX)*(path[i].EpointX-path[i].SpointX)+(path[i].EpointY-path[i].SpointY)*(path[i].EpointY-path[i].SpointY))))
                        temp = (path[i].EpointX-path[i].SpointX)*(path[i].EpointX-path[i].SpointX)+(path[i].EpointY-path[i].SpointY)*(path[i].EpointY-path[i].SpointY);
                    wdv=pow(e,(-1*temp)/(2*((900*900*2)/(3*3)))) + 0.01;

                    V = V + ((q0*Pp[i].SpointX+q1*Pp[i].Scontrol_pointX+q2*Pp[i].Econtrol_pointX-Pp[i].Econtrol_pointX)*(q0*Pp[i].SpointX+q1*Pp[i].Scontrol_pointX+q2*Pp[i].Econtrol_pointX-Pp[i].Econtrol_pointX));
                    V = V + ((q0*Pp[i].SpointY+q1*Pp[i].Scontrol_pointY+q2*Pp[i].Econtrol_pointY-Pp[i].Econtrol_pointY)*(q0*Pp[i].SpointY+q1*Pp[i].Scontrol_pointY+q2*Pp[i].Econtrol_pointY-Pp[i].Econtrol_pointY));
                    V = V + ((q0*Pp[i].SpointZ+q1*Pp[i].Scontrol_pointZ+q2*Pp[i].Econtrol_pointZ-Pp[i].Econtrol_pointZ)*(q0*Pp[i].SpointZ+q1*Pp[i].Scontrol_pointZ+q2*Pp[i].Econtrol_pointZ-Pp[i].Econtrol_pointZ));
                    V = V * wdv;

                for(int j = 1; j < pathcount; j++){

                    if(path[i].SpointX == path[j].EpointX && path[i].SpointY == path[j].EpointY){


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                            if((path[i].SpointX >= path[j].Econtrol_pointX && path[i].Scontrol_pointX >= path[i].SpointX && path[i].SpointY >= path[j].Econtrol_pointY && path[i].Scontrol_pointY >= path[i].SpointY) ||
                               (path[i].SpointX <= path[j].Econtrol_pointX && path[i].Scontrol_pointX <= path[i].SpointX && path[i].SpointY >= path[j].Econtrol_pointY && path[i].Scontrol_pointY >= path[i].SpointY) ||
                               (path[i].SpointX >= path[j].Econtrol_pointX && path[i].Scontrol_pointX >= path[i].SpointX && path[i].SpointY <= path[j].Econtrol_pointY && path[i].Scontrol_pointY <= path[i].SpointY) ||
                               (path[i].SpointX <= path[j].Econtrol_pointX && path[i].Scontrol_pointX <= path[i].SpointX && path[i].SpointY <= path[j].Econtrol_pointY && path[i].Scontrol_pointY <= path[i].SpointY) )
                            {
                            matrix[0][0]=1;
                            matrix[0][1]=1;
                            matrix[0][2]=1;
                            matrix[0][3]=1;

                            matrix[1][0]=path[j].Scontrol_pointX;
                            matrix[1][1]=path[j].Econtrol_pointX;
                            matrix[1][2]=path[i].Scontrol_pointX;
                            matrix[1][3]=path[i].Econtrol_pointX;

                            matrix[2][0]=path[j].Scontrol_pointY;
                            matrix[2][1]=path[j].Econtrol_pointY;
                            matrix[2][2]=path[i].Scontrol_pointY;
                            matrix[2][3]=path[i].Econtrol_pointY;

                            temp = matrix[1][0];


                            for(int m = 0; m<4;m++){
                                matrix[1][m] = matrix[1][m] - (matrix[0][m]*(temp));
                            }

                            temp = matrix[2][0];

                            for(int m = 0; m<4;m++){
                                matrix[2][m] = matrix[2][m] - (matrix[0][m]*(temp));
                            }

                            temp = matrix[2][1]/matrix[1][1];

                            for(int m = 0; m<4;m++){
                                matrix[2][m] = matrix[2][m] - (matrix[1][m]*(temp));
                            }

                            matrix[2][3] = matrix[2][3] / matrix[2][2];

                            matrix[1][3] = (matrix[1][3]-(matrix[1][2]*matrix[2][3]))/matrix[1][1];

                            matrix[0][3] = matrix[0][3] - matrix[1][3] - matrix[2][3];

                            q0=matrix[0][3];
                            q1=matrix[1][3];
                            q2=matrix[2][3];

                            temp = 0;
                            temp = (path[j].Econtrol_pointX-path[j].Scontrol_pointX)*(path[j].Econtrol_pointX-path[j].Scontrol_pointX)+(path[j].Econtrol_pointY-path[j].Scontrol_pointY)*(path[j].Econtrol_pointY-path[j].Scontrol_pointY);
                            if(temp < (path[i].Scontrol_pointX-path[j].Econtrol_pointX)*(path[i].Scontrol_pointX-path[j].Econtrol_pointX)+(path[i].Scontrol_pointY-path[j].Econtrol_pointY)*(path[i].Scontrol_pointY-path[j].Econtrol_pointY))
                                temp = (path[i].Scontrol_pointX-path[j].Econtrol_pointX)*(path[i].Scontrol_pointX-path[j].Econtrol_pointX)+(path[i].Scontrol_pointY-path[j].Econtrol_pointY)*(path[i].Scontrol_pointY-path[j].Econtrol_pointY);
                            if(temp < (path[i].Econtrol_pointX-path[i].Scontrol_pointX)*(path[i].Econtrol_pointX-path[i].Scontrol_pointX)+(path[i].Econtrol_pointY-path[i].Scontrol_pointY)*(path[i].Econtrol_pointY-path[i].Scontrol_pointY))
                                temp = (path[i].Econtrol_pointX-path[i].Scontrol_pointX)*(path[i].Econtrol_pointX-path[i].Scontrol_pointX)+(path[i].Econtrol_pointY-path[i].Scontrol_pointY)*(path[i].Econtrol_pointY-path[i].Scontrol_pointY);
                            if(temp < (path[i].Scontrol_pointX-path[j].Scontrol_pointX)*(path[i].Scontrol_pointX-path[j].Scontrol_pointX)+(path[i].Scontrol_pointY-path[j].Scontrol_pointY)*(path[i].Scontrol_pointY-path[j].Scontrol_pointY))
                                temp = (path[i].Scontrol_pointX-path[j].Scontrol_pointX)*(path[i].Scontrol_pointX-path[j].Scontrol_pointX)+(path[i].Scontrol_pointY-path[j].Scontrol_pointY)*(path[i].Scontrol_pointY-path[j].Scontrol_pointY);
                            if(temp < (path[i].Econtrol_pointX-path[j].Econtrol_pointX)*(path[i].Econtrol_pointX-path[j].Econtrol_pointX)+(path[i].Econtrol_pointY-path[j].Econtrol_pointY)*(path[i].Econtrol_pointY-path[j].Econtrol_pointY))
                                temp = (path[i].Econtrol_pointX-path[j].Econtrol_pointX)*(path[i].Econtrol_pointX-path[j].Econtrol_pointX)+(path[i].Econtrol_pointY-path[j].Econtrol_pointY)*(path[i].Econtrol_pointY-path[j].Econtrol_pointY);
                            if(temp < (path[i].Econtrol_pointX-path[j].Scontrol_pointX)*(path[i].Econtrol_pointX-path[j].Scontrol_pointX)+(path[i].Econtrol_pointY-path[j].Scontrol_pointY)*(path[i].Econtrol_pointY-path[j].Scontrol_pointY))
                              temp = (path[i].Econtrol_pointX-path[j].Scontrol_pointX)*(path[i].Econtrol_pointX-path[j].Scontrol_pointX)+(path[i].Econtrol_pointY-path[j].Scontrol_pointY)*(path[i].Econtrol_pointY-path[j].Scontrol_pointY);
                            wdv=pow(e,(-1*temp)/(2*((900*900*2)/(3*3)))) + 0.01;

                            V = V + ((q0*Pp[j].Scontrol_pointX+q1*Pp[j].Econtrol_pointX+q2*Pp[i].Scontrol_pointX-Pp[i].Econtrol_pointX)*(q0*Pp[j].Scontrol_pointX+q1*Pp[j].Econtrol_pointX+q2*Pp[i].Scontrol_pointX-Pp[i].Econtrol_pointX));
                            V = V + ((q0*Pp[j].Scontrol_pointY+q1*Pp[j].Econtrol_pointY+q2*Pp[i].Scontrol_pointY-Pp[i].Econtrol_pointY)*(q0*Pp[j].Scontrol_pointY+q1*Pp[j].Econtrol_pointY+q2*Pp[i].Scontrol_pointY-Pp[i].Econtrol_pointY));
                            V = V + ((q0*Pp[j].Scontrol_pointZ+q1*Pp[j].Econtrol_pointZ+q2*Pp[i].Scontrol_pointZ-Pp[i].Econtrol_pointZ)*(q0*Pp[j].Scontrol_pointZ+q1*Pp[j].Econtrol_pointZ+q2*Pp[i].Scontrol_pointZ-Pp[i].Econtrol_pointZ));
                            V = V * wdv;



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                            t0 = (path[i].SpointX-path[i].Scontrol_pointX)/(path[j].Econtrol_pointX-path[i].Scontrol_pointX);
                            t1 = (path[i].SpointY-path[i].Scontrol_pointY)/(path[j].Econtrol_pointY-path[i].Scontrol_pointY);
                            double t3 = (t0 +t1)/2;

                            temp = 0;

                             temp = (path[i].SpointX-path[j].Econtrol_pointX)*(path[i].SpointX-path[j].Econtrol_pointX)+(path[i].SpointY-path[j].Econtrol_pointY)*(path[i].SpointY-path[j].Econtrol_pointY);
                            if(temp < ((path[i].Scontrol_pointX-path[i].SpointX)*(path[i].Scontrol_pointX-path[i].SpointX)+(path[i].Scontrol_pointY-path[i].SpointY)*(path[i].Scontrol_pointY-path[i].SpointY)))
                                temp = (path[i].Scontrol_pointX-path[i].SpointX)*(path[i].Scontrol_pointX-path[i].SpointX)+(path[i].Scontrol_pointY-path[i].SpointY)*(path[i].Scontrol_pointY-path[i].SpointY);
                            if(temp < (path[i].Scontrol_pointX-path[j].Econtrol_pointX)*(path[i].Scontrol_pointX-path[j].Econtrol_pointX)+(path[i].Scontrol_pointY-path[j].Econtrol_pointY)*(path[i].Scontrol_pointY-path[j].Econtrol_pointY))
                              temp = (path[i].Scontrol_pointX-path[j].Econtrol_pointX)*(path[i].Scontrol_pointX-path[j].Econtrol_pointX)+(path[i].Scontrol_pointY-path[j].Econtrol_pointY)*(path[i].Scontrol_pointY-path[j].Econtrol_pointY);
                            wdv = pow(e,(-1*temp)/(2*((900*900*2)/(3*3)))) + 0.01;
                            V = V + (t0*Pp[j].Econtrol_pointX+(1-t0)*Pp[i].Scontrol_pointX-Pp[i].SpointX)*(t0*Pp[j].Econtrol_pointX+(1-t0)*Pp[i].Scontrol_pointX-Pp[i].SpointX);
                            V = V + (t1*Pp[j].Econtrol_pointY+(1-t1)*Pp[i].Scontrol_pointY-Pp[i].SpointY)*(t1*Pp[j].Econtrol_pointY+(1-t1)*Pp[i].Scontrol_pointY-Pp[i].SpointY);
                            V = V + (t3*Pp[j].Econtrol_pointZ+(1-t3)*Pp[i].Scontrol_pointZ-Pp[i].SpointZ)*(t3*Pp[j].Econtrol_pointZ+(1-t3)*Pp[i].Scontrol_pointZ-Pp[i].SpointZ);

                            V = V *wdv;


                            temp = (path[i].SpointX-path[j].Econtrol_pointX)*(path[i].SpointX-path[j].Econtrol_pointX)+(path[i].SpointY-path[j].Econtrol_pointY)*(path[i].SpointY-path[j].Econtrol_pointY);
                            wdf = pow(e,(-1*temp)/(2*((900*900*2)/(3*3)))) + 0.01;
                            F = F + wdf * (Pp[i].SpointZ-Pp[j].Econtrol_pointZ)*(Pp[i].SpointZ-Pp[j].Econtrol_pointZ);

                            temp = (path[i].Scontrol_pointX-path[i].SpointX)*(path[i].Scontrol_pointX-path[i].SpointX)+(path[i].Scontrol_pointX-path[i].SpointX)*(path[i].Scontrol_pointX-path[i].SpointX);
                            wdf = pow(e,(-1*temp)/(2*((900*900*2)/(3*3)))) + 0.01;
                            F = F + wdf * (Pp[i].Scontrol_pointZ-Pp[i].SpointZ)*(Pp[i].Scontrol_pointZ-Pp[i].SpointZ);



                            A = A + ((Pp[j].Econtrol_pointX-path[j].Econtrol_pointX)*(Pp[j].Econtrol_pointX-path[j].Econtrol_pointX)+(Pp[j].Econtrol_pointY-path[j].Econtrol_pointY)*(Pp[j].Econtrol_pointY-path[j].Econtrol_pointY));
                            A = A + ((Pp[i].SpointX-path[i].SpointX)*(Pp[i].SpointX-path[i].SpointX)+(Pp[i].SpointY-path[i].SpointY)*(Pp[i].SpointY-path[i].SpointY));
                            A = A + ((Pp[i].Scontrol_pointX-path[i].Scontrol_pointX)*(Pp[i].Scontrol_pointX-path[i].Scontrol_pointX)+(Pp[i].Scontrol_pointY-path[i].Scontrol_pointY)*(Pp[i].Scontrol_pointY-path[i].Scontrol_pointY));

                            temp = (path[i].SpointX-path[j].Econtrol_pointX)*(path[i].SpointX-path[j].Econtrol_pointX)+(path[i].SpointY-path[j].Econtrol_pointY)*(path[i].SpointY-path[j].Econtrol_pointY);
                            wda = pow(e,(-1*temp)/(2*((900*900*2)/(3*3)))) + 0.01;
                            tempA = ((Pp[i].SpointX-Pp[j].Econtrol_pointX)-(path[i].SpointX-path[j].Econtrol_pointX))*((Pp[i].SpointX-Pp[j].Econtrol_pointX)-(path[i].SpointX-path[j].Econtrol_pointX))+
                                    ((Pp[i].SpointY-Pp[j].Econtrol_pointY)-(path[i].SpointY-path[j].Econtrol_pointY))*((Pp[i].SpointY-Pp[j].Econtrol_pointY)-(path[i].SpointY-path[j].Econtrol_pointY));
                            A = A + tempA * wda;

                            temp = ((path[i].Scontrol_pointX-path[i].SpointX)*(path[i].Scontrol_pointX-path[i].SpointX)+(path[i].Scontrol_pointY-path[i].SpointY)*(path[i].Scontrol_pointY-path[i].SpointY));
                            wda = pow(e,(-1*temp)/(2*((900*900*2)/(3*3)))) + 0.01;
                            tempA = (((Pp[i].Scontrol_pointX-Pp[i].SpointX)-(path[i].Scontrol_pointX-path[i].SpointX))*((Pp[i].Scontrol_pointX-Pp[i].SpointX)-(path[i].Scontrol_pointX-path[i].SpointX)))+
                                    (((Pp[i].Scontrol_pointY-Pp[i].SpointY)-(path[i].Scontrol_pointY-path[i].SpointY))*((Pp[i].Scontrol_pointY-Pp[i].SpointY)-(path[i].Scontrol_pointY-path[i].SpointY)));
                            A = A + tempA * wda;
                            }
                    }
                }



        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



                temp = (path[i].Scontrol_pointX-path[i].SpointX)*(path[i].Scontrol_pointX-path[i].SpointX)+(path[i].Scontrol_pointY-path[i].SpointY)*(path[i].Scontrol_pointY-path[i].SpointY);
                wdf=pow(e,(-1*temp)/(2*((900*900*2)/(3*3)))) + 0.01;
                F = F + wdf * (Pp[i].Scontrol_pointZ-Pp[i].SpointZ)*(Pp[i].Scontrol_pointZ-Pp[i].SpointZ);

                temp = ((path[i].Econtrol_pointX-path[i].Scontrol_pointX)*(path[i].Econtrol_pointX-path[i].Scontrol_pointX)+(path[i].Econtrol_pointY-path[i].Scontrol_pointY)*(path[i].Econtrol_pointY-path[i].Scontrol_pointY));
                wdf=pow(e,(-1*temp)/(2*((900*900*2)/(3*3)))) + 0.01;
                F = F + wdf * (Pp[i].Econtrol_pointZ-Pp[i].Scontrol_pointZ)*(Pp[i].Econtrol_pointZ-Pp[i].Scontrol_pointZ);

                temp = ((path[i].EpointX-path[i].Econtrol_pointX)*(path[i].EpointX-path[i].Econtrol_pointX)+(path[i].EpointY-path[i].Econtrol_pointY)*(path[i].EpointY-path[i].Econtrol_pointY));
                wdf=pow(e,(-1*temp)/(2*((900*900*2)/(3*3)))) + 0.01;
                F = F + wdf*(Pp[i].EpointZ-Pp[i].Econtrol_pointZ)*(Pp[i].EpointZ-Pp[i].Econtrol_pointZ);

                A = A + ((Pp[i].SpointX-path[i].SpointX)*(Pp[i].SpointX-path[i].SpointX)+(Pp[i].SpointY-path[i].SpointY)*(Pp[i].SpointY-path[i].SpointY));
                A = A + ((Pp[i].Scontrol_pointX-path[i].Scontrol_pointX)*(Pp[i].Scontrol_pointX-path[i].Scontrol_pointX)+(Pp[i].Scontrol_pointY-path[i].Scontrol_pointY)*(Pp[i].Scontrol_pointY-path[i].Scontrol_pointY));
                A = A + ((Pp[i].Econtrol_pointX-path[i].Econtrol_pointX)*(Pp[i].Econtrol_pointX-path[i].Econtrol_pointX)+(Pp[i].Econtrol_pointY-path[i].Econtrol_pointY)*(Pp[i].Econtrol_pointY-path[i].Econtrol_pointY));
                A = A + ((Pp[i].EpointX-path[i].EpointX)*(Pp[i].EpointX-path[i].EpointX)+(Pp[i].EpointY-path[i].EpointY)*(Pp[i].EpointY-path[i].EpointY));

                temp = ((path[i].Scontrol_pointX-path[i].SpointX)*(path[i].Scontrol_pointX-path[i].SpointX)+(path[i].Scontrol_pointY-path[i].SpointY)*(path[i].Scontrol_pointY-path[i].SpointY));
                wda = pow(e,(-1*temp)/(2*((900*900*2)/(3*3)))) + 0.01;
                tempA = (((Pp[i].Scontrol_pointX-Pp[i].SpointX)-(path[i].Scontrol_pointX-path[i].SpointX))*((Pp[i].Scontrol_pointX-Pp[i].SpointX)-(path[i].Scontrol_pointX-path[i].SpointX)))+
                        (((Pp[i].Scontrol_pointY-Pp[i].SpointY)-(path[i].Scontrol_pointY-path[i].SpointY))*((Pp[i].Scontrol_pointY-Pp[i].SpointY)-(path[i].Scontrol_pointY-path[i].SpointY)));
                A = A + tempA * wda;
                temp = (path[i].Econtrol_pointX-path[i].Scontrol_pointX)*(path[i].Econtrol_pointX-path[i].Scontrol_pointX)+(path[i].Econtrol_pointY-path[i].Scontrol_pointY)*(path[i].Econtrol_pointY-path[i].Scontrol_pointY);
                wda = pow(e,(-1*temp)/(2*((900*900*2)/(3*3)))) + 0.01;
                tempA = (((Pp[i].Econtrol_pointX-Pp[i].Scontrol_pointX)-(path[i].Econtrol_pointX-path[i].Scontrol_pointX))*((Pp[i].Econtrol_pointX-Pp[i].Scontrol_pointX)-(path[i].Econtrol_pointX-path[i].Scontrol_pointX)))+
                        (((Pp[i].Econtrol_pointY-Pp[i].Scontrol_pointY)-(path[i].Econtrol_pointY-path[i].Scontrol_pointY))*((Pp[i].Econtrol_pointY-Pp[i].Scontrol_pointY)-(path[i].Econtrol_pointY-path[i].Scontrol_pointY)));
                A = A + tempA * wda;
                temp = (path[i].EpointX-path[i].Econtrol_pointX)*(path[i].EpointX-path[i].Econtrol_pointX)+(path[i].EpointY-path[i].Econtrol_pointY)*(path[i].EpointY-path[i].Econtrol_pointY);
                wda = pow(e,(-1*temp)/(2*((900*900*2)/(3*3)))) + 0.01;
                tempA = (((Pp[i].EpointX-Pp[i].Econtrol_pointX)-(path[i].EpointX-path[i].Econtrol_pointX))*((Pp[i].EpointX-Pp[i].Econtrol_pointX)-(path[i].EpointX-path[i].Econtrol_pointX)))+
                        (((Pp[i].EpointY-Pp[i].Econtrol_pointY)-(path[i].EpointY-path[i].Econtrol_pointY))*((Pp[i].EpointY-Pp[i].Econtrol_pointY)-(path[i].EpointY-path[i].Econtrol_pointY)));
                A = A + tempA * wda;
            }



            if(cheak !=0){
                store = E;
                E=0;
                E=A+2*V+0.001*F;
                printf("%f     ", E);
                if(E>store){
                    E=store;
                }
                else {
                    for(int i = 1; i < pathcount; i++){
                        storeP[0][i][0].x = Pp[i].SpointX;
                        storeP[0][i][1].x = Pp[i].Scontrol_pointX;
                        storeP[0][i][2].x = Pp[i].Econtrol_pointX;
                        storeP[0][i][3].x = Pp[i].EpointX;

                        storeP[0][i][0].y = Pp[i].SpointY;
                        storeP[0][i][1].y = Pp[i].Scontrol_pointY;
                        storeP[0][i][2].y = Pp[i].Econtrol_pointY;
                        storeP[0][i][3].y = Pp[i].EpointY;

                        storeP[0][i][0].z = Pp[i].SpointZ;
                        storeP[0][i][1].z = Pp[i].Scontrol_pointZ;
                        storeP[0][i][2].z = Pp[i].Econtrol_pointZ;
                        storeP[0][i][3].z = Pp[i].EpointZ;
                    }
                }
            }
            else{
                E=A+2*V+0.001*F;
                    for(int i = 1; i < pathcount; i++){
                        storeP[0][i][0].x = Pp[i].SpointX;
                        storeP[0][i][1].x = Pp[i].Scontrol_pointX;
                        storeP[0][i][2].x = Pp[i].Econtrol_pointX;
                        storeP[0][i][3].x = Pp[i].EpointX;

                        storeP[0][i][0].y = Pp[i].SpointY;
                        storeP[0][i][1].y = Pp[i].Scontrol_pointY;
                        storeP[0][i][2].y = Pp[i].Econtrol_pointY;
                        storeP[0][i][3].y = Pp[i].EpointY;

                        storeP[0][i][0].z = Pp[i].SpointZ;
                        storeP[0][i][1].z = Pp[i].Scontrol_pointZ;
                        storeP[0][i][2].z = Pp[i].Econtrol_pointZ;
                        storeP[0][i][3].z = Pp[i].EpointZ;
                    }
            }

            printf("%f     \n", E);

            time++;
            cheak=1;
           // printf("V  %f , F  %f , A  %f \n", V, F, A);
            V = 0;
            F = 0;
            A = 0;


    }

    for(int i = 1; i < pathcount; i++){
         Pp[i].SpointX = storeP[0][i][0].x ;
         Pp[i].Scontrol_pointX = storeP[0][i][1].x ;
         Pp[i].Econtrol_pointX = storeP[0][i][2].x;
         Pp[i].EpointX = storeP[0][i][3].x;

         Pp[i].SpointY = storeP[0][i][0].y;
         Pp[i].Scontrol_pointY = storeP[0][i][1].y ;
         Pp[i].Econtrol_pointY = storeP[0][i][2].y;
         Pp[i].EpointY = storeP[0][i][3].y;

         Pp[i].SpointZ = storeP[0][i][0].z;
         Pp[i].Scontrol_pointZ = storeP[0][i][1].z ;
         Pp[i].Econtrol_pointZ = storeP[0][i][2].z;
         Pp[i].EpointZ = storeP[0][i][3].z;
    }

    printf("\n");

                for(int i = 1; i<(pathcount+1);i++){
                printf("%f %f %f   ",Pp[i].SpointX,Pp[i].SpointY,Pp[i].SpointZ);
                printf("%f %f %f   ",Pp[i].Scontrol_pointX,Pp[i].Scontrol_pointY,Pp[i].Scontrol_pointZ);
                printf("%f %f %f   ",Pp[i].Econtrol_pointX,Pp[i].Econtrol_pointY,Pp[i].Econtrol_pointZ);
                printf("%f %f %f\n",Pp[i].EpointX,Pp[i].EpointY,Pp[i].EpointZ);

            }
}


void Read_SVG(){

    fstream fin;
    fin.open("C:/Users/user/Desktop/project/blender_half_resampled_black.svg",ios::in);

    while(fin.getline(line,sizeof(line),'\n')){

        for(int i = 0; i < sizeof(line); i++){
                if(line[i] == 'l' && line[i + 4] == 'r'){
                    layercount++;
                }
                else if(line[i] == 'M'){
                        int j = i;
                    while( line[j] != 'C'){
                        if(isdigit(line[j]) || line[j] =='.' || line[j] == '-'){
                            layer = layer + line[j];
                        }
                        else if(line[j] == ' '){
                            if(layer != ""){
                                point = atof(layer.c_str());
                                path[pathcount].SpointY = point;
                                layer = "";
                            }
                        }
                        else if(line[j] == ','){
                            if(layer != ""){
                                point = atof(layer.c_str());
                                path[pathcount].SpointX = point;
                                layer = "";
                            }
                        }
                        j++;
                    }
                }
                else if(line[i] == 'C' && line[i-1] == ' '){
                    int j = i;
                    while( line[j] != '/'){
                        if(isdigit(line[j]) || line[j] =='.' || line[j] == '-'){
                            layer = layer + line[j];
                        }
                        else if(line[j] == ' '){
                            if(layer != "" && space == 0){
                                point = atof(layer.c_str());
                                path[pathcount].Scontrol_pointY = point;
                                layer = "";
                                space++;
                            }
                            else if(layer != "" && space == 1){
                                point = atof(layer.c_str());
                                path[pathcount].Econtrol_pointY = point;
                                layer = "";
                                space++;
                            }

                        }
                        else if(line[j] == ',' ){
                            if(layer != "" && space == 0){
                                point = atof(layer.c_str());
                                path[pathcount].Scontrol_pointX = point;
                                layer = "";
                            }
                            else if(layer != "" && space == 1){
                                point = atof(layer.c_str());
                                path[pathcount].Econtrol_pointX = point;
                                layer = "";
                            }
                            else if(layer != "" && space == 2){
                                point = atof(layer.c_str());
                                path[pathcount].EpointX = point;
                                layer = "";
                            }

                        }
                        else if(line[j] == '"'){
                            if(layer != ""){
                                point = atof(layer.c_str());
                                path[pathcount].EpointY = point;
                                layer = "";
                            }
                        }
                        j++;
                    }
                    pathcount++;
                    space = 0;
                }
                else if(line[i] == 'c' && line[i+1] == 'x'){
                     int j = i;
                    while( line[j] != 'y'){
                            if(isdigit(line[j]) || line[j] =='.' || line[j] == '-'){
                            layer = layer + line[j];
                            }
                            else if(line[j] == '"'){
                                if(layer != ""){
                                point = atof(layer.c_str());
                                graph[pointcount].x = point;
                                layer = "";
                            }
                            }
                        j++;
                    }
                }
                else if(line[i] == 'c' && line[i+1] == 'y'){
                     int j = i;
                    while( line[j] != 's'){
                            if(isdigit(line[j]) || line[j] =='.' || line[j] == '-'){
                            layer = layer + line[j];
                            }
                            else if(line[j] == '"'){
                                if(layer != ""){
                                point = atof(layer.c_str());
                                graph[pointcount].y = point;
                                layer = "";
                            }
                            }
                        j++;
                    }
                    pointcount++;
                }

        }

         for(int i = 0; i < sizeof(line); i++){
            line[i] = '\0';
         }
    }
    //cheak spoint
    //printf("%d\n" ,layercount);

   /* for(int i = 1; i < pathcount; i++){

        printf("C: %.4f,%.4f ", path[i].SpointX, path[i].SpointY);
        printf("M: %.4f,%.4f %.4f,%.4f %.4f,%.4f \n", path[i].Scontrol_pointX, path[i].Scontrol_pointY, path[i].Econtrol_pointX, path[i].Econtrol_pointY, path[i].EpointX, path[i].EpointY);
        printf("%d\n", i);
    }
    printf("%d", pathcount);
    for(int i = 1; i < pointcount; i++){
         printf("C: %.4f,%.4f \n", graph[i].x, graph[i].y);
    }*/
}

void orthRange(){
    for(int i = 1; i < pathcount; i++){
        if(path[i].SpointX > Xmax)
            Xmax = path[i].SpointX;
        else if(path[i].EpointX > Xmax)
            Xmax = path[i].EpointX;
        else if(path[i].Scontrol_pointX > Xmax)
            Xmax = path[i].Scontrol_pointX;
        else if(path[i].Econtrol_pointX > Xmax)
            Xmax = path[i].Econtrol_pointX;

        if(path[i].SpointX < Xmin)
            Xmin = path[i].SpointX;
        else if(path[i].EpointX < Xmin)
            Xmin = path[i].EpointX;
        else if(path[i].Scontrol_pointX < Xmin)
            Xmin = path[i].Scontrol_pointX;
        else if(path[i].Econtrol_pointX < Xmin)
            Xmin = path[i].Econtrol_pointX;

        if(path[i].SpointY > Ymax)
            Ymax = path[i].SpointY;
        else if(path[i].EpointY > Ymax)
            Ymax = path[i].EpointY;
        else if(path[i].Scontrol_pointY > Ymax)
            Ymax = path[i].Scontrol_pointY;
        else if(path[i].Econtrol_pointY > Ymax)
            Ymax = path[i].Econtrol_pointY;

        if(path[i].SpointY < Ymin)
            Ymin = path[i].SpointY;
        else if(path[i].EpointY < Ymin)
            Ymin = path[i].EpointY;
        else if(path[i].Scontrol_pointY < Ymin)
            Ymin = path[i].Scontrol_pointY;
        else if(path[i].Econtrol_pointY < Ymin)
            Ymin = path[i].Econtrol_pointY;
  //////////////////////////////////////////////////////////////////////////////////////////
        if(Pp[i].SpointX > PXmax)
            PXmax = Pp[i].SpointX;
        else if(Pp[i].EpointX > PXmax)
            PXmax = Pp[i].EpointX;
        else if(Pp[i].Scontrol_pointX > PXmax)
            PXmax = Pp[i].Scontrol_pointX;
        else if(Pp[i].Econtrol_pointX > PXmax)
            PXmax = Pp[i].Econtrol_pointX;

        if(Pp[i].SpointX < PXmin)
            PXmin = Pp[i].SpointX;
        else if(Pp[i].EpointX < PXmin)
            PXmin = Pp[i].EpointX;
        else if(Pp[i].Scontrol_pointX < PXmin)
            PXmin = Pp[i].Scontrol_pointX;
        else if(Pp[i].Econtrol_pointX < PXmin)
            PXmin = Pp[i].Econtrol_pointX;

        if(Pp[i].SpointY > PYmax)
            PYmax = Pp[i].SpointY;
        else if(Pp[i].EpointY > PYmax)
            PYmax = Pp[i].EpointY;
        else if(Pp[i].Scontrol_pointY > PYmax)
            PYmax = Pp[i].Scontrol_pointY;
        else if(Pp[i].Econtrol_pointY > PYmax)
            PYmax = Pp[i].Econtrol_pointY;

        if(Pp[i].SpointY < PYmin)
            PYmin = Pp[i].SpointY;
        else if(Pp[i].EpointY < PYmin)
            PYmin = Pp[i].EpointY;
        else if(Pp[i].Scontrol_pointY < PYmin)
            PYmin = Pp[i].Scontrol_pointY;
        else if(Pp[i].Econtrol_pointY < PYmin)
            PYmin = Pp[i].Econtrol_pointY;

         if(Pp[i].SpointZ > PZmax)
            PZmax = Pp[i].SpointZ;
        else if(Pp[i].EpointZ > PZmax)
            PZmax = Pp[i].EpointZ;
        else if(Pp[i].Scontrol_pointZ > PZmax)
            PZmax = Pp[i].Scontrol_pointZ;
        else if(Pp[i].Econtrol_pointZ > PZmax)
            PZmax = Pp[i].Econtrol_pointZ;

        if(Pp[i].SpointZ < PZmin)
            PZmin = Pp[i].SpointZ;
        else if(Pp[i].EpointZ < PZmin)
            PZmin = Pp[i].EpointZ;
        else if(Pp[i].Scontrol_pointZ < PZmin)
            PZmin = Pp[i].Scontrol_pointZ;
        else if(Pp[i].Econtrol_pointZ < PZmin)
            PZmin = Pp[i].Econtrol_pointZ;

    }

    Xmax = Xmax + 10;
    Ymax = Ymax + 10;
    Xmin = Xmin - 10;
    Ymin = Ymin - 10;

    PXmax = PXmax + 10;
    PYmax = PYmax + 10;
    PXmin = PXmin - 10;
    PYmin = PYmin - 10;
    PZmax = PZmax + 10;
    PZmin = PZmin - 10;

}

void drawDot(pathline path) {

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(PXmin, PXmax, PYmax, PYmin, 100, -100);
    glMatrixMode(GL_MODELVIEW);
    glBegin(GL_POINTS);
    glVertex3f(path.SpointX,path.SpointY, path.SpointZ);
    glVertex2i(path.Scontrol_pointX,path.Scontrol_pointY);
    glVertex2i(path.Econtrol_pointX,path.Econtrol_pointY);
    glVertex3f(path.EpointX,path.EpointY, path.EpointZ);
	glEnd();
}

void drawLine(pathline path){
    double t = 0;
    GLdouble Bx;
    GLdouble By;
    GLdouble Bz;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(Xmin, Xmax, Ymax, Ymin, 0, -900);
    glMatrixMode(GL_MODELVIEW);

    glBegin(GL_LINE_STRIP);


    for(int i = t; i <= 100; i++){
        Bx = path.SpointX*(1-t)*(1-t)*(1-t) + 3*path.Scontrol_pointX*t*(1-t)*(1-t) + 3*path.Econtrol_pointX*t*t*(1-t) + path.EpointX*t*t*t;
        By = path.SpointY*(1-t)*(1-t)*(1-t) + 3*path.Scontrol_pointY*t*(1-t)*(1-t) + 3*path.Econtrol_pointY*t*t*(1-t) + path.EpointY*t*t*t;
       //printf("%f\n", Bz);
        t = t + 0.01;
        glVertex2f(Bx, By);
    }
       glEnd();
}

void drawLine3d(pathline path){
    double t = 0;
    GLdouble Bx;
    GLdouble By;
    GLdouble Bz;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(PXmin, PXmax, PYmax, PYmin, 200, -200);
    glMatrixMode(GL_MODELVIEW);

    glBegin(GL_LINE_STRIP);

    for(int i = t; i <= 100; i++){
        Bx = path.SpointX*(1-t)*(1-t)*(1-t) + 3*path.Scontrol_pointX*t*(1-t)*(1-t) + 3*path.Econtrol_pointX*t*t*(1-t) + path.EpointX*t*t*t;
        By = path.SpointY*(1-t)*(1-t)*(1-t) + 3*path.Scontrol_pointY*t*(1-t)*(1-t) + 3*path.Econtrol_pointY*t*t*(1-t) + path.EpointY*t*t*t;
        Bz = path.SpointZ*(1-t)*(1-t)*(1-t) + 3*path.Scontrol_pointZ*t*(1-t)*(1-t) + 3*path.Econtrol_pointZ*t*t*(1-t) + path.EpointZ*t*t*t;
        t = t + 0.01;
        glVertex3f(Bx, By, Bz);

    }
    //glVertex3f(path.SpointX, path.SpointY, path.SpointZ);
    //glVertex3f(path.EpointX, path.EpointY, path.EpointZ);
       glEnd();
}

void myinit(){



/* attributes */

      glClearColor(0.0, 0.0, 0.0, 1.0); /* white background */
      glColor3f(1.0, 1.0, 1.0);
}


void display( void ){

    glClear(GL_COLOR_BUFFER_BIT);  /*clear the window */

     glViewport(0, 0, 500, 500);


    for(int i = 1; i <= slices; i++){
    //drawDot(path[i]);
    drawLine(path[i]);
    }
     glViewport(501, 0, 500, 500);

    glPushMatrix();
    for(int i = 1; i <= slices; i++){
    //drawDot(Pp[i]);
    drawLine3d(Pp[i]);
    }
    glPopMatrix();
    glFlush(); /* clear buffers */
 }

 static void key(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 27 :
        case 'q':
            exit(0);
            break;

        case '+':
            if(slices < pathcount)
                slices++;
            break;

    }

    glutPostRedisplay();
}

void randomize()
{
    int i;
    time_t t;
    srand((unsigned) time(&t));
}

int main(int argc, char** argv){

    Read_SVG();
    randomize();
    fidelity();
    orthRange();

    glutInit(&argc,argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB); /* default, not needed */
    glutInitWindowSize(1000,500); /* 500 x 500 pixel window */
    glutInitWindowPosition(10,0); /* place window top left on display */
    glutCreateWindow("CG"); /* window title */


    glutDisplayFunc(display); /* display callback invoked when window opened */
    glutKeyboardFunc(key);

    myinit(); /* set attributes */


    glutMainLoop(); /* enter event loop */

    system("pause");
    return 0;
}
