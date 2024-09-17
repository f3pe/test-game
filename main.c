#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#define PI 3.141592653

float px, py, pdx, pdy, pa; //player possition

/* Map config*/
int mapX = 8, mapY=8, mapS = 64;
int map[] =
{
    1,1,1,1,1,1,1,1,
    1,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,1,
    1,1,1,1,1,1,1,1,
};

void setDeltaPlayer(){
    pdx = cos(pa)*5; pdy = sin(pa)*5;
}

void init() {
    glClearColor(0.3, 0.3, 0.3, 0.0); // Fundo cinza
    gluOrtho2D(0, 800, 600, 0);
    px = 300; py = 300; pa = 0; 
    setDeltaPlayer();
}

void drawRays3D(){
    int r, mx, my, mp, dof; 
    float rx, ry, ra, xo, yo;
    ra=pa;
    for(r = 0; r < 1 ; r++){
        dof=0;
        float aTan = -1/tan(ra);
        if(ra > PI){
            ry = (((int)py>>6)<<6) - 0.0001;
            rx = (py-ry) * aTan+px;
            yo = -64;
            xo = -yo*aTan;
        }
        if(ra < PI){
            ry = (((int)py>>6)<<6) + 64;
            rx = (py-ry) * aTan+px;
            yo = 64;
            xo = -yo*aTan;
        }
        if(ra == 0 || ra == PI){
            rx = px;
            ry = py;
            dof = 8;
        }
        while(dof < 8){
            mx=(int)(rx) >> 6;
            my=(int)(ry) >> 6;
            mp = my * mapX+mx;
            if((mp < mapX * mapY) && (map[mp] == 1)){//hit wall
                dof = 8;
            }
            else{
                rx += xo;
                ry += yo;
                dof++;
            }
        }
        glColor3f(.6, .6, .6);
        glLineWidth(2);
        glBegin(GL_LINES);
        glVertex2i(px, py);
        glVertex2i(rx, ry);
        glEnd();
    }
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
            if(map[y*mapX+x] == 1){ 
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
    drawRays3D();
    glutSwapBuffers();
}

void buttons(unsigned char key, int x, int y){
    if(key == 'a'){
        pa -= 0.1; 
        if(pa < 0) pa += 2*PI;
        setDeltaPlayer();
    } 
    if(key == 'd') {
        pa += 0.1;
        if(pa > 2*PI) pa -= 2*PI;
        setDeltaPlayer();
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