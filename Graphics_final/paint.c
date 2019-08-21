/*
* @author Elena Chestnov
*/

#include <glut.h>
#include <stdio.h>

int xn, yn, xo, yo;
char res;
int res1, res2; //size of the screen
int submenu;

int size = 1; // pencil/eraser size
int color = 10; //current color
int tool = 1;  //current tool

int c[3][20] = {	{ 255,127,136,237,255,255,34 ,0  ,63 ,163,0,195,185,255,255,239,181,153,112,200 },
					{ 255,127,0  ,28 ,127,242,177,162,72 ,73 ,0,195,122,174,201,228,230,217,146,191 },
					{ 255,127,21 ,36 ,39 ,0  ,76 ,232,204,164,0,195,87 ,201,14 ,176,29 ,234,190,231 } }; // all colors

void Reshape(int width, int height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, res1 * 4, res2 * 4, 0);
	glMatrixMode(GL_MODELVIEW);
	glutReshapeWindow(res1, res2); // disables reshaping
	glClear(GL_COLOR_BUFFER_BIT);

}
//------- Top Menu -------------------------------------------------------------------
void Pencil(int i) {
	i *= 350;
	glBegin(GL_QUADS);
	glColor3f(0.5, 0.5, 0.5);
	glVertex2i(80 + i, 110);
	glVertex2i(290 + i, 30);
	glVertex2i(310 + i, 50);
	glVertex2i(100 + i, 130);

	glColor3f(0.4, 0.4, 0.4);
	glVertex2i(100 + i, 135);
	glVertex2i(310 + i, 55);
	glVertex2i(310 + i, 75);
	glVertex2i(100 + i, 155);

	glColor3f(0.7, 0.7, 0.7);
	glVertex2i(80 + i, 110);
	glVertex2i(100 + i, 130);
	glVertex2i(100 + i, 160);
	glVertex2i(40 + i, 160);
	glEnd();
}
void Eraser(int i) {
	i *= 350;
	glBegin(GL_QUADS);
	glColor3f(0.5, 0.5, 0.5);
	glVertex2i(100 + i, 100);
	glVertex2i(180 + i, 100);
	glVertex2i(260 + i, 60);
	glVertex2i(180 + i, 60);

	glColor3f(0.4, 0.4, 0.4);
	glVertex2i(160 + i, 160);
	glVertex2i(180 + i, 100);
	glVertex2i(260 + i, 60);
	glVertex2i(250 + i, 110);

	glColor3f(0.7, 0.7, 0.7);
	glVertex2i(160 + i, 160);
	glVertex2i(180 + i, 100);
	glVertex2i(100 + i, 100);
	glVertex2i(80 + i, 160);

	glEnd();
}
void Sizes(int i) {
	int j;
	i *= 350;
	for (j = 1;j <= 4;j++) {
		glLineWidth(j);
		if (j == size) {
			glColor3f(0, 0, 0);
			glBegin(GL_LINES);
			glVertex2i(40 + i, 40 * j + 5);
			glVertex2i(320 + i, 40 * j + 5);
			glEnd();
		}
		else {
			glColor3f(0.6, 0.6, 0.6);
			glBegin(GL_LINES);
			glVertex2i(40 + i, 40 * j + 5);
			glVertex2i(320 + i, 40 * j + 5);
			glEnd();
		}
	}
}
void Colors(int i) {
	int j;
	i = i * 350 + 5;
	glColor3ub(0, 0, 0);
	glRectf(14 + i, 70, 95 + i, 150);
	glColor3ub(c[0][color], c[1][color], c[2][color]);
	glRectf(20 + i, 75, 90 + i, 145);
	i += 100;
	for (j = 0;j < 10;j++, i += 85) {
		glColor3ub(c[0][j], c[1][j], c[2][j]);
		glRectf(20 + i, 25, 90 + i, 95);
		glColor3ub(c[0][j + 10], c[1][j + 10], c[2][j + 10]);
		glRectf(20 + i, 110, 90 + i, 180);
	}
}
void Text(void *font, const char* string)
{
	while (*string)
		glutStrokeCharacter(font, *string++);
}
void Draw(void) //top menu body
{
	int i, j;
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glColor3f(0, 0, 0);
	glRectf(0, 0, res1 * 4, 205);
	glColor3f(0.9, 0.9, 0.9);
	glRectf(0, 0, res1 * 4, 200);
	glLineWidth(1);
	glBegin(GL_LINES);
	glColor3f(0, 0, 0);
	for (i = 1;i < 4;i++) {
		glVertex2i(i * 350, 0);
		glVertex2i(i * 350, 200);
	}
	glVertex2i(res1 * 4 - 400, 0);
	glVertex2i(res1 * 4 - 400, 200);
	glEnd();

	Pencil(0);
	Eraser(1);
	Sizes(2);
	Colors(3);
	glColor3f(0, 0, 0);
	glLineWidth(2);

	glPushMatrix();
	glTranslatef(res1*4-300, 120, 0);
	glScalef(0.5,0.5, 0);
	glRotatef(180, 1, 0, 0);
	Text(GLUT_STROKE_MONO_ROMAN, "Exit");
	glPopMatrix();

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glRectf(20 + (tool-1)*350, 20, 330 + (tool-1)*350, 180); //shows current tool

	glFlush();
}
//------- Top Menu Functions -------------------------------------------------------------------
void TopMenu(int x, int y) {
	int i, j;
	if (x < 2005) {
		if (x > 0 && x < 350) { //pencil
			tool = 1;
		}
		else if (x < 700) { //eraser
			tool = 2;
		}
		else if (x < 1050) { //sizes
			if (y < 62)
				size = 1;
			else if (y < 105)
				size = 2;
			else if (y < 145)
				size = 3;
			else
				size = 4;
		}
		else if (x > 1170) //colors
			for (i = 1150, j = 0;j < 10;j++, i += 85) {
				if (x > 20 + i && x < 90 + i)
					if (y > 25 && y < 95) {
						color = j;
						tool = 1;
						break;
					}
					else if (y > 110 && y < 180) {
						color = j + 10;
						tool = 1;
						break;
					}
			}
		Draw();
		glColor3ub(c[0][color], c[1][color], c[2][color]);
		glLineWidth(size);
	}
	else if (x > res1 * 4 - 400 && x < res1 * 4) //exit
		exit(0);
}
//------- Drawing Functions -------------------------------------------------------------------

