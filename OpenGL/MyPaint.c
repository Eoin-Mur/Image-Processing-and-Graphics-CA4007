#include <GL/gl.h>
#include <GL/glext.h>
#include <GL/glut.h>
#include <stdio.h>
#include <string.h>

#define WW 800.0
#define WH 500.0
#define PW 200.0
#define PH 500.0

//gcc Reshape.c -o Reshape glut32.lib -lopengl32 -lglu32

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
	b;

struct button
{
	float x1;
	float y1;
	float x2;
	float y2;
};



int selectedShape = 0;
int mainWindow;
int palleteWindow = -1;
int CLEAR = 1;

void display()
{
	glClearColor(1.0,1.0,1.0,1.0);
	if(CLEAR == 1)
	{
		glClear(GL_COLOR_BUFFER_BIT);
	}
	CLEAR = !CLEAR;
	glColor3f(0.0,0.0,0.0);
	glPointSize(3.0);

	glFlush();

	return;
}

void displayPalette()
{
	glClearColor(1.0,1.0,1.0,1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0,0.0,0.0);
	glLineWidth(3.0);

	glBegin(GL_LINES);
		glVertex2f(-1.0,1.0);
		glVertex2f(-1.0,-1.0);
	glEnd();
	glFlush();


	glBegin(GL_POLYGON);
		glColor3f(0.5,0.5,0.5);
		glVertex2f((10-(PW/2))/(PW/2),(210-(PH/2))/(PH/2));
		glVertex2f((10-(PW/2))/(PW/2),(10-(PH/2))/(PH/2));
		glVertex2f((60-(PW/2))/(PW/2),(10-(PH/2))/(PH/2));
		glVertex2f((60-(PW/2))/(PW/2),(210-(PH/2))/(PH/2));
	glEnd();

	glBegin(GL_POLYGON);
		glColor3f(0.5,0.5,0.5);
		glVertex2f((70-(PW/2))/(PW/2),(210-(PH/2))/(PH/2));
		glVertex2f((70-(PW/2))/(PW/2),(10-(PH/2))/(PH/2));
		glVertex2f((120-(PW/2))/(PW/2),(10-(PH/2))/(PH/2));
		glVertex2f((120-(PW/2))/(PW/2),(210-(PH/2))/(PH/2));
	glEnd();

	glBegin(GL_POLYGON);
		glColor3f(0.5,0.5,0.5);
		glVertex2f((130-(PW/2))/(PW/2),(210-(PH/2))/(PH/2));
		glVertex2f((130-(PW/2))/(PW/2),(10-(PH/2))/(PH/2));
		glVertex2f((180-(PW/2))/(PW/2),(10-(PH/2))/(PH/2));
		glVertex2f((180-(PW/2))/(PW/2),(210-(PH/2))/(PH/2));
	glEnd();

	glColor3f(0.0,0.0,0.0);

	glBegin(GL_LINES);
		glVertex2f((10-(PW/2))/(PW/2),((210 * r)-(PH/2))/(PH/2));
		glVertex2f((60-(PW/2))/(PW/2),((210 * r)-(PH/2))/(PH/2));
	glEnd();

	glBegin(GL_LINES);
		glVertex2f((70-(PW/2))/(PW/2),((210 * g)-(PH/2))/(PH/2));
		glVertex2f((120-(PW/2))/(PW/2),((210 * g)-(PH/2))/(PH/2));
	glEnd();

	glBegin(GL_LINES);
		glVertex2f((130-(PW/2))/(PW/2),((210 * b)-(PH/2))/(PH/2));
		glVertex2f((180-(PW/2))/(PW/2),((210 * b)-(PH/2))/(PH/2));
	glEnd();

	return;

}

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
	glColor3f(r,g,b);
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

	curX=(x-(WW/2))/(WW/2); 
	curY=-(y-(WH/2))/(WH/2);

	glColor4f(1.0,1.0,1.0,0.0);
	glBegin(GL_POLYGON);
		glVertex2f(downX,downY);
		glVertex2f(downX,prevY);
		glVertex2f(prevX,prevY);
		glVertex2f(prevX,downY);
	glEnd();

	glColor3f(r,g,b);
	glBegin(GL_POLYGON);
		glVertex2f(downX,downY);
		glVertex2f(downX,curY);
		glVertex2f(curX,curY);
		glVertex2f(curX,downY);
	glEnd();

	prevX = curX;
	prevY = curY;

	glFlush();
	return;
}

