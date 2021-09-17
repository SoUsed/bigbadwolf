// HEADERS
#include "mainmenu.h"
#include "ui_mainmenu.h"
#include "bigbadwolf.h"
#include <fstream>
#include <QFileDialog>
#include <string.h>
#include <QMessageBox>
//------------------------------------------------------------------------------------------------------------------------------

MainMenu::MainMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainMenu),
    wolf(0)
{
    ui->setupUi(this);
}

MainMenu::~MainMenu()
{
    delete ui;
}

//------------------------------------------------------------------------------------------------------------------------------
// RESUME
void MainMenu::on_ResumeGameButton_clicked()
{
    close();
    deleteLater();
}

//------------------------------------------------------------------------------------------------------------------------------
// EXIT
void MainMenu::on_ExitGameButton_clicked()
{
    exit(0);
}

//------------------------------------------------------------------------------------------------------------------------------
// NEW GAME
void MainMenu::on_NewGameButton_clicked()
{
   char buffer[1024];
   std::ifstream NewMapLoader;
   QString NewMapLoader_Directory = QFileDialog::getOpenFileName(this,tr("Choose existing map"),0,tr("*.map"));
   NewMapLoader.open(NewMapLoader_Directory.toLocal8Bit().constData());
   NewMapLoader.getline(buffer,1023);
   ((BigBadWolf*)wolf)->mapsize_x = std::atoi(strtok(buffer," "));
   ((BigBadWolf*)wolf)->mapsize_y = std::atoi(strtok(NULL," "));
   //QMessageBox::information(0,QString("x"),QString::number(((BigBadWolf*)wolf)->mapsize_x),QString("OK"));
   //QMessageBox::information(0,QString("y"),QString::number(((BigBadWolf*)wolf)->mapsize_y),QString("OK"));
   ((BigBadWolf*)wolf)->intiSurface();
   for(int counter_y=0;counter_y<((BigBadWolf*)wolf)->mapsize_y;counter_y++)
   {
       NewMapLoader.getline(buffer,1023);
       ((BigBadWolf*)wolf)->map_surfaces[0][counter_y]=std::atoi(strtok(buffer," "));
       //QMessageBox::information(0,QString("newcoor"),QString::number(((BigBadWolf*)wolf)->map_surfaces[0][counter_y]),QString("OK"));
       for(int counter_x=1;counter_x<((BigBadWolf*)wolf)->mapsize_x;counter_x++)
       {
           ((BigBadWolf*)wolf)->map_surfaces[counter_x][counter_y]=std::atoi(strtok(NULL," "));
         //  QMessageBox::information(0,QString("newcoor"),QString::number(((BigBadWolf*)wolf)->map_surfaces[counter_x][counter_y]),QString("OK"));
       }
   }
   NewMapLoader.getline(buffer,1023);
   ((BigBadWolf*)wolf)->num_of_turns = atoi(buffer);
   NewMapLoader.getline(buffer,1023);
   ((BigBadWolf*)wolf)->num_of_goats = atoi(buffer);
   NewMapLoader.getline(buffer,1023);
   ((BigBadWolf*)wolf)->wolf_x = atoi(strtok(buffer," "));
   ((BigBadWolf*)wolf)->wolf_y = atoi(strtok(NULL," "));
   //QMessageBox::information(0,QString("newwolfx"),QString::number(((BigBadWolf*)wolf)->wolf_x),QString("OK"));
   //QMessageBox::information(0,QString("newwolfy"),QString::number(((BigBadWolf*)wolf)->wolf_y),QString("OK"));
   //QMessageBox::information(0,QString("newnumofgoats"),QString::number(((BigBadWolf*)wolf)->num_of_goats),QString("OK"));

   ((BigBadWolf*)wolf)->intiGoatnum();

   for(int i=0;i<((BigBadWolf*)wolf)->num_of_goats;i++)
   {
       NewMapLoader.getline(buffer,1023);
       ((BigBadWolf*)wolf)->goat_pos_x[i] = atoi(strtok(buffer," "));
       ((BigBadWolf*)wolf)->goat_pos_y[i] = atoi(strtok(NULL," "));
       ((BigBadWolf*)wolf)->goat_is_alive[i] = true;
       //QMessageBox::information(0,QString("newgoatx"),QString::number(((BigBadWolf*)wolf)->goat_pos_x[i]),QString("OK"));
       //QMessageBox::information(0,QString("newgoaty"),QString::number(((BigBadWolf*)wolf)->goat_pos_y[i]),QString("OK"));
   }

   close();
   if(((BigBadWolf*)wolf)->num_of_turns !=0)
   {
   ((BigBadWolf*)wolf)->step_status = 0;
   ((BigBadWolf*)wolf)->game_is_active=true;
   ((BigBadWolf*)wolf)->chosengoat = 0;
   ((BigBadWolf*)wolf)->turns_left = ((BigBadWolf*)wolf)->num_of_turns;
   ((BigBadWolf*)wolf)->stealthmode = false;
   ((BigBadWolf*)wolf)->wolf_luck=((BigBadWolf*)wolf)->starter_wolf_luck;
   ((BigBadWolf*)wolf)->goat_luck=((BigBadWolf*)wolf)->starter_goat_luck;
   ((BigBadWolf*)wolf)->eventstatus=0;

   }
   else
   {
       QMessageBox::information(0,QString("ERROR!"),QString("Error loading game.Loading process terminated or map file is invalid!"),QString("OK"));
   }
   deleteLater();
}
//------------------------------------------------------------------------------------------------------------------------------
// SAVE GAME
void MainMenu::on_SaveGameButton_clicked()
{
    std::ofstream MapSaver;
    QString MapSaver_Directory = QFileDialog::getSaveFileName(this,tr("Choose file to save"),0,tr("*.sav"));
    MapSaver.open(MapSaver_Directory.toLocal8Bit().constData());
}

//------------------------------------------------------------------------------------------------------------------------------
// LOAD GAME
void MainMenu::on_LoadGameButton_clicked()
{
    std::ifstream MapLoader;
    QString MapLoader_Directory = QFileDialog::getSaveFileName(this,tr("Choose existing game"),0,tr("*.sav"));
    MapLoader.open(MapLoader_Directory.toLocal8Bit().constData());
}

//------------------------------------------------------------------------------------------------------------------------------
// CREDITS
void MainMenu::on_CreditsButton_clicked()
{

}
