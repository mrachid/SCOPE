#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <GLFW/glfw3.h>
// #include <GLES3/gl3.h>

/* Dimension i n i t i a l e de l a f e n ê t r e graphique */
GLushort largeur_fenetre = 1000 ;
GLushort hauteur_fenetre = 800 ;
GLint nvertices =4, nfaces =4 ;

GLfloat vertices[][3] = {
	{400.0 , 400.0 , -10.0} ,
	{700.0 , 700.0 , -10.0} ,
	{0.0 , 500.0 , -10.0} ,
	{500.0 , 0.0 , -500.0}
};

GLuint faces[][3] = {
	{0 , 1 , 2} ,
	{0 , 1 , 3} ,
	{0 , 2 , 3} ,
	{1 , 2 , 3}
	} ;
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

void Affichage ( void)
{
int i , j ;
glClearColor(1.0,1.0,1.0,1.0) ;
glClear(GL_COLOR_BUFFER_BIT) ;
glColor3f(0.0,0.0,0.0) ;
glLineWidth (2) ;
glBegin (GL_TRIANGLES) ;
for ( i=0 ; i<nfaces ; i++)
for ( j=0 ; j <3 ; j++)
glVertex3fv(vertices[faces[i][j]]) ;
glEnd ( ) ;
}


// /** @brief Fonction d ’ a f f i c h a g e appelée périodiquement */
// void Affichage ( ) {
// 	/* Couleur de fond rouge */
// 	/* c o e f f i c i e n t s RGB + A de l a couleur de fond : */
// 	// glClearColor( 1.0 , 0.0 , 0.0 , 1.0);
// 	glBegin(GL_TRIANGLES);
// 	glVertex2f(0.0, 0.0);
// 	glVertex2f(1.0, 0.0);
// 	glVertex2f(0.0, 1.0);
// 	glEnd();
// 	/* On e f f a c e l e contenu de l a f e n ê t r e */
// 	glClear(GL_COLOR_BUFFER_BIT) ;
// }

/** @brief Fonction d ’ i n i t i a l i s a t i o n de l a f e n ê t r e SDL
	@param windowWidth l a r g e u r de l a f e n ê t r e en p i x e l s
	@param windowWidth l a r g e u r de l a f e n ê t r e en p i x e l s
	@param windowTitle Titre de l a f e n ê t r e dans sa barre de t i t r e
*/
SDL_Window * init_SDL_Window( int windowWidth , int windowHeight , const char* windowTitle ) 
{
	SDL_GL_SetAttribute (SDL_GL_CONTEXT_MAJOR_VERSION, 3 ) ;
	SDL_GL_SetAttribute (SDL_GL_CONTEXT_MINOR_VERSION, 3 ) ;
	SDL_Init (SDL_INIT_VIDEO) ;
	/* Le double b u f f e r i n g permet l e s animations temps r é e l */
	SDL_GL_SetAttribute (SDL_GL_DOUBLEBUFFER, 1) ;
	SDL_Window *window = SDL_CreateWindow( windowTitle , SDL_WINDOWPOS_CENTERED,
	SDL_WINDOWPOS_CENTERED, windowWidth , windowHeight , SDL_WINDOW_SHOWN |
	SDL_WINDOW_OPENGL) ;
	return window ;
}

int main ( int argc , char** argv )
{
	printf("test\n");
	/* I n i t i a l i s a t i o n d ’ une f e n ê t r e SDL */
	SDL_Window *window = init_SDL_Window(largeur_fenetre ,hauteur_fenetre , "Premier programme OpenGL avec SDL");
	/* d é f i n i t i o n du contexte OpenGL a s s o c i é à c e t t e f e n ê t r e */
	SDL_GLContext 	glcontext(SDL_GL_CreateContext(window));

	/* Affichage console de l a version d ’OpenGL et GLSL d i s p o n i b l e */
	printf("OpenGL%s , GLSL%s \n" , glGetString (GL_VERSION) ,
	glGetString (GL_SHADING_LANGUAGE_VERSION) ) ;

	glPolygonMode (GL_FRONT_AND_BACK, GL_LINE) ;
	/* D é f i n i t i o n du volume v i s i b l e */
	/* Nécessaire pour a f f i c h e r des o b j e t s géométriques */
	/* v o i r Chapitre suivant pour p e r s o n a l i s e r */
	glMatrixMode (GL_PROJECTION) ;
	glLoadIdentity ( ) ;
	glOrtho (0 , largeur_fenetre , 0 , hauteur_fenetre , 1 , 600) ;
	glMatrixMode (GL_MODELVIEW) ;
	glLoadIdentity ( ) ;

	/* *****************************************************************\
	| Boucle récupérant l e s évennements SDL et a f f i c h a n t périodiquement |
	\***************************************************************** */
	bool terminer = false;
	SDL_Event evenements; /* union contenant un évennement */
	GLint currentTime , nextDueFrameDate = 0; /* pour timer a f f i c h a g e */

	int nbFrames=0 ; /* compteur de frames */
	while ( ! terminer )
	{
		while ( SDL_PollEvent(&evenements ) ) /* on d é f i l e l e s évennements */
		{
			switch ( evenements . type ) { /* suivant l e type d ’ évennement */
				case SDL_QUIT : /* fermeture de l a f e n ê t r e */
					terminer = true ;
					break ;
				case SDL_KEYDOWN : /* fermeture de l a f e n ê t r e */
					switch(evenements.key.keysym.sym)
		            {
		                case SDLK_ESCAPE:
							terminer = true ;
							break;
		            }
		            break;
			}
 		}

		/* g e s t i o n des frames par secondes ( i c i 50 f p s ) */
		currentTime = SDL_GetTicks(); /* date courante en m i l l i s e c o n d e */

		if(currentTime > nextDueFrameDate)
		{
	 		nextDueFrameDate = currentTime + 20; /* t o u t e s l e s 20 m i l l i s e c o n d e s */
			dessinerRepere(50);
			Affichage(); /* on r a f f r a i c h i t l a vue */
			nbFrames++; /* On incrémente l e compteur de frames */
			SDL_GL_SwapWindow(window); /* On envoie l e b u f f e r à l ’ écran */
	 	}
 	}
	// Libération des ressources SDL
	SDL_GL_DeleteContext(glcontext);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
 }