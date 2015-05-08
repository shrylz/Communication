#include <SDL.h>
#include <SDL_ttf.h>
#include <stdio.h>

void screen_init();
void ttf_init();
void drawLine(int x, int y, int w, int h);
void drawRectGreen(int x, int y, int w, int h);
void drawRectLightGray(int x, int y, int w, int h);
void text(int x, int y, int w, int h, char *txt,TTF_Font *font);
void matrix();
void rowLines();
void colLines();
void viewpoints();
void instructions();
void textField();

SDL_Surface* screen;
TTF_Font *font25, *font30;
SDL_Color color = {0,0,0};

char matrixLetters[6][100] = {{"E      A      R       I        .       ?    SPC BCK"},
							  {"O   T   N   S   B   F   Y   W"},
							  {"L   C   U   D   K   V   X   Z"},
							  {"P   M   H   G   J   Q   1   2"},
							  {"3   4   5   6   7   8   9   0"},
							  {"+   -   =   &   /   '   !   TTS"}};

int main(int argc, char *argv[])
{
	char  title[75] = "COMMUNICATION AID USING ELECTROOCULOGRAPHY WITH TEXT-TO-SPEECH";
	
	SDL_Event event;
	Uint8 done = 0;
	
	screen_init();
	ttf_init();
	
	text(60,50,1000,40,title,font30);
	
	matrix();
	viewpoints();
	instructions();
	textField();
		
	SDL_Flip(screen);
	while (!done)
	{
	/* Check for events */
		while (SDL_PollEvent(&event))
		{
			fflush(stdin);
			if(event.type == SDL_QUIT)
			{
				done = 1;
			}
			if(event.type == SDL_KEYDOWN)
			{
				if(event.key.keysym.sym == SDLK_ESCAPE)
				{
					 done = 1;
				}
			}
		}
	}
	SDL_Quit();
	return;
}	
		
void screen_init()
{
	/* Initialize SDL */
	SDL_Init(SDL_INIT_VIDEO); 
	/* Initialize the screen surface */
	screen = SDL_SetVideoMode(0, 0, 32, SDL_FULLSCREEN);
	
	/* gray background */ 
	SDL_Rect bg = {0, 0, 1360, 770};
	SDL_FillRect(screen, &bg, SDL_MapRGB(screen->format, 211, 211, 211));
}

void ttf_init()
{
	TTF_Init();
	
	font25 = TTF_OpenFont("BookAntiqua.ttf",25);
	font30 = TTF_OpenFont("BookAntiqua.ttf",30);
}

void drawLine(int x, int y, int w, int h)
{
	SDL_Rect line = {x,y,w,h};
	SDL_FillRect(screen, &line, SDL_MapRGB(screen->format, 0, 0, 0));
}

void drawRectGreen(int x, int y, int w, int h)
{
	SDL_Rect greenBox = {x,y,w,h};
	SDL_FillRect(screen, &greenBox, SDL_MapRGB(screen->format, 50, 205, 50));	
}

void drawRectLightGray(int x, int y, int w, int h)
{
	SDL_Rect greenBox = {x,y,w,h};
	SDL_FillRect(screen, &greenBox, SDL_MapRGB(screen->format, 245, 245, 245));	
}

void text(int x, int y, int w, int h, char *txt, TTF_Font *f)
{
	SDL_Rect t = {x,y,w,h};
	SDL_Surface *txtSurface = TTF_RenderText_Solid(f,txt, color); 
	SDL_BlitSurface(txtSurface,NULL,screen,&t);
		
}

void matrix()
{
	int i, j,line_x=108,line_y=140;
	drawRectLightGray(80,125,560,420);
    rowLines();	
    colLines();
    
    text(110,90,30,30,"1         2          3          4         5         6          7         8",font25);
    text(55,145,30,30,"1",font25);
    text(55,215,30,30,"2",font25);
    text(55,285,30,30,"3",font25);
    text(55,355,30,30,"4",font25);
    text(55,425,30,30,"5",font25);
    text(55,495,30,30,"6",font25);
    
    for(i=0;i<1;i++)
    {
		text(line_x,line_y,30,30,matrixLetters[i],font30);
	}
}

void rowLines()
{
	drawLine(80,125,560,2);
	drawLine(80,195,560,2);
	drawLine(80,265,560,2);
	drawLine(80,335,560,2);
	drawLine(80,405,560,2);
	drawLine(80,475,560,2);
	drawLine(80,545,561,2);
}

void colLines()
{
	drawLine(80,125,2,420);
	drawLine(150,125,2,420);
	drawLine(220,125,2,420);
	drawLine(290,125,2,420);
	drawLine(360,125,2,420);
	drawLine(430,125,2,420);
	drawLine(500,125,2,420);
	drawLine(570,125,2,420);
	drawLine(640,125,2,421);
}

void viewpoints(void)
{
	drawRectGreen(0,0,40,40);							//8
	text(12,0,30,30,"8",font30);
	drawRectGreen(670,0,40,40);							//1
	text(682,0,30,30,"1",font30);
	drawRectGreen(1320,0,40,40);						//5
	text(1332,0,30,30,"5",font30);
	drawRectGreen(0,365,40,40);							//4
	text(12,365,30,30,"4",font30);
	drawRectGreen(670,365,40,40);						//C
	text(680,365,30,30,"C",font30);
	drawRectGreen(1320,365,40,40);						//2
	text(1332,365,30,30,"2",font30);
	drawRectGreen(0,730,40,40);							//7
	text(12,730,30,30,"7",font30);
	drawRectGreen(670,730,40,40);						//3
	text(682,730,30,30,"3",font30);
	drawRectGreen(1320,730,40,40);						//6
	text(1332,730,30,30,"6",font30);
}

void instructions()
{
	drawRectLightGray(750,125,530,420);
	drawLine(750,125,530,2);
	drawLine(750,545,531,2);
	drawLine(750,125,2,420);
	drawLine(1280,125,2,421);
	text(900,90,30,30,"INSTRUCTIONS",font25);
	text(765,125,30,30,"Steps to select a character:",font25);
	text(765,155,30,30,"1. Look at the 'C' in green box.",font25);
	text(765,185,30,30,"2. Wait for the 'C' box to change into red.",font25);
	text(765,215,30,30,"3. Select row no. by looking at the no.",font25);
	text(765,245,30,30,"    in a green box.",font25);
	text(765,275,30,30,"4. Wait for the row in the matrix to be",font25);
	text(765,305,30,30,"    highlighted.",font25);
	text(765,335,30,30,"5. Repeat steps 1 and 2.",font25);
	text(765,365,30,30,"6. Select column no. by looking at the no.",font25);
	text(765,395,30,30,"    in a green box.",font25);
	text(765,425,30,30,"7. Wait for the character to be highlighted.",font25);
	text(765,455,30,30,"    and displayed in text box.",font25);
	text(765,485,30,30,"  LEGEND: SPC=Space   BCK=Backspace",font25);
	text(900,515,30,30,"TTS=Text-to-Speech",font25);
	
}

void textField()
{
	drawRectLightGray(80,600,1200,50);
	drawLine(80,600,1200,2);
	drawLine(80,650,1201,2);
	drawLine(80,600,2,50);
	drawLine(1280,600,2,51);
}
