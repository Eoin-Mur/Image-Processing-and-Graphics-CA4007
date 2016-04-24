#include <GL/gl.h>
#include <GL/glext.h>
#include <GL/glut.h>
#include <stdio.h>
#include <string.h>


//draw window demensions
#define WW 800.0
#define WH 600.0

//Color picker window demensions
#define CW 250.0
#define CH 250.0

//brigthness window demensions
#define BW 200.0
#define BH 250.0
//transparaency window demnsions 
#define TW 100.0
#define TH 200.0

//windows works perfect :)
//gcc MyPaint.c -o myPaint glut32.lib -lopengl32 -lglu32 -std=c99


//linux(menus act up a bit with linux where they call redisplay when you enter them, erasing the screen
//probably just due to the glut package i used)
//gcc MyPaint.c -o MyPaint -lglut -lGLU -lGL -lm -std=c99


void drawPolly(int x1, int y1, int x2, int y2, float h, float w);
void drawPoint(GLint x, GLint y);
void drawRectagle(GLint x, GLint y);
void drawPoint(GLint x, GLint y);
void drawLine(GLint x, GLint y);



GLfloat 
	downX, 
	downY, 
	upX, 
	upY;

GLfloat
	prevX,
	prevY;

float
	r,
	g,
	b,
	a = 1.0;


int selectedShape = -1;

//global variables for our windows id's
int mainWindow;
int palleteWindow = -1;
int brightnessWindow = -1;
int transWindow = -1;

//variables for use in drawing our polygons
int numPolyPoints = -1;
int drawnPPoints = 0;
int polyArray[16]; 
int tempFlag = -1;

