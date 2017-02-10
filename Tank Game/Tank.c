    #include "tankwar.h"
    
//////////// Draw TANK
    void drawtank(int num)
    {
        int x = tanks[num].x;
        int y = tanks[num].y;
        int dir = tanks[num].dir;
        rectfill(screen, x-11, y-11, x+11, y+11, tanks[num].color);
        rectfill(screen, x-6, y-6, x+6, y+6, 7);
        
        if(dir == 0 || dir == 2)
        {
            rectfill(screen, x-16, y-16, x-11, y+16, 8);
            rectfill(screen, x+11, y-16, x+16, y+16, 8);
        }
        else
        if(dir == 1 || dir == 3)
        {
            rectfill(screen, x-16, y-16, x+16, y-11, 8);
            rectfill(screen, x-16, y+16, x+16, y+11, 8);
        }
        
        switch(dir)
        {
            case 0:
                rectfill(screen, x-1, y, x+1, y-16, 8);
                break;
            case 1:
                rectfill(screen, x, y-1, x+16, y+1, 8);
                break;
            case 2:
                rectfill(screen, x-1, y, x+1, y+16, 8);
                break;
            case 3:
                rectfill(screen, x, y-1, x-16, y+1, 8);
                break;
        }
    }

//////////// Erase TANK
    void erasetank(int num)
    {
        int left = tanks[num].x - 17;
        int top = tanks[num].y - 17;
        int right = tanks[num].x + 17;
        int bottom = tanks[num].y + 17;
        
        rectfill(screen, left, top, right, bottom, 0);
    }

//////////// Move TANK
    void movetank(int num)
    {
        int dir = tanks[num].dir;
        int speed = tanks[num].speed;
        
        switch(dir)
        {
            case 0:
                tanks[num].y -= speed;
                break;
            case 1:
                tanks[num].x += speed;
                break;
            case 2:
                tanks[num].y += speed;
                break;
            case 3:
                tanks[num].x -= speed;
                break;
        }
        
        if(tanks[num].x > SCREEN_W-22)
        {
            tanks[num].x = SCREEN_W-22;
            tanks[num].speed = 0;
        }
        if(tanks[num].x < 22)
        {
            tanks[num].x = 22;
            tanks[num].speed = 0;
        }
        if(tanks[num].y > SCREEN_H-22)
        {
            tanks[num].y = SCREEN_H-22;
            tanks[num].speed = 0;
        }
        if(tanks[num].y < 22)
        {
            tanks[num].y = 22;
            tanks[num].speed = 0;
        }
    }

//////////// EXPLODE
    void explode(int num, int x, int y)
    {
        int n;
        
        int tx = tanks[!num].x;
        int ty = tanks[!num].y;
        
        if(x > tx - 16 && x < tx + 16 && y > ty -16 && y < ty+16)
            score(num);
        
        for(n = 0; n < 10; n++)
        {
            rectfill(screen, x -16, y-16, x+16, y+16, rand() % 16);
            rest(1);
        }
        
        rectfill(screen, x-16, y-16, x+16, y+16, 0);
    }

//////////// UpdateBULLET
    void updatebullet(int num)
    {
        int x = bullets[num].x;
        int y = bullets[num].y;
        
        if(bullets[num].alive)
        {
            rect(screen, x-1, y-1, x+1, y+1, 0);
            
            bullets[num].x += bullets[num].xspd;
            bullets[num].y += bullets[num].yspd;
            x = bullets[num].x;
            y = bullets[num].y;
            
            if(x < 5 || x > SCREEN_W-5 || y < 20 || y > SCREEN_H-5)
            {
                bullets[num].alive = 0;
                return;
            }
            
            x = bullets[num].x;
            y = bullets[num].y;
            rect(screen, x-1, y-1, x+1, y+1, 14);
            
            if(getpixel(screen, bullets[num].x, bullets[num].y))
            {
                bullets[num].alive = 0;
                explode(num, x, y);
            }
            
            textprintf_ex(screen, font, SCREEN_W/2-50, 1, 2, 0,
                         "B1 %-3dx%-3d B2 %-3dx%-3d",
                         bullets[0].x, bullets[0].y,
                         bullets[1].x, bullets[1].y);
        }
    }

//////////// Check PATH
    int checkpath(int x1, int y1, int x2, int y2, int x3, int y3)
    {
        if(getpixel(screen, x1, y1) ||
           getpixel(screen, x2, y2) ||
           getpixel(screen, x3, y3))
           return 1;
        else
            return 0;
    }

//////////// Clear PATH
    void clearpath(int num)
    {
        int dir = tanks[num].dir;
        int speed = tanks[num].speed;
        int x = tanks[num].x;
        int y = tanks[num].y;
        
        switch(dir)
        {
            case 0:
                if(speed > 0)
                {
                    if(checkpath(x-16, y-20, x, y-20, x+16, y-20))
                        tanks[num].speed = 0;
                }
                else
                    if(checkpath(x-16, y+20, x, y+20, x+16, y+20))
                        tanks[num].speed = 0;
                break;
                
            case 1:
                if(speed > 0)
                {
                    if(checkpath(x+20, y-16, x+20, y, x+20, y+16))
                        tanks[num].speed = 0;
                }
                else
                    if(checkpath(x-20, y-16, x-20, y, x-20, y+16))
                        tanks[num].speed = 0;
                break;
                
            case 2:
                if(speed > 0)
                {
                    if(checkpath(x-16, y+20, x, y+20, x+16, y+20))
                        tanks[num].speed = 0;
                }
                else
                    if(checkpath(x-16, y-20, x, y-20, x+16, y-20))
                        tanks[num].speed = 0;
                break;
                
            case 3:
                if(speed > 0)
                {
                    if(checkpath(x-20, y-16, x-20, y, x-20, y+16))
                        tanks[num].speed = 0;
                }
                else
                    if(checkpath(x+20, y-16, x+20, y, x+20, y+16))
                        tanks[num].speed = 0;
                break;
        }
    }

