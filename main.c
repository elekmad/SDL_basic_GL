#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#define SPEED_RATE 0.5f

static GLfloat rotation = 0.5f, rotationspeed=0;
static uint32_t delay = 0;

int opengl_init() 
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
//To set up orthogonal 3D view, see http://en.wikipedia.org/wiki/File:Graphical_projection_comparison.png for examples
    glOrtho(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

//To enable depth rendering, otherwhise, front may be display even if invisible
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_LINE_STIPPLE);
    glEnable(GL_POINT_SMOOTH);
//    glEnable(GL_POLYGON_SMOOTH);
//    glEnable(GL_POLYGON_STIPPLE);

    glDepthFunc(GL_LEQUAL);
    glShadeModel(GL_SMOOTH);
    glClearColor(0, 0, 0, 0);
    
    
    
    if(glGetError() != GL_NO_ERROR)
    {
        return -1;
    }
    
    return 0;
}


void draw_cube()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
//    glTranslatef(0.0f, 0.0f, -6.0f);
    glRotatef(rotation, 1.0f, 1.5f, 0.0f);
    
    glBegin(GL_QUADS);
    
    /* Cube Top */
    glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);
    
    
    /* Cube Bottom */
    glColor4f(1.0f, 0.5f, 0.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);
    
    /* Cube Front */
    glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    
    /* Cube Back */
    glColor4f(0.0f, 1.0f, 0.5f, 1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    
    /* Cube Left Side */
    glColor4f(0.5f, 0.5f, 0.5f, 1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    
    /* Cube Right Side */
    glColor4f(0.15f, 0.25f, 0.75f, 1.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);
    
    
    glEnd();
    //glLoadIdentity();
    uint32_t new_tick = SDL_GetTicks();
    if(new_tick - delay > 100)
    {
		delay = new_tick;
		rotation += rotationspeed;
                if(rotation > 360)
                    rotation -= 360;
                if(rotation < 0)
                    rotation += 360;
		printf("rotation of %f\n", rotation);
    }
}

int main( int argc, char *argv[ ] )
{
    SDL_Window *window;
    if( SDL_Init( SDL_INIT_VIDEO ) == -1 )
    {
        printf( "Can't init SDL:  %s\n", SDL_GetError( ) );
        return EXIT_FAILURE;
    }

    if( SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1) == -1)
    {
        printf( "Can't set attribute DOUBLE BUFFER :  %s\n", SDL_GetError( ) );
        return EXIT_FAILURE;
    }
    atexit( SDL_Quit );
    SDL_Surface *surface;
    window = SDL_CreateWindow("Ma fenêtre de jeu", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_OPENGL );

    SDL_GLContext *glcontext;
    glcontext = SDL_GL_CreateContext(window);

    if( opengl_init() == -1)
    {
        printf("Error at opengl init\n");
        return EXIT_FAILURE;
    }

    int nValue;
    if( SDL_GL_GetAttribute(SDL_GL_DOUBLEBUFFER, &nValue) < 0)
    {
        printf("Echec de recuperation du parametre SDL_GL_DOUBLEBUFFER : %s\n", SDL_GetError());
        return (EXIT_FAILURE);
    }

    // assurons nous que le mode "double buffer" est bien actif
    if(nValue != 1)
    {
        printf("Erreur : SDL_GL_DOUBLEBUFFER inactif : %d\n", nValue);
        return (EXIT_FAILURE);
    }

    surface = SDL_GetWindowSurface(window);

    if( surface == NULL )
    {
        printf( "Can't set video mode: %s\n", SDL_GetError( ) );
        return EXIT_FAILURE;
    }   

    // Main loop
    SDL_Event event;
    while(1)
    {

       // Check for messages
        if (SDL_PollEvent(&event))
        {
            // Check for the quit message
            switch (event.type)
            {
                case SDL_QUIT:
                    SDL_Quit();
                    return EXIT_SUCCESS;// Quit the program
                    break;
				case SDL_KEYUP:
				case SDL_KEYDOWN:
					printf("keydown %d\n", event.key.keysym.sym);
					switch(event.key.keysym.sym)
					{
					case SDLK_DOWN:
						rotationspeed = (event.type == SDL_KEYDOWN ? rotationspeed + SPEED_RATE : rotationspeed);
						break;
					case SDLK_UP:
						rotationspeed = (event.type == SDL_KEYDOWN ? rotationspeed - SPEED_RATE : rotationspeed);
						break;
					case SDLK_ESCAPE:
						SDL_Quit();
						return EXIT_SUCCESS;// Quit the program
						break;
					}
					printf("speed %f\n", rotationspeed);
					break;
            }
        }
       
        //Update the display

        //Erase screen
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

        SDL_GL_MakeCurrent(window, glcontext);
        int h, w;
        SDL_GL_GetDrawableSize(window, &w, &h);
        glViewport(0, 0, (GLint)w, (GLint)h);
        draw_cube();
        //Swap the GL bufers, front and back.
        SDL_GL_SwapWindow(window);
        
    }

    // Tell the SDL to clean up and shut down
    SDL_Quit();

    return EXIT_SUCCESS;
}
