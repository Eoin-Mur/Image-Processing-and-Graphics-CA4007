#include <GL/gl.h>
#include <GL/glext.h>
#include <GL/glut.h>
#include <math.h>

#define M_PI 3.14159265358979323846

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	//glColor3f(0.0,1.0,0.0);
	glBegin(GL_POLYGON);
		glColor3f(1.0,0,0);
		glVertex2f(-1,-1);
		glColor3f(0,1.0,0);
		glVertex2f(-1,1);
		glColor3f(1.0,1.0,0);
		glVertex2f(1,1);
		glColor3f(0,0,1.0);
		glVertex2f(1,-1);
	glEnd();

	glFlush();
	return;
}


void drawCircle(float radius)
{
	glColor3f(1.0,1.0,1.0);
	glBegin(GL_LINE_LOOP);

	for (int i=0; i < 360; i++)
	{
		float angle = 2 * M_PI * i/360;
		float x = cos(angle);
		float y = sin(angle);
		glVertex2f(x,y);
	}

glEnd();
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutCreateWindow("simple");
	glutDisplayFunc(display);
	glutMainLoop();
}