//
//  main.cpp
//  MoveObject_OpenGL
//
//  Created by Josep on 13/11/18.
//  Copyright © 2018 Universitat de Lleida. All rights reserved.
//


// First thing first, we have to include the essential files in our project file.

#include <iostream>
#include <stdlib.h>
#include <glut.h>

// including files

using namespace std;

#define WIDTH 600
#define HEIGHT 400
#define SPEED 50

// Initializing the variables which are going to affect the position of the object.
float xr = 0, yr = 0; //to control the object’s movement


// lets now setup our keyboard controlling function
void specialkey(int key, int x, int y){
    switch (key) {
            //when the up key is pressed
        case GLUT_KEY_UP:
            yr =yr + HEIGHT/SPEED;
            cout<<x<<endl;
            glutPostRedisplay();
            break;
        case GLUT_KEY_DOWN: //when the down arrow key is pressed
            yr = yr - HEIGHT/SPEED;
            cout<<x<<endl;
            glutPostRedisplay();
            break;
            //when the left arrow key is pressed
        case GLUT_KEY_LEFT:
            xr = xr - WIDTH/SPEED;
            cout<<x<<endl;
            glutPostRedisplay();
            break;
        case GLUT_KEY_RIGHT: //when the right arrow key is pressed
            xr = xr + WIDTH/SPEED;
            cout<<x<<endl;
            glutPostRedisplay();
            break;
    }
}

//Adding display function now
void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1,0, 0);
    glBegin(GL_QUADS);//object made with the help of quads
        glVertex2f(20+xr, 10+yr);
        glVertex2f(30+xr, 10+yr);
        glVertex2f(30+xr, 20+yr);
        glVertex2f(20+xr,20+yr);
    glEnd();
    glFlush();
    glutPostRedisplay();
    glutSwapBuffers();
}


//setting up our main function
int main(int argc, char **argv){
    // insert code here...

    printf("use array key");
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutInitWindowPosition(600,50);
    glutCreateWindow("Moving Square");
    
    glutDisplayFunc(display);//display call back function
    
    glClearColor(0, 0,0,0);
    gluOrtho2D(0.0,400,0.0,400);
    glutSpecialFunc(specialkey); // keyboard call back function
    
    glutMainLoop();
    return 0;
}