//HEADERS
#include "bigbadwolf.h"
#include "ui_bigbadwolf.h"
#include <QMessageBox>
#include <QKeyEvent>
#include "mainmenu.h"
#include <QThread>
#include <vector>
#include <QPainter>
#include <QPixmap>
#include <QDir>
#include <math.h>
#include <fstream>
//------------------------------------------------------------------------------------------------------------------------------
//GEN RANDOM VARIATION
void BigBadWolf::genvariation()
{
    variation = rand()%99;
}

//------------------------------------------------------------------------------------------------------------------------------
//FUNCTION CHECKING IF FLOOR IS GOOD TO STAND ON
bool IsStandable(int & eventstatus,int floor_code,int target_x,int target_y, int mapsize_x, int mapsize_y)
{
    if(floor_code == 0 || floor_code == 10 || (floor_code>=22 && floor_code<=28) || target_x < 0 || target_y < 0 || target_x > mapsize_x-1 || target_y > mapsize_y-1 )
    {
        eventstatus = 1;
        return false;

    }
    else return true;
}
//FUNCTION CHECKING IF FLOOR IS GOOD TO DIG IT
bool IsDiggable(int floor_code)
{

    return true; // TBC
}

//------------------------------------------------------------------------------------------------------------------------------
// LUCK FUNCTIONS
   // ATTACK
bool BigBadWolf::Attack(int & eventstatus,int & wluck,int & gluck,bool stealthmode)
{
    int chance=0;
    if(stealthmode)
    {
        chance = wluck/gluck*50;  // TO BE BALANCED!
    }
    else
    {
        chance = wluck/gluck*65;  // TO BE BALANCED!
    }
    int actual = (rand()%1001)/10;
    if(chance<=actual)
    {
        //QMessageBox::information(0,QString("Tr00!"),0,QString("OK"));
        wluck--;
        gluck++;
        eventstatus=6;
        genvariation();
        return true;
    }
    else
    {
        //QMessageBox::information(0,QString("Not actually tr00!"),0,QString("OK"));
        wluck++;
        gluck--;
        eventstatus=7;
        genvariation();
        return false;
    }
}
    // MAKING NOISE
bool MakeNoise(int luck,int typeofsurface, bool stealthmode)
{
return false;
}
    // STEPING INTO PIT
bool BigBadWolf::StepIntoPit(int & eventstatus,int & luck,bool stealthmode, int & state) // Change state if true?
{
    int needed_points=0;
    int actual_points = (rand()%1000) /10;
    if(state<=10 && state>=5)
    {
        needed_points=state+3;
    }
    if(state<=20 && state>10)
    {
        needed_points=2*state-5;
    }
    if(state>20 && state<=32)
    {
        needed_points=3*state-16;
    }
    if(stealthmode)
    {
    needed_points /= 5; // TBC!
    }

    if(actual_points>=needed_points)
    {
        if(state>20 && state<=32)
        {
            luck--;
        }
        return false;
    }
    else
    {
        //QMessageBox::information(0,QString("Tr00!"),0,QString("OK"));
        state/=2; // TBC!
        luck++;
        genvariation();
        if(eventstatus==6)
        {
            eventstatus=8;
        }
        else
        {
            eventstatus=9;
        }
        return true;
    }

}

extern QString strPath;

//------------------------------------------------------------------------------------------------------------------------------
//PIXMAPS INIT

int distance(int x1, int y1, int x2, int y2)
{
   double d =  (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2);
   return (int)(sqrt (d)+0.4);
}

