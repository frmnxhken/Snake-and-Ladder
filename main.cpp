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
                    // Merah
                    glColor3f(1.0, 0.0, 0.0);
                } else {
                    // Putih
                    glColor3f(1.0, 1.0, 1.0);
                }
                glBegin(GL_POLYGON);
                    glVertex2f(j * wx, hy * (i + 1));
                    glVertex2f((j + 1) * wx, hy * (i + 1));
                    glVertex2f((j + 1) * wx, hy * i);
                    glVertex2f(j * wx, hy * i);
                glEnd();
            } else {
                if(j % 2 == 0) {
                    // Putih
                    glColor3f(1.0, 1.0, 1.0);
                } else {
                    // Merah
                    glColor3f(1.0, 0.0, 0.0);
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

    // Nim of Team
    // Highest nim = ilham
    // So total of columns = 12 and total of rows = 7

    int wahyudi = 4;
    int dani = 9;
    int evi = 5;
    int ilham = 7;



    for(int i = 0; i < x; i++) {
        for(int j = 0; j < y; j++) {
            if(i % 2 == 0) {
                int currentNumber = (i * y + j + 1);
                if(currentNumber % 10 == wahyudi || currentNumber % 10 == dani || currentNumber % 10 == evi || currentNumber % 10 == ilham) {
                    drawNumber((i * y + j + 1), j * wx + 10, i * hy + 10);
                }
            } else {
                int currentNumber = (i * y + (y - j));
                if(currentNumber % 10 == wahyudi || currentNumber % 10 == dani || currentNumber % 10 == evi || currentNumber % 10 == ilham) {
                    drawNumber((i * y + (y - j)), j * wx + 10, i * hy + 10);
                }
            }
        }
    }
}

void drawBorderTile(int w, int h) {
    glColor3f(0.0, 0.0, 0.0);

    glBegin(GL_POLYGON);
        //Border Kiri
        glVertex2f(0, h);
        glVertex2f(4, h);
        glVertex2f(4, 0);
        glVertex2f(0, 0);
    glEnd();

    glBegin(GL_POLYGON);
    // Border Atas
        glVertex2f(0, h);
        glVertex2f(w, h);
        glVertex2f(w, h - 4);
        glVertex2f(0, h - 4);
    glEnd();

    glBegin(GL_POLYGON);
        // Border Kanan
        glVertex2f(w, 0);
        glVertex2f(w - 4, 0);
        glVertex2f(w - 4, h);
        glVertex2f(w, h);
    glEnd();

    glBegin(GL_POLYGON);
        // Border Bawah
        glVertex2f(0, 0);
        glVertex2f(w, 0);
        glVertex2f(w, 4);
        glVertex2f(0, 4);
    glEnd();

}

void drawTrack(int w, int h, int x, int wx) {
    //Hitam
    glColor3f(0.0, 0.0, 0.0);

    for(int i = 1; i <= x; i++) {
        if(i % 2 == 0) {
            glBegin(GL_POLYGON);
                // Border Kanan Kiri
                glVertex2f(w, i * wx);
                glVertex2f(wx, i * wx);
                glVertex2f(wx, i * wx - 4);
                glVertex2f(w, i * wx - 4);
            glEnd();
        } else {
            glBegin(GL_POLYGON);
                // Border Kiri Kanan
                glVertex2f(0, i * wx);
                glVertex2f(w - wx, i * wx);
                glVertex2f(w - wx, i * wx - 4);
                glVertex2f(0, i * wx - 4);
            glEnd();
        }
    }
}

void pionTile() {

}

void display(){
	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(4);

    int x = 7;
    int y = 12;
    int ny = 7;
    int w = 600;
    int h = 350;
    int wx = 350 / x;
    int hy = 600 / y;

    //drawBorderTile(w, h);
    drawTile(x, y, ny, wx, hy);
    drawPatternNumber(x, y, ny, wx, hy);
    glColor3f(0.0, 1.0, 0.0);
    drawBorderTile(w, h);
    drawTrack(w, h, x, wx);

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
	glutCreateWindow("Ular Tangga");
	glutDisplayFunc(display);
	myinit();
	glutMainLoop();
	return 0;
}
