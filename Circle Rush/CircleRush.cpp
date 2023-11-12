#include<iostream>
#include<graphics.h>
#include<conio.h>
#include<dos.h>
#include<time.h>
#include<stdio.h>

#define ScreenWidth 1000
#define ScreenHeight 700

using namespace std;
 
int main(){
    // for unique random number generation
    srand((unsigned) time(0));
    
    int graphicDriver = DETECT, graphicMode, error, temp;
    initgraph( & graphicDriver, & graphicMode, "C:\\tc\\bgi");
  
    // playerX-Player X, playerY-Player Y, playerRadius-Player Radius, playerStep-Player Step
    int playerX=350, playerY=515, playerRadius=12, playerStep=6;
    
    // barX-Bar X, barY-Bar Y, barWidth-Bar Width, barHeight-Bar Height
    int barX=200, barY=500, barWidth=300, barHeight=30;
    
    //enemy (x,y,type[enemy,fruit])
    int enemies[5][3]= { {ScreenWidth/2, 0, 0} };
    // enemyIndex-enemy index, enemyStep- enemy Step, enemyGap-enemy Gap, enemyRadius-enemy radius
    int enemyIndex=1, enemyStep=4, enemyGap=0, enemyRadius=12;
    
    char choice, textChances[5], textScore[5];
    int chances = 0, score = 0;    
    
    while(1){
        setcolor(WHITE);
        
        //Draw Board
        rectangle(0,0,ScreenWidth-300,ScreenHeight);
        rectangle(ScreenWidth-300,0,ScreenWidth,ScreenHeight);
        
        // printing chances
        settextstyle(4,0,3);
        outtextxy(ScreenWidth-220, 100, "Chances");
        settextstyle(4,0,7);
        outtextxy(ScreenWidth-180, 150, itoa(chances,textChances,10)); 
        
        // printing score
        settextstyle(4,0,4);
        outtextxy(ScreenWidth-220, 300, "Score");
        settextstyle(4,0,7);
        
        // itoa function converts number to character array
        if( score<10 ) // if score is one digit 
            outtextxy(ScreenWidth-180, 370, itoa(score,textScore,10));
        else if( score>=10 )// if score is more than one digit
            outtextxy(ScreenWidth-220, 370, itoa(score,textScore,10));
         
        //draw bar
        rectangle(barX,barY,barX+barWidth,barY+barHeight);
        
        if(kbhit()){ // if any key is pressed while playing
            choice = getch(); // catch that character in options variable
            if(choice == 32){ // if spacebar (code: 32) is pressed
                playerStep = -playerStep; // reverse ball direction
            }
        }
        
        // Draw Enemies
        for(int i=0; i<enemyIndex; i++){
            if( enemies[i][2] == 0 ){ // if type is enemy (code: 0) 
                setcolor(WHITE);
                setfillstyle(3,WHITE);
            }else if( enemies[i][2] == 1 ){  // if type is fruit (code: 1)
                setcolor(GREEN);
                setfillstyle(3,GREEN);
            }
            fillellipse(enemies[i][0], enemies[i][1], enemyRadius, enemyRadius);
            enemies[i][1] += enemyStep; // update enemy y position for enemy movement
            if(enemies[i][1]-enemyRadius > barY+barHeight){ // if enemy goes below bar
                enemies[i][0]=barX+rand()%barWidth; // generate enemy at random pos on x axis
                enemies[i][1]=0; // set inital enemy y pos to 0
                if(i==0)
                    enemies[i][2]=1; // make every first enemy a fruit
            }
        }
        
        // Generate Enemies
        if( enemyIndex < 5 ){ // generate enemy only if they are less than 5
            enemies[enemyIndex][0] = barX+rand()%barWidth; // random enemy position at x axis
            enemies[enemyIndex][1] = 0; // 0 at y axis 
            enemies[enemyIndex][2] = 0; // type = enemy
            
            enemyGap = 100+rand()%200; // for random vertical gap between enemies
            if( enemies[enemyIndex-1][1] >= enemyGap )
                enemyIndex++; // create new enemy if last enemy moves to specific gap position
        }
        
        //Player Hit
        for(int i=0; i<enemyIndex; i++){
            if( enemies[i][1]+enemyRadius >= playerY-playerRadius ){ 
                if( playerX >= enemies[i][0]-enemyRadius && playerX <= enemies[i][0]+enemyRadius ){
                    if( enemies[i][2] == 0 ){ // if type = enemy
                        chances--; // decrease chances
                        enemies[i][1] = 0; // reset enemy position
                        if(chances <= 0){ // if chances are 0 or less
                            cleardevice(); 
                            
                            settextstyle(4,0,4);
                            outtextxy(300,200, "Game Over"); 
                            
                            //On Game over reset chances, score and Enemey Index
                            chances = 3;
                            score = 0;
                            enemyIndex = 1;
                            
                            getch();
                            break;
                        }
                    }
                    else{ // If player hit fruit 
                        score += 5; // update score
                        enemies[i][1] = 0; // reset enemey y position to 0
                    }
                }
            }
        }
        
        // Draw Player 
        setcolor(YELLOW); // for border color
        setfillstyle(1,YELLOW); // for fill color and other styles
        fillellipse(playerX, playerY, playerRadius, playerRadius);
        playerX += playerStep; // increment playerX for ball movement
        
        // restrict ball to move inside bar
        if( playerX-playerRadius<=barX || playerX+playerRadius>=barX+barWidth ){
            playerStep = -playerStep;
        }
        
        delay(30);
        cleardevice();
    }
    
    getch();
    closegraph();
}
