#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<string>
#include<fstream>
#include<windows.h>
#include<GL/glut.h>

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
};

pathline path[1000];
int pathcount = 0;
int space = 0;
int layercount = 0;

void Read_SVG(){

    fstream fin;
    fin.open("D:/HomeWork/CG/FinalProject/project/blender_half_resampled_black.svg",ios::in);

    while(fin.getline(line,sizeof(line),'\n')){

        for(int i = 0; i < sizeof(line); i++){
                if(line[i] == 'l' && line[i + 4] == 'r'){
                    layercount++;
                }
                else if(line[i] == 'M'){
                    for(int j = i; j <= (i+17); j++){
                        if(isdigit(line[j]) || line[j] =='.'){
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
                    }
                }
                else if(line[i] == 'C' && line[i-1] == ' '){
                    for(int j = i ; j < (i+50); j++){
                        if(isdigit(line[j]) || line[j] =='.'){
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
    printf("%d\n" ,layercount);
    for(int i = 0; i < pathcount; i++){
        printf("C: %.4f,%.4f ", path[i].SpointX, path[i].SpointY);
        printf("M: %.4f,%.4f %.4f,%.4f %.4f,%.4f \n", path[i].Scontrol_pointX, path[i].Scontrol_pointY, path[i].Econtrol_pointX, path[i].Econtrol_pointY, path[i].EpointX, path[i].EpointY);
    }
    printf("%d", pathcount);
}

void drawDot(pathline path) {
    glBegin(GL_POINTS);
    glVertex2i(path.SpointX,path.SpointY);
    glVertex2i(path.Scontrol_pointX,path.Scontrol_pointY);
    glVertex2i(path.Econtrol_pointX,path.Econtrol_pointY);
    glVertex2i(path.EpointX,path.EpointY);
	glEnd();
}

void myinit()
{

/* attributes */

      glClearColor(0.0, 0.0, 0.0, 1.0); /* white background */
      glColor3f(1.0, 1.0, 1.0); /* draw in red */

/* set up viewing */
/* 500 x 500 window with origin lower left */

      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      gluOrtho2D(0.0, 500.0, 0.0, 500.0);
      glMatrixMode(GL_MODELVIEW);
}


void display( void )
{

    glClear(GL_COLOR_BUFFER_BIT);  /*clear the window */
    for(int i = 0; i < pathcount; i++){
    drawDot(path[i]);
    }
    glFlush(); /* clear buffers */
 }

int main(int argc, char** argv){

    Read_SVG();

    glutInit(&argc,argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB); /* default, not needed */
    glutInitWindowSize(500,500); /* 500 x 500 pixel window */
    glutInitWindowPosition(0,0); /* place window top left on display */
    glutCreateWindow("Sierpinski Gasket"); /* window title */


    glutDisplayFunc(display); /* display callback invoked when window opened */

    myinit(); /* set attributes */

    glutMainLoop(); /* enter event loop */

    system("pause");
    return 0;
}