void DragFunc(int xx, int yy) {
	int i;
		xo = xn;
		yo = yn;
		xn = xx * 4;
		yn = yy * 4;
		if (yn < 206)
			yn = yo = 206+size;
		else if (yn > res2 * 4)
			yn = yo = res2 * 4;
		if (xn < 0)
			xn = xo = 0;
		else if (xn > res1 * 4)
			xn = xo = res1 * 4;

		glBegin(GL_LINES);
		glVertex2i(xo, yo);
		glVertex2i(xn, yn);
		glEnd();

		glFlush();
}
//------- Mouse Functions -------------------------------------------------------------------
void MouseFunc(int button, int state, int x, int y)
{
	xn = x * 4;
	yn = y * 4;
	if (tool == 1)
		glColor3ub(c[0][color], c[1][color], c[2][color]);
	else if (tool == 2)
		glColor3ub(255, 255, 255);
	glLineWidth(size);

	if (button == GLUT_LEFT_BUTTON&&state == GLUT_DOWN)
		if (yn > 206+size)
			glutMotionFunc(DragFunc);

		else if (yn > 0)
			TopMenu(xn, yn);
}
//------- Menus -------------------------------------------------------------------
void select(int opt)
{
	res = opt + '0';
	switch (res) {
	case '1':
		res1 = 800;
		res2 = 540;
		break;
	case '2':
		res1 = 1024;
		res2 = 708;
		break;
	case '3':
		res1 = 1920;
		res2 = 1020;
		break;
	case 27:  /*  Escape Key */
		exit(0);
		break;
	default:
		break;
	}
	glutReshapeWindow(res1, res2);
	glClear(GL_COLOR_BUFFER_BIT);
}
void main_menu(int value)
{
	int i, j;
	switch (value) {
	case 1:
		glClear(GL_COLOR_BUFFER_BIT);
		Draw();
		break;
	case 2:
		exit(0);
		break;
	default:
		break;
	}
}
int main(int argc, char *argv[])
{
	printf("\nPlease chose a resolution by typing the option number:\n1. 800x600\n2. 1024x768\n3. 1920x1080\n");
start:
	res=getch();
	switch (res) {
	case '1':
		res1 = 800;
		res2 = 540;
		break;
	case '2':
		res1 = 1024;
		res2 = 708;
		break;
	case '3':
		res1 = 1920;
		res2 = 1020;
		break;
	default:
		goto start;
		break;
	}

	glutInit(&argc, argv);
	glutInitWindowSize(res1, res2);
	glutInitWindowPosition(0, 0);
	glutInitDisplayMode(GLUT_SINGLE);
	glutCreateWindow("Painting Tool");
	glClearColor(1, 1, 1, 1.0f);
	glutReshapeFunc(Reshape);
	glClear(GL_COLOR_BUFFER_BIT);
	glutDisplayFunc(Draw);
	glutMouseFunc(MouseFunc);

	submenu = glutCreateMenu(select);
	glutAddMenuEntry("800x600", 1);
	glutAddMenuEntry("1024x768", 2);
	glutAddMenuEntry("1920x1080", 3);
	
	glutCreateMenu(main_menu);
	glutAddMenuEntry("Clear", 1);
	glutAddMenuEntry("Exit", 2);
	glutAddSubMenu("Change resolution", submenu);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutMainLoop();
	return 0;
}