//------------------------------------------------------------------------------------------------------------------------------
//REDRAW
void BigBadWolf::redraw()
{
    QPixmap NewPic(960,540);
    QPainter NewPicPtr(&NewPic);
    if(step_status==1)  // WOLF'S TURN
    for(int tile_x=0;tile_x<13;tile_x++) // CAN BE CHANGED TO 11!
        for(int tile_y=0;tile_y<9;tile_y++)
        {
            //if((wolf_x-screen_center_x-tile_x+6)*(wolf_x-screen_center_x-tile_x+6)+(wolf_y-screen_center_y-tile_y+4)*(wolf_y-screen_center_y-tile_y+4) <= 9) // 9 - square of visible range

            if (distance(wolf_x,wolf_y, screen_center_x+tile_x-6,screen_center_y+tile_y-4)<=wolf_visiblearea) // TO BE CHANGED
       {

            seen_by_wolf[screen_center_x+tile_x-6][screen_center_y+tile_y-4]=true;
            // OBSTACLE 0
                if(map_surfaces[screen_center_x+tile_x-6][screen_center_y+tile_y-4]==/*INT CODE OF TILE */ 0 ) // SEARCH FOR ERRORS HERE!
                {
                NewPicPtr.drawPixmap(60*tile_x,60*tile_y,60,60,ObstalceTest1);
                }
            // GRASS WITH TREE 10
                if(map_surfaces[screen_center_x+tile_x-6][screen_center_y+tile_y-4]==/*INT CODE OF TILE */ 10 ) // SEARCH FOR ERRORS HERE!
                {
                NewPicPtr.drawPixmap(60*tile_x,60*tile_y,60,60,GrassAndTree1_10);
                }
            // BED ON CARPET 22
                if(map_surfaces[screen_center_x+tile_x-6][screen_center_y+tile_y-4]==/*INT CODE OF TILE */ 22 ) // SEARCH FOR ERRORS HERE!
                {
                NewPicPtr.drawPixmap(60*tile_x,60*tile_y,60,60,BedOnACarpet1_22);
                }
            // GRASS2 WITH TREE 23
                if(map_surfaces[screen_center_x+tile_x-6][screen_center_y+tile_y-4]==/*INT CODE OF TILE */ 23 ) // SEARCH FOR ERRORS HERE!
                {
                NewPicPtr.drawPixmap(60*tile_x,60*tile_y,60,60,GrassAndTree2_23);
                }
            // GRASS2FENCE FACE
                if(map_surfaces[screen_center_x+tile_x-6][screen_center_y+tile_y-4]==/*INT CODE OF TILE */ 24 ) // SEARCH FOR ERRORS HERE!
                {
                NewPicPtr.drawPixmap(60*tile_x,60*tile_y,60,60,Grass2FenceFaceFull_24);
                }
            // GRASS2FENCE LEFT SIDE
                if(map_surfaces[screen_center_x+tile_x-6][screen_center_y+tile_y-4]==/*INT CODE OF TILE */ 25 ) // SEARCH FOR ERRORS HERE!
                {
                NewPicPtr.drawPixmap(60*tile_x,60*tile_y,60,60,Grass2FenceSideLeft_25);
                }
            // GRASS2FENCE RIGHT SIDE
                if(map_surfaces[screen_center_x+tile_x-6][screen_center_y+tile_y-4]==/*INT CODE OF TILE */ 26 ) // SEARCH FOR ERRORS HERE!
                {
                NewPicPtr.drawPixmap(60*tile_x,60*tile_y,60,60,Grass2FenceSideRight_26);
                }
            // GRASS2FENCE LEFT ENDED FACE
                if(map_surfaces[screen_center_x+tile_x-6][screen_center_y+tile_y-4]==/*INT CODE OF TILE */ 27 ) // SEARCH FOR ERRORS HERE!
                {
                NewPicPtr.drawPixmap(60*tile_x,60*tile_y,60,60,Grass2FenceFaceLeftEnd_27);
                }
            // GRASS2FENCE RIGHT ENDED FACE
                if(map_surfaces[screen_center_x+tile_x-6][screen_center_y+tile_y-4]==/*INT CODE OF TILE */ 28 ) // SEARCH FOR ERRORS HERE!
                {
                NewPicPtr.drawPixmap(60*tile_x,60*tile_y,60,60,Grass2FenceFaceRightEnd_28);
                }
            // GREEN SQUARE 1
            if(map_surfaces[screen_center_x+tile_x-6][screen_center_y+tile_y-4]==/*INT CODE OF TILE */ 1 ) // SEARCH FOR ERRORS HERE!
            {
            NewPicPtr.drawPixmap(60*tile_x,60*tile_y,60,60,TerrainTest1_Green);
            if(screen_center_x+tile_x-6 == wolf_x && screen_center_y+tile_y-4 == wolf_y) // SEARCH FOR ERRORS HERE!
            {
                NewPicPtr.drawPixmap(60*tile_x,60*tile_y,60,60,WolfTest1_Green);
            }
            for(int i = 0; i < num_of_goats;i++)
            {
                    if((screen_center_x+tile_x-6 == goat_pos_x[i]) && (screen_center_y+tile_y-4 == goat_pos_y[i]) && goat_is_alive[i])
                      {
                        NewPicPtr.drawPixmap(60*tile_x,60*tile_y,60,60,GoatTest1_Green);
                      }
            }

            }
            // BLACK SQUARE 2
                if(map_surfaces[screen_center_x+tile_x-6][screen_center_y+tile_y-4]==/*INT CODE OF TILE */ 2 ) // SEARCH FOR ERRORS HERE!
                {
                NewPicPtr.drawPixmap(60*tile_x,60*tile_y,60,60,TerrainTest1_Black);
                if(screen_center_x+tile_x-6 == wolf_x && screen_center_y+tile_y-4 == wolf_y) // SEARCH FOR ERRORS HERE!
                {
                    NewPicPtr.drawPixmap(60*tile_x,60*tile_y,60,60,WolfTest1_Black);
                }
                for(int i = 0; i < num_of_goats;i++)
                {
                        if((screen_center_x+tile_x-6 == goat_pos_x[i]) && (screen_center_y+tile_y-4 == goat_pos_y[i]) && goat_is_alive[i])
                          {
                            NewPicPtr.drawPixmap(60*tile_x,60*tile_y,60,60,GoatTest1_Black);
                          }
                }}
            // GRASS1 11
                if(map_surfaces[screen_center_x+tile_x-6][screen_center_y+tile_y-4]==/*INT CODE OF TILE */ 11 ) // SEARCH FOR ERRORS HERE!
                {
                NewPicPtr.drawPixmap(60*tile_x,60*tile_y,60,60,Grass1_11);
                if(screen_center_x+tile_x-6 == wolf_x && screen_center_y+tile_y-4 == wolf_y) // SEARCH FOR ERRORS HERE!
                {
                     NewPicPtr.drawPixmap(60*tile_x,60*tile_y,60,60,Grass1_11_w);
                }
                for(int i = 0; i < num_of_goats;i++)
                {
                       if((screen_center_x+tile_x-6 == goat_pos_x[i]) && (screen_center_y+tile_y-4 == goat_pos_y[i]) && goat_is_alive[i])
                       {
                           NewPicPtr.drawPixmap(60*tile_x,60*tile_y,60,60,Grass1_11_g);
                       }
                }
                }
            // GRASS2 12
                if(map_surfaces[screen_center_x+tile_x-6][screen_center_y+tile_y-4]==/*INT CODE OF TILE */ 12 ) // SEARCH FOR ERRORS HERE!
                {
                NewPicPtr.drawPixmap(60*tile_x,60*tile_y,60,60,Grass2_12);
                if(screen_center_x+tile_x-6 == wolf_x && screen_center_y+tile_y-4 == wolf_y) // SEARCH FOR ERRORS HERE!
                {
                    NewPicPtr.drawPixmap(60*tile_x,60*tile_y,60,60,Grass2_12_w);
                }
                for(int i = 0; i < num_of_goats;i++)
                {
                    if((screen_center_x+tile_x-6 == goat_pos_x[i]) && (screen_center_y+tile_y-4 == goat_pos_y[i]) && goat_is_alive[i])
                    {
                        NewPicPtr.drawPixmap(60*tile_x,60*tile_y,60,60,Grass2_12_g);
                    }
                } }
                // GRASS3 13
                if(map_surfaces[screen_center_x+tile_x-6][screen_center_y+tile_y-4]==/*INT CODE OF TILE */ 13 ) // SEARCH FOR ERRORS HERE!
                {
                NewPicPtr.drawPixmap(60*tile_x,60*tile_y,60,60,Grass3_13);
                if(screen_center_x+tile_x-6 == wolf_x && screen_center_y+tile_y-4 == wolf_y) // SEARCH FOR ERRORS HERE!
                {
                     NewPicPtr.drawPixmap(60*tile_x,60*tile_y,60,60,Grass3_13_w);
                }
                for(int i = 0; i < num_of_goats;i++)
                {
                      if((screen_center_x+tile_x-6 == goat_pos_x[i]) && (screen_center_y+tile_y-4 == goat_pos_y[i]) && goat_is_alive[i])
                      {
                           NewPicPtr.drawPixmap(60*tile_x,60*tile_y,60,60,Grass3_13_g);
                      }
                }
                }
                // PATH 1 14
                if(map_surfaces[screen_center_x+tile_x-6][screen_center_y+tile_y-4]==/*INT CODE OF TILE */ 14 ) // SEARCH FOR ERRORS HERE!
                {
                NewPicPtr.drawPixmap(60*tile_x,60*tile_y,60,60,GrassPath2x1WatchingUpLeft1_14);
                if(screen_center_x+tile_x-6 == wolf_x && screen_center_y+tile_y-4 == wolf_y) // SEARCH FOR ERRORS HERE!
                {
                    NewPicPtr.drawPixmap(60*tile_x,60*tile_y,60,60,GrassPath2x1WatchingUpLeft1_14_w);
                }
                for(int i = 0; i < num_of_goats;i++)
                {
                    if((screen_center_x+tile_x-6 == goat_pos_x[i]) && (screen_center_y+tile_y-4 == goat_pos_y[i]) && goat_is_alive[i])
                    {
                       NewPicPtr.drawPixmap(60*tile_x,60*tile_y,60,60,GrassPath2x1WatchingUpLeft1_14_g);
                    }
                } }
                // PATH2 15
                if(map_surfaces[screen_center_x+tile_x-6][screen_center_y+tile_y-4]==/*INT CODE OF TILE */ 15 ) // SEARCH FOR ERRORS HERE!
                {
                NewPicPtr.drawPixmap(60*tile_x,60*tile_y,60,60,GrassPath2x1WatchingUpRight1_15);
                if(screen_center_x+tile_x-6 == wolf_x && screen_center_y+tile_y-4 == wolf_y) // SEARCH FOR ERRORS HERE!
                {
                     NewPicPtr.drawPixmap(60*tile_x,60*tile_y,60,60,GrassPath2x1WatchingUpRight1_15_w);
                }
                for(int i = 0; i < num_of_goats;i++)
                {
                      if((screen_center_x+tile_x-6 == goat_pos_x[i]) && (screen_center_y+tile_y-4 == goat_pos_y[i]) && goat_is_alive[i])
                      {
                           NewPicPtr.drawPixmap(60*tile_x,60*tile_y,60,60,GrassPath2x1WatchingUpRight1_15_g);
                      }
                }
                }
                // PATH3 16
                if(map_surfaces[screen_center_x+tile_x-6][screen_center_y+tile_y-4]==/*INT CODE OF TILE */ 16 ) // SEARCH FOR ERRORS HERE!
                {
                NewPicPtr.drawPixmap(60*tile_x,60*tile_y,60,60,GrassPath1x1WatchingLeft2_16);
                if(screen_center_x+tile_x-6 == wolf_x && screen_center_y+tile_y-4 == wolf_y) // SEARCH FOR ERRORS HERE!
                {
                    NewPicPtr.drawPixmap(60*tile_x,60*tile_y,60,60,GrassPath1x1WatchingLeft2_16_w);
                }
                for(int i = 0; i < num_of_goats;i++)
                {
                    if((screen_center_x+tile_x-6 == goat_pos_x[i]) && (screen_center_y+tile_y-4 == goat_pos_y[i]) && goat_is_alive[i])
                    {
                       NewPicPtr.drawPixmap(60*tile_x,60*tile_y,60,60,GrassPath1x1WatchingLeft2_16_g);
                    }
                } }
                // PATH4 17
                if(map_surfaces[screen_center_x+tile_x-6][screen_center_y+tile_y-4]==/*INT CODE OF TILE */ 17 ) // SEARCH FOR ERRORS HERE!
                {
                NewPicPtr.drawPixmap(60*tile_x,60*tile_y,60,60,GrassPath1x1WatchingLeft3_17);
                if(screen_center_x+tile_x-6 == wolf_x && screen_center_y+tile_y-4 == wolf_y) // SEARCH FOR ERRORS HERE!
                {
                     NewPicPtr.drawPixmap(60*tile_x,60*tile_y,60,60,GrassPath1x1WatchingLeft3_17_w);
                }
                for(int i = 0; i < num_of_goats;i++)
                {
                      if((screen_center_x+tile_x-6 == goat_pos_x[i]) && (screen_center_y+tile_y-4 == goat_pos_y[i]) && goat_is_alive[i])
                      {
                           NewPicPtr.drawPixmap(60*tile_x,60*tile_y,60,60,GrassPath1x1WatchingLeft3_17_g);
                      }
                }
                }
                // PATH5 18
                if(map_surfaces[screen_center_x+tile_x-6][screen_center_y+tile_y-4]==/*INT CODE OF TILE */ 18 ) // SEARCH FOR ERRORS HERE!
                {
                NewPicPtr.drawPixmap(60*tile_x,60*tile_y,60,60,GrassWithoutPath1x1_1_18);
                if(screen_center_x+tile_x-6 == wolf_x && screen_center_y+tile_y-4 == wolf_y) // SEARCH FOR ERRORS HERE!
                {
                    NewPicPtr.drawPixmap(60*tile_x,60*tile_y,60,60,GrassWithoutPath1x1_1_18_w);
                }
                for(int i = 0; i < num_of_goats;i++)
                {
                    if((screen_center_x+tile_x-6 == goat_pos_x[i]) && (screen_center_y+tile_y-4 == goat_pos_y[i]) && goat_is_alive[i])
                    {
                       NewPicPtr.drawPixmap(60*tile_x,60*tile_y,60,60,GrassWithoutPath1x1_1_18_g);
                    }
                } }
                // PARQUET1 19
                if(map_surfaces[screen_center_x+tile_x-6][screen_center_y+tile_y-4]==/*INT CODE OF TILE */ 19 ) // SEARCH FOR ERRORS HERE!
                {
                NewPicPtr.drawPixmap(60*tile_x,60*tile_y,60,60,WoodenParquet1x1_1_19);
                if(screen_center_x+tile_x-6 == wolf_x && screen_center_y+tile_y-4 == wolf_y) // SEARCH FOR ERRORS HERE!
                {
                     NewPicPtr.drawPixmap(60*tile_x,60*tile_y,60,60,WoodenParquet1x1_1_19_w);
                }
                for(int i = 0; i < num_of_goats;i++)
                {
                      if((screen_center_x+tile_x-6 == goat_pos_x[i]) && (screen_center_y+tile_y-4 == goat_pos_y[i]) && goat_is_alive[i])
                      {
                           NewPicPtr.drawPixmap(60*tile_x,60*tile_y,60,60,WoodenParquet1x1_1_19_g);
                      }
                }
                }
                // PARQUET2 20
                if(map_surfaces[screen_center_x+tile_x-6][screen_center_y+tile_y-4]==/*INT CODE OF TILE */ 20 ) // SEARCH FOR ERRORS HERE!
                {
                NewPicPtr.drawPixmap(60*tile_x,60*tile_y,60,60,WoodenParquet1x1_2_20);
                if(screen_center_x+tile_x-6 == wolf_x && screen_center_y+tile_y-4 == wolf_y) // SEARCH FOR ERRORS HERE!
                {
                    NewPicPtr.drawPixmap(60*tile_x,60*tile_y,60,60,WoodenParquet1x1_2_20_w);
                }
                for(int i = 0; i < num_of_goats;i++)
                {
                    if((screen_center_x+tile_x-6 == goat_pos_x[i]) && (screen_center_y+tile_y-4 == goat_pos_y[i]) && goat_is_alive[i])
                    {
                       NewPicPtr.drawPixmap(60*tile_x,60*tile_y,60,60,WoodenParquet1x1_2_20_g);
                    }
                } }
                // CARPET1 21
                if(map_surfaces[screen_center_x+tile_x-6][screen_center_y+tile_y-4]==/*INT CODE OF TILE */ 21 ) // SEARCH FOR ERRORS HERE!
                {
                NewPicPtr.drawPixmap(60*tile_x,60*tile_y,60,60,Carpet1x1_1_21);
                if(screen_center_x+tile_x-6 == wolf_x && screen_center_y+tile_y-4 == wolf_y) // SEARCH FOR ERRORS HERE!
                {
                     NewPicPtr.drawPixmap(60*tile_x,60*tile_y,60,60,Carpet1x1_1_21_w);
                }
                for(int i = 0; i < num_of_goats;i++)
                {
                      if((screen_center_x+tile_x-6 == goat_pos_x[i]) && (screen_center_y+tile_y-4 == goat_pos_y[i]) && goat_is_alive[i])
                      {
                           NewPicPtr.drawPixmap(60*tile_x,60*tile_y,60,60,Carpet1x1_1_21_g);
                      }
                } }





        }else
            if(!seen_by_wolf[screen_center_x+tile_x-6][screen_center_y+tile_y-4])
            {
            NewPicPtr.drawPixmap(60*tile_x,60*tile_y,60,60,WarFog);
            }
            else
            {
                if(map_surfaces[screen_center_x+tile_x-6][screen_center_y+tile_y-4]==/*INT CODE OF TILE */ 10 )
                {
                     NewPicPtr.drawPixmap(60*tile_x,60*tile_y,60,60,GrassAndTree1_10_f);
                }
                if(map_surfaces[screen_center_x+tile_x-6][screen_center_y+tile_y-4]==/*INT CODE OF TILE */ 11 )
                {
                     NewPicPtr.drawPixmap(60*tile_x,60*tile_y,60,60,Grass1_11_f);
                }
                if(map_surfaces[screen_center_x+tile_x-6][screen_center_y+tile_y-4]==/*INT CODE OF TILE */ 12 )
                {
                     NewPicPtr.drawPixmap(60*tile_x,60*tile_y,60,60,Grass2_12_f);
                }
                if(map_surfaces[screen_center_x+tile_x-6][screen_center_y+tile_y-4]==/*INT CODE OF TILE */ 13 )
                {
                     NewPicPtr.drawPixmap(60*tile_x,60*tile_y,60,60,Grass3_13_f);
                }
                if(map_surfaces[screen_center_x+tile_x-6][screen_center_y+tile_y-4]==/*INT CODE OF TILE */ 14 )
                {
                     NewPicPtr.drawPixmap(60*tile_x,60*tile_y,60,60,GrassPath2x1WatchingUpLeft1_14_f);
                }
                if(map_surfaces[screen_center_x+tile_x-6][screen_center_y+tile_y-4]==/*INT CODE OF TILE */ 15 )
                {
                     NewPicPtr.drawPixmap(60*tile_x,60*tile_y,60,60,GrassPath2x1WatchingUpRight1_15_f);
                }
                if(map_surfaces[screen_center_x+tile_x-6][screen_center_y+tile_y-4]==/*INT CODE OF TILE */ 16 )
                {
                     NewPicPtr.drawPixmap(60*tile_x,60*tile_y,60,60,GrassPath1x1WatchingLeft2_16_f);
                }
                if(map_surfaces[screen_center_x+tile_x-6][screen_center_y+tile_y-4]==/*INT CODE OF TILE */ 17 )
                {
                     NewPicPtr.drawPixmap(60*tile_x,60*tile_y,60,60,GrassPath1x1WatchingLeft3_17_f);
                }
                if(map_surfaces[screen_center_x+tile_x-6][screen_center_y+tile_y-4]==/*INT CODE OF TILE */ 18 )
                {
                     NewPicPtr.drawPixmap(60*tile_x,60*tile_y,60,60,GrassWithoutPath1x1_1_18_f);
                }
                if(map_surfaces[screen_center_x+tile_x-6][screen_center_y+tile_y-4]==/*INT CODE OF TILE */ 19 )
                {
                     NewPicPtr.drawPixmap(60*tile_x,60*tile_y,60,60,WoodenParquet1x1_1_19_f);
                }
                if(map_surfaces[screen_center_x+tile_x-6][screen_center_y+tile_y-4]==/*INT CODE OF TILE */ 20 )
                {
                     NewPicPtr.drawPixmap(60*tile_x,60*tile_y,60,60,WoodenParquet1x1_2_20_f);
                }
                if(map_surfaces[screen_center_x+tile_x-6][screen_center_y+tile_y-4]==/*INT CODE OF TILE */ 21 )
                {
                     NewPicPtr.drawPixmap(60*tile_x,60*tile_y,60,60,Carpet1x1_1_21_f);
                }
                if(map_surfaces[screen_center_x+tile_x-6][screen_center_y+tile_y-4]==/*INT CODE OF TILE */ 22 )
                {
                     NewPicPtr.drawPixmap(60*tile_x,60*tile_y,60,60,BedOnACarpet1_22_f);
                }
                if(map_surfaces[screen_center_x+tile_x-6][screen_center_y+tile_y-4]==/*INT CODE OF TILE */ 23 )
                {
                     NewPicPtr.drawPixmap(60*tile_x,60*tile_y,60,60,GrassAndTree2_23_f);
                }
                if(map_surfaces[screen_center_x+tile_x-6][screen_center_y+tile_y-4]==/*INT CODE OF TILE */ 24 )
                {
                     NewPicPtr.drawPixmap(60*tile_x,60*tile_y,60,60,Grass2FenceFaceFull_24_f);
                }
                if(map_surfaces[screen_center_x+tile_x-6][screen_center_y+tile_y-4]==/*INT CODE OF TILE */ 25 )
                {
                     NewPicPtr.drawPixmap(60*tile_x,60*tile_y,60,60,Grass2FenceSideLeft_25_f);
                }
                if(map_surfaces[screen_center_x+tile_x-6][screen_center_y+tile_y-4]==/*INT CODE OF TILE */ 26 )
                {
                     NewPicPtr.drawPixmap(60*tile_x,60*tile_y,60,60,Grass2FenceSideRight_26_f);
                }
                if(map_surfaces[screen_center_x+tile_x-6][screen_center_y+tile_y-4]==/*INT CODE OF TILE */ 27 )
                {
                     NewPicPtr.drawPixmap(60*tile_x,60*tile_y,60,60,Grass2FenceFaceLeftEnd_27_f);
                }
                if(map_surfaces[screen_center_x+tile_x-6][screen_center_y+tile_y-4]==/*INT CODE OF TILE */ 28 )
                {
                     NewPicPtr.drawPixmap(60*tile_x,60*tile_y,60,60,Grass2FenceFaceRightEnd_28_f);
                }
                if(map_surfaces[screen_center_x+tile_x-6][screen_center_y+tile_y-4]==/*INT CODE OF TILE */ 0 )
                {
                     NewPicPtr.drawPixmap(60*tile_x,60*tile_y,60,60,ObstalceTest1_f);
                }
            }
        }











    if(step_status==3)  // GOAT'S TURN
        {
        for(int tile_x=0;tile_x<13;tile_x++) // CAN BE CHANGED TO 11!
            for(int tile_y=0;tile_y<9;tile_y++)
            {
            NewPicPtr.drawPixmap(60*tile_x,60*tile_y,60,60,WarFog);
            if(seen_by_goats[screen_center_x+tile_x-6][screen_center_y+tile_y-4])
           {
            if(map_surfaces[screen_center_x+tile_x-6][screen_center_y+tile_y-4]==/*INT CODE OF TILE */ 10 )
            {
                 NewPicPtr.drawPixmap(60*tile_x,60*tile_y,60,60,GrassAndTree1_10_f);
            }
            if(map_surfaces[screen_center_x+tile_x-6][screen_center_y+tile_y-4]==/*INT CODE OF TILE */ 11 )
            {
                 NewPicPtr.drawPixmap(60*tile_x,60*tile_y,60,60,Grass1_11_f);
            }
            if(map_surfaces[screen_center_x+tile_x-6][screen_center_y+tile_y-4]==/*INT CODE OF TILE */ 12 )
            {
                 NewPicPtr.drawPixmap(60*tile_x,60*tile_y,60,60,Grass2_12_f);
            }
            if(map_surfaces[screen_center_x+tile_x-6][screen_center_y+tile_y-4]==/*INT CODE OF TILE */ 13 )
            {
                 NewPicPtr.drawPixmap(60*tile_x,60*tile_y,60,60,Grass3_13_f);
            }
            if(map_surfaces[screen_center_x+tile_x-6][screen_center_y+tile_y-4]==/*INT CODE OF TILE */ 14 )
            {
                 NewPicPtr.drawPixmap(60*tile_x,60*tile_y,60,60,GrassPath2x1WatchingUpLeft1_14_f);
            }
            if(map_surfaces[screen_center_x+tile_x-6][screen_center_y+tile_y-4]==/*INT CODE OF TILE */ 15 )
            {
                 NewPicPtr.drawPixmap(60*tile_x,60*tile_y,60,60,GrassPath2x1WatchingUpRight1_15_f);
            }
            if(map_surfaces[screen_center_x+tile_x-6][screen_center_y+tile_y-4]==/*INT CODE OF TILE */ 16 )
            {
                 NewPicPtr.drawPixmap(60*tile_x,60*tile_y,60,60,GrassPath1x1WatchingLeft2_16_f);
            }
            if(map_surfaces[screen_center_x+tile_x-6][screen_center_y+tile_y-4]==/*INT CODE OF TILE */ 17 )
            {
                 NewPicPtr.drawPixmap(60*tile_x,60*tile_y,60,60,GrassPath1x1WatchingLeft3_17_f);
            }
            if(map_surfaces[screen_center_x+tile_x-6][screen_center_y+tile_y-4]==/*INT CODE OF TILE */ 18 )
            {
                 NewPicPtr.drawPixmap(60*tile_x,60*tile_y,60,60,GrassWithoutPath1x1_1_18_f);
            }
            if(map_surfaces[screen_center_x+tile_x-6][screen_center_y+tile_y-4]==/*INT CODE OF TILE */ 19 )
            {
                 NewPicPtr.drawPixmap(60*tile_x,60*tile_y,60,60,WoodenParquet1x1_1_19_f);
            }
            if(map_surfaces[screen_center_x+tile_x-6][screen_center_y+tile_y-4]==/*INT CODE OF TILE */ 20 )
            {
                 NewPicPtr.drawPixmap(60*tile_x,60*tile_y,60,60,WoodenParquet1x1_2_20_f);
            }
            if(map_surfaces[screen_center_x+tile_x-6][screen_center_y+tile_y-4]==/*INT CODE OF TILE */ 21 )
            {
                 NewPicPtr.drawPixmap(60*tile_x,60*tile_y,60,60,Carpet1x1_1_21_f);
            }
            if(map_surfaces[screen_center_x+tile_x-6][screen_center_y+tile_y-4]==/*INT CODE OF TILE */ 22 )
            {
                 NewPicPtr.drawPixmap(60*tile_x,60*tile_y,60,60,BedOnACarpet1_22_f);
            }
            if(map_surfaces[screen_center_x+tile_x-6][screen_center_y+tile_y-4]==/*INT CODE OF TILE */ 23 )
            {
                 NewPicPtr.drawPixmap(60*tile_x,60*tile_y,60,60,GrassAndTree2_23_f);
            }
            if(map_surfaces[screen_center_x+tile_x-6][screen_center_y+tile_y-4]==/*INT CODE OF TILE */ 24 )
            {
                 NewPicPtr.drawPixmap(60*tile_x,60*tile_y,60,60,Grass2FenceFaceFull_24_f);
            }
            if(map_surfaces[screen_center_x+tile_x-6][screen_center_y+tile_y-4]==/*INT CODE OF TILE */ 25 )
            {
                 NewPicPtr.drawPixmap(60*tile_x,60*tile_y,60,60,Grass2FenceSideLeft_25_f);
            }
            if(map_surfaces[screen_center_x+tile_x-6][screen_center_y+tile_y-4]==/*INT CODE OF TILE */ 26 )
            {
                 NewPicPtr.drawPixmap(60*tile_x,60*tile_y,60,60,Grass2FenceSideRight_26_f);
            }
            if(map_surfaces[screen_center_x+tile_x-6][screen_center_y+tile_y-4]==/*INT CODE OF TILE */ 27 )
            {
                 NewPicPtr.drawPixmap(60*tile_x,60*tile_y,60,60,Grass2FenceFaceLeftEnd_27_f);
            }
            if(map_surfaces[screen_center_x+tile_x-6][screen_center_y+tile_y-4]==/*INT CODE OF TILE */ 28 )
            {
                 NewPicPtr.drawPixmap(60*tile_x,60*tile_y,60,60,Grass2FenceFaceRightEnd_28_f);
            }
            if(map_surfaces[screen_center_x+tile_x-6][screen_center_y+tile_y-4]==/*INT CODE OF TILE */ 0 )
            {
                 NewPicPtr.drawPixmap(60*tile_x,60*tile_y,60,60,ObstalceTest1_f);
            }
           }

            for(int j=0;j<num_of_goats;j++)
            {
                if(distance(goat_pos_x[j],goat_pos_y[j], screen_center_x+tile_x-6,screen_center_y+tile_y-4)<=goats_visiblearea && goat_is_alive[j])
                {

                    seen_by_goats[screen_center_x+tile_x-6][screen_center_y+tile_y-4]=true;


                    // OBSTACLE 0
                        if(map_surfaces[screen_center_x+tile_x-6][screen_center_y+tile_y-4]==/*INT CODE OF TILE */ 0 ) // SEARCH FOR ERRORS HERE!
                        {
                        NewPicPtr.drawPixmap(60*tile_x,60*tile_y,60,60,ObstalceTest1);
                        }
                        // GRASS WITH TREE 10
                            if(map_surfaces[screen_center_x+tile_x-6][screen_center_y+tile_y-4]==/*INT CODE OF TILE */ 10 ) // SEARCH FOR ERRORS HERE!
                            {
                            NewPicPtr.drawPixmap(60*tile_x,60*tile_y,60,60,GrassAndTree1_10);
                            }
                        // BED ON CARPET 22
                            if(map_surfaces[screen_center_x+tile_x-6][screen_center_y+tile_y-4]==/*INT CODE OF TILE */ 22 ) // SEARCH FOR ERRORS HERE!
                            {
                            NewPicPtr.drawPixmap(60*tile_x,60*tile_y,60,60,BedOnACarpet1_22);
                            }
                        // GRASS2 WITH TREE 23
                            if(map_surfaces[screen_center_x+tile_x-6][screen_center_y+tile_y-4]==/*INT CODE OF TILE */ 23 ) // SEARCH FOR ERRORS HERE!
                            {
                            NewPicPtr.drawPixmap(60*tile_x,60*tile_y,60,60,GrassAndTree2_23);
                            }
                        // GRASS2FENCE FACE
                            if(map_surfaces[screen_center_x+tile_x-6][screen_center_y+tile_y-4]==/*INT CODE OF TILE */ 24 ) // SEARCH FOR ERRORS HERE!
                            {
                            NewPicPtr.drawPixmap(60*tile_x,60*tile_y,60,60,Grass2FenceFaceFull_24);
                            }
                        // GRASS2FENCE LEFT SIDE
                            if(map_surfaces[screen_center_x+tile_x-6][screen_center_y+tile_y-4]==/*INT CODE OF TILE */ 25 ) // SEARCH FOR ERRORS HERE!
                            {
                            NewPicPtr.drawPixmap(60*tile_x,60*tile_y,60,60,Grass2FenceSideLeft_25);
                            }
                        // GRASS2FENCE RIGHT SIDE
                            if(map_surfaces[screen_center_x+tile_x-6][screen_center_y+tile_y-4]==/*INT CODE OF TILE */ 26 ) // SEARCH FOR ERRORS HERE!
                            {
                            NewPicPtr.drawPixmap(60*tile_x,60*tile_y,60,60,Grass2FenceSideRight_26);
                            }
                        // GRASS2FENCE LEFT ENDED FACE
                            if(map_surfaces[screen_center_x+tile_x-6][screen_center_y+tile_y-4]==/*INT CODE OF TILE */ 27 ) // SEARCH FOR ERRORS HERE!
                            {
                            NewPicPtr.drawPixmap(60*tile_x,60*tile_y,60,60,Grass2FenceFaceLeftEnd_27);
                            }
                        // GRASS2FENCE RIGHT ENDED FACE
                            if(map_surfaces[screen_center_x+tile_x-6][screen_center_y+tile_y-4]==/*INT CODE OF TILE */ 28 ) // SEARCH FOR ERRORS HERE!
                            {
                            NewPicPtr.drawPixmap(60*tile_x,60*tile_y,60,60,Grass2FenceFaceRightEnd_28);
                            }

                        // GREEN SQUARE 1
                    if(map_surfaces[screen_center_x+tile_x-6][screen_center_y+tile_y-4]==/*INT CODE OF TILE */ 1 ) // SEARCH FOR ERRORS HERE!
                    {
                    NewPicPtr.drawPixmap(60*tile_x,60*tile_y,60,60,TerrainTest1_Green);
                    if(screen_center_x+tile_x-6 == wolf_x && screen_center_y+tile_y-4 == wolf_y) // SEARCH FOR ERRORS HERE!
                    {
                        NewPicPtr.drawPixmap(60*tile_x,60*tile_y,60,60,WolfTest1_Green);
                    }
                    for(int i = 0; i < num_of_goats;i++)
                    {
                            if((screen_center_x+tile_x-6 == goat_pos_x[i]) && (screen_center_y+tile_y-4 == goat_pos_y[i]) && goat_is_alive[i])
                              {
                                NewPicPtr.drawPixmap(60*tile_x,60*tile_y,60,60,GoatTest1_Green);
                              }
                    }

                    }



                    // BLACK SQUARE 2
                        if(map_surfaces[screen_center_x+tile_x-6][screen_center_y+tile_y-4]==/*INT CODE OF TILE */ 2 ) // SEARCH FOR ERRORS HERE!
                        {
                        NewPicPtr.drawPixmap(60*tile_x,60*tile_y,60,60,TerrainTest1_Black);
                        if(screen_center_x+tile_x-6 == wolf_x && screen_center_y+tile_y-4 == wolf_y) // SEARCH FOR ERRORS HERE!
                        {
                            NewPicPtr.drawPixmap(60*tile_x,60*tile_y,60,60,WolfTest1_Black);
                        }
                        for(int i = 0; i < num_of_goats;i++)
                        {
                                if((screen_center_x+tile_x-6 == goat_pos_x[i]) && (screen_center_y+tile_y-4 == goat_pos_y[i]) && goat_is_alive[i])
                                  {
                                    NewPicPtr.drawPixmap(60*tile_x,60*tile_y,60,60,GoatTest1_Black);
                                  }
                        }}

                    // GRASS1 11
                        if(map_surfaces[screen_center_x+tile_x-6][screen_center_y+tile_y-4]==/*INT CODE OF TILE */ 11 ) // SEARCH FOR ERRORS HERE!
                        {
                        NewPicPtr.drawPixmap(60*tile_x,60*tile_y,60,60,Grass1_11);
                        if(screen_center_x+tile_x-6 == wolf_x && screen_center_y+tile_y-4 == wolf_y) // SEARCH FOR ERRORS HERE!
                        {
                             NewPicPtr.drawPixmap(60*tile_x,60*tile_y,60,60,Grass1_11_w);
                        }
                        for(int i = 0; i < num_of_goats;i++)
                        {
                               if((screen_center_x+tile_x-6 == goat_pos_x[i]) && (screen_center_y+tile_y-4 == goat_pos_y[i]) && goat_is_alive[i])
                               {
                                   NewPicPtr.drawPixmap(60*tile_x,60*tile_y,60,60,Grass1_11_g);
                               }
                            }
                            }
                        // GRASS2 12
                        if(map_surfaces[screen_center_x+tile_x-6][screen_center_y+tile_y-4]==/*INT CODE OF TILE */ 12 ) // SEARCH FOR ERRORS HERE!
                        {
                        NewPicPtr.drawPixmap(60*tile_x,60*tile_y,60,60,Grass2_12);
                        if(screen_center_x+tile_x-6 == wolf_x && screen_center_y+tile_y-4 == wolf_y) // SEARCH FOR ERRORS HERE!
                        {
                            NewPicPtr.drawPixmap(60*tile_x,60*tile_y,60,60,Grass2_12_w);
                        }
                        for(int i = 0; i < num_of_goats;i++)
                        {
                            if((screen_center_x+tile_x-6 == goat_pos_x[i]) && (screen_center_y+tile_y-4 == goat_pos_y[i]) && goat_is_alive[i])
                            {
                                NewPicPtr.drawPixmap(60*tile_x,60*tile_y,60,60,Grass2_12_g);
                            }
} }

                        // GRASS3 13
                        if(map_surfaces[screen_center_x+tile_x-6][screen_center_y+tile_y-4]==/*INT CODE OF TILE */ 13 ) // SEARCH FOR ERRORS HERE!
                        {
                        NewPicPtr.drawPixmap(60*tile_x,60*tile_y,60,60,Grass3_13);
                        if(screen_center_x+tile_x-6 == wolf_x && screen_center_y+tile_y-4 == wolf_y) // SEARCH FOR ERRORS HERE!
                        {
                             NewPicPtr.drawPixmap(60*tile_x,60*tile_y,60,60,Grass3_13_w);
                        }
                        for(int i = 0; i < num_of_goats;i++)
                        {
                              if((screen_center_x+tile_x-6 == goat_pos_x[i]) && (screen_center_y+tile_y-4 == goat_pos_y[i]) && goat_is_alive[i])
                              {
                                   NewPicPtr.drawPixmap(60*tile_x,60*tile_y,60,60,Grass3_13_g);
                              }
                        }
                        }
                        // PATH 1 14
                        if(map_surfaces[screen_center_x+tile_x-6][screen_center_y+tile_y-4]==/*INT CODE OF TILE */ 14 ) // SEARCH FOR ERRORS HERE!
                        {
                        NewPicPtr.drawPixmap(60*tile_x,60*tile_y,60,60,GrassPath2x1WatchingUpLeft1_14);
                        if(screen_center_x+tile_x-6 == wolf_x && screen_center_y+tile_y-4 == wolf_y) // SEARCH FOR ERRORS HERE!
                        {
                            NewPicPtr.drawPixmap(60*tile_x,60*tile_y,60,60,GrassPath2x1WatchingUpLeft1_14_w);
                        }
                        for(int i = 0; i < num_of_goats;i++)
                        {
                            if((screen_center_x+tile_x-6 == goat_pos_x[i]) && (screen_center_y+tile_y-4 == goat_pos_y[i]) && goat_is_alive[i])
                            {
                               NewPicPtr.drawPixmap(60*tile_x,60*tile_y,60,60,GrassPath2x1WatchingUpLeft1_14_g);
                            }
                        } }
                        // PATH2 15
                        if(map_surfaces[screen_center_x+tile_x-6][screen_center_y+tile_y-4]==/*INT CODE OF TILE */ 15 ) // SEARCH FOR ERRORS HERE!
                        {
                        NewPicPtr.drawPixmap(60*tile_x,60*tile_y,60,60,GrassPath2x1WatchingUpRight1_15);
                        if(screen_center_x+tile_x-6 == wolf_x && screen_center_y+tile_y-4 == wolf_y) // SEARCH FOR ERRORS HERE!
                        {
                             NewPicPtr.drawPixmap(60*tile_x,60*tile_y,60,60,GrassPath2x1WatchingUpRight1_15_w);
                        }
                        for(int i = 0; i < num_of_goats;i++)
                        {
                              if((screen_center_x+tile_x-6 == goat_pos_x[i]) && (screen_center_y+tile_y-4 == goat_pos_y[i]) && goat_is_alive[i])
                              {
                                   NewPicPtr.drawPixmap(60*tile_x,60*tile_y,60,60,GrassPath2x1WatchingUpRight1_15_g);
                              }
                        }
                        }
                        // PATH3 16
                        if(map_surfaces[screen_center_x+tile_x-6][screen_center_y+tile_y-4]==/*INT CODE OF TILE */ 16 ) // SEARCH FOR ERRORS HERE!
                        {
                        NewPicPtr.drawPixmap(60*tile_x,60*tile_y,60,60,GrassPath1x1WatchingLeft2_16);
                        if(screen_center_x+tile_x-6 == wolf_x && screen_center_y+tile_y-4 == wolf_y) // SEARCH FOR ERRORS HERE!
                        {
                            NewPicPtr.drawPixmap(60*tile_x,60*tile_y,60,60,GrassPath1x1WatchingLeft2_16_w);
                        }
                        for(int i = 0; i < num_of_goats;i++)
                        {
                            if((screen_center_x+tile_x-6 == goat_pos_x[i]) && (screen_center_y+tile_y-4 == goat_pos_y[i]) && goat_is_alive[i])
                            {
                               NewPicPtr.drawPixmap(60*tile_x,60*tile_y,60,60,GrassPath1x1WatchingLeft2_16_g);
                            }
                        } }
                        // PATH4 17
                        if(map_surfaces[screen_center_x+tile_x-6][screen_center_y+tile_y-4]==/*INT CODE OF TILE */ 17 ) // SEARCH FOR ERRORS HERE!
                        {
                        NewPicPtr.drawPixmap(60*tile_x,60*tile_y,60,60,GrassPath1x1WatchingLeft3_17);
                        if(screen_center_x+tile_x-6 == wolf_x && screen_center_y+tile_y-4 == wolf_y) // SEARCH FOR ERRORS HERE!
                        {
                             NewPicPtr.drawPixmap(60*tile_x,60*tile_y,60,60,GrassPath1x1WatchingLeft3_17_w);
                        }
                        for(int i = 0; i < num_of_goats;i++)
                        {
                              if((screen_center_x+tile_x-6 == goat_pos_x[i]) && (screen_center_y+tile_y-4 == goat_pos_y[i]) && goat_is_alive[i])
                              {
                                   NewPicPtr.drawPixmap(60*tile_x,60*tile_y,60,60,GrassPath1x1WatchingLeft3_17_g);
                              }
                        }
                        }
                        // PATH5 18
                        if(map_surfaces[screen_center_x+tile_x-6][screen_center_y+tile_y-4]==/*INT CODE OF TILE */ 18 ) // SEARCH FOR ERRORS HERE!
                        {
                        NewPicPtr.drawPixmap(60*tile_x,60*tile_y,60,60,GrassWithoutPath1x1_1_18);
                        if(screen_center_x+tile_x-6 == wolf_x && screen_center_y+tile_y-4 == wolf_y) // SEARCH FOR ERRORS HERE!
                        {
                            NewPicPtr.drawPixmap(60*tile_x,60*tile_y,60,60,GrassWithoutPath1x1_1_18_w);
                        }
                        for(int i = 0; i < num_of_goats;i++)
                        {
                            if((screen_center_x+tile_x-6 == goat_pos_x[i]) && (screen_center_y+tile_y-4 == goat_pos_y[i]) && goat_is_alive[i])
                            {
                               NewPicPtr.drawPixmap(60*tile_x,60*tile_y,60,60,GrassWithoutPath1x1_1_18_g);
                            }
                        } }
                        // PARQUET1 19
                        if(map_surfaces[screen_center_x+tile_x-6][screen_center_y+tile_y-4]==/*INT CODE OF TILE */ 19 ) // SEARCH FOR ERRORS HERE!
                        {
                        NewPicPtr.drawPixmap(60*tile_x,60*tile_y,60,60,WoodenParquet1x1_1_19);
                        if(screen_center_x+tile_x-6 == wolf_x && screen_center_y+tile_y-4 == wolf_y) // SEARCH FOR ERRORS HERE!
                        {
                             NewPicPtr.drawPixmap(60*tile_x,60*tile_y,60,60,WoodenParquet1x1_1_19_w);
                        }
                        for(int i = 0; i < num_of_goats;i++)
                        {
                              if((screen_center_x+tile_x-6 == goat_pos_x[i]) && (screen_center_y+tile_y-4 == goat_pos_y[i]) && goat_is_alive[i])
                              {
                                   NewPicPtr.drawPixmap(60*tile_x,60*tile_y,60,60,WoodenParquet1x1_1_19_g);
                              }
                        }
                        }
                        // PARQUET2 20
                        if(map_surfaces[screen_center_x+tile_x-6][screen_center_y+tile_y-4]==/*INT CODE OF TILE */ 20 ) // SEARCH FOR ERRORS HERE!
                        {
                        NewPicPtr.drawPixmap(60*tile_x,60*tile_y,60,60,WoodenParquet1x1_2_20);
                        if(screen_center_x+tile_x-6 == wolf_x && screen_center_y+tile_y-4 == wolf_y) // SEARCH FOR ERRORS HERE!
                        {
                            NewPicPtr.drawPixmap(60*tile_x,60*tile_y,60,60,WoodenParquet1x1_2_20_w);
                        }
                        for(int i = 0; i < num_of_goats;i++)
                        {
                            if((screen_center_x+tile_x-6 == goat_pos_x[i]) && (screen_center_y+tile_y-4 == goat_pos_y[i]) && goat_is_alive[i])
                            {
                               NewPicPtr.drawPixmap(60*tile_x,60*tile_y,60,60,WoodenParquet1x1_2_20_g);
                            }
                        } }
                        // CARPET1 21
                        if(map_surfaces[screen_center_x+tile_x-6][screen_center_y+tile_y-4]==/*INT CODE OF TILE */ 21 ) // SEARCH FOR ERRORS HERE!
                        {
                        NewPicPtr.drawPixmap(60*tile_x,60*tile_y,60,60,Carpet1x1_1_21);
                        if(screen_center_x+tile_x-6 == wolf_x && screen_center_y+tile_y-4 == wolf_y) // SEARCH FOR ERRORS HERE!
                        {
                             NewPicPtr.drawPixmap(60*tile_x,60*tile_y,60,60,Carpet1x1_1_21_w);
                        }
                        for(int i = 0; i < num_of_goats;i++)
                        {
                              if((screen_center_x+tile_x-6 == goat_pos_x[i]) && (screen_center_y+tile_y-4 == goat_pos_y[i]) && goat_is_alive[i])
                              {
                                   NewPicPtr.drawPixmap(60*tile_x,60*tile_y,60,60,Carpet1x1_1_21_g);
                              }
                        } }


                }

            }

            }


        }
    //--------------------------------------------------------------------------------------------------------------------------------------
    // THEN WORK WITH RIGHT PANEL

    // ActionPoints Left
    NewPicPtr.drawPixmap(780,360,180,60,AcP_left);

    if(step_status==1)
    {
    if(wolf_actionpoints_left%10==0)
        NewPicPtr.drawPixmap(900,420,60,60,num0);
    if(wolf_actionpoints_left%10==1)
        NewPicPtr.drawPixmap(900,420,60,60,num1);
    if(wolf_actionpoints_left%10==2)
        NewPicPtr.drawPixmap(900,420,60,60,num2);
    if(wolf_actionpoints_left%10==3)
        NewPicPtr.drawPixmap(900,420,60,60,num3);
    if(wolf_actionpoints_left%10==4)
        NewPicPtr.drawPixmap(900,420,60,60,num4);
    if(wolf_actionpoints_left%10==5)
        NewPicPtr.drawPixmap(900,420,60,60,num5);
    if(wolf_actionpoints_left%10==6)
        NewPicPtr.drawPixmap(900,420,60,60,num6);
    if(wolf_actionpoints_left%10==7)
        NewPicPtr.drawPixmap(900,420,60,60,num7);
    if(wolf_actionpoints_left%10==8)
        NewPicPtr.drawPixmap(900,420,60,60,num8);
    if(wolf_actionpoints_left%10==9)
        NewPicPtr.drawPixmap(900,420,60,60,num9);

    if(wolf_actionpoints_left>9)
    {
        if((int)(floor((float)(wolf_actionpoints_left)/10)) % 10==1)
            NewPicPtr.drawPixmap(840,420,60,60,num1);
        if((int)(floor((float)(wolf_actionpoints_left)/10)) % 10==2)
            NewPicPtr.drawPixmap(840,420,60,60,num2);
        if((int)(floor((float)(wolf_actionpoints_left)/10)) % 10==3)
            NewPicPtr.drawPixmap(840,420,60,60,num3);
        if((int)(floor((float)(wolf_actionpoints_left)/10)) % 10==4)
            NewPicPtr.drawPixmap(840,420,60,60,num4);
        if((int)(floor((float)(wolf_actionpoints_left)/10)) % 10==5)
            NewPicPtr.drawPixmap(840,420,60,60,num5);
        if((int)(floor((float)(wolf_actionpoints_left)/10)) % 10==6)
            NewPicPtr.drawPixmap(840,420,60,60,num6);
        if((int)(floor((float)(wolf_actionpoints_left)/10)) % 10==7)
            NewPicPtr.drawPixmap(840,420,60,60,num7);
        if((int)(floor((float)(wolf_actionpoints_left)/10)) % 10==8)
            NewPicPtr.drawPixmap(840,420,60,60,num8);
        if((int)(floor((float)(wolf_actionpoints_left)/10)) % 10==9)
            NewPicPtr.drawPixmap(840,420,60,60,num9);
    }
    else
    {
        NewPicPtr.drawPixmap(840,420,60,60,darkgreensquare);
    }
    }


    if(step_status==3)
    {
    if(goat_actionpoints_left[chosengoat]%10==0)
        NewPicPtr.drawPixmap(900,420,60,60,num0);
    if(goat_actionpoints_left[chosengoat]%10==1)
        NewPicPtr.drawPixmap(900,420,60,60,num1);
    if(goat_actionpoints_left[chosengoat]%10==2)
        NewPicPtr.drawPixmap(900,420,60,60,num2);
    if(goat_actionpoints_left[chosengoat]%10==3)
        NewPicPtr.drawPixmap(900,420,60,60,num3);
    if(goat_actionpoints_left[chosengoat]%10==4)
        NewPicPtr.drawPixmap(900,420,60,60,num4);
    if(goat_actionpoints_left[chosengoat]%10==5)
        NewPicPtr.drawPixmap(900,420,60,60,num5);
    if(goat_actionpoints_left[chosengoat]%10==6)
        NewPicPtr.drawPixmap(900,420,60,60,num6);
    if(goat_actionpoints_left[chosengoat]%10==7)
        NewPicPtr.drawPixmap(900,420,60,60,num7);
    if(goat_actionpoints_left[chosengoat]%10==8)
        NewPicPtr.drawPixmap(900,420,60,60,num8);
    if(goat_actionpoints_left[chosengoat]%10==9)
        NewPicPtr.drawPixmap(900,420,60,60,num9);

    if(goat_actionpoints_left[chosengoat]>9)
    {
        if((int)(floor((float)(goat_actionpoints_left[chosengoat])/10)) % 10==1)
            NewPicPtr.drawPixmap(840,420,60,60,num1);
        if((int)(floor((float)(goat_actionpoints_left[chosengoat])/10)) % 10==2)
            NewPicPtr.drawPixmap(840,420,60,60,num2);
        if((int)(floor((float)(goat_actionpoints_left[chosengoat])/10)) % 10==3)
            NewPicPtr.drawPixmap(840,420,60,60,num3);
        if((int)(floor((float)(goat_actionpoints_left[chosengoat])/10)) % 10==4)
            NewPicPtr.drawPixmap(840,420,60,60,num4);
        if((int)(floor((float)(goat_actionpoints_left[chosengoat])/10)) % 10==5)
            NewPicPtr.drawPixmap(840,420,60,60,num5);
        if((int)(floor((float)(goat_actionpoints_left[chosengoat])/10)) % 10==6)
            NewPicPtr.drawPixmap(840,420,60,60,num6);
        if((int)(floor((float)(goat_actionpoints_left[chosengoat])/10)) % 10==7)
            NewPicPtr.drawPixmap(840,420,60,60,num7);
        if((int)(floor((float)(goat_actionpoints_left[chosengoat])/10)) % 10==8)
            NewPicPtr.drawPixmap(840,420,60,60,num8);
        if((int)(floor((float)(goat_actionpoints_left[chosengoat])/10)) % 10==9)
            NewPicPtr.drawPixmap(840,420,60,60,num9);
    }
    else
    {
        NewPicPtr.drawPixmap(840,420,60,60,darkgreensquare);
    }
    }
    if(step_status==1)
        NewPicPtr.drawPixmap(780,420,60,60,darkgreenwolf);//TBC
    if(step_status==3)
        NewPicPtr.drawPixmap(780,420,60,60,darkgreengoat);

    // TURNS LEFT
    if(step_status==1 || step_status==3)
    {
        NewPicPtr.drawPixmap(780,0,180,60,TrL);
        if(turns_left % 10 == 0)
        {
            NewPicPtr.drawPixmap(900,60,60,60,num0);
        }
        if(turns_left % 10 == 1)
        {
            NewPicPtr.drawPixmap(900,60,60,60,num1);
        }
        if(turns_left % 10 == 2)
        {
            NewPicPtr.drawPixmap(900,60,60,60,num2);
        }
        if(turns_left % 10 == 3)
        {
            NewPicPtr.drawPixmap(900,60,60,60,num3);
        }
        if(turns_left % 10 == 4)
        {
            NewPicPtr.drawPixmap(900,60,60,60,num4);
        }
        if(turns_left % 10 == 5)
        {
            NewPicPtr.drawPixmap(900,60,60,60,num5);
        }
        if(turns_left % 10 == 6)
        {
            NewPicPtr.drawPixmap(900,60,60,60,num6);
        }
        if(turns_left % 10 == 7)
        {
            NewPicPtr.drawPixmap(900,60,60,60,num7);
        }
        if(turns_left % 10 == 8)
        {
            NewPicPtr.drawPixmap(900,60,60,60,num8);
        }
        if(turns_left % 10 == 9)
        {
            NewPicPtr.drawPixmap(900,60,60,60,num9);
        }


        if(turns_left>9)
        {
            if(turns_left/10 % 10 == 0)
            {
                NewPicPtr.drawPixmap(840,60,60,60,num0);
            }
            if(turns_left/10 % 10 == 1)
            {
                NewPicPtr.drawPixmap(840,60,60,60,num1);
            }
            if(turns_left/10 % 10 == 2)
            {
                NewPicPtr.drawPixmap(840,60,60,60,num2);
            }
            if(turns_left/10 % 10 == 3)
            {
                NewPicPtr.drawPixmap(840,60,60,60,num3);
            }
            if(turns_left/10 % 10 == 4)
            {
                NewPicPtr.drawPixmap(840,60,60,60,num4);
            }
            if(turns_left/10 % 10 == 5)
            {
                NewPicPtr.drawPixmap(840,60,60,60,num5);
            }
            if(turns_left/10 % 10 == 6)
            {
                NewPicPtr.drawPixmap(840,60,60,60,num6);
            }
            if(turns_left/10 % 10 == 7)
            {
                NewPicPtr.drawPixmap(840,60,60,60,num7);
            }
            if(turns_left/10 % 10 == 8)
            {
                NewPicPtr.drawPixmap(840,60,60,60,num8);
            }
            if(turns_left/10 % 10 == 9)
            {
                NewPicPtr.drawPixmap(840,60,60,60,num9);
            }

            if(turns_left>99)
            {
                if(turns_left/100 % 10 == 0)
                {
                    NewPicPtr.drawPixmap(780,60,60,60,num0);
                }
                if(turns_left/100 % 10 == 1)
                {
                    NewPicPtr.drawPixmap(780,60,60,60,num1);
                }
                if(turns_left/100 % 10 == 2)
                {
                    NewPicPtr.drawPixmap(780,60,60,60,num2);
                }
                if(turns_left/100 % 10 == 3)
                {
                    NewPicPtr.drawPixmap(780,60,60,60,num3);
                }
                if(turns_left/100 % 10 == 4)
                {
                    NewPicPtr.drawPixmap(780,60,60,60,num4);
                }
                if(turns_left/100 % 10 == 5)
                {
                    NewPicPtr.drawPixmap(780,60,60,60,num5);
                }
                if(turns_left/100 % 10 == 6)
                {
                    NewPicPtr.drawPixmap(780,60,60,60,num6);
                }
                if(turns_left/100 % 10 == 7)
                {
                    NewPicPtr.drawPixmap(780,60,60,60,num7);
                }
                if(turns_left/100 % 10 == 8)
                {
                    NewPicPtr.drawPixmap(780,60,60,60,num8);
                }
                if(turns_left/100 % 10 == 9)
                {
                    NewPicPtr.drawPixmap(780,60,60,60,num9);
                }
            }
            else
            {
                NewPicPtr.drawPixmap(780,60,60,60,darkgreensquare);
            }


        }
        else
        {
            NewPicPtr.drawPixmap(840,60,60,60,darkgreensquare);
            NewPicPtr.drawPixmap(780,60,60,60,darkgreensquare);
        }
    }
    if(step_status==1)
    {
        if(stealthmode)
        {
            NewPicPtr.drawPixmap(780,300,180,60,stealthmode_on);
        }
        else
        {
            NewPicPtr.drawPixmap(780,300,180,60,stealthmode_off);
        }


    }

    /*
    if(step_status==1||step_status==3)
    {
        NewPicPtr.drawPixmap(780,480,60,60,darkgreensquare);
        NewPicPtr.drawPixmap(840,480,60,60,darkgreensquare);
        NewPicPtr.drawPixmap(900,480,60,60,darkgreensquare);
        NewPicPtr.drawPixmap(780,120,60,60,darkgreensquare);
        NewPicPtr.drawPixmap(840,120,60,60,darkgreensquare);
        NewPicPtr.drawPixmap(900,120,60,60,darkgreensquare);
        NewPicPtr.drawPixmap(780,180,60,60,darkgreensquare);
        NewPicPtr.drawPixmap(840,180,60,60,darkgreensquare);
        NewPicPtr.drawPixmap(900,180,60,60,darkgreensquare);
        NewPicPtr.drawPixmap(780,240,60,60,darkgreensquare);
        NewPicPtr.drawPixmap(840,240,60,60,darkgreensquare);
        NewPicPtr.drawPixmap(900,240,60,60,darkgreensquare);
    }
    */








    // STATUS!
    NewPicPtr.drawPixmap(780,120,180,180,bigbgsquare);
    if((step_status==1||step_status==3) && game_is_active)
    {

      if(eventstatus==0) // NOTHING IS GOING ON
      {

        if(variation%7==0)
        {
           if(step_status==1)
            ui->StatusLabel->setText("Master,bite \nthis sassy goat!");
           else
            ui->StatusLabel->setText("To be eaten or\n not to be eaten,\n that is the \nquestion...");
        }
        if(variation%7==1)
        {
           if(step_status==1)
            ui->StatusLabel->setText("The Big Bad Wolf.\nThe Big Bad Wolf.");
           else
            ui->StatusLabel->setText("The Big Bad Wolf\n on the horizon!");
        }
        if(variation%7==2)
        {
           if(step_status==1)
            ui->StatusLabel->setText("There's always a \nbigger fish");
           else
            ui->StatusLabel->setText("He is watching \nyou!");
        }
        if(variation%7==3)
        {
            ui->StatusLabel->setText("Good weather \ntoday!");
        }
        if(variation%7==4)
        {
           if(step_status==1)
            ui->StatusLabel->setText("They are not \naware of \nanything");
           else
            ui->StatusLabel->setText("You aren't alone \nin this map...");
        }
        if(variation%7==5)
        {
           if(step_status==1)
            ui->StatusLabel->setText("Let's rock!");
           else
            ui->StatusLabel->setText("The hills have \neyes...");
        }
        if(variation%7==6)
        {
            if(step_status==1)
             ui->StatusLabel->setText("Have you ever \nthought that \nkilling is bad?");
            else
             ui->StatusLabel->setText("Life is worth \nbeing eaten");
        }

      }
      if(eventstatus==1) // IsStandable returned false
      {

          if(variation%3==0)
          {
               ui->StatusLabel->setText("Keep banging \nyour head against \nthe wall, it seems \nto work really well");
          }
          if(variation%3==1)
          {
               ui->StatusLabel->setText("Obstacle on \nthe way!");
          }
          if(variation%3==2)
          {
               ui->StatusLabel->setText("You have no \npower here...\nagainst the wall");
          }
      }
      if(eventstatus==4) // To deep pit(32)
      {
          if(variation%2==0)
          {
               ui->StatusLabel->setText("You can't \ngo deeper!");
          }
          if(variation%2==1)
          {
               ui->StatusLabel->setText("Depth of the \nhole more than \nyour height");
          }
      }
      if(eventstatus==3) // No Actionpoints
      {

          if(variation%2==0)
          {
               ui->StatusLabel->setText("You are too tired!\nCome back \nnext time");
          }
          if(variation%2==1)
          {
               ui->StatusLabel->setText("Already \nexhausted?\nI told you that\n smoking will \nharm you!");
          }

      }
      if(eventstatus==2)
      {
          ui->StatusLabel->setText("Can't dig here!");
      }
      if(eventstatus==5)
      {
          ui->StatusLabel->setText( (QString("Pit dug!Now it's \ndepth is ") + QString::number(map_surfaces_state[goat_pos_x[chosengoat]][goat_pos_y[chosengoat]])));
      }
      if(eventstatus==6)
      {

          if(variation%4==0)
          {
              ui->StatusLabel->setText("Pretty tasty goat!");
          }
          if(variation%4==1)
          {
              ui->StatusLabel->setText("Only horns and \nlegs remained");
          }
          if(variation%4==2)
          {
              ui->StatusLabel->setText("Astrologers \nannounced the \nweek of dead kids");
          }
          if(variation%4==3)
          {
              ui->StatusLabel->setText("It might be a \ngood slasher");
          }
      }
      if(eventstatus==7)
      {

          if(variation%3==0)
          {
              ui->StatusLabel->setText("Everyone fails \nsometimes");
          }
          if(variation%3==1)
          {
              ui->StatusLabel->setText("Come on!\nThey are only kids");
          }
          if(variation%3==2)
          {
              ui->StatusLabel->setText("Well, at least \nsuch a bad hunter,\n as you will never \nbe accused of \nkilling kids");
          }
      }
      if(eventstatus==8)
      {
          if(variation%3==0)
          {
              ui->StatusLabel->setText("Good news: you \nate a goat, \nbad news: you are \ntrapped in a pit");
          }
          if(variation%3==1)
          {
              ui->StatusLabel->setText("You fallen down \ninto a pit.\nDon't worry, you \nkilled a kid so \nyou have \nsomething to eat \nfor the first time");
          }
      }
      if(eventstatus==9)
      {
          if(variation%2==0)
          {
               ui->StatusLabel->setText("And the hunter \nbecomes the \nhunted.They put \nyou in a trap!");
          }
          if(variation%2==1)
          {
              ui->StatusLabel->setText("You stepped into \na pit!");
          }
      }

    }
    else
    {
        ui->StatusLabel->setText("");
    }


    // GOAT NAME
    if(step_status==3)
    {
    NewPicPtr.drawPixmap(780,300,180,60,bgsquare180x60);
    ui->GoatNameLabel->setText(goatnames[chosengoat]);
    }
    else
    {
        ui->GoatNameLabel->setText("");
    }

    // THEN DRAW A FRAME AROUND ALL OF SCREEN


    if(IsFrame)
    {
        NewPicPtr.drawPixmap(0,0,40,36,FrameElement1);
        NewPicPtr.drawPixmap(40,0,920,13,FrameElement2);
        NewPicPtr.drawPixmap(0,36,11,504,FrameElement3);
        NewPicPtr.drawPixmap(11,527,949,13,FrameElement4);
        NewPicPtr.drawPixmap(771,13,10,515,FrameElement5);
        NewPicPtr.drawPixmap(781,480,179,47,FrameElement6);
        NewPicPtr.drawPixmap(958,13,2,467,FrameElement7);
        NewPicPtr.drawPixmap(781,120,177,2,FrameElement8);
        NewPicPtr.drawPixmap(781,300,177,2,FrameElement9);
        NewPicPtr.drawPixmap(781,360,177,2,FrameElement10);
        NewPicPtr.drawPixmap(11,36,2,63,FrameElement11);
        NewPicPtr.drawPixmap(40,13,50,2,FrameElement12);
        NewPicPtr.drawPixmap(90,13,4,1,FrameElement13);
        NewPicPtr.drawPixmap(13,36,26,2,FrameElement14);
        NewPicPtr.drawPixmap(13,38,22,4,FrameElement15);
        NewPicPtr.drawPixmap(13,42,3,6,FrameElement16);
        NewPicPtr.drawPixmap(19,42,14,1,FrameElement17);
        NewPicPtr.drawPixmap(22,43,8,1,FrameElement18);
        NewPicPtr.drawPixmap(40,15,9,2,FrameElement19);
        NewPicPtr.drawPixmap(42,17,7,1,FrameElement20);
        NewPicPtr.drawPixmap(43,18,7,1,FrameElement21);
        NewPicPtr.drawPixmap(40,21,2,12,FrameElement22);
        NewPicPtr.drawPixmap(42,25,1,6,FrameElement23);
        NewPicPtr.drawPixmap(40,19,1,2,FrameElement24);
        NewPicPtr.drawPixmap(40,33,1,2,FrameElement25);
        NewPicPtr.drawPixmap(35,38,2,2,FrameElement26);
        NewPicPtr.drawPixmap(48,19,3,8,FrameElement27);
        NewPicPtr.drawPixmap(54,15,3,7,FrameElement28);
        NewPicPtr.drawPixmap(11,498,24,29,FrameElement29);
        NewPicPtr.drawPixmap(11,441,2,57,FrameElement30);
        NewPicPtr.drawPixmap(35,502,4,25,FrameElement31);
        NewPicPtr.drawPixmap(39,505,2,16,FrameElement32);
        NewPicPtr.drawPixmap(768,441,3,86,FrameElement33);
        NewPicPtr.drawPixmap(746,498,22,29,FrameElement34);
        NewPicPtr.drawPixmap(768,13,3,86,FrameElement35);
        NewPicPtr.drawPixmap(741,13,27,23,FrameElement36);
        NewPicPtr.drawPixmap(59,15,6,2,FrameElement37);
        NewPicPtr.drawPixmap(60,17,5,1,FrameElement38);
        NewPicPtr.drawPixmap(61,18,5,3,FrameElement39);
        NewPicPtr.drawPixmap(66,19,6,4,FrameElement40);
        NewPicPtr.drawPixmap(84,15,5,5,FrameElement41);
        NewPicPtr.drawPixmap(83,20,4,2,FrameElement42);
        NewPicPtr.drawPixmap(13,53,3,6,FrameElement43);
        NewPicPtr.drawPixmap(13,63,5,3,FrameElement44);
        NewPicPtr.drawPixmap(13,88,5,3,FrameElement45);
        NewPicPtr.drawPixmap(18,67,4,6,FrameElement46);
        NewPicPtr.drawPixmap(18,85,2,4,FrameElement47);
        NewPicPtr.drawPixmap(17,84,2,1,FrameElement48);
        NewPicPtr.drawPixmap(18,89,1,1,FrameElement49);
        NewPicPtr.drawPixmap(52,15,2,3,FrameElement50);
        NewPicPtr.drawPixmap(16,49,11,2,FrameElement51);
        NewPicPtr.drawPixmap(13,77,2,5,FrameElement52);
        NewPicPtr.drawPixmap(16,55,3,4,FrameElement53);
        NewPicPtr.drawPixmap(16,73,4,2,FrameElement54);
        NewPicPtr.drawPixmap(15,75,2,3,FrameElement55);
        NewPicPtr.drawPixmap(18,65,2,2,FrameElement56);
        NewPicPtr.drawPixmap(64,21,2,2,FrameElement57);
        NewPicPtr.drawPixmap(16,46,2,2,FrameElement58);
        NewPicPtr.drawPixmap(25,47,2,2,FrameElement59);
        NewPicPtr.drawPixmap(72,19,2,2,FrameElement60);
        NewPicPtr.drawPixmap(19,52,6,1,FrameElement61);
        NewPicPtr.drawPixmap(17,51,9,1,FrameElement62);
        NewPicPtr.drawPixmap(13,82,1,3,FrameElement63);
        NewPicPtr.drawPixmap(65,23,5,1,FrameElement64);
        NewPicPtr.drawPixmap(74,19,1,1,FrameElement65);
        NewPicPtr.drawPixmap(73,18,3,1,FrameElement66);
        NewPicPtr.drawPixmap(74,17,3,1,FrameElement67);
        NewPicPtr.drawPixmap(75,16,3,1,FrameElement68);
        NewPicPtr.drawPixmap(76,15,8,1,FrameElement69);
        NewPicPtr.drawPixmap(72,21,1,1,FrameElement70);
    }







    ui->MainWidget->setPixmap(NewPic);
}

