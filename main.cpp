#include <windows.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include<iostream>
#include <cmath>
#endif

using namespace std;

// Global Variabel
int * snakes;
int * ladders;

int scoreP1 = 1;
int scoreP2 = 1;
int turn = 1;
bool gameOver = false;

void drawNumber(int number, int x, int y) {
    // Change number to string
    char str[20];
    snprintf(str, sizeof(str), "%d", number);

    // Display number
    glRasterPos2i(x, y);
    for(int i = 0; i < strlen(str); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, str[i]);
    }
}

// Pattern tile
void drawTile(int x, int y, int ny, int wx, int hy) {
    for(int i = 0; i < x; i++) {
        for(int j = 0; j < y; j++) {
            if(i % 2 == 0) {
                if(j % 2 == 0) {
                    // Hijau
                    glColor3f(0.0, 0.7, 0.4);
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
                    // Hijau
                    glColor3f(0.0, 0.7, 0.4);
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

    /**

        Pattern yang lama jangan dihapus takutnya masih digunakan kembali

    **/

    /**for(int i = 0; i < x; i++) {
        for(int j = 0; j < y; j++) {
            if(i % 2 == 0) {
                int currentNumber = (i * y + j + 1);
                if(currentNumber % 10 == wahyudi || currentNumber % 10 == dani || currentNumber % 10 == evi || currentNumber % 10 == ilham) {
                    drawNumber((i * y + j + 1) % 10, j * wx + 10, i * hy + 10);
                }
            } else {
                int currentNumber = (i * y + (y - j));
                if(currentNumber % 10 == wahyudi || currentNumber % 10 == dani || currentNumber % 10 == evi || currentNumber % 10 == ilham) {
                    drawNumber((i * y + (y - j)) % 10, j * wx + 10, i * hy + 10);
                }
            }
        }
    }**/

    /**

        Jangan diubah-ubah kode yang ini

    **/

    for(int i = 0; i < x; i++) {
        for(int j = 0; j < y; j++) {
            int currentNumber;
            if(i % 2 == 0) {
                currentNumber = (i * y + j + 1);
            } else {
                currentNumber = (i * y + (y - j));
            }

            int firstDigit = floor(currentNumber / 10);
            int secondDigit = currentNumber % 10;

            // Pengecekan apakah digit pertama atau kedua mengandung angka yang ada pada nama
            if((firstDigit == wahyudi || firstDigit == dani || firstDigit == evi || firstDigit == ilham) &&
               (secondDigit == wahyudi || secondDigit == dani || secondDigit == evi || secondDigit == ilham)) {
                drawNumber(currentNumber, j * wx + 10, i * hy + 10);
                // Jika keduanya cocok, tampilkan kedua digit
            } else if (firstDigit == wahyudi || firstDigit == dani || firstDigit == evi || firstDigit == ilham) {
                drawNumber(firstDigit, j * wx + 10, i * hy + 10);
                // Jika hanya digit pertama cocok, tampilkan digit pertama saja
            } else if (secondDigit == wahyudi || secondDigit == dani || secondDigit == evi || secondDigit == ilham) {
                drawNumber(secondDigit, j * wx + 10, i * hy + 10);
                // Jika hanya digit kedua cocok, tampilkan digit kedua saja
            }
        }
    }
}

void drawBorderTile(int w, int h) {
    glColor3f(0.0, 0.0, 0.0);

    glBegin(GL_POLYGON);
        //Border Left
        glVertex2f(0, h);
        glVertex2f(4, h);
        glVertex2f(4, 0);
        glVertex2f(0, 0);
    glEnd();

    glBegin(GL_POLYGON);
    // Border Top
        glVertex2f(0, h);
        glVertex2f(w, h);
        glVertex2f(w, h - 4);
        glVertex2f(0, h - 4);
    glEnd();

    glBegin(GL_POLYGON);
        // Border Right
        glVertex2f(w, 0);
        glVertex2f(w - 4, 0);
        glVertex2f(w - 4, h);
        glVertex2f(w, h);
    glEnd();

    glBegin(GL_POLYGON);
        // Border Bottom
        glVertex2f(0, 0);
        glVertex2f(w, 0);
        glVertex2f(w, 4);
        glVertex2f(0, 4);
    glEnd();

}

// Border of track
void drawTrack(int w, int h, int x, int wx) {
    //Hitam
    glColor3f(0.0, 0.0, 0.0);

    for(int i = 1; i <= x; i++) {
        if(i % 2 == 0) {
            glBegin(GL_POLYGON);
                // Border Right - Left
                glVertex2f(w, i * wx);
                glVertex2f(wx, i * wx);
                glVertex2f(wx, i * wx - 4);
                glVertex2f(w, i * wx - 4);
            glEnd();
        } else {
            glBegin(GL_POLYGON);
                // Border Left Right
                glVertex2f(0, i * wx);
                glVertex2f(w - wx, i * wx);
                glVertex2f(w - wx, i * wx - 4);
                glVertex2f(0, i * wx - 4);
            glEnd();
        }
    }
}

void drawLadder(int startX, int startY, int step, int stepHeight, int stepWidth, int deg) {
    glColor3f(1.0, 0.7, 0.0);
    glPushMatrix();
    glRotatef(deg, 0.0, 0.0, 1.0);
    glBegin(GL_POLYGON);
        glVertex2f(startX, startY + step * stepHeight);
        glVertex2f(startX - 5, startY + step * stepHeight);
        glVertex2f(startX - 5, startY);
        glVertex2f(startX, startY);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex2f(startX + stepWidth, startY + step * stepHeight);
        glVertex2f(startX + stepWidth + 5, startY + step * stepHeight);
        glVertex2f(startX + stepWidth + 5, startY);
        glVertex2f(startX + stepWidth, startY);
    glEnd();

    // Childs of Ladder

    for(int i = 1; i <= step - 1; i++) {
        glBegin(GL_POLYGON);
            glVertex2f(startX, startY + stepHeight * i);
            glVertex2f(startX + stepWidth, startY + stepHeight * i);
            glVertex2f(startX + stepWidth, startY + stepHeight * i+ 5);
            glVertex2f(startX, startY + stepHeight * i + 5);
        glEnd();
    }

    glPopMatrix();

}

void drawSnake() {
    glColor3f(1.0, 0.0, 0.0);
    // Snake1
    glBegin(GL_POLYGON);
        glVertex2f(80,10);
		glVertex2f(150,100);
		glVertex2f(160,100);
		glVertex2f(80,15);
    glEnd();
    glBegin(GL_POLYGON);
		glVertex2f(150,100);
		glVertex2f(100,150);
		glVertex2f(160,100);
		glVertex2f(150,100);
    glEnd();
    glBegin(GL_POLYGON);
		glVertex2f(100,150);
		glVertex2f(180,180);
		glVertex2f(160,180);
		glVertex2f(100,150);
    glEnd();

    // Snake2
    glBegin(GL_POLYGON);
        glVertex2f(420, 110);
        glVertex2f(350, 150);
        glVertex2f(350, 150);
        glVertex2f(410, 110);
    glEnd();
    glBegin(GL_POLYGON);
        glVertex2f(350, 150);
        glVertex2f(400, 250);
        glVertex2f(400, 250);
        glVertex2f(360, 150);
    glEnd();
    glBegin(GL_POLYGON);
        glVertex2f(400, 250);
        glVertex2f(320, 320);
        glVertex2f(320, 320);
        glVertex2f(390, 250);
    glEnd();

    // Snake3
    glBegin(GL_POLYGON);
        glVertex2f(450, 10);
        glVertex2f(580, 80);
        glVertex2f(580, 70);
        glVertex2f(450, 10);
    glEnd();
    glBegin(GL_POLYGON);
        glVertex2f(580, 80);
        glVertex2f(520, 120);
        glVertex2f(520, 110);
        glVertex2f(580, 80);
    glEnd();
    glBegin(GL_POLYGON);
        glVertex2f(520, 110);
        glVertex2f(590, 170);
        glVertex2f(590, 160);
        glVertex2f(520, 110);
    glEnd();

}

// Function to move the pion
void move(int score, int w, int h, int wx, int hy, int& x, int& y) {
    // Y axis
    y = (floor((score - 1) / 12 + 1) * hy - 20);

    // X axis
    if(score <= 12) {
        x = floor(score * wx - 20);
    } else {
        if(floor((score / 12) % 2 != 0)) {;
            if(score % 12 != 0) {
                x = floor(w - ((score - 1) % 12) * wx - 20);
            } else {
                x = floor(((score - 1) % 12) * wx + 20);
            }
        } else {
            if(score % 12 != 0) {
                x = floor(((score - 1) % 12) * wx + 30);
            } else {
                x = floor(w - ((score - 1) % 12) * wx - 20);
            }

        }
    }
}
//Pion triangle
void pionTriangle(int score, int w, int h, int wx, int hy) {
    int x = 0;
    int y = 0;

    move(score, w, h, wx, hy, x, y);

    // Biru
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
        glVertex2f(x, y + 15);
        glVertex2f(x + 15, y);
        glVertex2f(x, y);
    glEnd();
}

// Pion square
void pionTile(int score, int w, int h, int wx, int hy) {
    int x = 0;
    int y = 0;

    move(score, w, h, wx, hy, x, y);

    // Biru
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_POLYGON);
        glVertex2f(x, y - 10);
        glVertex2f(x - 10, y - 10);
        glVertex2f(x - 10, y);
        glVertex2f(x, y);
    glEnd();
}

// function to generate random number range 1-6
int randomNumber() {
    srand (time(NULL));
    int randAngka = rand() % 6 + 1;
    return randAngka;
}

// Event Handler
void onPressSpace(unsigned char key, int x, int y) {
    if(!gameOver) {
        // state player 1
        if(turn == 1) {
            if (scoreP1 >= 84) {
                scoreP1 = 84;
                glutPostRedisplay();
                cout << "Player 1 Win!!!" << endl;
                gameOver = true;
            } else {
                if (key == ' ') {
                    scoreP1 += randomNumber();
                    turn = 2;
                    cout << "Player 1: " << randomNumber() << endl;
                    glutPostRedisplay();

                    // Ladder Checking
                    if(scoreP1 != 1 && ladders[scoreP1]) {
                        scoreP1 = ladders[scoreP1];
                        glutPostRedisplay();
                    }

                    // Snake Checking
                    if(scoreP1 != 1 && snakes[scoreP1]) {
                        scoreP1 = snakes[scoreP1];
                        glutPostRedisplay();
                    }

                    if(scoreP1 >= 84) {
                        cout << "Player 1 Win!!!" << endl;
                        scoreP1 = 84;
                        gameOver = true;
                    }
                }
            }
        } else {
            // state player 2
            if (scoreP2 >= 84) {
                scoreP2 = 84;
                glutPostRedisplay();
                cout << "Player 2 Win!!!" << endl;
                gameOver = true;
            } else {
                if (key == ' ') {
                    scoreP2 += randomNumber();
                    turn = 1;
                    cout << "Player 2: " << randomNumber() << endl;
                    glutPostRedisplay();

                    // Ladder Checking
                    if(scoreP2 != 1 && ladders[scoreP2]) {
                        scoreP2 = ladders[scoreP2];
                        glutPostRedisplay();
                    }

                    // Snake Checking
                    if(scoreP2 != 1 && snakes[scoreP2]) {
                        scoreP2 = snakes[scoreP2];
                        glutPostRedisplay();
                    }

                    if(scoreP2 >= 84) {
                        cout << "Player 2 Win!!!" << endl;
                        scoreP2 = 84;
                        gameOver = true;
                    }
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
    int w = 600;
    int h = 350;
    int wx = 350 / x;
    int hy = 600 / y;

    drawTile(x, y, ny, wx, hy);
    drawPatternNumber(x, y, ny, wx, hy);
    glColor3f(0.0, 1.0, 0.0);
    drawBorderTile(w, h);
    drawTrack(w, h, x, wx);

    drawLadder(210, 5, 8, 30, 30, 0);
    drawLadder(530, -120, 6, 30, 30, 30);
    drawLadder(-50, 120, 6, 30, 30, -30);
    drawLadder(-88, 320, 6, 30, 30, -90);

    drawSnake();

    pionTile(scoreP1, w, h, wx, hy);
    pionTriangle(scoreP2, w, h, wx, hy);

    glutKeyboardFunc(onPressSpace);

	glFlush();
}

void myinit(){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 600.0, 0.0, 350.0);
	glMatrixMode(GL_MODELVIEW);
	glClearColor(1.0,1.0,1.0,1.0);
}

void init_snakes_ladders()
{
	snakes = new int[100];
	ladders = new int[100];

    // Ladder Init
	ladders[1] = 1;
	ladders[5] = 53;
	ladders[15] = 18;
	ladders[25] = 70;
	ladders[38] = 81;

	// Snake Init
	snakes[45] = 2;
	snakes[79] = 33;
	snakes[37] = 10;
}

int main(int argc, char* argv[]){
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(600,350);
	glutInitWindowPosition(300,200);
	glutCreateWindow("Ular Tangga");
	cout << "Tekan Spasi Untuk Memulai Permainan" << endl;
	glutDisplayFunc(display);
	myinit();
	init_snakes_ladders();
	glutMainLoop();
	return 0;
}
