#include <stdio.h>
#include <SDL2/SDL.h>
#include <math.h>

#define WIDTH 900
#define HEIGHT 600
#define COLOR_WHITE 0xffffffff
#define COLOR_BLACK 0x00000000
#define COLOR_GRAY 0xefefefef
#define RAYS_NUMBER 100

struct Circle
{
	double x;
	double y;
	double radius;
};

struct Ray
{
	double x_start,y_start;
	double angle;
	double x_end,y_end;
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

void generate_rays(struct Circle circle ,struct Ray rays[RAYS_NUMBER])
{
	for(int i=0;i<RAYS_NUMBER;i++)
	{
		double angle = ((double) i/ RAYS_NUMBER)*2*M_PI;
		struct Ray ray = {circle.x,circle.y,angle};
		rays[i] = ray;
	}	
}

void FillRays(SDL_Surface* surface, struct Ray rays[RAYS_NUMBER], Uint32 color, struct Circle object)
{
	double radius_squared = pow(object.radius,2);
	for(int i=0;i<RAYS_NUMBER;i++)
	{
		struct Ray ray = rays[i];
		
		int end_of_screen = 0;
		int object_hit = 0;
		
		double step = 1;
		double x_draw = ray.x_start;
		double y_draw = ray.y_start;
		while (!end_of_screen && !object_hit)
		{
			x_draw += step*cos(ray.angle);
			y_draw += step*sin(ray.angle);

			SDL_Rect pixel = (SDL_Rect){x_draw,y_draw,1,1};
			SDL_FillRect(surface,&pixel,color);
			
			if(x_draw < 0 || x_draw > WIDTH)
				end_of_screen = 1;
			if(y_draw < 0 || y_draw > HEIGHT)
				end_of_screen = 1;
			// El rayo toca el objeto?
			double distance_squared = pow(x_draw-object.x,2)+pow(y_draw-object.y,2);
			if(distance_squared < radius_squared)
			{
				break;
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
	struct Circle shadow_circle = {650,300,140};
	SDL_Rect erase_rect = {0,0,WIDTH,HEIGHT};	
	
	struct Ray rays[RAYS_NUMBER];
	generate_rays(circle,rays);

	double obstacle_speed_y = 1;
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
				generate_rays(circle,rays);
			}
		}
		// Borramos la pantalla entera(rect) y ponemos el circulo donde el mouse
		SDL_FillRect(surface, &erase_rect, COLOR_BLACK);
		FillCircle(surface,circle,COLOR_WHITE);
		
		FillCircle(surface,shadow_circle,COLOR_WHITE);
		FillRays(surface,rays,COLOR_GRAY, shadow_circle);

		//move_shadow_circle(&shadow_circle);
		shadow_circle.y += obstacle_speed_y;
		if(shadow_circle.y-shadow_circle.radius < 0)
			obstacle_speed_y = -obstacle_speed_y;
		if(shadow_circle.y+shadow_circle.radius > HEIGHT)
			obstacle_speed_y = -obstacle_speed_y;

		SDL_UpdateWindowSurface(window);
		SDL_Delay(10);
	}	

}
