#include "socialnetworkwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Network *currentNetwork = new Network;
    currentNetwork->readUsers("C:/Users/samis/OneDrive/Desktop/CSCI62/ThirdTimesACharm/hw4/social_network.txt");
    currentNetwork->readPosts("C:/Users/samis/OneDrive/Desktop/CSCI62/ThirdTimesACharm/hw4/posts.txt");
    SocialNetworkWindow w(nullptr, currentNetwork);

    w.show();
    return a.exec();
}
