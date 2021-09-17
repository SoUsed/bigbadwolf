#ifndef MAINMENU_H
#define MAINMENU_H

#include <QWidget>

namespace Ui {
class MainMenu;
}


class MainMenu : public QWidget
{
    Q_OBJECT

public:
    explicit MainMenu(QWidget *parent = 0);
    ~MainMenu();

    void *wolf;
private slots:
    void on_ResumeGameButton_clicked();

    void on_ExitGameButton_clicked();

    void on_NewGameButton_clicked();

    void on_SaveGameButton_clicked();

    void on_LoadGameButton_clicked();

    void on_CreditsButton_clicked();

private:
    Ui::MainMenu *ui;
};

#endif // MAINMENU_H
