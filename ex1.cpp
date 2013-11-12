#include <GL/glut.h>

struct penta {
	float AX;
	float AY;
	float BX;
	float BY;
	float CX;
	float CY;
	float DX;
	float DY;
	float EX;
	float EY;
	
	penta(){
		AX = 100;
		AY = 100;
		BX = 69.098;
		BY = 195.106;
		CX = 150;
		CY = 253.884;
		DX = 230.902;
		DY = 195.106;
		EX = 200;
		EY = 100;
	}
	
	void draw(){
		glClear (GL_COLOR_BUFFER_BIT);
		glColor3f (0.0, 0.0, 0.0);
		glBegin(GL_LINE_LOOP);
			glVertex3f (AX, AY, 0.0);
			glVertex3f (BX, BY, 0.0);
			glVertex3f (CX, CY, 0.0);
			glVertex3f (DX, DY, 0.0);
			glVertex3f (EX, EY, 0.0);
		glEnd();
		glFlush();
	}
	
	void right(){
		float diff = 10;
		if(DX+10 > 800){
			diff = 800-DX;	
		}
		AX+=diff;
		BX+=diff;
		CX+=diff;
		DX+=diff;
		EX+=diff;
	}
	
	void left(){
		float diff = 10;
		if(BX-10 < 0){
			diff = BX;
		}
		AX-=diff;
		BX-=diff;
		CX-=diff;
		DX-=diff;
		EX-=diff;
	}
	
	void up(){
		float diff = 10;
		if(CY+10 > 600) diff = 600-CY;
		AY+=diff;
		BY+=diff;
		CY+=diff;
		DY+=diff;
		EY+=diff;
	}
	
	void down(){
		float diff = 10;
		if(AY - 10 < 0) diff = AY;
		AY-=diff;
		BY-=diff;
		CY-=diff;
		DY-=diff;
		EY-=diff;
	}
}p;

void init (void){
	/* select clearing (background) color */
	glClearColor (1.0, 1.0, 1.0, 0.0);
	/* initialize viewing values */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, 800.0, 0.0, 600.0, -1.0, 1.0);
}

void display(void){
	p.draw();
}

void handleKeypress (unsigned char key, int x, int y){
	if (key == 'p'){
		exit(0);
	}
}

void processSpecialKeys(int key, int x, int y) {
	switch(key) {
		case GLUT_KEY_LEFT :
			p.left();
			p.draw();
			break;
		case GLUT_KEY_RIGHT :
			p.right();
			p.draw();
			break;
		case GLUT_KEY_UP :
			p.up();
			p.draw();
			break;
		case GLUT_KEY_DOWN :
			p.down();
			p.draw();
			break;
	}
}

int main(int argc, char** argv){
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize (800, 600);
	glutInitWindowPosition (100, 100);
	glutCreateWindow ("hello");
	init();
	glutKeyboardFunc(handleKeypress);
	glutSpecialFunc(processSpecialKeys);
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}
