#include<iostream>
#include<conio.h>
#include<windows.h>
#include<time.h>

using namespace std;


#define SCREEN_WIDTH 90
#define SCREEN_HEIGHT 26
#define WIN_WIDTH 70

#define CAR_WIDTH 4
#define CAR_HEIGHT 4

#define ENEMY_WIDTH 4
#define ENEMY_HEIGHT 4

#define MAX_ENEMY 2
#define ROAD_LEFT 18
#define ROAD_RIGHT 50

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;


int enemyX[MAX_ENEMY];
int enemyY[MAX_ENEMY];
bool enemyActive[MAX_ENEMY];
bool isPaused = false;
bool restartGame = false;


char car[4][4] = {
    ' ','�','�',' ',
    '�','�','�','�',
    ' ','�','�',' ',
    '�','�','�','�'
};

int carPos;
int score;


void gotoxy(int x, int y){
    CursorPosition.X = x;
    CursorPosition.Y = y;
    SetConsoleCursorPosition(console, CursorPosition);
}

void setcursor(bool visible, DWORD size){
    CONSOLE_CURSOR_INFO lpCursor;
    lpCursor.bVisible = visible;
    lpCursor.dwSize = size;
    SetConsoleCursorInfo(console,&lpCursor);
}

void drawBorder(){
    for(int i=0;i<SCREEN_HEIGHT;i++){
        for(int j=0;j<17;j++){
            gotoxy(j,i); cout<<"�";
            gotoxy(WIN_WIDTH-j,i); cout<<"�";
        }
    }
}

void genEnemy(int i){
    enemyX[i] = ROAD_LEFT + rand() % (ROAD_RIGHT - ROAD_LEFT);
}

void drawEnemy(int i){
    if(enemyActive[i]){
        for(int h=0;h<ENEMY_HEIGHT;h++){
            gotoxy(enemyX[i], enemyY[i]+h);
            cout<<"****";
        }
    }
}

void eraseEnemy(int i){
    if(enemyActive[i]){
        for(int h=0;h<ENEMY_HEIGHT;h++){
            gotoxy(enemyX[i], enemyY[i]+h);
            cout<<"    ";
        }
    }
}

void resetEnemy(int i){
    eraseEnemy(i);
    enemyY[i] = 1;
    genEnemy(i);
}

void drawCar(){
    for(int i=0;i<CAR_HEIGHT;i++){
        for(int j=0;j<CAR_WIDTH;j++){
            gotoxy(carPos+j,22+i);
            cout<<car[i][j];
        }
    }
}

void eraseCar(){
    for(int i=0;i<CAR_HEIGHT;i++){
        for(int j=0;j<CAR_WIDTH;j++){
            gotoxy(carPos+j,22+i);
            cout<<" ";
        }
    }
}

/* ----------- IMPROVED COLLISION ----------- */
bool collision(){
    for(int i=0;i<MAX_ENEMY;i++){
        if(enemyActive[i]){
            if(enemyY[i]+ENEMY_HEIGHT >= 22){
                if(enemyX[i] < carPos+CAR_WIDTH &&
                   enemyX[i]+ENEMY_WIDTH > carPos){
                    return true;
                }
            }
        }
    }
    return false;
}

void updateScore(){
    gotoxy(WIN_WIDTH + 7, 5);
    cout<<"Score: "<<score<<"   ";
}


void gameover(){
    system("cls");
    cout<<endl;
    cout<<"\t\t--------------------------"<<endl;
    cout<<"\t\t-------- Game Over -------"<<endl;
    cout<<"\t\t-------- Score: "<<score<<"  -------"<<endl;
    cout<<"\t\t--------------------------"<<endl<<endl;

    cout<<"\t\tPress any key to go back to menu.";
    getch();
}
void pauseScreen(){
    int x = WIN_WIDTH/2 - 6;
    int y = SCREEN_HEIGHT/2 - 2;

    gotoxy(x, y);
    cout<<"== PAUSED ==";

    gotoxy(x - 6, y + 2);
    cout<<"P   - Resume";

    gotoxy(x - 6, y + 3);
    cout<<"R   - Restart";

    gotoxy(x - 6, y + 4);
    cout<<"ESC - Menu";
}
void clearPauseScreen(){
    int x = WIN_WIDTH/2 - 6;
    int y = SCREEN_HEIGHT/2 - 2;
    for(int i=0; i<5; i++){ // clear 5 lines used by pause menu
        gotoxy(x-6, y+i);
        cout<<"                              ";
    }
}

void clearStartText(){
    gotoxy(WIN_WIDTH/2 - 12, 5);
    cout<<"                          ";
}

