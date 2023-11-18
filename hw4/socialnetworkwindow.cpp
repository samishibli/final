#include "socialnetworkwindow.h"
#include "ui_socialnetworkwindow.h"


SocialNetworkWindow::SocialNetworkWindow(QWidget *parent, Network *currentNetwork): QMainWindow(parent), ui(new Ui::SocialNetworkWindow)
{
    ui->setupUi(this);
    socialNetwork = currentNetwork;
    connect(ui->loginButton, &QPushButton::clicked, this, &SocialNetworkWindow::loginButtonPressed);
    connect(ui->tableFriendsList, &QTableWidget::cellClicked, this,&SocialNetworkWindow::myTableClick);
    connect(ui->searchPushButton, &QPushButton::clicked,this,&SocialNetworkWindow::searchButtonClicked);
    connect(ui->backToProfileButton, &QPushButton::clicked,this,&SocialNetworkWindow::backToProfileClick);
    connect(ui->connectButton, &QPushButton::clicked,this,&SocialNetworkWindow::addFriend);
    connect(ui->friendSuggestionTable, &QTableWidget::cellClicked, this,&SocialNetworkWindow::suggestionTableClicked);
    ui->displayName->setAlignment(Qt::AlignCenter);
    ui->displayName->hide();
    ui->tableFriendsList->hide();
    ui->SearchText->hide();
    ui->searchEntry->hide();
    ui->searchPushButton->hide();
    ui->postsLabel->hide();
    ui->postsFromLabel->hide();
    ui->backToProfileButton->hide();
    ui->friendSuggestionTable->hide();
    ui->connectButton->hide();
}
SocialNetworkWindow::~SocialNetworkWindow()
{
    delete ui;
}
void SocialNetworkWindow::goToProfile(QString userName){

    std::string stdCurrentUser = userName.toStdString(); // Convert QString to std::string
    if(socialNetwork->getId(stdCurrentUser) != -1){
        currentUser = socialNetwork->getUser(socialNetwork->getId(stdCurrentUser));
        QString Name = QString::fromStdString(stdCurrentUser) + "'s Profile";
        ui->displayName->setText(Name);
        ui->searchEntry->clear();
        std::vector<size_t> friendList = currentUser->getFriendsList();
        ui->tableFriendsList->setRowCount(friendList.size());
        ui->tableFriendsList->setColumnCount(1);
        ui->tableFriendsList->horizontalHeader()->setStretchLastSection(true);
        int row = 0;
        QTableWidgetItem* nameItem = new QTableWidgetItem("Friends List of: " + userName);
        ui->tableFriendsList->setItem(row, 0, nameItem);
        row++;
        for(size_t friendId : friendList){
            User *currentFriend = socialNetwork->getUser(friendId);
            std::string currentFriendName = currentFriend->getName();
            QTableWidgetItem* nameItem = new QTableWidgetItem(QString::fromStdString(currentFriendName));
            ui->tableFriendsList->setItem(row, 0, nameItem);
            row++;
        }
        std::string postsToDisplay = currentUser->displayPosts(5, true);
        QString qPostsToDisplay = QString::fromStdString(postsToDisplay);
        ui->postsLabel->setText(qPostsToDisplay);
        ui->postsFromLabel->setText("Post's by: " + userName);
        ui->postsFromLabel->show();
        ui->postsLabel->show();
        ui->backToProfileButton->show();
        ui->connectButton->show();
        ui->connectButton->show();
        ui->friendSuggestionTable->hide();
    }
    else{
        ui->searchEntry->clear();
        ui->searchEntry->setPlaceholderText("User not found in network");
    }

}
void SocialNetworkWindow::displayLoggedInProfile(QString userName){
    std::string stdCurrentUser = userName.toStdString(); // Convert QString to std::string
    if(socialNetwork->getId(stdCurrentUser) != -1){
        loggedInUser = socialNetwork->getUser(socialNetwork->getId(stdCurrentUser));
        ui->displayName->setText("My Profile");
        //Hide everything from login page
        ui->usernamePrompt->hide();
        ui->userNameBox->hide();
        ui->loginButton->hide();
        ui->connectButton->hide();
        ui->backToProfileButton->hide();
        //show Profile Page
        ui->displayName->show();
        ui->SearchText->show();
        ui->searchEntry->show();
        ui->searchPushButton->show();

        //display Friends List
        std::vector<size_t> friendList = loggedInUser->getFriendsList();
        ui->tableFriendsList->setRowCount(friendList.size() + 1);
        ui->tableFriendsList->setColumnCount(1);
        ui->tableFriendsList->horizontalHeader()->setStretchLastSection(true);
        int row = 0;
        QTableWidgetItem* nameItem = new QTableWidgetItem("Friends List of: " + userName);
        ui->tableFriendsList->setItem(row, 0, nameItem);
        row++;
        for(size_t friendId : friendList){
            User *currentFriend = socialNetwork->getUser(friendId);
            std::string currentFriendName = currentFriend->getName();
            QTableWidgetItem* nameItem = new QTableWidgetItem(QString::fromStdString(currentFriendName));
            ui->tableFriendsList->setItem(row, 0, nameItem);
            row++;
        }
        ui->tableFriendsList->show();
        //show 5 most recent post for logged in
        std::string postsToDisplay = loggedInUser->displayPosts(5, false);
        QString qPostsToDisplay = QString::fromStdString(postsToDisplay);
        ui->postsLabel->setText(qPostsToDisplay);
        ui->postsFromLabel->setText("Post's from me");
        ui->postsFromLabel->show();
        ui->postsLabel->show();
        //display friend reccomendations
        std::size_t currentId = loggedInUser->getId();
        std::size_t score = 0;
        std::vector<std::size_t> friendSuggestions = socialNetwork->suggestFriends(currentId, score);
        ui->friendSuggestionTable->setRowCount(friendSuggestions.size() + 1);
        ui->friendSuggestionTable->setColumnCount(2);
        ui->friendSuggestionTable->horizontalHeader()->setStretchLastSection(true);
        int rowSugg = 0;
        QTableWidgetItem* suggNameItem = new QTableWidgetItem("Click to Connect");
        ui->friendSuggestionTable->setItem(rowSugg, 0, suggNameItem);
        rowSugg++;
        for(size_t friendSugg: friendSuggestions){
            User* currentSugg = socialNetwork->getUser(friendSugg);
            std::string currentSuggName = currentSugg->getName();
            QTableWidgetItem* suggNameItem = new QTableWidgetItem(QString::fromStdString(currentSuggName));
            ui->friendSuggestionTable->setItem(rowSugg,0,suggNameItem);

            QTableWidgetItem* connectItem = new QTableWidgetItem("Connect");
            connectItem->setTextAlignment(Qt::AlignCenter);  // Align text to the center
            ui->friendSuggestionTable->setItem(rowSugg, 1, connectItem);

            rowSugg++;
        }
        ui->friendSuggestionTable->show();
    }
    else{
        ui->userNameBox->clear();
        ui->userNameBox->setPlaceholderText("User not found in network");
    }

}
void SocialNetworkWindow::myTableClick(int row, int column) {
    QTableWidgetItem* item = ui->tableFriendsList->item(row, column);
    if (item) {
        QString clickedCellText = item->text();
        std::string stdClickedUser = clickedCellText.toStdString();
        if (stdClickedUser == loggedInUser->getName()) {
            displayLoggedInProfile(clickedCellText);
        } else {
            goToProfile(clickedCellText);
        }
    }
}
void SocialNetworkWindow::suggestionTableClicked(int row, int column){
    QTableWidgetItem* Suggestionitem = ui->friendSuggestionTable->item(row, column);
    if (Suggestionitem) {
        QString clickedCellText = Suggestionitem->text();
        std::string stdClickedUser = clickedCellText.toStdString();
        if (stdClickedUser == loggedInUser->getName()) {
            displayLoggedInProfile(clickedCellText);
        } else {
            goToProfile(clickedCellText);
        }
    }
    if (column == 1) {
        QTableWidgetItem* item = ui->friendSuggestionTable->item(row, 0);
        if (item) {
            QString clickedCellText = item->text();
            std::string stdClickedUser = clickedCellText.toStdString();
            std::string personalProfile = loggedInUser->getName();
            int success = socialNetwork->addConnection(personalProfile, stdClickedUser);
            if (success == -1) {
                // If connection is denied, update the cell text to "Denied"
                QTableWidgetItem* denialItem = new QTableWidgetItem("Denied");
                denialItem->setTextAlignment(Qt::AlignCenter);
                ui->friendSuggestionTable->setItem(row, 1, denialItem);
            } else {
                // If connection is accepted, update the cell text to "Accepted"
                QTableWidgetItem* acceptedItem = new QTableWidgetItem("Accepted");
                acceptedItem->setTextAlignment(Qt::AlignCenter);
                ui->friendSuggestionTable->setItem(row, 1, acceptedItem);
            }
        }
    }

}
void SocialNetworkWindow::searchButtonClicked(){
    QString userName = ui->searchEntry->toPlainText();
    goToProfile(userName);
}
void SocialNetworkWindow::loginButtonPressed(){
    //read the text from userNameBox
    QString userName= ui->userNameBox->toPlainText();
    displayLoggedInProfile(userName);

}
void SocialNetworkWindow::backToProfileClick(){
    std::string personalProfile = loggedInUser->getName();
    QString qPersonalProfile = QString::fromStdString(personalProfile);
    displayLoggedInProfile(qPersonalProfile);
}
void SocialNetworkWindow::addFriend(){
    std::string personalProfile = loggedInUser->getName();
    std::string potentialFriend = currentUser->getName();
    int success = socialNetwork->addConnection(personalProfile, potentialFriend);
//    if(success == -1){
//        ui->connectButton->setText("Denied");
//    }
//    else{
//        ui->connectButton->setText("Accepted");
//    }
}


