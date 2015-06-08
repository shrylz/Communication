#include <SDL.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
//#include "espeak/speak_lib.h"

void screen_init();
void ttf_init();
void drawLine(int x, int y, int w, int h);
void drawRectGreen(int x, int y, int w, int h);
void drawRectRed(int x, int y, int w, int h);
void drawRectLightGray(int x, int y, int w, int h);
void drawRectYellow(int x, int y, int w, int h);
void drawRectGray(int x, int y, int w, int h);
void drawRectSalmon(int x, int y, int w, int h);
void text(int x, int y, int w, int h, char *txt,TTF_Font *font);
void matrix();
void matrixText();
void rowLines();
void colLines();
void viewpoints();
void instructions();
void textField();
void centerRed();
void centerGreen();
void highlightRow1();
void highlightRow2();
void highlightRow3();
void highlightRow4();
void highlightRow5();
void highlightRow6();
char selectCharacter(int row,int col);
void selectedBSP(void);
void processSelected(char selected);
int displayChar(int row,int col);
void displayTextArea();
void tts();

SDL_Surface* screen;
TTF_Font *font25, *font30;
SDL_Color color = {0,0,0};


int word_index=0, tf_index=0, retVal=0, flagBSP=0, flagUseWord=0, mode_disp = 0, value=0;
int index1, line_x, line_y;

char /**ws_disp, word[30], buff[30],*/ textFieldVal[100], lower[100];

FILE *f;

char matrixVal[6][8] = {{'E','A','R','I','.','?',' ',' '},
                        {'O','T','N','S','B','F','Y','W'},
                        {'L','C','U','D','K','V','X','Z'},
                        {'P','M','H','G','J','Q','1','2'},
                        {'3','4','5','6','7','8','9','0'},
                        {'+','-','=','&','/','`','!',' '}};

char matrixLetters[6][100] = {{"E      A      R       I        .       ?    SPC BCK"},
							  {"O     T      N       S      B      F       Y     W"},
							  {"L      C      U      D      K      V      X      Z"},
							  {"P      M     H      G      J      Q       1       2"}, 
							  {"3       4       5       6       7       8       9      0"},
							  {"+       -       =      &       /        '       !     TTS"}};
							  
int mode=0, flag_row, row, col, wsflag;

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
	
	//SDL_Flip(screen);
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
				switch(mode)
				{
					case 0: //center
						if(event.key.keysym.sym == SDLK_c)
						{
							//mode = 1;
							if(!flag_row)
							{
								mode = 1;
								matrix();
							}
							else
							{
								mode = 2;
								flag_row = 0;
							}
							centerRed();
							SDL_Flip(screen);
						}
						break;
					case 1: //row
						row = event.key.keysym.sym-48;
						switch(row) 
						{
							case 1:
								highlightRow1();
								centerGreen();
								mode = 0;
								SDL_Flip(screen);
								break;
							case 2:
								highlightRow2();
								centerGreen();
								mode = 0;
								SDL_Flip(screen);
								break;
							case 3:
								highlightRow3();
								centerGreen();
								mode = 0;
								SDL_Flip(screen);
								break;
							case 4:
								highlightRow4();
								centerGreen();
								mode = 0;
								SDL_Flip(screen);
								break;
							case 5:
								highlightRow5();
								centerGreen();
								mode = 0;
								SDL_Flip(screen);
								break;
							case 6:
								highlightRow6();
								centerGreen();
								mode = 0;
								SDL_Flip(screen);
								break;
							default:
								mode = 1;
								break;
						}
						flag_row = 1;
						break;
					case 2: //col
						col = event.key.keysym.sym-48;
						if(col>0 && col<9)
						{
							//wsflag=displayChar(row,col);
							displayChar(row,col);
							//selectCharacter(row,col);
							centerGreen();
							mode = 0;
							row = 0;
							col = 0;
							SDL_Flip(screen);
						}
						break;
				}
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

void drawRectRed(int x, int y, int w, int h)
{
	SDL_Rect greenBox = {x,y,w,h};
	SDL_FillRect(screen, &greenBox, SDL_MapRGB(screen->format, 255, 0, 0));	
}

void drawRectLightGray(int x, int y, int w, int h)
{
	SDL_Rect greenBox = {x,y,w,h};
	SDL_FillRect(screen, &greenBox, SDL_MapRGB(screen->format, 245, 245, 245));	
}

void drawRectYellow(int x, int y, int w, int h)
{
	SDL_Rect greenBox = {x,y,w,h};
	SDL_FillRect(screen, &greenBox, SDL_MapRGB(screen->format, 255, 250, 205));	
}

void drawRectGray(int x, int y, int w, int h)
{
	SDL_Rect greenBox = {x,y,w,h};
	SDL_FillRect(screen, &greenBox, SDL_MapRGB(screen->format, 211, 211, 211));	
}

void drawRectSalmon(int x, int y, int w, int h)
{
	SDL_Rect greenBox = {x,y,w,h};
	SDL_FillRect(screen, &greenBox, SDL_MapRGB(screen->format, 255, 160, 122));	
	matrixText();
}

