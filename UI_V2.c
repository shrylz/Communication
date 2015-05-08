#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>

void screen_init(void);
void createRect(int pos_x, int pos_y, int width, int height);
void matrix(void);
void rowLines(void);
void colLines(void);
void viewpoints(void);
void instructions(void);
void textField(void);

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Renderer* fontrenderer = NULL;
SDL_Rect r;

void main (void)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
	
	screen_init();
	matrix();
	viewpoints();
	instructions();
	textField();
	
	TTF_Font *font = TTF_OpenFont("arial.ttf",25);
	
	SDL_Color color = {0,0,0};
	SDL_Surface *surface = TTF_RenderText_Solid(font,"COMMUNICATION AID USING ELECTROOCULOGRAPHY WITH TEXT-TO-SPEECH", color); 
	SDL_Texture *texture = SDL_CreateTextureFromSurface(fontrenderer,surface);
	//SDL_QueryTexture(texture,NULL,NULL,0,0);
	//SDL_Rect t = {90, 80, 1300, 40};
	
	int texW = 0;
	int texH = 0;
	SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
	SDL_Rect t = { 0, 0, texW, texH };
	SDL_RenderCopy(fontrenderer,texture,NULL,&t);
	//SDL_BlitSurface(surface,NULL,surface,&t);
	
	// Render the UI to the screen
    SDL_RenderPresent(renderer);
    SDL_RenderPresent(fontrenderer);
	//SDL_Flip(surface);
	
	SDL_Delay(5000);	
	
	SDL_DestroyWindow(window);
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyRenderer(fontrenderer);
    SDL_Quit();
    TTF_Quit();
    TTF_CloseFont(font);
}

void screen_init(void)
{
	window = SDL_CreateWindow
	(
		"Communication Aid", SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		640,
		480,
		SDL_WINDOW_SHOWN
	);

	// Setup renderer
	
	renderer =  SDL_CreateRenderer( window, 0, SDL_RENDERER_ACCELERATED);
	fontrenderer =  SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED);

	// Set render color to gray ( background will be rendered in this color )
	SDL_SetRenderDrawColor( renderer, 211, 211, 211, 1 );

	// Clear window
	SDL_RenderClear( renderer );
}

void createRect(int pos_x, int pos_y, int width, int height)
{
	r.x = pos_x;
	r.y = pos_y;
	r.w = width;
	r.h = height;
}

void matrix(void)
{
	createRect(80,125,560,420);
	
	// Set render color to white smoke ( rect will be rendered in this color )
    SDL_SetRenderDrawColor( renderer, 245, 245, 245, 1 );

    // Render rect
    SDL_RenderFillRect( renderer, &r );
    
    //outline of rect
    SDL_Rect outlineMatrix = {80,125,560,420};
    SDL_SetRenderDrawColor( renderer, 0, 0, 0, 1 );
    SDL_RenderDrawRect( renderer, &outlineMatrix );
    
    rowLines();	
    colLines();
}

void rowLines(void)
{
	SDL_SetRenderDrawColor( renderer, 0, 0, 0, 1 );
	SDL_RenderDrawLine( renderer,80,195,639,195);
	SDL_RenderDrawLine( renderer,80,265,639,265);
	SDL_RenderDrawLine( renderer,80,335,639,335);
	SDL_RenderDrawLine( renderer,80,405,639,405);
	SDL_RenderDrawLine( renderer,80,475,639,475);
}

void colLines(void)
{
	SDL_SetRenderDrawColor( renderer, 0, 0, 0, 1 );
	SDL_RenderDrawLine( renderer,150,125,150,545);
	SDL_RenderDrawLine( renderer,220,125,220,545);
	SDL_RenderDrawLine( renderer,290,125,290,545);
	SDL_RenderDrawLine( renderer,360,125,360,545);
	SDL_RenderDrawLine( renderer,430,125,430,545);
	SDL_RenderDrawLine( renderer,500,125,500,545);
	SDL_RenderDrawLine( renderer,570,125,570,545);
}

void viewpoints(void)
{
	SDL_SetRenderDrawColor( renderer, 50, 205, 50, 1 );	//green color
	createRect(0,0,40,40);								//8
	SDL_RenderFillRect( renderer, &r );
	createRect(670,0,40,40);							//1
	SDL_RenderFillRect( renderer, &r );
	createRect(1320,0,40,40);							//5
	SDL_RenderFillRect( renderer, &r );
	createRect(0,380,40,40);							//4
	SDL_RenderFillRect( renderer, &r );
	createRect(670,380,40,40);							//C
	SDL_RenderFillRect( renderer, &r );
	createRect(1320,380,40,40);							//2
	SDL_RenderFillRect( renderer, &r );
	createRect(0,730,40,40);							//7
	SDL_RenderFillRect( renderer, &r );
	createRect(670,730,40,40);							//3
	SDL_RenderFillRect( renderer, &r );
	createRect(1320,730,40,40);							//6
	SDL_RenderFillRect( renderer, &r );
}

void instructions(void)
{
	createRect(750,125,530,420);
	
	// Set render color to white smoke ( rect will be rendered in this color )
    SDL_SetRenderDrawColor( renderer, 245, 245, 245, 1 );

    // Render rect
    SDL_RenderFillRect( renderer, &r );
    
    //outline of rect
    SDL_Rect outlineInst = {750,125,530,420};
    SDL_SetRenderDrawColor( renderer, 0, 0, 0, 1 );
    SDL_RenderDrawRect( renderer, &outlineInst );	
}


void textField(void)
{
	createRect(80,600,1200,50);
	
	// Set render color to white smoke ( rect will be rendered in this color )
    SDL_SetRenderDrawColor( renderer, 245, 245, 245, 1 );

    // Render rect
    SDL_RenderFillRect( renderer, &r );
    
    //outline of rect
    SDL_Rect outlineInst = {80,600,1200,50};
    SDL_SetRenderDrawColor( renderer, 0, 0, 0, 1 );
    SDL_RenderDrawRect( renderer, &outlineInst );	
}

