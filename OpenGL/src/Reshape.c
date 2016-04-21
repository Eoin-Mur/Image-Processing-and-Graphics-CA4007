#include <GL/gl.h>
#include <GL/glut.h>
#include <GL/glext.h>
#include <math.h>


//gcc Reshape.c -o Reshape glut32.lib -lopengl32 -lglu32

GLsizei ww, hh;
float theta = M_PI/4;

void display(void)
{
	glClearColor(0.0,0.0,1.0,1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(3.0);
	glColor3f(1.0,0.0,0.0);
	glLineWidth(5.0);
	GLfloat x=cos(theta), y = sin(theta);

	glBegin(GL_LINE_LOOP);
		glVertex2f(-x,-y);
		glVertex2f(-y,x);
		glVertex2f(x,y);
		glVertex2f(y,-x);
	glEnd();

	glColor3f(0.0,1.0,0.0);
	glBegin(GL_POLYGON);
		glVertex2f(0.0,-0.5);
		glVertex2f(-0.2,0.2);
		glVertex2f(-0.5,0.0);
		glVertex2f(-0.2,-0.2);
		glVertex2f(-0.5,-0.5);
		glVertex2f(0.2,0.2);
		glVertex2f(0.5,0.5);
		glVertex2f(0.2,-0.2);
		glVertex2f(0.5,0.0);
		glVertex2f(0.2,0.2);
	glEnd();

	glFlush();
	return;
}

void MyReshape(GLsizei w, GLsizei h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-1.0,1.0,-1.0,1.0);
	glViewport(0,0,w/2,h/2);
	return;
}

//MyReshape updated to keep the shape structure intact
void MyReshape2(GLsizei w, GLsizei h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h )
		gluOrtho2D(-1.0, 1.0, -1.0 * ((GLfloat) h / (GLfloat) w), 1.0 * ((GLfloat) h / (GLfloat) w));
	else
		gluOrtho2D(-1.0 * ((GLfloat) w / (GLfloat) h), 1.0 * ((GLfloat) w / (GLfloat) h), -1.0, 1.0);

	glMatrixMode(GL_MODELVIEW);
	glViewport(0,0,w,h);

	ww = w;
	hh = h;
	
	return; 
}

void myIdle()
{
	theta += 0.001;
	if (theta > 2*M_PI) theta -= 2*M_PI;
	glutPostRedisplay();

	return;
}
int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(500,200);
	glutCreateWindow("simple");
//	glColor3f(1.0,0.0,0.0);
	glutDisplayFunc(display);
	glutReshapeFunc(MyReshape2);
	//glutIdleFunc(myIdle);	

	glutMainLoop();
}
