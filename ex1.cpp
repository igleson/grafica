#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>

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
	bool randing;
	
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
		randing = false;
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
	
	bool right(){
		if(DX != 800){
			float diff = 10;
			if(DX+10 > 800){
				diff = 800-DX;	
			}
			AX+=diff;
			BX+=diff;
			CX+=diff;
			DX+=diff;
			EX+=diff;
			return true;
		}
		return false;
	}
	
	bool left(){
		if(BX != 0){
			float diff = 10;
			if(BX-10 < 0){
				diff = BX;
			}
			AX-=diff;
			BX-=diff;
			CX-=diff;
			DX-=diff;
			EX-=diff;
			return true;
		}
		return false;
	}
	
	bool up(){
		if(CY != 600){
			float diff = 10;
			if(CY+10 > 600) diff = 600-CY;
			AY+=diff;
			BY+=diff;
			CY+=diff;
			DY+=diff;
			EY+=diff;
			return true;
		}
		return false;
	}
	
	bool down(){
		if(AY != 0){
			float diff = 10;
			if(AY - 10 < 0) diff = AY;
			AY-=diff;
			BY-=diff;
			CY-=diff;
			DY-=diff;
			EY-=diff;
			return true;
		}
		return false;
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

void startLeft(int value);
void startDown(int value);

void startRight(int value){
	if(p.randing){
		bool moved = p.right();	
		if(moved){
			glutTimerFunc(16,startRight,1); 		
		}else{
			glutTimerFunc(16,startLeft,1);
		}
		p.draw();
	}
}

void startLeft(int value){
	if(p.randing){
		bool moved = p.left();
		if(moved){
			glutTimerFunc(16,startLeft,1); 		
		}else{
			glutTimerFunc(16,startRight,1);
		}
		p.draw();
	}
}

void startUp(int value){
	if(p.randing){
		bool moved = p.up();
		if(moved){
			glutTimerFunc(16,startUp,1); 		
		}else{
			glutTimerFunc(16,startDown,1);
		}
		p.draw();
	}
}

void startDown(int value){
	if(p.randing){
		bool moved = p.down();
		if(moved){
			glutTimerFunc(16,startDown,1); 		
		}else{
			glutTimerFunc(16,startUp,1);
		}
		p.draw();
	}
}

void handleKeypress (unsigned char key, int x, int y){
	if (key == 'p'){
		if(!p.randing){
			p.randing = !p.randing;
			switch(rand()%4){
				case(0):
					startLeft(1);
					startDown(1);
					break;
				case(1):
					startLeft(1);
					startUp(1);
					break;
				case(2):
					startRight(1);
					startDown(1);
					break;
				case(3):
					startRight(1);
					startUp(1);
					break;
			}
		}else{
			p.randing = !p.randing;
		}
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