//------------------------------------------------------------------------------------------------------------------------------
//GAME LOAD


//------------------------------------------------------------------------------------------------------------------------------
BigBadWolf::BigBadWolf(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BigBadWolf),
    map_surfaces(0),
      BMP1( (strPath+QString("StartPicture_1.bmp")).toLocal8Bit().constData() ),
      BMP2( (strPath+QString("StartPicture_2.bmp")).toLocal8Bit().constData() ),
      BMP3( (strPath+QString("StartPicture_3.bmp")).toLocal8Bit().constData() ),
      BMP4( (strPath+QString("StartPicture_4.bmp")).toLocal8Bit().constData() ),
      mapsize_x(0),
      mapsize_y(0),
      game_is_active(false),
      WolfTest1_Green( (strPath+QString("1_w.bmp")).toLocal8Bit().constData() ),
      WolfTest1_Black( (strPath+QString("2_w.bmp")).toLocal8Bit().constData() ),
      TerrainTest1_Green( (strPath+QString("1.bmp")).toLocal8Bit().constData() ), // code 1
      TerrainTest1_Black( (strPath+QString("2.bmp")).toLocal8Bit().constData() ), // code 2
      GoatTest1_Green( (strPath+QString("1_g.png")).toLocal8Bit().constData() ),
      GoatTest1_Black( (strPath+QString("2_g.png")).toLocal8Bit().constData() ),
      ObstalceTest1( (strPath+QString("0_obst.bmp")).toLocal8Bit().constData() ), // code 0, obst
      ObstalceTest1_f( (strPath+QString("0_obst_f.bmp")).toLocal8Bit().constData() ), // code 0, obst

      //--------------------------------------------------------------------------------------------------------------
      //GROUNDS
      GrassAndTree1_10( (strPath+QString("10_GrassAndTree.bmp")).toLocal8Bit().constData() ), // code 10, obst
      Grass1_11( (strPath+QString("11_Grass1.bmp")).toLocal8Bit().constData() ), // code 11
      Grass2_12( (strPath+QString("12_Grass2.bmp")).toLocal8Bit().constData() ), // code 12
      Grass3_13( (strPath+QString("13_Grass3.bmp")).toLocal8Bit().constData() ), // code 13
      GrassPath2x1WatchingUpLeft1_14( (strPath+QString("14_GrassPath2x1_WatchingUp_LeftPart.bmp")).toLocal8Bit().constData() ), // code 14
      GrassPath2x1WatchingUpRight1_15( (strPath+QString("15_GrassPath2x1_WatchingUp_RightPart.bmp")).toLocal8Bit().constData() ), // code 15
      GrassPath1x1WatchingLeft2_16( (strPath+QString("16_GrassPath1x1_WatchingLeft.bmp")).toLocal8Bit().constData() ), // code 16
      GrassPath1x1WatchingLeft3_17( (strPath+QString("17_GrassPath1x1_WatchingUp.bmp")).toLocal8Bit().constData() ), // code 17
      GrassWithoutPath1x1_1_18( (strPath+QString("18_PathWithoutGrass1x1.bmp")).toLocal8Bit().constData() ), // code 18
      WoodenParquet1x1_1_19( (strPath+QString("19_WoodParquet1.png")).toLocal8Bit().constData() ), // code 19
      WoodenParquet1x1_2_20( (strPath+QString("20_WoodParquet2.png")).toLocal8Bit().constData() ), // code 20
      Carpet1x1_1_21( (strPath+QString("21_Carpet1FF1.png")).toLocal8Bit().constData() ), // code 21
      BedOnACarpet1_22( (strPath+QString("22_Carpet1FF1Bed.png")).toLocal8Bit().constData() ), // code 22, obst
      GrassAndTree2_23( (strPath+QString("23_Grass2AndTree.bmp")).toLocal8Bit().constData() ), // code 23, obst
      Grass2FenceFaceFull_24( (strPath+QString("24_Grass2Fence_Face.bmp")).toLocal8Bit().constData() ), // code 24, obst
      Grass2FenceSideLeft_25( (strPath+QString("25_Grass2Fence_Side_Left.bmp")).toLocal8Bit().constData() ), // code 25, obst
      Grass2FenceSideRight_26( (strPath+QString("26_Grass2Fence_Side_Right.bmp")).toLocal8Bit().constData() ), // code 26, obst
      Grass2FenceFaceLeftEnd_27( (strPath+QString("27_Grass2FenceFace_LeftEnded.bmp")).toLocal8Bit().constData() ), // code 27, obst
      Grass2FenceFaceRightEnd_28( (strPath+QString("28_Grass2FenceFace_RightEnded.bmp")).toLocal8Bit().constData() ), // code 28, obst

      //--------------------------------------------------------------------------------------------------------------
      //FOGGED GROUNDS
      GrassAndTree1_10_f( (strPath+QString("10_GrassAndTree_f.bmp")).toLocal8Bit().constData() ), // code 10, obst
      Grass1_11_f( (strPath+QString("11_Grass1_f.bmp")).toLocal8Bit().constData() ), // code 11
      Grass2_12_f( (strPath+QString("12_Grass2_f.bmp")).toLocal8Bit().constData() ), // code 12
      Grass3_13_f( (strPath+QString("13_Grass3_f.bmp")).toLocal8Bit().constData() ), // code 13
      GrassPath2x1WatchingUpLeft1_14_f( (strPath+QString("14_GrassPath2x1_WatchingUp_LeftPart_f.bmp")).toLocal8Bit().constData() ), // code 14
      GrassPath2x1WatchingUpRight1_15_f( (strPath+QString("15_GrassPath2x1_WatchingUp_RightPart_f.bmp")).toLocal8Bit().constData() ), // code 15
      GrassPath1x1WatchingLeft2_16_f( (strPath+QString("16_GrassPath1x1_WatchingLeft_f.bmp")).toLocal8Bit().constData() ), // code 16
      GrassPath1x1WatchingLeft3_17_f( (strPath+QString("17_GrassPath1x1_WatchingUp_f.bmp")).toLocal8Bit().constData() ), // code 17
      GrassWithoutPath1x1_1_18_f( (strPath+QString("18_PathWithoutGrass1x1_f.bmp")).toLocal8Bit().constData() ), // code 18
      WoodenParquet1x1_1_19_f( (strPath+QString("19_WoodParquet1_f.png")).toLocal8Bit().constData() ), // code 19
      WoodenParquet1x1_2_20_f( (strPath+QString("20_WoodParquet2_f.png")).toLocal8Bit().constData() ), // code 20
      Carpet1x1_1_21_f( (strPath+QString("21_Carpet1FF1_f.png")).toLocal8Bit().constData() ), // code 21
      BedOnACarpet1_22_f( (strPath+QString("22_Carpet1FF1Bed_f.png")).toLocal8Bit().constData() ), // code 22, obst
      GrassAndTree2_23_f( (strPath+QString("23_Grass2AndTree_f.bmp")).toLocal8Bit().constData() ), // code 23, obst
      Grass2FenceFaceFull_24_f( (strPath+QString("24_Grass2Fence_Face_f.bmp")).toLocal8Bit().constData() ), // code 24, obst
      Grass2FenceSideLeft_25_f( (strPath+QString("25_Grass2Fence_Side_Left_f.bmp")).toLocal8Bit().constData() ), // code 25, obst
      Grass2FenceSideRight_26_f( (strPath+QString("26_Grass2Fence_Side_Right_f.bmp")).toLocal8Bit().constData() ), // code 26, obst
      Grass2FenceFaceLeftEnd_27_f( (strPath+QString("27_Grass2FenceFace_LeftEnded_f.bmp")).toLocal8Bit().constData() ), // code 27, obst
      Grass2FenceFaceRightEnd_28_f( (strPath+QString("28_Grass2FenceFace_RightEnded_f.bmp")).toLocal8Bit().constData() ), // code 28, obst

      //--------------------------------------------------------------------------------------------------------------
      // GROUNDS WITH WOLF
      Grass1_11_w( (strPath+QString("11_Grass1_w.bmp")).toLocal8Bit().constData() ), // code 11
      Grass2_12_w( (strPath+QString("12_Grass2_w.bmp")).toLocal8Bit().constData() ),// code 12
      Grass3_13_w( (strPath+QString("13_Grass3_w.bmp")).toLocal8Bit().constData() ), // code 13
      GrassPath2x1WatchingUpLeft1_14_w( (strPath+QString("14_GrassPath2x1_WatchingUp_LeftPart_w.bmp")).toLocal8Bit().constData() ), // code 14
      GrassPath2x1WatchingUpRight1_15_w( (strPath+QString("15_GrassPath2x1_WatchingUp_RightPart_w.bmp")).toLocal8Bit().constData() ), // code 15
      GrassPath1x1WatchingLeft2_16_w( (strPath+QString("16_GrassPath1x1_WatchingLeft_w.bmp")).toLocal8Bit().constData() ), // code 16
      GrassPath1x1WatchingLeft3_17_w( (strPath+QString("17_GrassPath1x1_WatchingUp_w.bmp")).toLocal8Bit().constData() ), // code 17
      GrassWithoutPath1x1_1_18_w( (strPath+QString("18_PathWithoutGrass1x1_w.bmp")).toLocal8Bit().constData() ), // code 18
      WoodenParquet1x1_1_19_w( (strPath+QString("19_WoodParquet1_w.png")).toLocal8Bit().constData() ), // code 19
      WoodenParquet1x1_2_20_w( (strPath+QString("20_WoodParquet2_w.png")).toLocal8Bit().constData() ), // code 20
      Carpet1x1_1_21_w( (strPath+QString("21_Carpet1FF1_w.png")).toLocal8Bit().constData() ), // code 21

      //--------------------------------------------------------------------------------------------------------------
      // GROUNDS WITH GOAT
      Grass1_11_g( (strPath+QString("11_Grass1_g.bmp")).toLocal8Bit().constData() ), // code 11
      Grass2_12_g( (strPath+QString("12_Grass2_g.bmp")).toLocal8Bit().constData() ), // code 12
      Grass3_13_g( (strPath+QString("13_Grass3_g.bmp")).toLocal8Bit().constData() ), // code 13
      GrassPath2x1WatchingUpLeft1_14_g( (strPath+QString("14_GrassPath2x1_WatchingUp_LeftPart_g.bmp")).toLocal8Bit().constData() ), // code 14
      GrassPath2x1WatchingUpRight1_15_g( (strPath+QString("15_GrassPath2x1_WatchingUp_RightPart_g.bmp")).toLocal8Bit().constData() ), // code 15
      GrassPath1x1WatchingLeft2_16_g( (strPath+QString("16_GrassPath1x1_WatchingLeft_g.bmp")).toLocal8Bit().constData() ), // code 16
      GrassPath1x1WatchingLeft3_17_g( (strPath+QString("17_GrassPath1x1_WatchingUp_g.bmp")).toLocal8Bit().constData() ), // code 17
      GrassWithoutPath1x1_1_18_g( (strPath+QString("18_PathWithoutGrass1x1_g.bmp")).toLocal8Bit().constData() ), // code 18
      WoodenParquet1x1_1_19_g( (strPath+QString("19_WoodParquet1_g.png")).toLocal8Bit().constData() ), // code 19
      WoodenParquet1x1_2_20_g( (strPath+QString("20_WoodParquet2_g.png")).toLocal8Bit().constData() ), // code 20
      Carpet1x1_1_21_g( (strPath+QString("21_Carpet1FF1_g.png")).toLocal8Bit().constData() ), // code 21
      //--------------------------------------------------------------------------------------------------------------
      // FRAME ELEMENTS

      FrameElement1( (strPath+QString("/frame/frame_el1_0a0_40x36")).toLocal8Bit().constData() ),
      FrameElement2( (strPath+QString("/frame/frame_el2_40a0_920x13")).toLocal8Bit().constData() ),
      FrameElement3( (strPath+QString("/frame/frame_el3_0a36_11x504")).toLocal8Bit().constData() ),
      FrameElement4( (strPath+QString("/frame/frame_el4_11a527_949x13")).toLocal8Bit().constData() ),
      FrameElement5( (strPath+QString("/frame/frame_el5_777a13_10x515")).toLocal8Bit().constData() ),
      FrameElement6( (strPath+QString("/frame/frame_el6_781a480_179x47")).toLocal8Bit().constData() ),
      FrameElement7( (strPath+QString("/frame/frame_el7_958a13_2x467")).toLocal8Bit().constData() ),
      FrameElement8( (strPath+QString("/frame/frame_el8_781a120_177x2")).toLocal8Bit().constData() ),
      FrameElement9( (strPath+QString("/frame/frame_el9_781a300_177x2")).toLocal8Bit().constData() ),
      FrameElement10( (strPath+QString("/frame/frame_el10_781a360_177x2")).toLocal8Bit().constData() ),
      FrameElement11( (strPath+QString("/frame/frame_el11_11a36_2x63")).toLocal8Bit().constData() ),
      FrameElement12( (strPath+QString("/frame/frame_el12_40a13_50x2")).toLocal8Bit().constData() ),
      FrameElement13( (strPath+QString("/frame/frame_el13_90a13_4x1")).toLocal8Bit().constData() ),
      FrameElement14( (strPath+QString("/frame/frame_el14_13a36_26x2")).toLocal8Bit().constData() ),
      FrameElement15( (strPath+QString("/frame/frame_el15_13a38_22x4")).toLocal8Bit().constData() ),
      FrameElement16( (strPath+QString("/frame/frame_el16_13a42_3x6")).toLocal8Bit().constData() ),
      FrameElement17( (strPath+QString("/frame/frame_el17_19a42_14x1")).toLocal8Bit().constData() ),
      FrameElement18( (strPath+QString("/frame/frame_el18_22a43_8x1")).toLocal8Bit().constData() ),
      FrameElement19( (strPath+QString("/frame/frame_el19_40a15_9x2")).toLocal8Bit().constData() ),
      FrameElement20( (strPath+QString("/frame/frame_el20_42a17_7x1")).toLocal8Bit().constData() ),
      FrameElement21( (strPath+QString("/frame/frame_el21_43a18_7x1")).toLocal8Bit().constData() ),
      FrameElement22( (strPath+QString("/frame/frame_el22_40a21_2x12")).toLocal8Bit().constData() ),
      FrameElement23( (strPath+QString("/frame/frame_el23_42a25_1x6")).toLocal8Bit().constData() ),
      FrameElement24( (strPath+QString("/frame/frame_el24_40a19_1x2")).toLocal8Bit().constData() ),
      FrameElement25( (strPath+QString("/frame/frame_el25_40a33_1x2")).toLocal8Bit().constData() ),
      FrameElement26( (strPath+QString("/frame/frame_el26_35a38_2x2")).toLocal8Bit().constData() ),
      FrameElement27( (strPath+QString("/frame/frame_el27_48a19_1x2")).toLocal8Bit().constData() ),
      FrameElement28( (strPath+QString("/frame/frame_el28_54a15_3x7")).toLocal8Bit().constData() ),
      FrameElement29( (strPath+QString("/frame/frame_el29_11a498_24x29")).toLocal8Bit().constData() ),
      FrameElement30( (strPath+QString("/frame/frame_el30_11a441_2x57")).toLocal8Bit().constData() ),
      FrameElement31( (strPath+QString("/frame/frame_el31_35a502_4x25")).toLocal8Bit().constData() ),
      FrameElement32( (strPath+QString("/frame/frame_el32_39a505_2x16")).toLocal8Bit().constData() ),
      FrameElement33( (strPath+QString("/frame/frame_el33_768a441_3x86")).toLocal8Bit().constData() ),
      FrameElement34( (strPath+QString("/frame/frame_el34_746a498_22x29")).toLocal8Bit().constData() ),
      FrameElement35( (strPath+QString("/frame/frame_el35_768a13_3x86")).toLocal8Bit().constData() ),
      FrameElement36( (strPath+QString("/frame/frame_el36_741a13_27x23")).toLocal8Bit().constData() ),
      FrameElement37( (strPath+QString("/frame/frame_el37_59a15_6x2")).toLocal8Bit().constData() ),
      FrameElement38( (strPath+QString("/frame/frame_el38_60a17_5x1")).toLocal8Bit().constData() ),
      FrameElement39( (strPath+QString("/frame/frame_el39_61a18_5x3")).toLocal8Bit().constData() ),
      FrameElement40( (strPath+QString("/frame/frame_el40_66a19_6x4")).toLocal8Bit().constData() ),
      FrameElement41( (strPath+QString("/frame/frame_el41_84a15_5x5")).toLocal8Bit().constData() ),
      FrameElement42( (strPath+QString("/frame/frame_el42_83a20_4x2")).toLocal8Bit().constData() ),
      FrameElement43( (strPath+QString("/frame/frame_el43_13a53_3x6")).toLocal8Bit().constData() ),
      FrameElement44( (strPath+QString("/frame/frame_el44_13a63_5x3")).toLocal8Bit().constData() ),
      FrameElement45( (strPath+QString("/frame/frame_el45_13a88_5x3")).toLocal8Bit().constData() ),
      FrameElement46( (strPath+QString("/frame/frame_el46_18a67_4x6")).toLocal8Bit().constData() ),
      FrameElement47( (strPath+QString("/frame/frame_el47_18a85_2x4")).toLocal8Bit().constData() ),
      FrameElement48( (strPath+QString("/frame/frame_el48_17a84_2x1")).toLocal8Bit().constData() ),
      FrameElement49( (strPath+QString("/frame/frame_el49_18a89_1x1")).toLocal8Bit().constData() ),
      FrameElement50( (strPath+QString("/frame/frame_el50_52a15_2x3")).toLocal8Bit().constData() ),
      FrameElement51( (strPath+QString("/frame/frame_el51_16a49_11x2")).toLocal8Bit().constData() ),
      FrameElement52( (strPath+QString("/frame/frame_el52_13a77_2x5")).toLocal8Bit().constData() ),
      FrameElement53( (strPath+QString("/frame/frame_el53_16a55_3x4")).toLocal8Bit().constData() ),
      FrameElement54( (strPath+QString("/frame/frame_el54_16a73_4x2")).toLocal8Bit().constData() ),
      FrameElement55( (strPath+QString("/frame/frame_el55_15a75_2x3")).toLocal8Bit().constData() ),
      FrameElement56( (strPath+QString("/frame/frame_el56_18a65_2x2")).toLocal8Bit().constData() ),
      FrameElement57( (strPath+QString("/frame/frame_el57_64a21_2x2")).toLocal8Bit().constData() ),
      FrameElement58( (strPath+QString("/frame/frame_el58_16a46_2x2")).toLocal8Bit().constData() ),
      FrameElement59( (strPath+QString("/frame/frame_el59_25a47_2x2")).toLocal8Bit().constData() ),
      FrameElement60( (strPath+QString("/frame/frame_el60_72a19_2x2")).toLocal8Bit().constData() ),
      FrameElement61( (strPath+QString("/frame/frame_el61_19a52_6x1")).toLocal8Bit().constData() ),
      FrameElement62( (strPath+QString("/frame/frame_el62_17a51_9x1")).toLocal8Bit().constData() ),
      FrameElement63( (strPath+QString("/frame/frame_el63_13a82_1x3")).toLocal8Bit().constData() ),
      FrameElement64( (strPath+QString("/frame/frame_el64_65a23_5x1")).toLocal8Bit().constData() ),
      FrameElement65( (strPath+QString("/frame/frame_el65_74a19_1x1")).toLocal8Bit().constData() ),
      FrameElement66( (strPath+QString("/frame/frame_el66_73a18_3x1")).toLocal8Bit().constData() ),
      FrameElement67( (strPath+QString("/frame/frame_el67_74a17_3x1")).toLocal8Bit().constData() ),
      FrameElement68( (strPath+QString("/frame/frame_el68_75a16_3x1")).toLocal8Bit().constData() ),
      FrameElement69( (strPath+QString("/frame/frame_el69_76a15_8x1")).toLocal8Bit().constData() ),
      FrameElement70( (strPath+QString("/frame/frame_el70_72a21_1x1")).toLocal8Bit().constData() ),





      //--------------------------------------------------------------------------------------------------------------

      WSTS1( (strPath+QString("wsts1.bmp")).toLocal8Bit().constData() ),
      WSTS2( (strPath+QString("wsts2.bmp")).toLocal8Bit().constData() ),
      WSTS3( (strPath+QString("wsts3.bmp")).toLocal8Bit().constData() ),
      WSTS4( (strPath+QString("wsts4.bmp")).toLocal8Bit().constData() ),

      GSTS1( (strPath+QString("gsts1.bmp")).toLocal8Bit().constData() ),
      GSTS2( (strPath+QString("gsts2.bmp")).toLocal8Bit().constData() ),
      GSTS3( (strPath+QString("gsts3.bmp")).toLocal8Bit().constData() ),
      GSTS4( (strPath+QString("gsts4.bmp")).toLocal8Bit().constData() ),

      GWS1( ( (strPath+QString("gws1.bmp")).toLocal8Bit().constData() ) ),
      GWS2( ( (strPath+QString("gws2.bmp")).toLocal8Bit().constData() ) ),
      GWS3( ( (strPath+QString("gws3.bmp")).toLocal8Bit().constData() ) ),
      GWS4( ( (strPath+QString("gws4.bmp")).toLocal8Bit().constData() ) ),

      WWS1( ( (strPath+QString("wws1.bmp")).toLocal8Bit().constData() ) ),
      WWS2( ( (strPath+QString("wws2.bmp")).toLocal8Bit().constData() ) ),
      WWS3( ( (strPath+QString("wws3.bmp")).toLocal8Bit().constData() ) ),
      WWS4( ( (strPath+QString("wws4.bmp")).toLocal8Bit().constData() ) ),

      AcP_left ( (strPath+QString("actionpoints_left.bmp")).toLocal8Bit().constData() ),
      TrL ( (strPath+QString("turns_left.bmp")).toLocal8Bit().constData() ),


      num0( ( (strPath+QString("num0.bmp")).toLocal8Bit().constData() ) ),
      num1( ( (strPath+QString("num1.bmp")).toLocal8Bit().constData() ) ),
      num2( ( (strPath+QString("num2.bmp")).toLocal8Bit().constData() ) ),
      num3( ( (strPath+QString("num3.bmp")).toLocal8Bit().constData() ) ),
      num4( ( (strPath+QString("num4.bmp")).toLocal8Bit().constData() ) ),
      num5( ( (strPath+QString("num5.bmp")).toLocal8Bit().constData() ) ),
      num6( ( (strPath+QString("num6.bmp")).toLocal8Bit().constData() ) ),
      num7( ( (strPath+QString("num7.bmp")).toLocal8Bit().constData() ) ),
      num8( ( (strPath+QString("num8.bmp")).toLocal8Bit().constData() ) ),
      num9( ( (strPath+QString("num9.bmp")).toLocal8Bit().constData() ) ),
      darkgreensquare( ( (strPath+QString("green60x60.bmp")).toLocal8Bit().constData() ) ),
      darkgreenwolf( ( (strPath+QString("greenbg_wolf.bmp")).toLocal8Bit().constData() ) ),
      darkgreengoat( ( (strPath+QString("greenbg_goat.png")).toLocal8Bit().constData() ) ),
      bigbgsquare( ( (strPath+QString("BigBGSquare.png")).toLocal8Bit().constData() ) ),
      bgsquare180x60( ( (strPath+QString("BGSquare_180x60.png")).toLocal8Bit().constData() ) ),

      stealthmode_off( ( (strPath+QString("stealthmode_off.bmp")).toLocal8Bit().constData() ) ),
      stealthmode_on( ( (strPath+QString("stealthmode_on.bmp")).toLocal8Bit().constData() ) ),

      WarFog( (strPath+QString("war_fog.bmp")).toLocal8Bit().constData() )/*,

      goat_actionpoints(11),  // TO BE BALANCED
      wolf_actionpoints(29),
      starter_goat_luck(55),
      starter_wolf_luck(60),
      goat_luck(starter_goat_luck),
      wolf_luck(starter_wolf_luck),
      move_cost(1),
      attack_cost(4),
      stealth_move_cost(3),
      stealth_attack_cost(7)*/
{
    ui->setupUi(this);

    // LOAD OPTIONS
    std::ifstream LoadOptions;
    char buf[512];
    LoadOptions.open( (((strPath.left(strPath.length()-11))+QString("/options.lib")).toLocal8Bit().constData()) );
    LoadOptions.getline(buf,512);
    goat_actionpoints=atoi(strtok(buf," "));
    LoadOptions.getline(buf,512);
    wolf_actionpoints=atoi(strtok(buf," "));
    LoadOptions.getline(buf,512);
    starter_goat_luck=atoi(strtok(buf," "));
    LoadOptions.getline(buf,512);
    starter_wolf_luck=atoi(strtok(buf," "));
    LoadOptions.getline(buf,512);
    goat_luck=atoi(strtok(buf," "));
    LoadOptions.getline(buf,512);
    wolf_luck=atoi(strtok(buf," "));
    LoadOptions.getline(buf,512);
    move_cost=atoi(strtok(buf," "));
    LoadOptions.getline(buf,512);
    attack_cost=atoi(strtok(buf," "));
    LoadOptions.getline(buf,512);
    stealth_move_cost=atoi(strtok(buf," "));
    LoadOptions.getline(buf,512);
    stealth_attack_cost=atoi(strtok(buf," "));
    LoadOptions.getline(buf,512);
    wolf_visiblearea=atoi(strtok(buf," "));
    LoadOptions.getline(buf,512);
    goats_visiblearea=atoi(strtok(buf," "));
    LoadOptions.getline(buf,512);
    IsFrame=bool(atoi(strtok(buf," ")));
    LoadOptions.close();

    std::ifstream LoadGoatNames;
    LoadGoatNames.open( (((strPath.left(strPath.length()-11))+QString("/goatnames.lib")).toLocal8Bit().constData()) );
    LoadGoatNames.getline(buf,512);
    int numofn = atoi(buf);
    intiGoatname(numofn);
    for(int j=0;j<numofn;j++)
    {
        LoadGoatNames.getline(buf,512);
        goatnames[j] = QString(strtok(buf," "));
    }
    LoadGoatNames.close();

    //QMessageBox::information(0,QString::number(goat_luck),QString::number(stealth_attack_cost),QString::number(wolf_actionpoints));
    //QMessageBox::information(0,0,strPath,QString("OK"));

    QTimer::singleShot(150,this,SLOT(onTimeOut()));
    phath = 0;
}


