#include <math.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>

static void error_callback(int error, const char* description)
{
    fputs(description, stderr);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

// void dessinerRectangle(double x, double y)
// {

//     glBegin(GL_QUADS);
//     glVertex2d(-x/2, 0);
//     glVertex2d(x/2, 0);
//     glVertex2d(x/2, -y/2);
//     glVertex2d(-x/2, -y/2);
//     glEnd();

// }


/*
    Dessine un rectangle avec comme point de référence
    le milieu du côté gauche
*/
void dessineRectangle(double largeur,double hauteur)
{
    // glScalef(0.1f,0.1f,0.1f);
    glBegin(GL_QUADS);
    glVertex2d(0,-hauteur/2);
    glVertex2d(0,hauteur/2);
    glVertex2d(largeur,hauteur/2);
    glVertex2d(largeur,-hauteur/2);
    glEnd();
}

/*
    Dessine le repère actuel pour faciliter
    la compréhension des transformations.
    Utiliser « echelle » pour avoir un repère bien orienté et positionné
    mais avec une échelle différente.
*/
void dessinerRepere(unsigned int echelle = 1)
{
    glPushMatrix();
    glScalef(echelle,echelle,echelle);
    glBegin(GL_LINES);
    glColor3ub(0,0,255);
    glVertex2i(0,0);
    glVertex2i(1,0);
    glColor3ub(0,255,0);
    glVertex2i(0,0);
    glVertex2i(0,1);
    glEnd();
    glPopMatrix();
}



void    dessine()
{
 
    // dessinerRepere();
    glColor3ub(254,128,1);
    dessineRectangle(0.3,0.1);

    glTranslated(0.15, 0.05, 0);
    glRotated(70,0,0,1);
    glColor3ub(248,230,7);

    dessineRectangle(0.5,0.08);

    // glLoadIdentity( );
    // dessinerRepere();
    glTranslated(0.5,0,0);
    glRotated(-40,0,0,1);
    glColor3ub(186,234,21);
    dessineRectangle(0.25, 0.08);

    glTranslated(0.25,0,0);
    glRotated(-30, 0, 0, 1);
    
    glBegin(GL_LINES);
    glColor3ub(255,255,255);
    glVertex2f(0, 0);
    glVertex2f(0, -0.4);
    glEnd();

    glTranslated(0, -0.4, 0);
    dessinerRepere();
    glColor3ub(254,128,1);
    dessineRectangle(0.01,0.05);




    // glRotated(75,0,0,1);
    // dessinerRepere(50);


}

int main(void)
{
    GLFWwindow* window;
    glfwSetErrorCallback(error_callback);
    if (!glfwInit())
        exit(EXIT_FAILURE);
    window = glfwCreateWindow(1000, 800, "scop", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);


gluPerspective(70,(double)640/480,1,1000);
    // dessine();


    while (!glfwWindowShouldClose(window))
    {
        // float ratio;
        // int width, height;
        // glfwGetFramebufferSize(window, &width, &height);
        // ratio = width / (float) height;
        // glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        // glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
        
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        // dessine();

GLint i;
glBegin(GL_POLYGON);
for (i=0 ; i<6 ; i++)
glVertex2f(cos(2*i*M_PI/6), sin(2*i*M_PI/6));
glEnd();

        // glRotatef((float) glfwGetTime() * 50.f, 1.f, 0.f, 1.f);
        // glBegin(GL_QUADS);
        // glVertex3d(-0.75, 0.75, 0);
        // glVertex3d(0.75, 0.75, 0);
        // glColor3ub(0, 0, 255);
        // glVertex3d(0.75f, -0.75, 0);
        // glVertex3d(-0.75, -0.75, 0);
        // glColor3ub(255, 0, 0);
        // glEnd();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}

