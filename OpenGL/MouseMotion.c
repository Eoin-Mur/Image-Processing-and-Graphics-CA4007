#include <GL/gl.h>
#include <GL/glext.h>
#include <GL/glut.h>

/* 
This program illustrates the Mouse Motion Callbacks.
MyMouse illustrates the Passive Motion Callback.
It causes the square to change colour whenever the mouse
enters the square.
MyMouse2 illustrates the Active Motion Callback.
It causes a black point to appear whenever you press
a mouse button.

Please note, this program assumes the window size is 500x500.
If you resize the window it will not work properly
*/

void display(void)
{
	glClearColor(0.0,0.0,1.0,1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(3.0);
	glColor3f(1.0,0.0,0.0);

	glBegin(GL_POLYGON);
		glVertex2f(-0.5,-0.5);
		glVertex2f(-0.5,0.5);
		glVertex2f(0.5,0.5);
		glVertex2f(0.5,-0.5);
	glEnd();

	glFlush();
	return;
}

void MyMouse(GLint x, GLint y)
{
	if (x > 125 && x < 375 && y > 125 && y < 375)
		glColor3f(0.0,1.0,0.0);
	else
		glColor3f(1.0,0.0,0.0);

	glBegin(GL_POLYGON);
		glVertex2f(-0.5,-0.5);
		glVertex2f(-0.5,0.5);
		glVertex2f(0.5,0.5);
		glVertex2f(0.5,-0.5);
	glEnd();

	glFlush();	


	return;
}


void MyMouse2(GLint x, GLint y)
{
	glColor3f(0.0,0.0,0.0);
	glPointSize(3.0);
	glBegin(GL_POINTS);
		glVertex2f((x-250.0)/250.0,-(y-250.0)/250.0);
	glEnd();

	glFlush();	

	return;
}
	
int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(500,200);
	glutCreateWindow("mouse");
	glutDisplayFunc(display);
	glutPassiveMotionFunc(MyMouse);
	glutMotionFunc(MyMouse2);


	glutMainLoop();
}