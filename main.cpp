#include <windows.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#include <string.h>
#include <stdio.h>
#endif

void drawNumber(int number, int x, int y) {
    // Mengubah angka menjadi string
    char str[20];
    snprintf(str, sizeof(str), "%d", number);

    // Menampilkan angka
    glRasterPos2i(x, y);
    for(int i = 0; i < strlen(str); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, str[i]);
    }
}

void drawTile(int x, int y, int ny, int wx, int hy) {
    for(int i = 0; i < x; i++) {
        for(int j = 0; j < y; j++) {
            if(i % 2 == 0) {
                if(j % 2 == 0) {
                    // Biru
                    glColor3f(0.0, 0.0, 1.0);
                } else {
                    // Kuning
                    glColor3f(1.0, 1.0, 0.0);
                }
                glBegin(GL_POLYGON);
                    glVertex2f(j * wx, hy * (i + 1));
                    glVertex2f((j + 1) * wx, hy * (i + 1));
                    glVertex2f((j + 1) * wx, hy * i);
                    glVertex2f(j * wx, hy * i);
                glEnd();
            } else {
                if(j % 2 == 0) {
                    // Kuning
                    glColor3f(1.0, 1.0, 0.0);
                } else {
                    // Biru
                    glColor3f(0.0, 0.0, 1.0);
                }
                glBegin(GL_POLYGON);
                    glVertex2f(j * wx, hy * (i+ 1));
                    glVertex2f((j + 1) * wx, hy * (i + 1));
                    glVertex2f((j + 1) * wx, hy * i);
                    glVertex2f(j * wx, hy * i);
                glEnd();
            }
        }
    }
}

void drawPatternNumber(int x, int y, int ny, int wx, int hy) {
    glColor3f(0.0,0.0,0.0);

    for(int i = 0; i < x; i++) {
        for(int j = 0; j < y; j++) {
            if(i % 2 == 0) {
                int currentNumber = (i * y + j + 1);
                if(currentNumber % 10 == 4 || currentNumber % 10 == 7) {
                    drawNumber((i * y + j + 1), j * wx + 10, i * hy + 10);
                }
            } else {
                int currentNumber = (i * y + (y - j));
                if(currentNumber % 10 == 4 || currentNumber % 10 == 7) {
                    drawNumber((i * y + (y - j)), j * wx + 10, i * hy + 10);
                }
            }
        }
    }

}

void display(){
	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(4);

    int x = 7;
    int y = 12;
    int ny = 7;
    int wx = 350 / x;
    int hy = 600 / y;

    drawTile(x, y, ny, wx, hy);
    drawPatternNumber(x, y, ny, wx, hy);

	glFlush();
}

void myinit(){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 600.0, 0.0, 350.0);
	glMatrixMode(GL_MODELVIEW);
	glClearColor(1.0,1.0,1.0,1.0);
}

int main(int argc, char* argv[]){
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(600,350);
	glutInitWindowPosition(300,200);
	glutCreateWindow("Segitiga Titik");
	glutDisplayFunc(display);
	myinit();
	glutMainLoop();
	return 0;
}