//------------------------------------------------------------------------------------------------------------------------------

BigBadWolf::~BigBadWolf()
{
    delete ui;
}

//------------------------------------------------------------------------------------------------------------------------------
// KEY PRESSED
void BigBadWolf::keyPressEvent(QKeyEvent *event)
{
    int evk = event->key();
    //QMessageBox::information(0,QString("U pressed key!"),QString::number(evk),QString("OK"));

    //------------------------------------------------------------------------------------------------------------------------------
    // PRESSED ESC
    if(evk==16777216) // Esc code
    {
        pmmn = new MainMenu;
        pmmn->wolf = this;
        pmmn->show();
        return;
    }
    // PRESSED ONE OF ARROWS
    if(evk==16777237 && game_is_active) // Down Arrow code in active game
    {
        eventstatus=0;
        //MOVE DOWN
        if(step_status==1)
        {

            bool cango=true;
            for(int i=0;i<num_of_goats;i++)
            {
                if(goat_pos_x[i] == wolf_x && goat_pos_y[i] == wolf_y+1 && goat_is_alive[i])
                {
                    if( wolf_actionpoints_left >= stealth_move_cost + stealth_attack_cost && stealthmode)
                    {
                         wolf_actionpoints_left-=stealth_attack_cost;
                    if(Attack(eventstatus,wolf_luck,goat_luck,stealthmode))
                    {
                        goat_is_alive[i]=false;
                    }
                    else
                    {
                    cango=false;
                    }
                    }
                    if( wolf_actionpoints_left >= move_cost + attack_cost && !stealthmode)
                    {
                         wolf_actionpoints_left-=attack_cost;
                    if(Attack(eventstatus,wolf_luck,goat_luck,stealthmode))
                    {
                        goat_is_alive[i]=false;
                    }
                    else
                    {
                    cango=false;
                    }
                    }
                    else
                    {
                        genvariation();
                        eventstatus=3;
                        cango=false;
                    }
                }
            }
            if(IsStandable(eventstatus,map_surfaces[wolf_x][wolf_y+1],wolf_x,wolf_y+1,mapsize_x,mapsize_y) && cango && wolf_actionpoints_left>=stealth_move_cost && stealthmode)
            {
            wolf_y++;
            variation = rand()%99999;
            wolf_actionpoints_left-=stealth_move_cost;// IT'S WRONG!
            if(StepIntoPit(eventstatus,wolf_luck,stealthmode,map_surfaces_state[wolf_x][wolf_y]))
              {
                    wolf_actionpoints_left=0;
              }

            }
            else
            if(IsStandable(eventstatus,map_surfaces[wolf_x][wolf_y+1],wolf_x,wolf_y+1,mapsize_x,mapsize_y) && cango && wolf_actionpoints_left>=move_cost && !stealthmode)
              {
              wolf_y++;
              variation = rand()%99999;
              wolf_actionpoints_left-=move_cost;// IT'S WRONG!
              if(StepIntoPit(eventstatus,wolf_luck,stealthmode,map_surfaces_state[wolf_x][wolf_y]))
                {
                      wolf_actionpoints_left=0;
                }
              }else
            {
                if((stealthmode && wolf_actionpoints_left<stealth_move_cost) || (!stealthmode && wolf_actionpoints_left<move_cost))
                {
                    genvariation();
                    eventstatus=3;
                }
            }
              screen_center_x = wolf_x;
              screen_center_y = wolf_y;
        }

        if(step_status==3)
        {
            bool cango=true;
              for(int i=0;i<num_of_goats;i++)
              {
                  if(goat_pos_x[i] == goat_pos_x[chosengoat] && goat_pos_y[chosengoat]+1 == goat_pos_y[i] && goat_is_alive[i] && i != chosengoat)
                      {
                      cango=false;
                      }
              }
              if(wolf_x == goat_pos_x[chosengoat] && wolf_y == goat_pos_y[chosengoat]+1 )
              {
                  cango=false;
              }
              if(IsStandable(eventstatus,map_surfaces[goat_pos_x[chosengoat]][goat_pos_y[chosengoat]+1],goat_pos_x[chosengoat],goat_pos_y[chosengoat]+1,mapsize_x,mapsize_y) && cango && goat_actionpoints_left[chosengoat]>= move_cost + map_surfaces_state[goat_pos_x[chosengoat]][goat_pos_y[chosengoat]+1]/8) // TBC
              {
              goat_pos_y[chosengoat]++;
              variation = rand()%99999;
              goat_actionpoints_left[chosengoat]-=move_cost + map_surfaces_state[goat_pos_x[chosengoat]][goat_pos_y[chosengoat]]/8;// TBC
              }
              else if(goat_actionpoints_left[chosengoat]<move_cost + map_surfaces_state[goat_pos_x[chosengoat]][goat_pos_y[chosengoat]]/8)
              {
                  eventstatus=3;
                  genvariation();
              }
              screen_center_x = goat_pos_x[chosengoat];
              screen_center_y = goat_pos_y[chosengoat];
        }

    }
    else if(evk==16777235 && game_is_active) // Up Arrow code in active game
    {
        eventstatus=0;
        //MOVE UP
        if(step_status==1) // WOLF TURN
        {
              bool cango=true;
              for(int i=0;i<num_of_goats;i++)
              {
                  if(goat_pos_x[i] == wolf_x && goat_pos_y[i] == wolf_y-1 && goat_is_alive[i])
                  {
                      if( wolf_actionpoints_left>= stealth_move_cost + stealth_attack_cost && stealthmode)
                      {
                           wolf_actionpoints_left-=stealth_attack_cost;
                      if(Attack(eventstatus,wolf_luck,goat_luck,stealthmode))
                      {
                          goat_is_alive[i]=false;
                      }
                      else
                      {
                      cango=false;
                      }
                      }else
                      if( wolf_actionpoints_left>= move_cost + attack_cost && !stealthmode)
                  {
                       wolf_actionpoints_left-=attack_cost;
                  if(Attack(eventstatus,wolf_luck,goat_luck,stealthmode))
                  {
                      goat_is_alive[i]=false;
                  }
                  else
                  {
                  cango=false;
                  }
                  }
                  else
                  {
                      genvariation();
                      eventstatus=3;
                      cango=false;
                  }
              }}
              if(IsStandable(eventstatus,map_surfaces[wolf_x][wolf_y-1],wolf_x,wolf_y-1,mapsize_x,mapsize_y) && cango  && wolf_actionpoints_left>=stealth_move_cost && stealthmode)
              {
              wolf_y--;
              variation = rand()%99999;
              wolf_actionpoints_left-=stealth_move_cost;// IT'S WRONG!
              if(StepIntoPit(eventstatus,wolf_luck,stealthmode,map_surfaces_state[wolf_x][wolf_y]))
                {
                      wolf_actionpoints_left=0;
                }
              }

              if(IsStandable(eventstatus,map_surfaces[wolf_x][wolf_y-1],wolf_x,wolf_y-1,mapsize_x,mapsize_y) && cango  && wolf_actionpoints_left>=move_cost && !stealthmode)
              {
              wolf_y--;
              variation = rand()%99999;
              wolf_actionpoints_left-=move_cost;// IT'S WRONG!
                      if(StepIntoPit(eventstatus,wolf_luck,stealthmode,map_surfaces_state[wolf_x][wolf_y]))
                        {
                              wolf_actionpoints_left=0;
                        }
              }else
              {
                  if((stealthmode && wolf_actionpoints_left<stealth_move_cost) || (!stealthmode && wolf_actionpoints_left<move_cost))
                  {
                      genvariation();
                      eventstatus=3;
                  }
              }
              screen_center_x = wolf_x;
              screen_center_y = wolf_y;
        }

        if(step_status==3)
        {
            bool cango=true;
              for(int i=0;i<num_of_goats;i++)
              {
                  if(goat_pos_x[i] == goat_pos_x[chosengoat] && goat_pos_y[chosengoat]-1 == goat_pos_y[i] && goat_is_alive[i] && i != chosengoat)
                      {
                      cango=false;
                      }
              }
              if(wolf_x == goat_pos_x[chosengoat] && wolf_y == goat_pos_y[chosengoat]-1)
              {
                  cango=false;
              }
              if(IsStandable(eventstatus,map_surfaces[goat_pos_x[chosengoat]][goat_pos_y[chosengoat]-1],goat_pos_x[chosengoat],goat_pos_y[chosengoat]-1,mapsize_x,mapsize_y) && cango  && goat_actionpoints_left[chosengoat]>=move_cost  + (map_surfaces_state[goat_pos_x[chosengoat]][goat_pos_y[chosengoat]-1]/8))
              {
              goat_pos_y[chosengoat]--;
              variation = rand()%99999;
              goat_actionpoints_left[chosengoat]-=move_cost + (map_surfaces_state[goat_pos_x[chosengoat]][goat_pos_y[chosengoat]]/8);// IT'S WRONG!
              }
              else if(goat_actionpoints_left[chosengoat]<move_cost + map_surfaces_state[goat_pos_x[chosengoat]][goat_pos_y[chosengoat]]/8)
              {
                  eventstatus=3;
                  genvariation();
              }
              screen_center_x = goat_pos_x[chosengoat];
              screen_center_y = goat_pos_y[chosengoat];
        }

    }
    else if(evk==16777234 && game_is_active) // Left Arrow code in active game
    {
        eventstatus=0;
        //MOVE LEFT
        if(step_status==1)
        {
              bool cango=true;
              for(int i=0;i<num_of_goats;i++)
              {
                  if(goat_pos_x[i] == wolf_x-1 && goat_pos_y[i] == wolf_y && goat_is_alive[i])
                  {
                      if( wolf_actionpoints_left>= stealth_move_cost + stealth_attack_cost && stealthmode)
                      {
                           wolf_actionpoints_left-=stealth_attack_cost;
                      if(Attack(eventstatus,wolf_luck,goat_luck,stealthmode))
                      {
                          goat_is_alive[i]=false;
                      }
                      else
                      {
                      cango=false;
                      }
                      }else
                      if( wolf_actionpoints_left>= move_cost + attack_cost && !stealthmode)
                      {
                           wolf_actionpoints_left-=attack_cost;
                      if(Attack(eventstatus,wolf_luck,goat_luck,stealthmode))
                      {
                          goat_is_alive[i]=false;
                      }
                      else
                      {
                      cango=false;
                      }
                      }
                      else
                      {
                          genvariation();
                          eventstatus=3;
                          cango=false;
                      }
              }}
              if(IsStandable(eventstatus,map_surfaces[wolf_x-1][wolf_y],wolf_x-1,wolf_y,mapsize_x,mapsize_y) && cango && wolf_actionpoints_left>=stealth_move_cost && stealthmode)
              {
              wolf_x--;
              variation = rand()%99999;
              wolf_actionpoints_left-=stealth_move_cost;// IT'S WRONG!
              if(StepIntoPit(eventstatus,wolf_luck,stealthmode,map_surfaces_state[wolf_x][wolf_y]))
                {
                      wolf_actionpoints_left=0;
                }
              }
              else
              if(IsStandable(eventstatus,map_surfaces[wolf_x-1][wolf_y],wolf_x-1,wolf_y,mapsize_x,mapsize_y) && cango && wolf_actionpoints_left>=move_cost && !stealthmode)
              {
              wolf_x--;
              variation = rand()%99999;
              wolf_actionpoints_left-=move_cost;// IT'S WRONG!
              if(StepIntoPit(eventstatus,wolf_luck,stealthmode,map_surfaces_state[wolf_x][wolf_y]))
                {
                      wolf_actionpoints_left=0;
                }
              }else
              {
                  if((stealthmode && wolf_actionpoints_left<stealth_move_cost) || (!stealthmode && wolf_actionpoints_left<move_cost))
                  {
                      genvariation();
                      eventstatus=3;
                  }
              }
              screen_center_x = wolf_x;
              screen_center_y = wolf_y;
        }

        if(step_status==3)
        {
            bool cango=true;
              for(int i=0;i<num_of_goats;i++)
              {
                  if(goat_pos_x[i] == goat_pos_x[chosengoat]-1 && goat_pos_y[chosengoat] == goat_pos_y[i] && goat_is_alive[i] && i != chosengoat)
                      {
                      cango=false;
                      }
              }
              if(wolf_x == goat_pos_x[chosengoat]-1 && wolf_y == goat_pos_y[chosengoat] )
              {
                  cango=false;
              }
              if(IsStandable(eventstatus,map_surfaces[goat_pos_x[chosengoat]-1][goat_pos_y[chosengoat]],goat_pos_x[chosengoat]-1,goat_pos_y[chosengoat],mapsize_x,mapsize_y) && cango  && goat_actionpoints_left[chosengoat]>=move_cost+(map_surfaces_state[goat_pos_x[chosengoat]-1][goat_pos_y[chosengoat]]/8))
              {
              goat_pos_x[chosengoat]--;
               variation = rand()%99999;
              goat_actionpoints_left[chosengoat]-=move_cost + (map_surfaces_state[goat_pos_x[chosengoat]][goat_pos_y[chosengoat]]/8);// IT'S WRONG!
              }
              else if(goat_actionpoints_left[chosengoat]<move_cost + map_surfaces_state[goat_pos_x[chosengoat]][goat_pos_y[chosengoat]]/8)
              {
                  eventstatus=3;
                  genvariation();
              }
              screen_center_x = goat_pos_x[chosengoat];
              screen_center_y = goat_pos_y[chosengoat];
        }

    }
    else if(evk==16777236 && game_is_active) // Right Arrow code in active game
    {
        eventstatus=0;
        //MOVE RIGHT
        if(step_status==1)
        {
            bool cango=true;
              for(int i=0;i<num_of_goats;i++)
              {
                  if(goat_pos_x[i] == wolf_x+1 && goat_pos_y[i] == wolf_y && goat_is_alive[i])
                  {
                      if( wolf_actionpoints_left>= stealth_move_cost + stealth_attack_cost && stealthmode)
                      {
                           wolf_actionpoints_left-=stealth_attack_cost;
                      if(Attack(eventstatus,wolf_luck,goat_luck,stealthmode))
                      {
                          goat_is_alive[i]=false;
                      }
                      else
                      {
                      cango=false;
                      }
                      }
                      else
                      if( wolf_actionpoints_left>= move_cost + attack_cost && !stealthmode)
                      {
                           wolf_actionpoints_left-=attack_cost;
                      if(Attack(eventstatus,wolf_luck,goat_luck,stealthmode))
                      {
                          goat_is_alive[i]=false;
                      }
                      else
                      {
                      cango=false;
                      }
                      }
                      else
                      {
                          cango=false;
                          genvariation();
                          eventstatus=3;
                      }
                  }
              }
              if(IsStandable(eventstatus,map_surfaces[wolf_x+1][wolf_y],wolf_x+1,wolf_y,mapsize_x,mapsize_y) && cango && wolf_actionpoints_left>=stealth_move_cost && stealthmode)
              {
              wolf_x++;
              variation = rand()%99999;
              wolf_actionpoints_left-=stealth_move_cost;// IT'S WRONG!
              if(StepIntoPit(eventstatus,wolf_luck,stealthmode,map_surfaces_state[wolf_x][wolf_y]))
                {
                      wolf_actionpoints_left=0;
                }
              }else
              if(IsStandable(eventstatus,map_surfaces[wolf_x+1][wolf_y],wolf_x+1,wolf_y,mapsize_x,mapsize_y) && cango && wolf_actionpoints_left>=move_cost && !stealthmode)
              {
              wolf_x++;
              variation = rand()%99999;
              wolf_actionpoints_left-=move_cost;// IT'S WRONG!
              if(StepIntoPit(eventstatus,wolf_luck,stealthmode,map_surfaces_state[wolf_x][wolf_y]))
                {
                      wolf_actionpoints_left=0;
                }
              }else
              {
                  if((stealthmode && wolf_actionpoints_left<stealth_move_cost) || (!stealthmode && wolf_actionpoints_left<move_cost))
                  {
                      genvariation();
                      eventstatus=3;
                  }
              }
              screen_center_x = wolf_x;
              screen_center_y = wolf_y;
        }


        if(step_status==3)
        {
            bool cango=true;
              for(int i=0;i<num_of_goats;i++)
              {
                  if(goat_pos_x[i] == goat_pos_x[chosengoat]+1 && goat_pos_y[chosengoat] == goat_pos_y[i] && goat_is_alive[i] && i != chosengoat)
                      {
                      cango=false;
                      }
              }
              if(wolf_x == goat_pos_x[chosengoat]+1 && wolf_y == goat_pos_y[chosengoat] )
              {
                  cango=false;
              }
              if(IsStandable(eventstatus,map_surfaces[goat_pos_x[chosengoat]+1][goat_pos_y[chosengoat]],goat_pos_x[chosengoat]+1,goat_pos_y[chosengoat],mapsize_x,mapsize_y) && cango  && goat_actionpoints_left[chosengoat]>=move_cost+(map_surfaces_state[goat_pos_x[chosengoat]+1][goat_pos_y[chosengoat]]/8))
              {
              goat_pos_x[chosengoat]++;
              variation = rand()%99999;
              goat_actionpoints_left[chosengoat]-=move_cost  + (map_surfaces_state[goat_pos_x[chosengoat]][goat_pos_y[chosengoat]]/8);// IT'S WRONG!
              }
              else if(goat_actionpoints_left[chosengoat]<move_cost + map_surfaces_state[goat_pos_x[chosengoat]][goat_pos_y[chosengoat]]/8)
              {
                  eventstatus=3;
                  genvariation();
              }
              screen_center_x = goat_pos_x[chosengoat];
              screen_center_y = goat_pos_y[chosengoat];
        }
    }
    // CHANGING STEALTH MODE
    else if(evk==16777248 && game_is_active && step_status == 1) // Shift code in active game on wolf's turn
    {
        if(stealthmode)
        {
            //QMessageBox::information(0,QString("Stealth Mode"),QString("Off!"),QString("OK"));
            stealthmode=false;
        }
        else
        {
            //QMessageBox::information(0,QString("Stealth Mode"),QString("On!"),QString("OK"));
            stealthmode=true;
        }
    }
    // ENDING TURN
    else if( evk==84 && game_is_active && (step_status==1 || step_status==3) )
    {
        // END TURN AND SWITCH PHASE
            if(step_status==1)
            {
                eventstatus=0;
                step_status++;
            }
            if(step_status==3)
            {
                eventstatus=0;
                step_status=0;
            }
    }
    //PRESSED ENTER
    else if(evk==16777220)
    {
        //DO SOMETHING
        if((step_status == 4 || step_status == 5) && game_is_active)
        {
            game_is_active = false;
            step_status=0;
        }

        if(step_status==0 && game_is_active)
        {
            eventstatus=0;
            turns_left--;
            screen_center_x = wolf_x;
            screen_center_y = wolf_y;
            step_status++;
            wolf_actionpoints_left=wolf_actionpoints;
        }

        if(step_status==2 && game_is_active)
        {
            eventstatus=0;
            bool isanyonealive=false;
            for(int j=0;j<num_of_goats;j++)
            {
                if(goat_is_alive[j])
                {
                    isanyonealive=true;
                }
            }
            if(isanyonealive)
            {
                chosengoat=0;
            while(!goat_is_alive[chosengoat])
            {
                chosengoat++;
            }
            if(turns_left!=0)
            {
            screen_center_x=goat_pos_x[chosengoat];
            screen_center_y=goat_pos_y[chosengoat];
            for(int i=0;i<num_of_goats;i++)
            {
                if(goat_is_alive[i])
                    goat_actionpoints_left[i]=goat_actionpoints;
                else
                    goat_actionpoints_left[i]=0;
            }
            step_status++;
            }
            else
            {
                step_status=5;
            }
            }
            else
            {
                step_status=4;
            }
        }
    }


    //PRESSED i,j,k,l - replace screencenter
    else if(evk==73 && (step_status==1 || step_status == 3))// i
    {
        screen_center_y--;
    }
    else if(evk==74)// j
    {
        if(step_status==1 || step_status == 3)
            screen_center_x--;
    }
    else if(evk==75)// k
    {
        if(step_status==1 || step_status == 3)
            screen_center_y++;
    }
    else if(evk==76)// l
    {
        if(step_status==1 || step_status == 3)
            screen_center_x++;
    }
    //------------------------------------------------------------------------------------------------------------------------------
    // GOAT DIGGING
    if(evk==68 && game_is_active && step_status==3) // d
    {
       variation=rand()%999999;
       if(goat_actionpoints_left[chosengoat]>0 && map_surfaces_state[goat_pos_x[chosengoat]][goat_pos_y[chosengoat]] < 32)
       {
          if(IsDiggable(map_surfaces[goat_pos_x[chosengoat]][goat_pos_y[chosengoat]]))
          {
          map_surfaces_state[goat_pos_x[chosengoat]][goat_pos_y[chosengoat]]++;
          goat_actionpoints_left[chosengoat]--;
          eventstatus=5;
          }
          else
          {
              eventstatus=2;
          }
       }
       else
       {
           if(goat_actionpoints_left[chosengoat]==0)
           {
               eventstatus=3;
           }
           else if(map_surfaces_state[goat_pos_x[chosengoat]][goat_pos_y[chosengoat]] == 32)
               eventstatus=4;
       }
    }


    //------------------------------------------------------------------------------------------------------------------------------
    // CHANGING ACTIVE GOAT
    if(evk==16777217 && game_is_active && step_status == 3) // TAB
    {
        choosenewgoat:
        chosengoat++;
        if(chosengoat >= num_of_goats)
        {
            chosengoat=0;
        }
        if(!goat_is_alive[chosengoat])
        {
            goto choosenewgoat;
        }
        //QMessageBox::information(0,QString("Goat Changed"),QString::number(chosengoat),QString("OK"));
        screen_center_x = goat_pos_x[chosengoat];
        screen_center_y = goat_pos_y[chosengoat];
    }


    //------------------------------------------------------------------------------------------------------------------------------
    //redraw();
}

