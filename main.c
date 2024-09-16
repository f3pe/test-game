#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#define PI 3.141592653




float px, py, pdx, pdy, pa; //player possition

/* Map config*/
int mapX = 10, mapY=10, mapS = 60;
int map[10][10] =
{
    {1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1}
};


void init() {
    glClearColor(0.3, 0.3, 0.3, 0.0); // Fundo cinza
    gluOrtho2D(0, 800, 600, 0);
    px = 300; py = 300; pa = 0; pdx = cos(pa)*5; pdy = sin(pa)*5;
}

void drawPlayer(){
    glColor3f(1, 0, 0);
    glPointSize(10);
    glBegin(GL_POINTS);
    glVertex2i(px, py);
    glEnd();

    glLineWidth(3);
    glBegin(GL_LINES);
    glVertex2i(px, py);
    glVertex2i(px+pdx*5,py+pdy*5);
    glEnd();
}

void drawMap2D(){
    int x, y, xo, yo;
    for(y = 0; y < mapY; y++){
        for(x = 0; x < mapX; x++){
            if(map[y][x] == 1){ 
                glColor3f(0, 0, 0.75);
            }else{ 
                glColor3f(0, 0, 0);
            }
            xo = x*mapS; yo = y*mapS;
            glBegin(GL_QUADS);
            glVertex2i(xo + 1, yo + 1);
            glVertex2i(xo + 1, yo+mapS - 1);
            glVertex2i(xo+mapS - 1, yo+mapS - 1);
            glVertex2i(xo+mapS - 1, yo + 1);
            glEnd();
        }
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    drawMap2D();
    drawPlayer();
    glutSwapBuffers();
}

void buttons(unsigned char key, int x, int y){
    if(key == 'a'){
        pa -= 0.1; 
        if(pa < 0) pa += 2*PI;
        pdx = cos(pa)*5;
        pdy = sin(pa)*5;
    } 
    if(key == 'd') {
        pa += 0.1;
        if(pa > 2*PI) pa -= 2*PI;
        pdx = cos(pa)*5;
        pdy = sin(pa)*5;
    };
    if(key == 'w') {
        px += pdx;
        py += pdy;
    }
    if(key == 's') {
        px -= pdx;
        py -= pdy;
    }
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Raycaster - Felipe Coutinho");
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(buttons);
    glutMainLoop();
    return 0;
}