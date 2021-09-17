#ifndef BIGBADWOLF_H
#define BIGBADWOLF_H
#include "mainmenu.h"
#include <QMainWindow>

#include <QTimer>

namespace Ui {
class BigBadWolf;
}

class BigBadWolf : public QMainWindow
{
    Q_OBJECT

public:
    explicit BigBadWolf(QWidget *parent = 0);
    ~BigBadWolf();

    //VARIABLES INIT
        // GAME INFO:
          // TEMP THING
    bool IsFrame;
          // COMMON THINGS:
    int screen_center_x;
    int screen_center_y;
    bool game_is_active;
    int step_status; // 0 - wolf's start screen,1 - wolf's turn,2- goat's start screen,3 - goat's turn
    int mapsize_x;
    int mapsize_y;
    int** map_surfaces;
    int num_of_turns;
    int move_cost;
    int stealth_move_cost;
    int stealth_attack_cost;
    int attack_cost;
          // CHANGEABLE THINGS:
    int num_of_pits;
    int* pit_pos_x;
    int* pit_pos_y;
    int** map_surfaces_state;
    int turns_left;
    int eventstatus;
    int variation;
        //WOLF INFO:
    int wolf_speed;
    int wolf_luck;
    int starter_wolf_luck;
    int wolf_x;
    int wolf_y;
    int wolf_actionpoints; // MUST BE INITIALIZED HERE!!!
    int wolf_actionpoints_left;
    int wolf_visiblearea;
    bool stealthmode;
    bool** seen_by_wolf;
        //GOAT INFO:
    int goat_actionpoints; // MUST BE INITIALIZED HERE!!!
    int num_of_goats;
    int goat_luck; // MUST BE INITIALIZED HERE!!!
    int* goat_pos_x;
    int* goat_pos_y;
    int starter_goat_luck;
    int* goat_actionpoints_left;
    bool* goat_is_alive;
    int goats_visiblearea;
    int chosengoat;
    bool** seen_by_goats;
    QString* goatnames;

    void intiSurface();
    void intiGoatname(int numofn);
    void intiGoatnum();
    void genvariation();
    bool Attack(int & eventstatus,int & wluck,int & gluck,bool stealthmode);
    bool StepIntoPit(int & eventstatus,int & luck,bool stealthmode, int & state);
private slots:

    void onTimeOut();

private:
    Ui::BigBadWolf *ui;
protected:
    void redraw();

    virtual void keyPressEvent(QKeyEvent *event);

    QPixmap BMP1,BMP2,BMP3,BMP4;
    MainMenu *pmmn;

    int phath;
    //----------------------------------------------------------------------------------------------------------------------------
    // GROUNDS AND TEXTURES

    QPixmap WolfTest1_Green;
    QPixmap WolfTest1_Black;
    QPixmap TerrainTest1_Green;
    QPixmap TerrainTest1_Black;
    QPixmap GoatTest1_Green;
    QPixmap GoatTest1_Black;
    QPixmap ObstalceTest1;
    QPixmap ObstalceTest1_f;
    //----------------------------------------------------------------------------------------------------------------------------

    QPixmap GrassAndTree1_10;
    QPixmap Grass1_11;
    QPixmap Grass2_12;
    QPixmap Grass3_13;
    QPixmap GrassPath2x1WatchingUpLeft1_14;
    QPixmap GrassPath2x1WatchingUpRight1_15;
    QPixmap GrassPath1x1WatchingLeft2_16;
    QPixmap GrassPath1x1WatchingLeft3_17;
    QPixmap GrassWithoutPath1x1_1_18;
    QPixmap WoodenParquet1x1_1_19;
    QPixmap WoodenParquet1x1_2_20;
    QPixmap Carpet1x1_1_21;
    QPixmap BedOnACarpet1_22;
    QPixmap GrassAndTree2_23;
    QPixmap Grass2FenceFaceFull_24;
    QPixmap Grass2FenceSideLeft_25;
    QPixmap Grass2FenceSideRight_26;
    QPixmap Grass2FenceFaceLeftEnd_27;
    QPixmap Grass2FenceFaceRightEnd_28;


    QPixmap GrassAndTree1_10_f;
    QPixmap Grass1_11_f;
    QPixmap Grass2_12_f;
    QPixmap Grass3_13_f;
    QPixmap GrassPath2x1WatchingUpLeft1_14_f;
    QPixmap GrassPath2x1WatchingUpRight1_15_f;
    QPixmap GrassPath1x1WatchingLeft2_16_f;
    QPixmap GrassPath1x1WatchingLeft3_17_f;
    QPixmap GrassWithoutPath1x1_1_18_f;
    QPixmap WoodenParquet1x1_1_19_f;
    QPixmap WoodenParquet1x1_2_20_f;
    QPixmap Carpet1x1_1_21_f;
    QPixmap BedOnACarpet1_22_f;
    QPixmap GrassAndTree2_23_f;
    QPixmap Grass2FenceFaceFull_24_f;
    QPixmap Grass2FenceSideLeft_25_f;
    QPixmap Grass2FenceSideRight_26_f;
    QPixmap Grass2FenceFaceLeftEnd_27_f;
    QPixmap Grass2FenceFaceRightEnd_28_f;


