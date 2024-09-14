#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>

float px, py; //player possition

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
    {1,0,0,0,0,0,0,0,0,0},
    {1,1,1,1,1,1,1,1,1,1}
};


void init() {
    glClearColor(0.3, 0.3, 0.3, 0.0); // Fundo cinza
    gluOrtho2D(0, 800, 600, 0);
    px = 300; py = 300;
}

void drawPlayer(){
    glColor3f(1, 0, 0);
    glPointSize(30);
    glBegin(GL_POINTS);
    glVertex2i(px, py);
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
            glVertex2i(xo, yo);
            glVertex2i(xo, yo+mapS);
            glVertex2i(xo+mapS, yo+mapS);
            glVertex2i(xo+mapS, yo);
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
    if(key== 'a') px-=10;
    if(key== 'd') px+=10;
    if(key== 'w') py-=10;
    if(key== 's') py+=10;
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