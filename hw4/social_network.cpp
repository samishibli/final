
#include "user.h"
#include "network.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>
using namespace std;

// Function to add a user
void addUser(Network &network)
{
    string user_input;
    cout << "Enter the information for the user you would like to add" << endl;
    cout << "following this format Jason Chen 2001 95053: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    getline(cin, user_input, '\n');
    // Split the input into individual values
    istringstream ss(user_input);
    string first_name, last_name;
    int birth_year, zip_code;
    ss >> first_name >> last_name >> birth_year >> zip_code;
    // Concatenate name
    string fullName = first_name + " " + last_name;

    User *newUser = new User();
    newUser->setId(0);
    newUser->setName(fullName);
    newUser->setBirthYear(birth_year);
    newUser->setZipCode(zip_code);
    newUser->setFriendsList(vector<size_t>());
    cout << "New User Successfully added: " << endl;
    network.addUser(newUser);
}

// Function to add a friend connection
void addFriendConnection(Network &network)
{
    string user_input;
    cout << "Enter the Names of two friends you would like to make a connection with" << endl;
    cout << "Example Sami Shibli Jason Chen: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    getline(cin, user_input, '\n');
    // Split the input into individual values
    istringstream ss(user_input);
    string first_name, last_name, otherFirst_Name, otherLast_name;
    ss >> first_name >> last_name >> otherFirst_Name >> otherLast_name;
    // Concatenate name
    string firstfullName = first_name + " " + last_name;
    string secondfullName = otherFirst_Name + " " + otherLast_name;

    if (network.addConnection(firstfullName, secondfullName) == -1)
        cout << "Connection Failed!" << endl;
    else
        cout << "Successful Connection!" << endl;
}

// Function to remove a friend connection
void removeFriendConnection(Network &network)
{
    string user_input;
    cout << "Enter the Names of two friends you would like to delete a connection with" << endl;
    cout << "Example Sami Shibli Jason Chen: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    getline(cin, user_input, '\n');
    // Split the input into individual values
    istringstream ss(user_input);
    string first_name, last_name, otherFirst_Name, otherLast_name;
    ss >> first_name >> last_name >> otherFirst_Name >> otherLast_name;
    // Concatenate name
    string firstfullName = first_name + " " + last_name;
    string secondfullName = otherFirst_Name + " " + otherLast_name;

    if (network.removeConnection(firstfullName, secondfullName) == -1)
        cout << "Remove Failed!" << endl;
    else
        cout << "Connection Removed!" << endl;
}

// Function to print all users
void printAllUsers(Network &network)
{
    cout << " ID "
         << " "
         << " Name "
         << " "
         << " Birth Year "
         << " "
         << " Zipcode "
         << " " << endl;
    for (User *user : network.getUsers())
    {
        cout << user->getId() << " " << user->getName() << " " << user->getBirthYear() << " " << user->getZipCode() << endl;
    }
}

