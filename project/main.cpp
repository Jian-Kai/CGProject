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



points Sp[1000];
points Ep[1000];
points SCp[1000];
points ECp[1000];
double e = 2.71828;


pathline path[1000];
int pathcount = 1;
int space = 0;
int layercount = 0;
double Xmax, Xmin, Ymax, Ymin;

double storeP[10000][1000][4];
int repeat, enter;



void fidelity(){

    int cheak = 0;
    int time = 1;
    double E, V, F;
    double store;
    while(time <= 10000){


            for(int i= 1; i < pathcount; i++){
                Sp[i].z = (rand()%342)+1;
                SCp[i].z = (rand()%342)+1;
                ECp[i].z = (rand()%342)+1;
                Ep[i].z = (rand()%342)+1;
            }
           for(int k = 1; k < time; k++){
                for(int j = 1; j < pathcount; j++){
                    if(Sp[j].z == storeP[k][j][0] && SCp[j].z == storeP[k][j][1] && ECp[j].z == storeP[k][j][2]  && Ep[j].z == storeP[k][j][3]){
                        repeat++;
                    }
                }
                if(repeat == pathcount){
                    for(int i= 1; i < pathcount; i++){
                        Sp[i].z = (rand()%342)+1;
                        SCp[i].z = (rand()%342)+1;
                        ECp[i].z = (rand()%342)+1;
                        Ep[i].z = (rand()%342)+1;
                        k=1;
                    }
                    repeat = 0;
                }
            }

            for(int i= 1; i < pathcount; i++){
                storeP[time][i][0] = Sp[i].z;
                storeP[time][i][1] = SCp[i].z;
                storeP[time][i][2] = ECp[i].z;
                storeP[time][i][3] = Ep[i].z;
            }



            for(int i = 1; i < pathcount; i++){

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

                 for(int i = 0; i<4;i++){
                    matrix[1][i] = matrix[1][i] - (matrix[0][i]*(temp));
                }

                temp = matrix[2][0];

                for(int i = 0; i<4;i++){
                    matrix[2][i] = matrix[2][i] - (matrix[0][i]*(temp));
                }

                temp = matrix[2][1]/matrix[1][1];

                for(int i = 0; i<4;i++){
                    matrix[2][i] = matrix[2][i] - (matrix[1][i]*(temp));
                }

                matrix[2][3] = matrix[2][3] / matrix[2][2];

                matrix[1][3] = (matrix[1][3]-(matrix[1][2]*matrix[2][3]))/matrix[1][1];

                matrix[0][3] = matrix[0][3] - matrix[1][3] - matrix[2][3];

                //printf("%f  %f  %f  %f    %d\n", matrix[0][3],matrix[1][3],matrix[2][3], matrix[0][3]+matrix[1][3]+matrix[2][3], i);


                double q0,q1,q2,t0,t1;
                double wdv;

                q0=matrix[0][3];
                q1=matrix[1][3];
                q2=matrix[2][3];


                //quadruplet
                if(q0 != 0 && q1 != 0 && q2 != 0){
                    temp = (path[i].Scontrol_pointX-path[i].SpointX)*(path[i].Scontrol_pointX-path[i].SpointX)+(path[i].Scontrol_pointY-path[i].SpointY)*(path[i].Scontrol_pointY-path[i].SpointY);
                    if(temp < ((path[i].Econtrol_pointX-path[i].Scontrol_pointX)*(path[i].Econtrol_pointX-path[i].Scontrol_pointX)+(path[i].Econtrol_pointY-path[i].Scontrol_pointY)*(path[i].Econtrol_pointY-path[i].Scontrol_pointY)))
                        temp = ((path[i].Econtrol_pointX-path[i].Scontrol_pointX)*(path[i].Econtrol_pointX-path[i].Scontrol_pointX)+(path[i].Econtrol_pointY-path[i].Scontrol_pointY)*(path[i].Econtrol_pointY-path[i].Scontrol_pointY));
                    if(temp < ((path[i].EpointX-path[i].Econtrol_pointX)*(path[i].EpointX-path[i].Econtrol_pointX)+(path[i].EpointY-path[i].Econtrol_pointY)*(path[i].EpointY-path[i].Econtrol_pointY)))
                        temp = ((path[i].EpointX-path[i].Econtrol_pointX)*(path[i].EpointX-path[i].Econtrol_pointX)+(path[i].EpointY-path[i].Econtrol_pointY)*(path[i].EpointY-path[i].Econtrol_pointY));
                    wdv=pow(e,(-1*temp*temp)/(2*342*342*2)) + 0.01;

                    V = V + wdv*((q0*Sp[i].z+q1*SCp[i].z+q2*ECp[i].z-Ep[i].z)*(q0*Sp[i].z+q1*SCp[i].z+q2*ECp[i].z-Ep[i].z));
                }
                else{
                    enter++;
                    t0 = (path[i].Scontrol_pointX-path[i].Econtrol_pointX)/(path[i].SpointX-path[i].Econtrol_pointX);
                    t1 = (path[i].Scontrol_pointY-path[i].Econtrol_pointY)/(path[i].SpointY-path[i].Econtrol_pointY);
                    if(t0 == t1) printf("1:true ");

                    temp = (path[i].Scontrol_pointX-path[i].SpointX)*(path[i].Scontrol_pointX-path[i].SpointX)+(path[i].Scontrol_pointY-path[i].SpointY)*(path[i].Scontrol_pointY-path[i].SpointY);
                    if(temp < ((path[i].Econtrol_pointX-path[i].Scontrol_pointX)*(path[i].Econtrol_pointX-path[i].Scontrol_pointX)+(path[i].Econtrol_pointY-path[i].Scontrol_pointY)*(path[i].Econtrol_pointY-path[i].Scontrol_pointY)))
                        temp = ((path[i].Econtrol_pointX-path[i].Scontrol_pointX)*(path[i].Econtrol_pointX-path[i].Scontrol_pointX)+(path[i].Econtrol_pointY-path[i].Scontrol_pointY)*(path[i].Econtrol_pointY-path[i].Scontrol_pointY));

                    wdv=pow(e,(-1*temp*temp)/(2*342*342*2)) + 0.01;
                    V = V + wdv*(t0*Sp[i].z+(1-t0)*ECp[i].z-SCp[i].z);

                    t0 = (path[i].Econtrol_pointX-path[i].EpointX)/(path[i].Scontrol_pointX-path[i].EpointX);
                    t1 = (path[i].Econtrol_pointY-path[i].EpointY)/(path[i].Scontrol_pointY-path[i].EpointY);
                    if(t0 == t1) printf("2:true \n");

                    temp = ((path[i].Econtrol_pointX-path[i].Scontrol_pointX)*(path[i].Econtrol_pointX-path[i].Scontrol_pointX)+(path[i].Econtrol_pointY-path[i].Scontrol_pointY)*(path[i].Econtrol_pointY-path[i].Scontrol_pointY));
                    if(temp < ((path[i].EpointX-path[i].Econtrol_pointX)*(path[i].EpointX-path[i].Econtrol_pointX)+(path[i].EpointY-path[i].Econtrol_pointY)*(path[i].EpointY-path[i].Econtrol_pointY)))
                        temp = ((path[i].EpointX-path[i].Econtrol_pointX)*(path[i].EpointX-path[i].Econtrol_pointX)+(path[i].EpointY-path[i].Econtrol_pointY)*(path[i].EpointY-path[i].Econtrol_pointY));

                    wdv=pow(e,(-1*temp*temp)/(2*342*342*2)) + 0.01;
                    V = V + wdv*(t0*SCp[i].z+(1-t0)*Ep[i].z-ECp[i].z);

                }



        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                double wdf;

                temp = temp = (path[i].Scontrol_pointX-path[i].SpointX)*(path[i].Scontrol_pointX-path[i].SpointX)+(path[i].Scontrol_pointY-path[i].SpointY)*(path[i].Scontrol_pointY-path[i].SpointY);
                wdf=pow(e,(-1*temp*temp)/(2*342*342*2)) + 0.01;
                F = F + wdf * (SCp[i].z-Sp[i].z)*(SCp[i].z-Sp[i].z);

                temp = ((path[i].Econtrol_pointX-path[i].Scontrol_pointX)*(path[i].Econtrol_pointX-path[i].Scontrol_pointX)+(path[i].Econtrol_pointY-path[i].Scontrol_pointY)*(path[i].Econtrol_pointY-path[i].Scontrol_pointY));
                wdf=pow(e,(-1*temp*temp)/(2*342*342*2)) + 0.01;
                F = F + wdf * (ECp[i].z-SCp[i].z)*(ECp[i].z-SCp[i].z);

                temp = ((path[i].EpointX-path[i].Econtrol_pointX)*(path[i].EpointX-path[i].Econtrol_pointX)+(path[i].EpointY-path[i].Econtrol_pointY)*(path[i].EpointY-path[i].Econtrol_pointY));
                wdf=pow(e,(-1*temp*temp)/(2*342*342*2)) + 0.01;
                F = F + wdf*(Ep[i].z-ECp[i].z)*(Ep[i].z-ECp[i].z);
            }

            if(cheak !=0){
                store = E;
                E=2*V+0.001*F;
                if(E>=store){
                    E=store;
                }
                else {
                    for(int i = 1; i < pathcount; i++){
                        storeP[0][i][0] = Sp[i].z;
                        storeP[0][i][1] = SCp[i].z;
                        storeP[0][i][2] = ECp[i].z;
                        storeP[0][i][3] = Ep[i].z;

                    }
                }
            }
            else{
                E=2*V+0.001*F;
                    for(int i = 1; i < pathcount; i++){
                        storeP[0][i][0] = Sp[i].z;
                        storeP[0][i][1] = SCp[i].z;
                        storeP[0][i][2] = ECp[i].z;
                        storeP[0][i][3] = Ep[i].z;

                    }
            }

            time++;
            cheak=1;
            printf("V  %f , F  %f , E  %f \n", V, F, E);
            V = 0;
            F = 0;
    }
    for(int i = 1; i < pathcount; i++){
           path[i].SpointZ = storeP[0][i][0];
           path[i].Scontrol_pointZ = storeP[0][i][1];
           path[i].Econtrol_pointZ = storeP[0][i][2];
           path[i].EpointZ = storeP[0][i][3];

    }
   // printf("%d",enter);

}


