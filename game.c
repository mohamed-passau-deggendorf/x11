#include <X11/Xlib.h>
#include <stdbool.h>


enum SceneElement{
Empty,
Wall,
Player,
Enemy,
Goal

};

struct Game{
enum SceneElement **scene;//[16][16];
int PlayerX;
int PlayerY;

Display* display;
Window window;
GC gc;

};


enum GameState{
Move,
Stuck,
Win,
Lose
};

void render(struct Game* game){
	//printf("render \n");

//XDrawRectangle(display, win, gc, 120, 150, 50, 60);
int k; int l; unsigned long cl;
	XColor xcolour;
for(k=0;k<16;k++) for(l=0;l<16;l++ ) { 
			switch(game->scene[k][l]){//0xff
			case Empty : cl=0xdde0f0;  break;
			case Wall: cl=0x0; break;
			case Player: cl=0x03891; break;
			case Enemy: cl=0xed2658; break;//0xff00ff
			case Goal: cl=0x81e3b9; break; //0xff00 0xf7f736 0xa0f736

				}



	
		XSetForeground(game->display, game->gc, cl);
		XSetBackground(game->display, game->gc, cl);
	XFillRectangle(game->display, game->window, game->gc, 40+20*k, 40+20*l, 20, 20); }
 }

enum GameState step(struct Game * game,XEvent event) {
//printf("step \n");

	int posX = game->PlayerX; 	int posY = game->PlayerY;
	//game->scene[posX][posY]=Empty;;
	//printf("%d \n",event.xkey.keycode);

	switch( event.xkey.keycode ){

		case 111 : if(posY--==0 || game->scene[posX][posY] == Wall) return Stuck; game->scene[posX][posY+1]=Empty;  game->PlayerY=posY; break;
		case 113 : if(posX--==0|| game->scene[posX][posY] == Wall) return Stuck; game->scene[posX+1][posY]=Empty; game->PlayerX=posX; break;
		case 114 : if(posX++==15|| game->scene[posX][posY] == Wall) return Stuck; game->scene[posX-1][posY]=Empty; game->PlayerX=posX; break;
		case 116 : game->PlayerY=posY; if(posY++==15|| game->scene[posX][posY] == Wall) return Stuck; game->scene[posX][posY-1]=Empty; break;

		}

	//if()

	switch(game->scene[posX][posY]) {
		case Enemy : return Lose ; break;
		case Goal : return Win ; break;

		}

	game->scene[game->PlayerX=posX][game->PlayerY=posY]=Player;
	return Move;
}

int main(int argc, char* argv[]){

	struct Game *game = malloc(sizeof(struct Game));
	//game->scene[0]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};scente
	game->scene = malloc(16*sizeof(enum SceneElement*));
	int k,l;
	game->PlayerX = game->PlayerY=0;
	enum GameState state = Move;
	enum SceneElement scene[16][16]={

	{Player,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Enemy,Empty,Empty,Empty},
	{Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty},
	{Empty,Wall,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty},
	{Empty,Wall,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Enemy,Empty,Empty,Empty,Empty,Empty,Empty},
	{Empty,Wall,Empty,Enemy,Enemy,Enemy,Enemy,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty},
	{Empty,Wall,Empty,Empty,Empty,Enemy,Enemy,Empty,Empty,Empty,Empty,Enemy,Empty,Empty,Empty,Empty},
	{Empty,Wall,Empty,Empty,Empty,Wall,Goal,Wall,Wall,Wall,Wall,Wall,Wall,Empty,Empty,Empty},
	{Empty,Empty,Wall,Empty,Empty,Wall,Empty,Enemy,Wall,Empty,Empty,Empty,Empty,Enemy,Empty,Empty},
	{Empty,Empty,Wall,Empty,Empty,Wall,Empty,Empty,Wall,Enemy,Empty,Empty,Empty,Empty,Empty,Empty},
	{Wall,Empty,Wall,Wall,Wall,Wall,Wall,Empty,Wall,Wall,Wall,Empty,Empty,Empty,Empty,Empty},
	{Empty,Empty,Wall,Empty,Empty,Empty,Empty,Empty,Enemy,Empty,Empty,Empty,Empty,Empty,Empty,Empty},
	{Empty,Empty,Wall,Empty,Empty,Empty,Empty,Empty,Enemy,Empty,Empty,Empty,Empty,Empty,Empty,Empty},
	{Empty,Empty,Empty,Wall,Empty,Empty,Empty,Empty,Enemy,Empty,Enemy,Empty,Empty,Wall,Enemy,Empty},
	{Wall,Wall,Enemy,Empty,Empty,Empty,Enemy,Empty,Empty,Empty,Empty,Empty,Empty,Wall,Empty,Enemy},
	{Empty,Wall,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Enemy},
	{Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Enemy},

	

	};
	for(k=0;k<16;k++) {
	game->scene[k] = malloc(16*sizeof(enum SceneElement));
	for(l=0;l<16;l++)game->scene[k][l]=scene[k][l];

		}

    Display* display = XOpenDisplay(NULL);
    XEvent event;
	GC gc;
	int screen = DefaultScreen(display);

	    Window window = XCreateSimpleWindow(
        display, XDefaultRootWindow(display),
        100, 100, 400, 400, 4, 0xff0000/*BlackPixel(display, screen)*/, WhitePixel(display, screen));

	 XMapWindow(display, window);
	    XSelectInput(display, window, KeyPressMask | ButtonPressMask | ExposureMask | ButtonMotionMask);
	gc=XCreateGC(display, window, 0,0);
	game->window = window; game->display=display; game->gc=gc;
	redo : game->PlayerX = game->PlayerY=0; state=Move;
	while (True){
	 XNextEvent(display, &event);
	switch(event.type){
		case KeyPress : ;
		if(state<Win) {
		state =  step(game,event);
		/*else*/ if(state == Win) { XSetForeground(game->display, game->gc, 0xff); XDrawString(display, window, gc, 10, 10, "Winner", 6); }
		else if(state == Lose) { XSetForeground(game->display, game->gc, 0x000ff); XDrawString(display, window, gc, 10, 10, "Lose", 4); } } else if(event.xkey.keycode == 9 || event.xkey.keycode == 36 || event.xkey.keycode ==65) { 
				 XSetForeground(game->display, game->gc, 0xffffff);
				XFillRectangle(game->display, game->window, game->gc, 0, 0, 200, 40);
				//step(game,event);
				game->scene[0][0]=Player;
				render(game);

			goto redo; }

		break;


	}
	render(game);

		}



}