void drawLine(GLint x, GLint y)
{
	GLfloat curX, curY;

	curX=(x-(WW/2))/(WW/2); 
	curY=-(y-(WH/2))/(WH/2);

	glColor3f(r,g,b);
	glLineWidth(3.0);

	glBegin(GL_LINES);
		glColor4f(1.0,1.0,1.0,0.0);
		glVertex2f(downX, downY);
		glVertex2f(prevX, prevY);
		glColor3f(r,g,b);
		glVertex2f(downX, downY);
		glVertex2f(curX, curY);
	glEnd();

	glFlush();

	prevX = curX;
	prevY = curY;
	return;
}

void selectColor(int item)
{
	switch(item)
	{
		case 0:
		{
			r = 0.0,g = 0.0,b = 0.0;
			//glColor3f(0.0,0.0,0.0);
		} break;
		case 1: 
		{
			r = 1.0,g = 0.0,b = 0.0;
			//glColor3f(1.0,0.0,0.0);
		} break;
		case 2:
		{
			r = 0.0,g = 1.0,b = 0.0;
			//glColor3f(0.0,1.0,0.0);
		} break;
		case 3:
		{
			r = 0.0,g = 0.0,b = 1.0;
			//glColor3f(0.0,0.0,1.0);
		} break;
		case 4:
		{
			r = 1.0,g = 0.0,b = 1.0;
			//glColor3f(0.0,0.0,1.0);
		} break;
		case 5:
		{
			r = 1.0,g = 1.0,b = 0.0;
			//glColor3f(0.0,0.0,1.0);
		} break;
		case 6:
		{
			r = 0.0,g = 1.0,b = 1.0;
			//glColor3f(0.0,0.0,1.0);
		} break;
		case 7:
		{
			r = 1.0,g = 0.5,b = 0.0;
			//glColor3f(0.0,0.0,1.0);
		} break;
		default: {} break;
	}
	if(palleteWindow != -1)
	{	
		glutSetWindow(palleteWindow);
		glutPostRedisplay();
		glutSetWindow(mainWindow);
	}	
	return;
}

void selectShape(int item)
{
	selectedShape = item;
	return;
}

void mousePressHandler(GLint button, GLint state, GLint x, GLint y)
{
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		downX = (x-(WW/2))/(WW/2); 
		downY = -(y-(WH/2))/(WH/2);
		prevX = downX;
		prevY = downY;
	}
	else if(button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		upX = (x-(WW/2))/(WW/2);
		upY = (y-(WH/2))/(WH/2);
		prevX = upX;
		prevY = upY;
	}
	//printf("downx = %d, downy = %d\n", downX, downY);
	return;
}

void test(GLint button, GLint state, GLint x, GLint y)
{
	printf("x = %d, y = %d\n", x,y);
}