//------------------------------------------------------------------------------------------------------------------------------
//START SCREEN ANIMATION
void BigBadWolf::onTimeOut()
{
    if (game_is_active && step_status != 0 && step_status != 2 && step_status !=4 && step_status !=5)
    {
        if(screen_center_x < 6)
        {
            screen_center_x = 6;
        }
        if(screen_center_y < 4)
        {
            screen_center_y=4;
        }
        if(screen_center_x > mapsize_x - 7)
        {
            screen_center_x=mapsize_x-7;
        }
        if(screen_center_y > mapsize_y - 5)
        {
            screen_center_y=mapsize_y - 5;
        }
            redraw();
    }
    else if(step_status == 0 && game_is_active)
    {
        ui->StatusLabel->setText("");
        switch(phath)
        {
        case 0:
            ui->MainWidget->setPixmap(WSTS1);
            break;
        case 1:
            ui->MainWidget->setPixmap(WSTS2);
            break;
        case 2:
            ui->MainWidget->setPixmap(WSTS3);
            break;
        default:
            ui->MainWidget->setPixmap(WSTS4);
        }

        phath++;
        if (phath>3)
            phath = 0;
    }
    else if(step_status == 2 && game_is_active)
    {
        ui->StatusLabel->setText("");
        switch(phath)
        {
        case 0:
            ui->MainWidget->setPixmap(GSTS1);
            break;
        case 1:
            ui->MainWidget->setPixmap(GSTS2);
            break;
        case 2:
            ui->MainWidget->setPixmap(GSTS3);
            break;
        default:
            ui->MainWidget->setPixmap(GSTS4);
        }

        phath++;
        if (phath>3)
            phath = 0;
    }
    else if(step_status==4 && game_is_active)
    {
        // WOLF WON!
        ui->StatusLabel->setText("");
        switch (phath)
        {
        case 0:
            ui->MainWidget->setPixmap(WWS1);
            break;
        case 1:
            ui->MainWidget->setPixmap(WWS2);
            break;
        case 2:
            ui->MainWidget->setPixmap(WWS3);
            break;
        default:
            ui->MainWidget->setPixmap(WWS4);
        }

        phath++;
        if (phath>3)
            phath = 0;

    }
    else if(step_status==5 && game_is_active)
    {
        // GOATS WON!
        ui->StatusLabel->setText("");
        switch (phath)
        {
        case 0:
            ui->MainWidget->setPixmap(GWS1);
            break;
        case 1:
            ui->MainWidget->setPixmap(GWS2);
            break;
        case 2:
            ui->MainWidget->setPixmap(GWS3);
            break;
        default:
            ui->MainWidget->setPixmap(GWS4);
        }

        phath++;
        if (phath>3)
            phath = 0;

    }
    else
    {
        ui->StatusLabel->setText("");
        switch (phath)
        {
        case 0:
            ui->MainWidget->setPixmap(BMP1);
            break;
        case 1:
            ui->MainWidget->setPixmap(BMP2);
            break;
        case 2:
            ui->MainWidget->setPixmap(BMP3);
            break;
        default:
            ui->MainWidget->setPixmap(BMP4);
        }

        phath++;
        if (phath>3)
            phath = 0;
    }


    QTimer::singleShot(150,this,SLOT(onTimeOut()));
}

