#include "main.hpp"

SDL_Renderer* gRenderer = NULL;
SDL_Window* gWindow = NULL;

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( "Evacuation Simulation", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create vsynced renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
			}
		}
	}

	return success;
}

void close()
{
	//Destroy window	
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

void init_walls(std::vector<SDL_Rect> &walls)
{
    walls[0].x = 50;
    walls[0].y = 50;
    walls[0].w = 490;
    walls[0].h = 30;

    walls[1].x = 50;
    walls[1].y = 280;
    walls[1].w = 120;
    walls[1].h = 30;

    walls[2].x = 190;
    walls[2].y = 280;
    walls[2].w = 210;
    walls[2].h = 30;

    walls[3].x = 420;
    walls[3].y = 280;
    walls[3].w = 120;
    walls[3].h = 30;

    walls[4].x = 50;
    walls[4].y = 510;
    walls[4].w = 350;
    walls[4].h = 30;

    walls[5].x = 420;
    walls[5].y = 510;
    walls[5].w = 120;
    walls[5].h = 30;

    walls[6].x = 50;
    walls[6].y = 50;
    walls[6].w = 30;
    walls[6].h = 120;

    walls[7].x = 50;
    walls[7].y = 190;
    walls[7].w = 30;
    walls[7].h = 350;

    walls[8].x = 280;
    walls[8].y = 50;
    walls[8].w = 30;
    walls[8].h = 120;

    walls[9].x = 280;
    walls[9].y = 190;
    walls[9].w = 30;
    walls[9].h = 210;

    walls[10].x = 280;
    walls[10].y = 420;
    walls[10].w = 30;
    walls[10].h = 120;

    walls[11].x = 510;
    walls[11].y = 50;
    walls[11].w = 30;
    walls[11].h = 490;
}

int main( int argc, char* args[] )
{
	//Start up SDL and create window
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{	
		//Main loop flag
		bool quit = false;

		//Event handler
		SDL_Event e;

		//The dot that will be moving around on the screen
		Person p1(100, 100, 7.5);
		// otherDot( SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4 );

		//Set the wall
		std::vector<SDL_Rect> walls(12);
		init_walls(walls);
		
		//While application is running
		while( !quit )
		{
			//Handle events on queue
			while( SDL_PollEvent( &e ) != 0 )
			{
				//User requests quit
				if( e.type == SDL_QUIT )
				{
					quit = true;
				}

			}

			//Clear screen
			SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
			SDL_RenderClear( gRenderer );
			
			//Render wall
			SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0xFF );
			for(int i=0; i<12; i++)
			{
				SDL_RenderDrawRect( gRenderer, &walls[i] );
			}						

			//Render person
			p1.render();

			//Update screen
			SDL_RenderPresent( gRenderer );
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}