void Read_SVG(){

    fstream fin;
    fin.open("D:/HomeWork/CG/FinalProject/project/car_97_rmCurves_half_resampled_black.svg",ios::in);

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
    printf("%d", pathcount);*/
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

    }

    Xmax = Xmax + 10;
    Ymax = Ymax + 10;
    Xmin = Xmin - 10;
    Ymin = Ymin - 10;

}

void drawDot(pathline path) {
    glBegin(GL_POINTS);
    glVertex2i(path.SpointX,path.SpointY);
    //glVertex2i(path.Scontrol_pointX,path.Scontrol_pointY);
    //glVertex2i(path.Econtrol_pointX,path.Econtrol_pointY);
    glVertex2i(path.EpointX,path.EpointY);
	glEnd();
}

void drawLine(pathline path){
    double t = 0;
    GLdouble Bx;
    GLdouble By;
    GLdouble Bz;

    glBegin(GL_LINE_STRIP);

    for(int i = t; i <= 100; i++){
        Bx = path.SpointX*(1-t)*(1-t)*(1-t) + 3*path.Scontrol_pointX*t*(1-t)*(1-t) + 3*path.Econtrol_pointX*t*t*(1-t) + path.EpointX*t*t*t;
        By = path.SpointY*(1-t)*(1-t)*(1-t) + 3*path.Scontrol_pointY*t*(1-t)*(1-t) + 3*path.Econtrol_pointY*t*t*(1-t) + path.EpointY*t*t*t;
        Bz = path.SpointZ*(1-t)*(1-t)*(1-t) + 3*path.Scontrol_pointZ*t*(1-t)*(1-t) + 3*path.Econtrol_pointZ*t*t*(1-t) + path.EpointZ*t*t*t;
       //printf("%f\n", Bz);
        t = t + 0.01;




        glVertex3f(Bx, By, Bz);
      // glVertex2i(Bx, By);

    }
       glEnd();
}

void myinit(){

     orthRange();

/* attributes */

      glClearColor(0.0, 0.0, 0.0, 1.0); /* white background */
      glColor3f(1.0, 1.0, 1.0); /* draw in red */

/* set up viewing */
/* 500 x 500 window with origin lower left */

      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      glOrtho(Xmin*2, Xmax*2, Ymax*2, Ymin*2, 0, -500);
      glMatrixMode(GL_MODELVIEW);

}


void display( void ){

    glClear(GL_COLOR_BUFFER_BIT);  /*clear the window */

    glTranslated(400, 0, 0);


    for(int i = 1; i < pathcount; i++){
    //drawDot(path[i]);
    drawLine(path[i]);
    }

    glFlush(); /* clear buffers */
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




    glutInit(&argc,argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB); /* default, not needed */
    glutInitWindowSize(500,500); /* 500 x 500 pixel window */
    glutInitWindowPosition(0,0); /* place window top left on display */
    glutCreateWindow("CG"); /* window title */


    glutDisplayFunc(display); /* display callback invoked when window opened */

    myinit(); /* set attributes */


    glutMainLoop(); /* enter event loop */

    system("pause");
    return 0;
}
