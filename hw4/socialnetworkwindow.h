#ifndef SOCIALNETWORKWINDOW_H
#define SOCIALNETWORKWINDOW_H
#include "network.h"


#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class SocialNetworkWindow; }
QT_END_NAMESPACE

class SocialNetworkWindow : public QMainWindow
{
    Q_OBJECT

public:
    SocialNetworkWindow(QWidget *parent = nullptr, Network *currentNetwork = nullptr);
    ~SocialNetworkWindow();
    void loginButtonPressed();
    void myTableClick(int row, int column);
    void suggestionTableClicked(int row, int column);
    void searchButtonClicked();
    void goToProfile(QString userName);
    void displayLoggedInProfile(QString userName);
    void backToProfileClick();
    void addFriend();


private:
    Ui::SocialNetworkWindow *ui;
    Network* socialNetwork;
    User* loggedInUser;
    User* currentUser;
};
#endif // SOCIALNETWORKWINDOW_H