void play(){
    while(true){ // outer loop handles restart
        // Initialize game
        carPos = WIN_WIDTH/2;
        score = 0;

        for(int i=0;i<MAX_ENEMY;i++){
            enemyActive[i] = (i==0); // only first enemy active initially
            enemyY[i] = 1;
            genEnemy(i);
        }

        system("cls");
        drawBorder();

        // -------- CENTER TITLE --------
        gotoxy(WIN_WIDTH/2 - 4, 1); cout<<"Car Game";
        gotoxy(WIN_WIDTH/2 - 5, 2); cout<<"--------";

        // -------- PRESS START --------
        gotoxy(WIN_WIDTH/2 - 12, 5); cout<<"Press any key to start";

        // -------- SCORE PANEL --------
        gotoxy(WIN_WIDTH + 7, 5); cout<<"Score: 0";

        // -------- CONTROL PANEL --------
        gotoxy(WIN_WIDTH + 7, 8);  cout<<"Control";
        gotoxy(WIN_WIDTH + 6, 9);  cout<<"--------";
        gotoxy(WIN_WIDTH + 4, 11); cout<<"A Key - Left";
        gotoxy(WIN_WIDTH + 4, 12); cout<<"D Key - Right";
        gotoxy(WIN_WIDTH + 4, 13); cout<<"P Key - Pause";
        gotoxy(WIN_WIDTH + 4, 14); cout<<"R Key - Restart";

        getch(); // wait for key press
        clearStartText();

        isPaused = false;
        restartGame = false;

        // -------- GAME LOOP --------
        while(true){
            // Handle input
            if(kbhit()){
                char ch = getch();

                if(ch=='p' || ch=='P'){
                    isPaused = !isPaused;
                    if(isPaused) pauseScreen();
                    else clearPauseScreen();
                }

                if(ch=='r' || ch=='R'){
                    restartGame = true;
                    break; // exit inner loop to restart
                }

                if(ch==27) return; // ESC to menu

                if(!isPaused){
                    if((ch=='a'||ch=='A') && carPos>ROAD_LEFT) carPos -= 4;
                    if((ch=='d'||ch=='D') && carPos<ROAD_RIGHT) carPos += 4;
                }
            }

            if(isPaused){
                Sleep(100);
                continue;
            }

            // Draw car and enemies
            drawCar();
            for(int i=0;i<MAX_ENEMY;i++) drawEnemy(i);

            // Check collision
            if(collision()){
                gameover();
                break; // exit game loop on collision
            }

            Sleep(50); // control game speed

            // Erase previous positions
            eraseCar();
            for(int i=0;i<MAX_ENEMY;i++) eraseEnemy(i);

            // Activate second enemy after first moves down a bit
            if(enemyY[0]==10) enemyActive[1]=true;

            // Move enemies
            for(int i=0;i<MAX_ENEMY;i++){
                if(enemyActive[i]) enemyY[i]++;
                if(enemyY[i]>SCREEN_HEIGHT-ENEMY_HEIGHT){
                    resetEnemy(i);
                    score++;
                    updateScore();
                }
            }
        }

        if(!restartGame) break; // exit outer loop if not restarting
    }
}



void instructions(){
    system("cls");

    int midX = SCREEN_WIDTH / 2 - 15;
    int midY = SCREEN_HEIGHT / 2 - 5;

    gotoxy(midX, midY);     cout<<"Instructions";
    gotoxy(midX, midY+1);   cout<<"----------------";

    gotoxy(midX, midY+3);   cout<<"Avoid cars by moving left or right.";
    gotoxy(midX, midY+5);   cout<<"A key  - Move Left";
    gotoxy(midX, midY+6);   cout<<"D key  - Move Right";
    gotoxy(midX, midY+7);   cout<<"P key  - Pause";
    gotoxy(midX, midY+8);   cout<<"R key  - Restart";
    gotoxy(midX, midY+9);   cout<<"ESC    - Exit Game";

    gotoxy(midX, midY+11);   cout<<"Press any key to go back...";
    getch();
}


int main(){
    setcursor(false, 0);
    srand(time(0));

    while(true){
        system("cls");

        int midX = SCREEN_WIDTH / 2 - 15;
        int midY = SCREEN_HEIGHT / 2 - 5;

        gotoxy(midX, midY);     cout<<"--------------------------";
        gotoxy(midX, midY+1);   cout<<"        |  Car Game |";
        gotoxy(midX, midY+2);   cout<<"--------------------------";

        gotoxy(midX, midY+4);   cout<<"1. Start Game";
        gotoxy(midX, midY+5);   cout<<"2. Instructions";
        gotoxy(midX, midY+6);   cout<<"3. Quit";

        gotoxy(midX, midY+8);   cout<<"Select option: ";
        char op = getch();

        if(op=='1') play();
        else if(op=='2') instructions();
        else if(op=='3') exit(0);
    }
}