void moveSliders( GLint x , GLint y )
{	
	GLfloat curX, curY;
	curX=(10-(PW/2))/(PW/2); 
	curY=-(y-(PH/2))/(PH/2);

	if(x >= 10 && x <= 60 && y >= 290 && y <= 490)
	{	
		r = ((490.0-(float)y)/200.0);
		curX=(10-(PW/2))/(PW/2); 
		curY=((210 * r)-(PH/2))/(PH/2);

		glBegin(GL_LINES);
			glColor4f(0.5,0.5,0.5,0.0);
			glVertex2f((10-(PW/2))/(PW/2),prevY);
			glVertex2f((60-(PW/2))/(PW/2),prevY);
			glColor3f(0.0,0.0,0.0);
			glVertex2f((10-(PW/2))/(PW/2),((210 *  r)-(PH/2))/(PH/2));
			glVertex2f((60-(PW/2))/(PW/2),((210 *  r)-(PH/2))/(PH/2));
		glEnd();
		glFlush();
	}
	if(x >= 70 && x <= 120 && y >= 290 && y <= 490)
	{	
		g = ((490.0-(float)y)/200.0);

		curX=(70-(PW/2))/(PW/2); 
		curY=((210 * g)-(PH/2))/(PH/2);

		glBegin(GL_LINES);
			glColor4f(0.5,0.5,0.5,0.0);
			glVertex2f((70-(PW/2))/(PW/2),prevY);
			glVertex2f((120-(PW/2))/(PW/2),prevY);
			glColor3f(0.0,0.0,0.0);
			glVertex2f((70-(PW/2))/(PW/2),((210 *  g)-(PH/2))/(PH/2));
			glVertex2f((120-(PW/2))/(PW/2),((210 *  g)-(PH/2))/(PH/2));
		glEnd();
		glFlush();
	}
	if(x >= 130 && x <= 180 && y >= 290 && y <= 490)
	{	
		b = ((490.0-(float)y)/200.0);

		curX=(130-(PW/2))/(PW/2); 
		curY=((210 * b)-(PH/2))/(PH/2);

		glBegin(GL_LINES);
			glColor4f(0.5,0.5,0.5,0.0);
			glVertex2f((130-(PW/2))/(PW/2),prevY);
			glVertex2f((180-(PW/2))/(PW/2),prevY);
			glColor3f(0.0,0.0,0.0);
			glVertex2f((130-(PW/2))/(PW/2),((210 *  b)-(PH/2))/(PH/2));
			glVertex2f((180-(PW/2))/(PW/2),((210 *  b)-(PH/2))/(PH/2));
		glEnd();
		glFlush();
	}
	glColor3f(r,g,b);
	prevX = curX;
	prevY = curY;
	return;
}

void menu(int item)
{
	switch(item)
	{
		case 0:
		{
			CLEAR = 1;
			glutPostRedisplay();
		}break;
		case 1:
		{
			glutInitWindowSize(PW,PH);
			glutInitWindowPosition(500 - (PW+20),200);
			palleteWindow = glutCreateWindow("color picker");

			glutDisplayFunc(displayPalette);
			glutMouseFunc(mousePressHandler);
			glutMotionFunc(moveSliders);

		}
		default:{}break;
	}
	return;
}

int createMainWindow()
{
	glutInitWindowSize(WW,WH);
	glutInitWindowPosition(500,200);
	int id = glutCreateWindow("MyPaint");

	glutSetMenu(addMainMenu());
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutDisplayFunc(display);

	glutMouseFunc(mousePressHandler);
	glutMotionFunc(drawShape);

	return id;
}

int createPalleteWindow()
{
	int id = glutCreateSubWindow(mainWindow,(WW-PW),0,PW,WH);
	glutDisplayFunc(displayPalette);
	glutMouseFunc(mousePressHandler);
	glutMotionFunc(moveSliders);

	return id;

}

int addMainMenu()
{
	int colorSubMenu = glutCreateMenu(selectColor);
	glutAddMenuEntry("Black",0);
	glutAddMenuEntry("Red",1);
	glutAddMenuEntry("Green",2);
	glutAddMenuEntry("Blue",3);
	glutAddMenuEntry("Pink",4);
	glutAddMenuEntry("Yellow",5);
	glutAddMenuEntry("Aqua",6);
	glutAddMenuEntry("Orange",7);

	int shapeMenu = glutCreateMenu(selectShape);
	glutAddMenuEntry("point",0);
	glutAddMenuEntry("Line",1);
	glutAddMenuEntry("Rectangle",2);
	//glutAddMenuEntry("Polygon",3);
	
	int mainMenu = glutCreateMenu(menu);
	glutAddSubMenu("color",colorSubMenu);
	glutAddSubMenu("shape",shapeMenu);
	glutAddMenuEntry("clear",0);
	glutAddMenuEntry("Add Color",1);

	return mainMenu;
}

int main(int argc, char **argv)
{

	glutInit(&argc, argv);
	
	mainWindow = createMainWindow();

	//palleteWindow = createPalleteWindow();
	//CLEAR = 0;
	glutMainLoop();
}