#include <stdio.h>
#include <SDL2/SDL.h>
#include <math.h>

#define WIDTH 900
#define HEIGHT 600
#define COLOR_WHITE 0xffffffff
#define COLOR_BLACK 0x00000000

struct Circle
{
	double x;
	double y;
	double radius;
};

void FillCircle(SDL_Surface* surface, struct Circle circle, Uint32 color)
{
	// Creamos un cuadrado donde estara el circulo
	double radius_squared = pow(circle.radius,2);
	for (double x=circle.x-circle.radius; x<=circle.x+circle.radius;x++)
	{
		for(double y=circle.y-circle.radius; y<=circle.y+circle.radius;y++)
		{
			// Ahora, los px que esten dentro del radio se colorean
			double distance_squared = pow(x-circle.x,2) + pow(y-circle.y,2);
			if (distance_squared < radius_squared)
			{
				SDL_Rect pixel = (SDL_Rect){x,y,1,1};
				SDL_FillRect(surface, &pixel, color);
			}

		}
	}
}

int main()
{
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window* window = SDL_CreateWindow("Raytracing", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);

	SDL_Surface* surface = SDL_GetWindowSurface(window);

	struct Circle circle = {200,200,80};
	SDL_Rect erase_rect = {0,0,WIDTH,HEIGHT};	

	int simulation_running = 1;
	SDL_Event event;
	// Con este while hacemos que el circulo siga al mouse
	while(simulation_running)
	{
		while(SDL_PollEvent(&event))
		{
			if(event.type == SDL_QUIT)
			{
				simulation_running = 0;
			}
			if(event.type == SDL_MOUSEMOTION && event.motion.state != 0)
			{
				circle.x = event.motion.x;
				circle.y = event.motion.y;
			}
		}
		// Borramos la pantalla entera(rect) y ponemos el circulo donde el mouse
		SDL_FillRect(surface, &erase_rect, COLOR_BLACK);
		FillCircle(surface,circle,COLOR_WHITE);

		SDL_UpdateWindowSurface(window);
		SDL_Delay(10);
	}	

}
