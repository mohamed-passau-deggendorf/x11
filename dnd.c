/*
 *  This is a  X11 program that uses Xlib calls only (no toolkit!). 
   The program is a Drag and Drop Demo
 
 */

#include <X11/Xlib.h>
#include <stdbool.h>

int main(int argc, char* argv[])
{
    Display* display = XOpenDisplay(NULL);
    XEvent event;
	GC gc;
	int screen = DefaultScreen(display);

	    Window window = XCreateSimpleWindow(
        display, XDefaultRootWindow(display),
        100, 100, 400, 300, 4, BlackPixel(display, screen), WhitePixel(display, screen));
	Window field =  XCreateSimpleWindow(
        display, window,
        100, 100, 60, 120, 4, BlackPixel(display, screen), WhitePixel(display, screen));
	Window field1 =  XCreateSimpleWindow(
        display, window,
        180, 100, 60, 120, 4, BlackPixel(display, screen), WhitePixel(display, screen));
	Window field2 =  XCreateSimpleWindow(
        display, window,
        260, 100, 60, 120, 4, BlackPixel(display, screen), WhitePixel(display, screen));
	Window fieldx =  XCreateSimpleWindow(
        display, window,
        100, 230, 60, 120, 4, BlackPixel(display, screen), WhitePixel(display, screen));
	Window fieldx1 =  XCreateSimpleWindow(
        display, window,
        180, 230, 60, 120, 4, BlackPixel(display, screen), WhitePixel(display, screen));
	Window fieldx2 =  XCreateSimpleWindow(
        display, window,
        260, 230, 60, 120, 4, BlackPixel(display, screen), WhitePixel(display, screen));
	Window button = XCreateSimpleWindow(
        display, window,
        10, 10, 30, 60, 1, BlackPixel(display, screen), 0xc5ccbe);
	Window button1 = XCreateSimpleWindow(
        display, window,
        10, 100, 30, 60, 1, BlackPixel(display, screen), 0x8489e8);
	

	




    	
	 XMapWindow(display, field);
	  XMapWindow(display, field1);
	 XMapWindow(display, field2);
	 XMapWindow(display, fieldx);
	  XMapWindow(display, fieldx1);
	 XMapWindow(display, fieldx2);
	 XMapWindow(display, button);
	 XMapWindow(display, button1);
	    XMapWindow(display, window);
    XSelectInput(display, window, KeyPressMask | ButtonPressMask | ExposureMask | ButtonMotionMask);
      XSelectInput(display, button, KeyPressMask | ButtonPressMask  | ButtonReleaseMask  | ExposureMask | ButtonMotionMask);
	  XSelectInput(display, button1, KeyPressMask | ButtonPressMask  | ButtonReleaseMask  | ExposureMask | ButtonMotionMask);

	gc=XCreateGC(display, window, 0,0);
	bool active = false, active1 = false;
		unsigned long white = WhitePixel(display, screen);
	unsigned long black = BlackPixel(display, screen);
	int old_x,old_y;
	bool flag [6][2]={{false,false},{false,false},{false,false},{false,false},{false,false},{false,false}};

	XSetForeground(display,gc,black);
	


    while (True) {
      XNextEvent(display, &event);


	switch(event.type) {

	case ButtonPress :  ;
	if(event.xbutton.window==button){active = true;
	XSetWindowBorder(display, button, 0xcc5555); 


	old_x=event.xmotion.x_root ; old_y=event.xmotion.y_root;


	 }

		if(event.xbutton.window==button1){active1 = true;
	XSetWindowBorder(display, button1, 0xcc5555); 


	old_x=event.xmotion.x_root ; old_y=event.xmotion.y_root;


	 }


	break;

	case ButtonRelease : 

	if(event.xbutton.window==button){active = false;  XSetWindowBackground(display, button, 0xc5ccbe);	 XMapWindow(display, button);}


	if(event.xbutton.window==button1){active1 = false;  XSetWindowBackground(display, button1, 0xc5ccbe);	 XMapWindow(display, button1);}
	break;


	case MotionNotify : ;

	


     


	if(active&&event.xbutton.window==button){
	XWindowAttributes xwa;
XGetWindowAttributes(display, button, &xwa);
	int new_x=event.xmotion.x_root-old_x +xwa.x,new_y=event.xmotion.y_root-old_y+xwa.y;
	XMoveWindow(display, button,new_x,new_y);


	XWindowAttributes xww;
XGetWindowAttributes(display, window, &xww);


XGetWindowAttributes(display, button, &xwa);

	XWindowAttributes xwb;
XGetWindowAttributes(display, field, &xwb);

       XWindowAttributes xwc;
XGetWindowAttributes(display, field1, &xwc);
	  XWindowAttributes xwd;
XGetWindowAttributes(display, field2, &xwd);



 	XWindowAttributes xwbx;
XGetWindowAttributes(display, fieldx, &xwbx);

       XWindowAttributes xwcx;
XGetWindowAttributes(display, fieldx1, &xwcx);
	  XWindowAttributes xwdx;
XGetWindowAttributes(display, fieldx2, &xwdx);



	if(new_x  < xwb.x+xwb.width -xwa.width && new_x > xwb.x &&  new_y  < xwb.y+xwb.height - xwa.height && new_y  > xwb.y   )
	{XSetWindowBorder(display, field, 0xff0000); flag[0][0]=true; }
	else {if(!flag[0][1]) XSetWindowBorder(display, field, 0x0); flag[0][0]=false; } 



 		if(new_x < xwc.x+xwc.width -xwa.width && new_x > xwc.x &&  new_y < xwc.y+xwc.height - xwa.height && new_y > xwc.y  )
	{XSetWindowBorder(display, field1, 0xcc00cc);flag[1][0]=true; }
	else {if(!flag[1][1])XSetWindowBorder(display, field1, 0x0); flag[1][0]=false; } 


	if(new_x < xwd.x+xwd.width -xwa.width && new_x > xwd.x &&  new_y < xwd.y+xwd.height - xwa.height && new_y > xwd.y  )
	{XSetWindowBorder(display, field2, 0xff);flag[2][0]=true; }
	else {if(!flag[2][1])XSetWindowBorder(display, field2, 0x0);flag[2][0]=false;} 


		if(new_x < xwbx.x+xwbx.width -xwa.width && new_x > xwbx.x &&  new_y < xwbx.y+xwbx.height - xwa.height && new_y > xwbx.y  )

	{XSetWindowBorder(display, fieldx, 0xdeadb1); flag[3][0]=true; }
	else {if(!flag[3][1])XSetWindowBorder(display, fieldx, 0x0); flag[3][0]=false;} 



 		if(new_x < xwcx.x+xwcx.width -xwa.width && new_x > xwcx.x &&  new_y < xwcx.y+xwcx.height - xwa.height && new_y > xwcx.y    ) 
	{XSetWindowBorder(display, fieldx1, 0xde9ee6 ); flag[4][0]=true;}
	else {if(!flag[4][1])XSetWindowBorder(display, fieldx1, 0x0); flag[4][0]=false;} 


	if(new_x < xwdx.x+xwdx.width -xwa.width && new_x > xwdx.x &&  new_y < xwdx.y+xwdx.height - xwa.height && new_y > xwdx.y   )
	{XSetWindowBorder(display, fieldx2, 0x295699 ); flag[5][0]=true; }
	else {if(!flag[5][1])XSetWindowBorder(display, fieldx2, 0x0); flag[5][0]=false;} 


	

 

	old_x=event.xmotion.x_root ; old_y=event.xmotion.y_root;}


	if(active1&&event.xbutton.window==button1){
	XWindowAttributes xwa;
XGetWindowAttributes(display, button1, &xwa);
	int new_x=event.xmotion.x_root-old_x +xwa.x,new_y=event.xmotion.y_root-old_y+xwa.y;
	XMoveWindow(display, button1,new_x,new_y);


	XWindowAttributes xww;
XGetWindowAttributes(display, window, &xww);


XGetWindowAttributes(display, button1, &xwa);

	XWindowAttributes xwb;
XGetWindowAttributes(display, field, &xwb);

       XWindowAttributes xwc;
XGetWindowAttributes(display, field1, &xwc);
	  XWindowAttributes xwd;
XGetWindowAttributes(display, field2, &xwd);



 	XWindowAttributes xwbx;
XGetWindowAttributes(display, fieldx, &xwbx);

       XWindowAttributes xwcx;
XGetWindowAttributes(display, fieldx1, &xwcx);
	  XWindowAttributes xwdx;
XGetWindowAttributes(display, fieldx2, &xwdx);



	if(new_x  < xwb.x+xwb.width -xwa.width && new_x > xwb.x &&  new_y  < xwb.y+xwb.height - xwa.height && new_y  > xwb.y  )

	{XSetWindowBorder(display, field, 0xff0000); flag[0][1]=true;  }
	else {if(!flag[0][0])XSetWindowBorder(display, field, 0x0); flag[0][1]=false;} 



 		if(new_x < xwc.x+xwc.width -xwa.width && new_x > xwc.x &&  new_y < xwc.y+xwc.height - xwa.height && new_y > xwc.y  )
	{XSetWindowBorder(display, field1, 0xcc00cc);flag[1][1]=true; }
	else {if(!flag[1][0])XSetWindowBorder(display, field1, 0x0); flag[1][1]=false;} 


	if(new_x < xwd.x+xwd.width -xwa.width && new_x > xwd.x &&  new_y < xwd.y+xwd.height - xwa.height && new_y > xwd.y   )
	{XSetWindowBorder(display, field2, 0xff);flag[2][1]=true; }
	else {if(!flag[2][0])XSetWindowBorder(display, field2, 0x0);flag[2][1]=false;} 


		if(new_x < xwbx.x+xwbx.width -xwa.width && new_x > xwbx.x &&  new_y < xwbx.y+xwbx.height - xwa.height && new_y > xwbx.y   )

	{XSetWindowBorder(display, fieldx, 0xff1111); flag[3][1]=true; }
	else {if(!flag[3][0])XSetWindowBorder(display, fieldx, 0x0); flag[3][1]=false;} 



 		if(new_x < xwcx.x+xwcx.width -xwa.width && new_x > xwcx.x &&  new_y < xwcx.y+xwcx.height - xwa.height && new_y > xwcx.y    )
	{XSetWindowBorder(display, fieldx1, 0xde9ee6); flag[4][1]=true;}
	else {if(!flag[4][0])XSetWindowBorder(display, fieldx1, 0x0); flag[4][1]=false;} 


	if(new_x < xwdx.x+xwdx.width -xwa.width && new_x > xwdx.x &&  new_y < xwdx.y+xwdx.height - xwa.height && new_y > xwdx.y    )
	{XSetWindowBorder(display, fieldx2, 0x295699); flag[5][1]=true; }
	else {if(!flag[5][0])XSetWindowBorder(display, fieldx2, 0x0); flag[5][1]=false;} 


	

 

	old_x=event.xmotion.x_root ; old_y=event.xmotion.y_root;}


	break;

			}
    }

    return 0;
}
