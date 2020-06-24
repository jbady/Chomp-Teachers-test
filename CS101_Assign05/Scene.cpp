#include "Scene.h"

void initialize_Scene(struct Scene *s)
{
	// Load in board from text file
	load_Board(s->board, &s->num_pellets, &s->num_powerups);
	initialize_Player(&s->p, PLAYER_HOME_X, PLAYER_HOME_Y, 0, 0, PLAYER_CHAR, PLAYER_COLOR);
	
}

void render_Scene(struct Scene *s)
{
	// Draw board
	draw_Board(s->board);
	draw_player(&s->p);
}

// Routine to update scene
int update_Scene(struct Scene *s)
{
	// TODO: for now, just see if a key was pressed,
	// and if so, return true (game is done)
	
	player_AI(&s->p, s->board);
	update_player(&s->p);
	
	/*int key = cons_get_keypress();
	if (key == -1) {
		return 0;
	} else {
		return 1;
	}*/
	if (s->board[s->p.y][s->p.x]==PELLET){
		s->board[s->p.y][s->p.x] = EMPTY;
	}
	if (s->board[s->p.y][s->p.x]==POWER_UP){
		s->board[s->p.y][s->p.x] = EMPTY;
	}
	return 0;
}

// Routine to draw game board - DO NOT MODIFY!
void draw_Board(int board[HEIGHT][WIDTH])
{
	int i,j;
	int loc;

	cons_change_color(WHITE,BLACK);
	// Loop over game grid and draw appropriate character
	for(i=0; i<HEIGHT; i++)
	{
		for(j=0; j<WIDTH; j++)
		{
			// Move to current location
			cons_move_cursor(i,j);
			loc = board[i][j];
			cons_change_color(BLACK,BLACK);
			// Draw wall
			if(loc == WALL)
			{
				cons_change_color(BLUE,BLUE+INTENSE);
				cons_printw("%c",WALL_CHAR);
			}
			// Draw pellet
			else if(loc == PELLET)
			{
				cons_change_color(WHITE,BLACK);
				cons_printw("%c",PELLET_CHAR);
			}
			// Draw powerup
			else if(loc == POWER_UP)
			{
				cons_change_color(WHITE, BLACK);
				cons_printw("%c",POWER_CHAR);
			}
		}
	}
}

// Routine to load board from text file - DO NOT MODIFY!
void load_Board(int board[HEIGHT][WIDTH], int *num_pellets, int *num_powerups)
{
	FILE* in;
	char ch;
	int i,j;
	
	*num_pellets = 0;
	*num_powerups = 0;
	
	in = fopen("board.txt","r");
	if(!in)
	{
		printf("Unable to open file.");
		exit(0);
	}

	for(i=0; i<HEIGHT; i++)
	{
		for(j=0; j<WIDTH; j++)
		{
			fscanf(in,"%c",&ch);
			if(ch=='+')
			{
				board[i][j] = WALL;
			}
			else if(ch=='.')
			{
				board[i][j] = PELLET;
				(*num_pellets)++;
			}
			else if(ch=='O')
			{
				board[i][j] = POWER_UP;
				(*num_powerups)++;
			}
			else
			{
				board[i][j] = EMPTY;
			}
		}
		fscanf(in,"%c",&ch);
		fscanf(in,"%c",&ch);
	}

	fclose(in);

	return;
}
