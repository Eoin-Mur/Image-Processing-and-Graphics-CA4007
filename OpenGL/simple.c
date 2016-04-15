#include <GL/gl.h>
#include <GL/glext.h>
#include <GL/glut.h>

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	//glColor3f(0.0,1.0,0.0);
	glBegin(GL_POLYGON);
		glVertex2f(-1,-1);
		glVertex2f(-1,1);
		glVertex2f(1,1);
		glVertex2f(1,-1);
	glEnd();

	glFlush();
	return;
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutCreateWindow("simple");
	glutDisplayFunc(display);
	glutMainLoop();
}