    QPixmap Grass1_11_w;
    QPixmap Grass2_12_w;
    QPixmap Grass3_13_w;
    QPixmap GrassPath2x1WatchingUpLeft1_14_w;
    QPixmap GrassPath2x1WatchingUpRight1_15_w;
    QPixmap GrassPath1x1WatchingLeft2_16_w;
    QPixmap GrassPath1x1WatchingLeft3_17_w;
    QPixmap GrassWithoutPath1x1_1_18_w;
    QPixmap WoodenParquet1x1_1_19_w;
    QPixmap WoodenParquet1x1_2_20_w;
    QPixmap Carpet1x1_1_21_w;


    QPixmap Grass1_11_g;
    QPixmap Grass2_12_g;
    QPixmap Grass3_13_g;
    QPixmap GrassPath2x1WatchingUpLeft1_14_g;
    QPixmap GrassPath2x1WatchingUpRight1_15_g;
    QPixmap GrassPath1x1WatchingLeft2_16_g;
    QPixmap GrassPath1x1WatchingLeft3_17_g;
    QPixmap GrassWithoutPath1x1_1_18_g;
    QPixmap WoodenParquet1x1_1_19_g;
    QPixmap WoodenParquet1x1_2_20_g;
    QPixmap Carpet1x1_1_21_g;



    //----------------------------------------------------------------------------------------------------------------------------

    QPixmap WSTS1;
    QPixmap WSTS2;
    QPixmap WSTS3;
    QPixmap WSTS4;

    QPixmap GSTS1;
    QPixmap GSTS2;
    QPixmap GSTS3;
    QPixmap GSTS4;

    QPixmap GWS1;
    QPixmap GWS2;
    QPixmap GWS3;
    QPixmap GWS4;

    QPixmap WWS1;
    QPixmap WWS2;
    QPixmap WWS3;
    QPixmap WWS4;

    QPixmap num1,num2,num3,num4,num5,num6,num7,num8,num9,num0;
    QPixmap AcP_left;
    QPixmap TrL;
    QPixmap darkgreensquare;
    QPixmap darkgreenwolf;
    QPixmap darkgreengoat;
    QPixmap bigbgsquare;
    QPixmap bgsquare180x60;

    QPixmap stealthmode_on;
    QPixmap stealthmode_off;

    QPixmap WarFog;

    //----------------------------------------------------------------------------------------------------------------------------
    // FRAME ELEMENTS
    QPixmap FrameElement1;
    QPixmap FrameElement2;
    QPixmap FrameElement3;
    QPixmap FrameElement4;
    QPixmap FrameElement5;
    QPixmap FrameElement6;
    QPixmap FrameElement7;
    QPixmap FrameElement8;
    QPixmap FrameElement9;
    QPixmap FrameElement10;
    QPixmap FrameElement11;
    QPixmap FrameElement12;
    QPixmap FrameElement13;
    QPixmap FrameElement14;
    QPixmap FrameElement15;
    QPixmap FrameElement16;
    QPixmap FrameElement17;
    QPixmap FrameElement18;
    QPixmap FrameElement19;
    QPixmap FrameElement20;
    QPixmap FrameElement21;
    QPixmap FrameElement22;
    QPixmap FrameElement23;
    QPixmap FrameElement24;
    QPixmap FrameElement25;
    QPixmap FrameElement26;
    QPixmap FrameElement27;
    QPixmap FrameElement28;
    QPixmap FrameElement29;
    QPixmap FrameElement30;
    QPixmap FrameElement31;
    QPixmap FrameElement32;
    QPixmap FrameElement33;
    QPixmap FrameElement34;
    QPixmap FrameElement35;
    QPixmap FrameElement36;
    QPixmap FrameElement37;
    QPixmap FrameElement38;
    QPixmap FrameElement39;
    QPixmap FrameElement40;
    QPixmap FrameElement41;
    QPixmap FrameElement42;
    QPixmap FrameElement43;
    QPixmap FrameElement44;
    QPixmap FrameElement45;
    QPixmap FrameElement46;
    QPixmap FrameElement47;
    QPixmap FrameElement48;
    QPixmap FrameElement49;
    QPixmap FrameElement50;
    QPixmap FrameElement51;
    QPixmap FrameElement52;
    QPixmap FrameElement53;
    QPixmap FrameElement54;
    QPixmap FrameElement55;
    QPixmap FrameElement56;
    QPixmap FrameElement57;
    QPixmap FrameElement58;
    QPixmap FrameElement59;
    QPixmap FrameElement60;
    QPixmap FrameElement61;
    QPixmap FrameElement62;
    QPixmap FrameElement63;
    QPixmap FrameElement64;
    QPixmap FrameElement65;
    QPixmap FrameElement66;
    QPixmap FrameElement67;
    QPixmap FrameElement68;
    QPixmap FrameElement69;
    QPixmap FrameElement70;
};

#endif // BIGBADWOLF_H