// Function to print friends of a user
void printFriendsOfUser(Network &network)
{
    string user_input;
    cout << "Enter Name of person to see their friends" << endl;
    cout << "Example: Jason Chen: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    getline(cin, user_input, '\n');
    // Split the input into individual values
    istringstream ss(user_input);
    string first_name, last_name;
    ss >> first_name >> last_name;
    // Concatenate name
    string fullName = first_name + " " + last_name;
    cout << "ID"
         << " "
         << "Name"
         << " "
         << "Year Born"
         << " "
         << "ZipCode" << endl;
    User *personFound = nullptr;
    int person = network.getId(fullName);
    personFound = network.getUser(person);
    if (personFound->getFriendsList().empty())
    {
        cout << "User has no friend connections :(" << endl;
    }
    else
    {
        for (size_t v : personFound->getFriendsList())
        {
            User *u = network.getUser(v);
            cout << *u;
        }
    }
}
void printShortestPath(Network &network)
{
    string user_input;
    cout << "Enter the Names of two users:" << endl;
    cout << "Example: Sami Shibli Jason Chen: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    getline(cin, user_input, '\n');
    // Split the input into individual values
    istringstream ss(user_input);
    string first_name, last_name, otherFirst_Name, otherLast_name;
    ss >> first_name >> last_name >> otherFirst_Name >> otherLast_name;
    // Concatenate name
    string firstFullName = first_name + " " + last_name;
    string secondFullName = otherFirst_Name + " " + otherLast_name;

    size_t distanceFrom = network.getId(firstFullName);
    size_t distanceTo = network.getId(secondFullName);
    vector<size_t> result = network.shortestPath(distanceFrom, distanceTo);
    cout << "Distance: " << result.size() - 1 << endl;
    for (size_t v : result)
    {
        User *u = network.getUser(v);
        cout << u->getName();
        // Check if the current node is not the last node in the path
        if (v != result.back())
        {
            cout << " -> ";
        }
    }
    cout << endl;
}
void printNearestNeighbor(Network &network)
{
    string user_input;
    cout << "Enter the Names of a user and the depth you want to travel:" << endl;
    cout << "Example: Aled Montes 3: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    getline(cin, user_input, '\n');
    // Split the input into individual values
    istringstream ss(user_input);
    string first_name, last_name;
    int distance;
    ss >> first_name >> last_name >> distance;
    // Concatenate name
    string firstFullName = first_name + " " + last_name;

    size_t From = network.getId(firstFullName);
    size_t To = 0;
    vector<size_t> result = network.distanceUser(From, To, distance);
    if (result.empty())
    {
        cout << "No neighbors exist at this distance!";
    }
    for (size_t v : result)
    {
        User *u = network.getUser(v);
        cout << u->getName();
        // Check if the current node is not the last node in the path
        if (v != result.back())
        {
            cout << " -> ";
        }
    }
    cout << endl;
}
void suggestFriends(Network &network)
{
    string user_input;
    cout << "Enter Name of person to see their friends" << endl;
    cout << "Example: Jason Chen: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    getline(cin, user_input, '\n');
    // Split the input into individual values
    istringstream ss(user_input);
    string first_name, last_name;
    ss >> first_name >> last_name;
    // Concatenate name
    string fullName = first_name + " " + last_name;
    size_t score = 0;
    size_t user = network.getId(fullName);
    std::vector<size_t> result = network.suggestFriends(user, score);
    cout << "The suggested friend(s) is/are:" << endl;
    for (size_t v : result)
    {
        User *newUser = network.getUser(v);
        cout << newUser->getName() << ": " << score;
        cout << endl;
    }
}
void generateDisjointSets(Network &network)
{
    std::vector<std::vector<size_t>> result = network.groups();
    int counter = 1;
    for (vector<size_t> sets : result)
    {
        cout << "Set " << counter << " => ";
        for (size_t iD : sets)
        {
            User *user = network.getUser(iD);
            cout << user->getName() << ", ";
        }
        cout << endl;
        counter++;
    }
}
void displayPost(Network &network)
{
    string user_input;
    cout << "Enter the Names of a user and how many post you would like to see:" << endl;
    cout << "Example: Aled Montes 3: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    getline(cin, user_input, '\n');
    // Split the input into individual values
    istringstream ss(user_input);
    string first_name, last_name;
    size_t howMany;
    ss >> first_name >> last_name >> howMany;
    // Concatenate name
    string fullName = first_name + " " + last_name;

    bool isPublic = false;
    std::string result = "";
    result = network.displayPosts(fullName, howMany, isPublic);
    cout << endl;
    cout << "Posts on " << fullName << "'s page:" << endl
         << endl;
    std::cout << result << std::endl;
}
int main()
{
    Network network;
    char filename[256];

    cout << "Enter name for file for program to read: ";
    cin.getline(filename, sizeof(filename));

    network.readUsers(filename);

    char otherFileName[256];
    cout << "Enter name for file for program to read different Post: ";
    cin.getline(otherFileName, sizeof(otherFileName));
    network.readPosts(otherFileName);

    int option;
    do
    {
        cout << "MENU:" << endl;
        cout << "Option 1: Add a user" << endl;
        cout << "Option 2: Add Friend Connection" << endl;
        cout << "Option 3: Remove Friend Connection" << endl;
        cout << "Option 4: Print Users" << endl;
        cout << "Option 5: Print Friends" << endl;
        cout << "Option 6: Write to a file" << endl;
        cout << "Option 7: Find shortest path between two users" << endl;
        cout << "Option 8: Find Neighbor" << endl;
        cout << "Option 9: Find Friend Suggestions" << endl;
        cout << "Option 10: Generate Disjoint Sets" << endl;
        cout << "Option 11: Read Posts" << endl;
        cout << "Option 12: Exit Program" << endl;
        cout << "Enter a digit to choose from one of the options: ";
        cin >> option;

        switch (option)
        {
        case 1:
            addUser(network);
            break;
        case 2:
            addFriendConnection(network);
            break;
        case 3:
            removeFriendConnection(network);
            break;
        case 4:
            printAllUsers(network);
            break;
        case 5:
            printFriendsOfUser(network);
            break;
        case 6:
            char nameOfFile[256];
            cout << "Enter name for file to write contents of network to (Example: users_new.txt): ";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cin.getline(nameOfFile, sizeof(nameOfFile));
            network.writeUsers(nameOfFile);
            break;
        case 7:
            printShortestPath(network);
            break;
        case 8:
            printNearestNeighbor(network);
            break;
        case 9:
            suggestFriends(network);
            break;
        case 10:
            generateDisjointSets(network);
            break;
        case 11:
            displayPost(network);
            break;
        case 12:
            std::cout << "Exiting the program." << std::endl;
            break;
        default:
            std::cout << "Invalid command. Please enter a valid command (1-7)." << std::endl;
            break;
        }
    } while (option != 12);

    return 0;
}
