//
//  main.cpp
//  MoveParticle_OpenGL-Xcode
//
//  Created by Josep on 8/11/18.
//  Copyright © 2018 Universitat de Lleida. All rights reserved.
//

#include <iostream>

// For Mac 
#include <GLUT/glut.h>
#pragma GCC diagnostic ignored "-Wall"

// For Linux :
// #include <GL/glut.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define WIDTH 600
#define HEIGHT 400

#define MOVE 1
#define QUIET 2

#define SPEED 10

float xr = 0, yr = 0; //to control the object’s movement


//-----------------------------------------------

void display();;
//void keyboard(unsigned char c,int x,int y);
void specialkey(int key, int x, int y);
void idle();

//-----------------------------------------------

class particle {
    
    float x,y;   //-- Current position
    float vx,vy; //-- Velocity vector
    int state;
    
    long time_remaining;
    
public:
    
    particle();
    void set_position(int x,int y);
    void init_movement(int destination_x,int destination_y,int duration);
    void integrate(long t);
    void draw();
    
    void stopMovement();
    void getState();
    int getPositionX();
    int getPositionY();
};


//-----------------------------------------------

particle::particle()
{
    state=QUIET;
}

//-----------------------------------------------

void particle::set_position(int x,int y)
{
    this->x = x;
    this->y = y;
}

int particle::getPositionX()
{
    return x;

}

int particle::getPositionY()
{
    return y;
    
}


//-----------------------------------------------

void particle::init_movement(int destination_x,int destination_y,int duration)
{
    vx = (destination_x - x)/duration;
    vy = (destination_y - y)/duration;
    
    state=MOVE;
    time_remaining=duration;
}

void particle::stopMovement()
{
    state=QUIET;
    time_remaining=0;
}

//-----------------------------------------------

void particle::integrate(long t)
{
    if(state==MOVE && t<time_remaining)
    {
        x = x + vx*t;
        y = y + vy*t;
        time_remaining-=t;
    }
    else if(state==MOVE && t>=time_remaining)
    {
        x = x + vx*time_remaining;
        y = y + vy*time_remaining;
        state=QUIET;
    }
}

//-----------------------------------------------

void particle::draw()
{
    glColor3f(1,0,0); // RGB color : 1,1,1 white
    glBegin(GL_QUADS);
        glVertex2i(x-6,y-6);
        glVertex2i(x+6,y-6);
        glVertex2i(x+6,y+6);
        glVertex2i(x-6,y+6);
    glEnd();
}

void particle::getState()
{

}

//-----------------------------------------------
// -- MAIN
//-----------------------------------------------

particle square;
long last_t=0;

int main(int argc,char *argv[])
{
    srand((unsigned int)time(NULL));
    square.set_position(50,50);
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("Variable Frame Rate");
    
    glutDisplayFunc(display);
    //glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialkey); // keyboard call back function
    
    glutIdleFunc(idle);
    
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0,WIDTH-1,0.0,HEIGHT-1);
    
    glutMainLoop();
    return 0;
}


//-----------------------------------------------
//-----------------------------------------------
void display()
{
    glClearColor(0,0,0,0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    
    square.draw();
    
    glutSwapBuffers();
}

//-----------------------------------------------
//-----------------------------------------------

void keyboard(unsigned char c,int x,int y)
{
    
};


// lets now setup our keyboard controlling function
void specialkey(int key, int x, int y){
    switch (key) {
            //when the up key is pressed
        case GLUT_KEY_UP:
            square.init_movement(square.getPositionX(),HEIGHT,2000);
            //yr =yr + SPEED;
            glutPostRedisplay();
            break;
        case GLUT_KEY_DOWN: //when the down arrow key is pressed
             square.init_movement(square.getPositionX(),0,2000);
            // yr = yr - SPEED;
            glutPostRedisplay();
            break;
            //when the left arrow key is pressed
        case GLUT_KEY_LEFT:
            square.init_movement(0,square.getPositionY(),2000);
            //xr = xr - SPEED;
            glutPostRedisplay();
            break;
        case GLUT_KEY_RIGHT: //when the right arrow key is pressed
            square.init_movement(WIDTH,square.getPositionY(),2000);
            // xr = xr + SPEED;
            glutPostRedisplay();
            break;
        case ' ' :
            std::cout<<"Space pressed"<<std::endl;
            square.stopMovement();
            
            /*if (square.getState() ==QUIET){
                
            }else{
                // pause particle
                square.stopMovement;
            }
*/
            break;
    }
    std::cout<<x<<std::endl;
    
}


//-----------------------------------------------
//-----------------------------------------------

void idle() //inactividad
{
    long t;
    
    t=glutGet(GLUT_ELAPSED_TIME);
    
    if(last_t==0)
        last_t=t;
    else
    {
        square.integrate(t-last_t);
        last_t=t;
    }
    
    glutPostRedisplay();
}