//display function for the main window
//just clear the window settings its background to white
void display()
{
	glClearColor(1.0,1.0,1.0,1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor4f(0.0,0.0,0.0,1.0);
	glPointSize(3.0);

	glFlush();

	return;
}

//display funciotion for the RGB sliders in the brightness window 
void displayRGBSlider()
{
	glClearColor(1.0,1.0,1.0,1.0);

	glClear(GL_COLOR_BUFFER_BIT);
	glColor4f(0.0,0.0,0.0,1.0);
	glLineWidth(3.0);

	glColor4f(0.5,0.5,0.5,1.0);

	//draw 3 rectangeles as the base for our slider
	drawPolly(10,10,60,210,BH,BW);
	drawPolly(70,10,120,210,BH,BW);
	drawPolly(130,10,180,210,BH,BW);
	glColor4f(0.0,0.0,0.0,1.0);

	//draw a line to display the current set value by calcuating the y value relative to the R,G or B value
	glBegin(GL_LINES);
		glVertex2f((10-(BW/2))/(BW/2),((210 * r)-(BH/2))/(BH/2));
		glVertex2f((60-(BW/2))/(BW/2),((210 * r)-(BH/2))/(BH/2));
	glEnd();

	glBegin(GL_LINES);
		glVertex2f((70-(BW/2))/(BW/2),((210 * g)-(BH/2))/(BH/2));
		glVertex2f((120-(BW/2))/(BW/2),((210 * g)-(BH/2))/(BH/2));
	glEnd();

	glBegin(GL_LINES);
		glVertex2f((130-(BW/2))/(BW/2),((210 * b)-(BH/2))/(BH/2));
		glVertex2f((180-(BW/2))/(BW/2),((210 * b)-(BH/2))/(BH/2));
	glEnd();

	glColor4f(r,g,b,a);
	drawPolly(10,220,180,250,BH,BW);

	glFlush();
	return;
}

//lighter display version of the RGB slider dsiplay exect the entire window acts
//as the slider
void displayTransSlider()
{
	glClearColor(1.0,1.0,1.0,1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glLineWidth(3.0);

	glColor4f(0.5,0.5,0.5,1.0);
	glBegin(GL_POLYGON);
		glVertex2f(-1,-1);
		glVertex2f(-1,1);
		glVertex2f(1,1);
		glVertex2f(1,-1);
	glEnd();
	glColor4f(0.0,0.0,0.0,1.0);
	glBegin(GL_LINES);
		glVertex2f((1-(TW/2))/(TW/2),((201 - (200 * a))-(TH/2))/(TH/2));
		glVertex2f((100-(TW/2))/(TW/2),((201 - (200 * a))-(TH/2))/(TH/2));
	glEnd();

	glFlush();

	return;
}

//function to just draw a recatnage this is just used with the RGB
//sliders to clean up the code a bit
void drawPolly(int x1, int y1, int x2, int y2, float h, float w)
{
	//10,250 180,250
	glBegin(GL_POLYGON);
		//glColor4f(r,g,b,a);
		glVertex2f((x1-(w/2))/(w/2), (y1-(h/2))/(h/2));
		glVertex2f((x1-(w/2))/(w/2), (y2-(h/2))/(h/2));
		glVertex2f((x2-(w/2))/(w/2), (y2-(h/2))/(h/2));
		glVertex2f((x2-(w/2))/(w/2), (y1-(h/2))/(h/2));
	glEnd();

	glFlush();

	return;
}

//dislay function for the color picker
//just crate a square window and at each point draw
//set the color to be different as OpenGL nicely enough
//handles the blending of the colors and allows for a 
//color wheel type effect
void colorSquare()
{
	glClear(GL_COLOR_BUFFER_BIT);

	//glColor3f(0.0,1.0,0.0);
	glBegin(GL_POLYGON);
		glColor4f(1.0,0,0,1.0);
		glVertex2f(-1,-1);
		glColor4f(0,1.0,0,1);
		glVertex2f(-1,1);
		glColor4f(1.0,1.0,0,1.0);
		glVertex2f(1,1);
		glColor4f(0,0,1.0,1.0);
		glVertex2f(1,-1);
	glEnd();

	glFlush();
}

//motion function used in the main window to draw our shapes
void drawShape(GLint x, GLint y)
{
	switch(selectedShape)
	{
		case 0:
		{
			drawPoint( x , y );
		} break;
		case 1:
		{
			drawLine( x , y );
		}
		break;
		case 2:
		{
			drawRectagle( x , y );
		}break;
		//leave the option for drawing a polygon blank as this is handled
		//in the mousePressFunction rather then the motion
		case 3:
		{

		}break;
		default:
		{
			drawPoint( x , y );
		}
		break;
	}
	return;
}

void drawPoint( GLint x , GLint y )
{
	glColor4f(r,g,b,a);
	glPointSize(3.0);
	glBegin(GL_POINTS);
		glVertex2f((x-(WW/2))/(WW/2),-(y-(WH/2))/(WH/2));
	glEnd();

	glFlush();	

	return;
}

void drawRectagle( GLint x , GLint y )
{
	GLfloat curX, curY;

	//calculte the x and y postion relative to the screen first
	curX=(x-(WW/2))/(WW/2); 
	curY=-(y-(WH/2))/(WH/2);

	//get rid of the previously drawn rectangle by overwiting 
	//it with a white rectangle. this allows use to continues draw our shapes
	//rather then clicking points
	glColor4f(1.0,1.0,1.0,1.0);
	glBegin(GL_POLYGON);
		glVertex2f(downX,downY);
		glVertex2f(downX,prevY);
		glVertex2f(prevX,prevY);
		glVertex2f(prevX,downY);
	glEnd();

	//draw the rectangle using the point in which the mouse was first pressed down
	//as registered in our mouse press handler as the starting point
	//and then use the current x and y values as regestered in this motion function
	glColor4f(r,g,b,a);
	glBegin(GL_POLYGON);
		glVertex2f(downX,downY);
		glVertex2f(downX,curY);
		glVertex2f(curX,curY);
		glVertex2f(curX,downY);
	glEnd();

	//set our prev x and y value to the current value on exit
	//this is used above to erase the old rectange
	prevX = curX;
	prevY = curY;

	glFlush();
	return;
}

//draw line funcion acts the same way as the draw rectangle function
void drawLine(GLint x, GLint y)
{
	GLfloat curX, curY;

	curX=(x-(WW/2))/(WW/2); 
	curY=-(y-(WH/2))/(WH/2);

	glColor4f(r,g,b,a);
	glLineWidth(3.0);

	glBegin(GL_LINES);
		glColor4f(1.0,1.0,1.0,1.0);
		glVertex2f(downX, downY);
		glVertex2f(prevX, prevY);
		glColor4f(r,g,b,a);
		glVertex2f(downX, downY);
		glVertex2f(curX, curY);
	glEnd();

	glFlush();

	prevX = curX;
	prevY = curY;
	return;
}

//function to draw our polygon 
//this function is only called once the user has clicked the specifyed number of points
//it is called from the mouse press handler
void drawPolygon(int pointsArray[], int numberOfPoints)
{

	//first need to erase guide points
	for(int i = 0; i < numberOfPoints; i++)
	{
		glBegin(GL_POINTS);
			glColor4f(1.0,1.0,1.0,1.0);
			glVertex2f((pointsArray[i * 2]-(WW/2))/(WW/2),-(pointsArray[(i * 2)+1]-(WH/2))/(WH/2));
		glEnd();

		glFlush();
	}

	//read in the points specifed by the user from our array and then draw pass the points
	//to the vertex2f function to have them be drawn as a polygon
	glColor4f(r,g,b,a);
	glBegin(GL_POLYGON);
		for (int i = 0; i < numberOfPoints; ++i)
		{
			glVertex2f((pointsArray[i * 2]-(WW/2))/(WW/2),-(pointsArray[(i * 2)+1]-(WH/2))/(WH/2));
		}
	glEnd();

	glFlush();

	//reset the number of drawnPoints so the user can create another polygon
	drawnPPoints = 0;
	return;
}

//menu function used by the color menu just sets the RGB values based of the users choice
void selectColor(int item)
{
	switch(item)
	{
		case 0:
		{
			r = 0.0,g = 0.0,b = 0.0;
		} break;
		case 1: 
		{
			r = 1.0,g = 0.0,b = 0.0;
		} break;
		case 2:
		{
			r = 0.0,g = 1.0,b = 0.0;
		} break;
		case 3:
		{
			r = 0.0,g = 0.0,b = 1.0;
		} break;
		case 4:
		{
			r = 1.0,g = 0.0,b = 1.0;
		} break;
		case 5:
		{
			r = 1.0,g = 1.0,b = 0.0;
		} break;
		case 6:
		{
			r = 0.0,g = 1.0,b = 1.0;
		} break;
		case 7:
		{
			r = 1.0,g = 0.5,b = 0.0;
		} break;
		default: {} break;
	}
	//if the brigthness window is open we want to update that
	//so that the sliders bars reflect the color change with out having
	//to click back into the window to post a update
	if(brightnessWindow != -1)
	{	
		glutSetWindow(brightnessWindow);
		glutPostRedisplay();
		glutSetWindow(mainWindow);
	}	
	return;
}

//shape menu function we just set our global variable with the users choice
void selectShape(int item)
{
	selectedShape = item;
	return;
}

//mouse press functon
void mousePressHandler(GLint button, GLint state, GLint x, GLint y)
{

	// if the user presses the left button down
	//we calculate the mouse position relative to the screen
	//and save it to a global this will be used in the motion function
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		downX = (x-(WW/2))/(WW/2); 
		downY = -(y-(WH/2))/(WH/2);
		prevX = downX;
		prevY = downY;
	}
	//same as above but with the up register
	else if(button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		upX = (x-(WW/2))/(WW/2);
		upY = (y-(WH/2))/(WH/2);
		prevX = upX;
		prevY = upY;
	}
	
	if(selectedShape == 3 && drawnPPoints != numPolyPoints 
		&& button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		downX = (x-(WW/2))/(WW/2); 
		downY = -(y-(WH/2))/(WH/2);
		prevX = downX;
		prevY = downY;
	}
	//This is where we draw our polygon
	//if the user has selected to draw a polygon and have not already selected the points
	//on screen we add it to an array
	else if(selectedShape == 3 && drawnPPoints != numPolyPoints 
		&& button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		upX = (x-(WW/2))/(WW/2);
		upY = (y-(WH/2))/(WH/2);
		prevX = upX;
		prevY = upY;
		
		polyArray[drawnPPoints * 2] = x;
		polyArray[(drawnPPoints * 2) + 1] = y;
		
		//draw a reference point so the user can get an idea of the polygons shape
		drawPoint(x,y);
		drawnPPoints++;
		//if the point drawn was the last one call our function to draw the polygon
		if(drawnPPoints == numPolyPoints)
		{
			drawPolygon(polyArray, numPolyPoints);
		}
	}
	return;
}

//Function to read in the color of the pixel the cursor is on
//this is used in the color picker window
void colorMouseHandler(GLint button, GLint state, GLint x, GLint y)
{
	//first allocate an array of bytes we can store the pixel data
	GLubyte *pixelData = malloc(4 * 1 * 1);
	glReadPixels(x, glutGet(GLUT_WINDOW_HEIGHT) - y, 1,1, GL_RGBA, GL_UNSIGNED_BYTE, pixelData);

	//as the data is saved as a byte we need to dived it by 255 to get it
	//in a value we can pass to color4f
	r = (float)pixelData[0] / 255.0;
	g = (float)pixelData[1] / 255.0;
	b = (float)pixelData[2] / 255.0;

	//if the brightness window is open we want to update the 
	//sliders to reflect the users choice
	if(brightnessWindow != -1)
	{	
		int cur = glutGetWindow();
		glutSetWindow(brightnessWindow);
		glutPostRedisplay();
		glutSetWindow(cur);
	}	
}

//function to move our RGB sliders
void moveRGBSliders( GLint x , GLint y )
{	
	GLfloat curX, curY;
	curX=(10-(BW/2))/(BW/2); 
	curY=-(y-(BH/2))/(BH/2);

	//if the mouse is in the slider
	if(x >= 10 && x <= 60 && y >= 40 && y <= 230)
	{	
		//calculate the color value for that slider relative to its slider position
		r = ((210 - ((float)y - 30.0))/200.0);
		curX=(10-(BW/2))/(BW/2); 
		curY=((210 * r)-(BH/2))/(BH/2);

		//draw our slider again to remove the old value line
		glColor4f(0.5,0.5,0.5,1.0);
		drawPolly(10,10,60,210,BH,BW);

		//update the line to reflect the new position on the slider
		glBegin(GL_LINES);
			glColor4f(0.0,0.0,0.0,1.0);
			glVertex2f((10-(BW/2))/(BW/2),((210 *  r)-(BH/2))/(BH/2));
			glVertex2f((60-(BW/2))/(BW/2),((210 *  r)-(BH/2))/(BH/2));
		glEnd();
		glFlush();
	}
	if(x >= 70 && x <= 120 && y >= 40 && y <= 230)
	{	
		g = ((210 - ((float)y - 30.0)) /200.0);
		curX=(70-(BW/2))/(BW/2); 
		curY=((210 * g)-(BH/2))/(BH/2);

		glColor4f(0.5,0.5,0.5,1.0);
		drawPolly(70,10,120,210,BH,BW);

		glBegin(GL_LINES);
			glColor4f(0.0,0.0,0.0,1.0);
			glVertex2f((70-(BW/2))/(BW/2),((210 *  g)-(BH/2))/(BH/2));
			glVertex2f((120-(BW/2))/(BW/2),((210 *  g)-(BH/2))/(BH/2));
		glEnd();
		glFlush();
	}
	if(x >= 130 && x <= 180 && y >= 40 && y <= 230)
	{	
		b = ((210 - ((float)y - 30.0))/200.0);
		curX=(130-(BW/2))/(BW/2); 
		curY=((210 * b)-(BH/2))/(BH/2);

		glColor4f(0.5,0.5,0.5,1.0);
		drawPolly(130,10,180,210,BH,BW);

		glBegin(GL_LINES);
			glColor4f(0.0,0.0,0.0,1.0);
			glVertex2f((130-(BW/2))/(BW/2),((210 *  b)-(BH/2))/(BH/2));
			glVertex2f((180-(BW/2))/(BW/2),((210 *  b)-(BH/2))/(BH/2));
		glEnd();
		glFlush();
	}
	//set our color back to be the selected RGB values
	glColor4f(r,g,b,a);
	prevX = curX;
	prevY = curY;
	//draw our color reference window box so the user can see what
	//change moving the sliders made to the current color
	drawPolly(10,220,180,250,BH,BW);
	return;
}

//function to move our transparancy slider
void moveTransSlider( GLint x , GLint y )
{	

	//simply calculate our alpha value relative to the slider position
	//and then just call the display function again
	a = (float)y / 200.0;

	displayTransSlider();

	//printf("%d , %d , %f \n", x, y,a);
}	

//function for our main menu
void menu(int item)
{
	switch(item)
	{	
		//if the user choose to clear the window just call the redisplay function
		case 0:
		{
			glutPostRedisplay();
		}break;
		//if the user chose the color picker option
		case 1:
		{
			//if the color picker is not open 
			if(palleteWindow == -1 )
			{
				//create the window 
				glutInitWindowSize(CW,CH);
				//we want to position it to the left of our draw window
				glutInitWindowPosition(500 - (CW+20),100);
				palleteWindow = glutCreateWindow("color picker");

				//assigne the display function and the color picker mouse fucntion
				glutDisplayFunc(colorSquare);
				glutMouseFunc(colorMouseHandler);
			}
			//else if the window is open just destroy it
			else
			{
				glutDestroyWindow(palleteWindow);
				palleteWindow = -1;
			}

		}break;
		//if the user selected to open the brightness window
		case 2:
		{
			if(brightnessWindow == -1)
			{
				glutInitWindowSize(BW, BH);
				glutInitWindowPosition(500 - (BW+20),400);
				brightnessWindow = glutCreateWindow("Brightness");

				glutDisplayFunc(displayRGBSlider);
				glutMotionFunc(moveRGBSliders);
			}
			else
			{
				glutDestroyWindow(brightnessWindow);
				brightnessWindow = -1;
			}
		}break;
		//if the user choose to open the transparency window
		case 3:
		{

			if(transWindow == -1)
			{
				glutInitWindowSize(TW, TH);
				//the left side is getting clutered so we will put it on the right side
				glutInitWindowPosition(500 + WW + 20,100);
				transWindow = glutCreateWindow("Transparency");

				glutDisplayFunc(displayTransSlider);
				glutMotionFunc(moveTransSlider);
			}
			else
			{
				glutDestroyWindow(transWindow);
				transWindow = -1;
			}
		}break;
		default:{}break;
	}
	return;
}

//function to handle the number of points in the polygon the user wants to draw
void selectPoly(int item)
{
	numPolyPoints = item;
	selectedShape = 3;
}


//our main windows create function
int createMainWindow()
{
	glutInitWindowSize(WW,WH);
	glutInitWindowPosition(500,100);
	int id = glutCreateWindow("MyPaint");

	glutSetMenu(addMainMenu());
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutDisplayFunc(display);
	glutMouseFunc(mousePressHandler);
	glutMotionFunc(drawShape);

	return id;
}


//our menus create function
int addMainMenu()
{	
	//create all our sub menus first so we can add them to their
	//parents
	int colorSubMenu = glutCreateMenu(selectColor);
	glutAddMenuEntry("Black",0);
	glutAddMenuEntry("Red",1);
	glutAddMenuEntry("Green",2);
	glutAddMenuEntry("Blue",3);
	glutAddMenuEntry("Pink",4);
	glutAddMenuEntry("Yellow",5);
	glutAddMenuEntry("Aqua",6);
	glutAddMenuEntry("Orange",7);

	int polyMenu = glutCreateMenu(selectPoly);
	glutAddMenuEntry(" 3 ",3);
	glutAddMenuEntry(" 5 ",5);
	glutAddMenuEntry(" 6 ",6);
	glutAddMenuEntry(" 7 ",7);
	glutAddMenuEntry(" 8 ",8);

	int shapeMenu = glutCreateMenu(selectShape);
	glutAddMenuEntry("point",0);
	glutAddMenuEntry("Line",1);
	glutAddMenuEntry("Rectangle",2);
	glutAddSubMenu("Polygon",polyMenu);
	
	int mainMenu = glutCreateMenu(menu);
	glutAddSubMenu("Color",colorSubMenu);
	glutAddSubMenu("Shape",shapeMenu);
	glutAddMenuEntry("Clear",0);
	glutAddMenuEntry("Color Pallete",1);
	glutAddMenuEntry("Brightness",2);
	glutAddMenuEntry("Transparency",3);
	
	return mainMenu;
}

//MAIN
int main(int argc, char **argv)
{
	//init 
	glutInit(&argc, argv);
	//create our main window
	mainWindow = createMainWindow();

	//enable Blending and pass out blend function to enable the use of 
	//alpha in color4f
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glutMainLoop();
}