void text(int x, int y, int w, int h, char *txt, TTF_Font *f)
{
	SDL_Rect t = {x,y,w,h};
	SDL_Surface *txtSurface = TTF_RenderText_Solid(f,txt, color); 
	SDL_BlitSurface(txtSurface,NULL,screen,&t);
		
}

void matrix()
{
	drawRectLightGray(80,125,560,420);
    rowLines();	
    colLines();
    
    matrixText();
}

void matrixText()
{
	int i, j,line_x=108,line_y=140;
	text(110,90,30,30,"1         2          3          4         5         6          7         8",font25);
    text(55,145,30,30,"1",font25);
    text(55,215,30,30,"2",font25);
    text(55,285,30,30,"3",font25);
    text(55,355,30,30,"4",font25);
    text(55,425,30,30,"5",font25);
    text(55,495,30,30,"6",font25);
    
    for(i=0;i<6;i++)
    {
		text(line_x,line_y,30,30,matrixLetters[i],font30);
		line_y+=70;
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

void centerRed()
{
	drawRectRed(670,365,40,40);
	text(680,365,30,30,"C",font30);
}

void centerGreen()
{
	drawRectGreen(670,365,40,40);
	text(680,365,30,30,"C",font30);
}

void highlightRow1()
{
	drawRectYellow(82,127,556,66);
	matrixText();
	colLines();
}

void highlightRow2()
{
	drawRectYellow(82,197,556,66);
	matrixText();
	colLines();
}
	
void highlightRow3()
{
	drawRectYellow(82,267,556,66);
	matrixText();
	colLines();
}

void highlightRow4()
{
	drawRectYellow(82,337,556,66);
	matrixText();
	colLines();
}

void highlightRow5()
{
	drawRectYellow(82,407,556,66);
	matrixText();
	colLines();
}

void highlightRow6()
{
	drawRectYellow(82,477,556,66);
	matrixText();
	colLines();
}

char selectCharacter(int row,int col)
{
    switch(row)
    {
        case 1:
            switch(col)
            {
                case 1:                                   /*E*/
                     drawRectSalmon(82,127,68,68);
                     return 'E';
                case 2:                                   /*A*/
                     drawRectSalmon(152,127,68,68);
                     return 'A';
                case 3:                                   /*R*/
                     drawRectSalmon(222,127,68,68);
                     return 'R';
                case 4:                                   /*I*/
                     drawRectSalmon(292,127,68,68);
                     return 'I';
                case 5:                                   /*.*/
                     drawRectSalmon(362,127,68,68);
                     return '.';
                case 6:                                   /*?*/
                     drawRectSalmon(432,127,68,68);
                     return '?';
                case 7:                                   /*SPC*/
                     drawRectSalmon(502,127,68,68);
                     return '_';
                case 8:                                   /*BACK*/
                     drawRectSalmon(572,127,68,68);
                     return '<';
                default:
                  break;
             }
             break;
        case 2:
             switch(col)
             {
                case 1:									  /*O*/
                     drawRectSalmon(82,197,68,68);
                     return 'O';
                case 2:                                   /*T*/
                     drawRectSalmon(152,197,68,68);
                     return 'T';
                case 3:                                   /*N*/
                     drawRectSalmon(222,197,68,68);
                     return 'N';
                case 4:                                   /*S*/
                     drawRectSalmon(292,197,68,68);
                     return 'S';
                case 5:                                   /*B*/
                     drawRectSalmon(362,197,68,68);
                     return 'B';
                case 6:                                   /*F*/
                     drawRectSalmon(432,197,68,68);
                     return 'F';
                case 7:                                   /*Y*/
                     drawRectSalmon(502,197,68,68);
                     return 'Y';
                case 8:                                   /*W*/
                     drawRectSalmon(572,197,68,68);
                     return 'W';
                default:
                 break;
             }
            break;
        case 3:
             switch(col)
             {
                case 1:                                   /*L*/
                     drawRectSalmon(82,267,68,68);
                     return 'L';
                case 2:                                   /*C*/
                     drawRectSalmon(152,267,68,68);
                     return 'C';
                case 3:                                   /*U*/
                     drawRectSalmon(222,267,68,68);
                     return 'U';
                case 4:                                   /*D*/
                     drawRectSalmon(292,267,68,68);
                     return 'D';
                case 5:                                   /*K*/
                     drawRectSalmon(362,267,68,68);
                     return 'K';
                case 6:                                   /*V*/
                     drawRectSalmon(432,267,68,68);
                     return 'V';
                case 7:                                   /*X*/
                     drawRectSalmon(502,267,68,68);
                     return 'X';
                case 8:                                   /*Z*/
                     drawRectSalmon(572,267,68,68);
                     return 'Z';
                default:
                 break;
             }
            break;
        case 4:
            switch(col)
            {
                case 1:                                   /*P*/
                     drawRectSalmon(82,337,68,68);
                     return 'P';
                case 2:                                   /*M*/
                     drawRectSalmon(152,337,68,68);
                     return 'M';
                case 3:                                   /*H*/
                     drawRectSalmon(222,337,68,68);
                     return 'H';
                case 4:                                   /*G*/
                     drawRectSalmon(292,337,68,68);
                     return 'G';
                case 5:                                   /*J*/
                     drawRectSalmon(362,337,68,68);
                     return 'J';
                case 6:                                   /*Q*/
                     drawRectSalmon(432,337,68,68);
                     return 'Q';
                case 7:                                   /*1*/
                     drawRectSalmon(502,337,68,68);
                     return '1';
                case 8:                                   /*2*/
                     drawRectSalmon(572,337,68,68);
                     return '2';
                default:
                 break;
             }
            break;
        case 5:
            switch(col)
            {
                case 1:                                   /*3*/
                     drawRectSalmon(82,407,68,68);
                     return '3';
                case 2:                                   /*4*/
                     drawRectSalmon(152,407,68,68);
                     return '4';
                case 3:                                   /*5*/
                     drawRectSalmon(222,407,68,68);
                     return '5';
                case 4:                                   /*6*/
                     drawRectSalmon(292,407,68,68);
                     return '6';
                case 5:                                   /*7*/
                     drawRectSalmon(362,407,68,68);
                     return '7';
                case 6:                                   /*8*/
                     drawRectSalmon(432,407,68,68);
                     return '8';
                case 7:                                   /*9*/
                     drawRectSalmon(502,407,68,68);
                     return '9';
                case 8:                                   /*0*/
                     drawRectSalmon(572,407,68,68);
                     return '0';
                default:
                 break;
            }
            break;
        case 6:
            switch(col)
            {
                case 1:                                   /*+*/
                     drawRectSalmon(82,477,68,68);
                     return '+';
                case 2:                                   /*-*/
                     drawRectSalmon(152,477,68,68);
                     return '-';
                case 3:                                   /*=*/
                     drawRectSalmon(222,477,68,68);
                     return '=';
                case 4:                                   /*&*/
                     drawRectSalmon(292,477,68,68);
                     return '&';
                case 5:                                   /*/*/
                     drawRectSalmon(362,477,68,68);
                     return '/';
                case 6:                                   /*'*/
                     drawRectSalmon(432,477,68,68);
                     return '`';
                case 7:                                   //Exclam
                     drawRectSalmon(502,477,68,68);
                     return '!';
                case 8:									  //TTS
                     drawRectSalmon(572,477,68,68);
                     return '>';
                default:
                     break;
             }
            break;
        default:
            break;
    }
    return '\0';
}

void selectedBSP()
{
    if(tf_index!=0)
    {
        textFieldVal[--tf_index]= '\0';
        /*if(word_index!=0)
        {
            word[--word_index]='\0';
            if((word_index!=0))
                 wordSuggestion(0);
        }*/
    }
    textField();
    flagBSP=1;
    return;
}

void processSelected(char selected)
{
    flagBSP=0;  
    if(selected=='<')                        //-------------------backspace
        selectedBSP();
    else if(selected =='>')                  //-------------------TTS
    {
    	tts();
    	memset(textFieldVal,0,sizeof(textFieldVal));
    	tf_index=0;
    	textField();
    	//memset(word,0,sizeof(word));
    }
    else if(selected!='_' && selected!='.' && selected!='?' && selected!='!') //-------------------character
    {
        if( tf_index<79 && word_index<79)
        {
            textFieldVal[tf_index++]= selected;
            //word[word_index++]= selected;
            //wordSuggestion(0);
        }
        else
        {
            /*if(word_index>=79)
            {
                memset(word,0,sizeof(word));
                word_index=0;
            }*/
            text(82,560,600,40,"Text Field Full.",font25);
            SDL_Delay(1000);
            memset(textFieldVal,0,sizeof(textFieldVal));
            tf_index=0;
            //strcat(textFieldVal,word);
            //tf_index = word_index;
            textField();
            //clear message
            drawRectGray(82,560,600,40);
        }
    }
    else
    {
        if(selected == '_')                 //-------------------Space
		    textFieldVal[tf_index++]=' ';
        else     							//----------------------- . || ? || !                        
            textFieldVal[tf_index++]= selected;

        /*if(word[0]!=0)
        {
             wordSuggestion(1);
             word_index=0;
             memset(word,0,sizeof(word));
        }
        memset(buff,0,sizeof(buff));*/
    }
    return;
}

int displayChar(int row,int col)
{
    char selected='\0';
    selected = selectCharacter(row, col);    //-----------------------select the character

    processSelected(selected);

    displayTextArea();
}

void displayTextArea()
{
    text(83,610,1200,40,textFieldVal,font25);
}

void tts()
{
    //process for tts
    int i;
    char command[128]={'\0'};
    
    for(i=0;i<strlen(textFieldVal);i++)
    {
		lower[i] = tolower(textFieldVal[i]);
	}
    
    strcat(command,"pico2wave -w tts.wav '");
    strcat(command,lower);
    strcat(command,"' && aplay --rate=32000 tts.wav");
    
    system(command);
    //system("espeak -ven+f3 -s 90 -f tts.txt -w tts.wav && aplay tts.wav");
}


