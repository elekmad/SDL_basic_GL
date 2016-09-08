#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <GL/glut.h>

#define SPEED_RATE 0.5f

static GLfloat rotation = 2.5f, rotationspeed=1, t_x=0.0f, t_y=0.0f, t_z=0.0f;
static uint32_t delay = 0;

int opengl_init() 
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_LINE_STIPPLE);
    glEnable(GL_POINT_SMOOTH);
}

int opengl_clear(SDL_Window *window) 
{
    int h, w;
    SDL_GL_GetDrawableSize(window, &w, &h);
    glViewport(0, 0, w, h);
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
//To set up orthogonal 3D view, see http://en.wikipedia.org/wiki/File:Graphical_projection_comparison.png for examples
    glOrtho(-10.0, 10.0, -10.0, 10.0, -10.0, 10.0);

    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    return 0;
}


void draw_cube()
{
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
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_GetAttribute(SDL_GL_DEPTH_SIZE, &nValue);
    printf("Depth %d\n", nValue);

    surface = SDL_GetWindowSurface(window);

    if( surface == NULL )
    {
        printf( "Can't set video mode: %s\n", SDL_GetError( ) );
        return EXIT_FAILURE;
    }   

    opengl_init();
    // Main loop
    SDL_Event event;
    while(1)
    {
        opengl_clear(window);

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
					//printf("keydown %d\n", event.key.keysym.sym);
					switch(event.key.keysym.sym)
					{
					case SDLK_DOWN:
						t_y += (event.type == SDL_KEYDOWN ? SPEED_RATE : 0);
                                                printf("y = %f\n", t_y);
						break;
					case SDLK_UP:
						t_y -= (event.type == SDL_KEYDOWN ? SPEED_RATE : 0);
                                                printf("y = %f\n", t_y);
						break;
					case SDLK_LEFT:
						t_x += (event.type == SDL_KEYDOWN ? SPEED_RATE : 0);
                                                printf("y = %f\n", t_x);
						break;
					case SDLK_RIGHT:
						t_x -= (event.type == SDL_KEYDOWN ? SPEED_RATE : 0);
                                                printf("x = %f\n", t_x);
						break;
					case SDLK_PAGEUP:
						t_z += (event.type == SDL_KEYDOWN ? SPEED_RATE : 0);
                                                printf("z = %f\n", t_z);
						break;
					case SDLK_PAGEDOWN:
						t_z -= (event.type == SDL_KEYDOWN ? SPEED_RATE : 0);
                                                printf("z = %f\n", t_z);
						break;


					case SDLK_ESCAPE:
						SDL_Quit();
						return EXIT_SUCCESS;// Quit the program
						break;
					}
					//printf("speed %f\n", rotationspeed);
					break;
            }
        }
       
        uint32_t new_tick = SDL_GetTicks();
        if(new_tick - delay > 100)
        {
            delay = new_tick;
            rotation += rotationspeed;
            if(rotation > 360)
                rotation -= 360;
            if(rotation < 0)
                rotation += 360;
            //printf("rotation of %f\n", rotation);
        }

        glRotatef(rotation, 1.0f, 1.5f, 0.0f);

        draw_cube();
        //Swap the GL bufers, front and back.
        SDL_GL_SwapWindow(window);
        
    }

    // Tell the SDL to clean up and shut down
    SDL_Quit();

    return EXIT_SUCCESS;
}