//////////// Fire WEAPON
void fireweapon(int num)
{
    int x = tanks[num].x;
    int y = tanks[num].y;
    
    if(!bullets[num].alive)
    {
        bullets[num].alive = 1;
        
        switch(tanks[num].dir)
        {
            case 0:
                bullets[num].x = x;
                bullets[num].y = y-22;
                bullets[num].xspd = 0;
                bullets[num].yspd = -BULLETSPEED;
                break;
                
            case 1:
                bullets[num].x = x+22;
                bullets[num].y = y;
                bullets[num].xspd = BULLETSPEED;
                bullets[num].yspd = 0;
                break;
                
            case 2:
                bullets[num].x = x;
                bullets[num].y = y+22;
                bullets[num].xspd = 0;
                bullets[num].yspd = BULLETSPEED;
                break;
                
            case 3:
                bullets[num].x = x-22;
                bullets[num].y = y;
                bullets[num].xspd = -BULLETSPEED;
                bullets[num].yspd = 0;
            }
        }
    }

//////////// forward FUNCTION
    void forward(int num)
    {
        tanks[num].speed++;
        if(tanks[num].speed > MAXSPEED)
           tanks[num].speed = MAXSPEED;
    }

//////////// backward FUNCTION
    void backward(int num)
    {
        tanks[num].speed--;
        if(tanks[num].speed < -MAXSPEED)
           tanks[num].speed = -MAXSPEED;
    }

//////////// turnleft FUNCTION
    void turnleft(int num)
    {
        tanks[num].dir--;
        if(tanks[num].dir < 0)
           tanks[num].dir = 3;
    }

//////////// turnright FUNCTION
    void turnright(int num)
    {
        tanks[num].dir++;
        if(tanks[num].dir > 3)
           tanks[num].dir = 0;
    }

//////////// input FUNCTION
    void getinput()
    {
        if(key[KEY_ESC])
            gameover = 1;
        
        if(key[KEY_W])
            forward(0);
        if(key[KEY_D])
            turnright(0);
        if(key[KEY_A])
            turnleft(0);
        if(key[KEY_S])
            backward(0);
        if(key[KEY_SPACE])
            fireweapon(0);
        
        if(key[KEY_UP])
            forward(1);
        if(key[KEY_RIGHT])
            turnright(1);
        if(key[KEY_DOWN])
            backward(1);
        if(key[KEY_LEFT])
            turnleft(1);
        if(key[KEY_ENTER])
            fireweapon(1);
        
        rest(10);
    }

//////////// score FUNCTION
    void score(int player)
    {
        int points = ++tanks[player].score;
        
        textprintf_ex(screen, font, SCREEN_W-70*(player+1), 1, BURST, 0,
                     "P%d: %d", player+1, points);
    }

//////////// setup tanks FUNCTION
    void setuptanks()
    {
        // player 1
        tanks[0].x = 30;
        tanks[0].y = 40;
        tanks[0].dir = 1;
        tanks[0].speed = 0;
        tanks[0].color = 0;
        tanks[0].score = 0;
        
        // player 2
        tanks[1].x = SCREEN_W - 30;
        tanks[1].y = SCREEN_H - 30;
        tanks[1].dir = 3;
        tanks[1].speed = 0;
        tanks[1].color = 12;
        tanks[1].score = 0;
    }

//////////// setup debris FUNCTION
    void setupdebris()
    {
        int n,x,y,size,color;
        
        for(n = 0; n < BLOCKS; n++)
        {
            x = BLOCKSIZE + rand() % (SCREEN_W-BLOCKSIZE*2);
            y = BLOCKSIZE + rand() % (SCREEN_H-BLOCKSIZE*2);
            size = (10 + rand() % BLOCKSIZE)/2;
            color = makecol(rand()%255, rand()%255, rand()%255);
            rectfill(screen, x-size, y-size, x+size, y+size, color);
        }
    }

//////////// setup screen FUNCTION
    void setupscreen()
    {
        int ret = set_gfx_mode(MODE, WIDTH, HEIGHT, 0, 0);
        if(ret != 0) {
            allegro_message(allegro_error);
            return;
        }
        
        textprintf_ex(screen, font, 1, 1, BURST, 0,
                     "Tank War - %dx%d", SCREEN_W, SCREEN_H);
        
        rect(screen, 0, 12, SCREEN_W-1, SCREEN_H-1, TAN);
        rect(screen, 1, 13, SCREEN_W-2, SCREEN_H-2, TAN);
    }

//////////// main FUNCTION
    int main(void)
    {
        allegro_init();
        
        install_keyboard();
        install_timer();
        srand(time(NULL));
        setupscreen();
        setupdebris();
        setuptanks();
        
        while(!gameover)
        {
            erasetank(0);
            erasetank(1);
            
            clearpath(0);
            clearpath(1);
            
            movetank(0);
            movetank(1);
            
            drawtank(0);
            drawtank(1);
            
            updatebullet(0);
            updatebullet(1);
            
            if(keypressed())
                getinput();
            
            rest(30);
        }
        
        allegro_exit();
        return 0;
    }
    END_OF_MAIN()