//---------------------------------------
void BigBadWolf::intiSurface()
{
    /*
    if(map_surfaces)
    {
        for (int i = 0; i < mapsize_yOLD; i++)
            delete [] map_surfaces[i];
        delete [] map_surfaces;
    }*/
    map_surfaces = new int*[mapsize_x];
    map_surfaces_state = new int*[mapsize_x];
    for (int i = 0; i < mapsize_x; i++)
    {
        map_surfaces[i] = new int[mapsize_y];
        map_surfaces_state[i] = new int[mapsize_y];
    }
    for(int t=0;t<mapsize_x;t++)
        for(int u=0;u<mapsize_y;u++)
        {
            map_surfaces_state[t][u]=0;
        }
    seen_by_goats = new bool*[mapsize_x];
    seen_by_wolf  = new bool*[mapsize_x];
    for (int i = 0; i < mapsize_x; i++)
    {
        seen_by_goats[i] = new bool[mapsize_y];
        seen_by_wolf[i] = new bool[mapsize_y];
    }
    for(int t=0;t<mapsize_x;t++)
        for(int u=0;u<mapsize_y;u++)
        {
            seen_by_goats[t][u]=false;
            seen_by_wolf[t][u]=false;
        }
}
void BigBadWolf::intiGoatnum()
{
    goat_actionpoints_left = new int[num_of_goats];
    goat_pos_x = new int[num_of_goats];
    goat_pos_y = new int[num_of_goats];
    goat_is_alive = new bool[num_of_goats];
}
void BigBadWolf::intiGoatname(int numofn)
{
    goatnames = new QString[numofn];
}
