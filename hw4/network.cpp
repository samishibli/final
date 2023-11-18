#include "network.h"
#include "user.h"
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <queue>
#include <stack>
#include <unordered_set>
#include <algorithm>

// Default constructor
// Pre: None
// Post: Creates an empty Network object
Network::Network()
{
    users_.clear();
    numMessages = 0;
}
// Destructor
// Pre: None
// Post: Cleans up allocated resources when the Network object is destroyed
Network::~Network()
{
    for (User *userPtr : users_)
    {
        delete userPtr;
    }
}
// Add a User pointer to the network
// Pre: userPointer is a valid pointer to a User object
// Post: Adds the User to the network
void Network::addUser(User *userPointer)
{
    users_.push_back(userPointer);
}
// Add a connection between two users in the network
// Pre: s1 and s2 are valid user names in the network
// Post: Adds a connection between the users if they exist, returns -1 if not
int Network::addConnection(std::string s1, std::string s2)
{
    // no self connection
    if (s1 == s2)
    {
        return -1;
    }
    else
    {
        User *profileOne = nullptr;
        User *profileTwo = nullptr;
        for (User *userPtr : users_)
        {
            if (userPtr->getName() == s1)
                profileOne = userPtr;
        }
        for (User *userPtr : users_)
        {
            if (userPtr->getName() == s2)
                profileTwo = userPtr;
        }
        // if one of the profiles does not exist return -1
        if (!(profileOne && profileTwo))
            return -1;
        profileOne->addFriend(profileTwo->getId());
        profileTwo->addFriend(profileOne->getId());
    }
    return 0;
}

// Remove a connection between two users in the network
// Pre: s1 and s2 are valid user names in the network
// Post: Removes the connection between the users if it exists, returns -1 if not
int Network::removeConnection(std::string s1, std::string s2)
{
    User *profileOne = nullptr;
    User *profileTwo = nullptr;
    for (User *userPtr : users_)
    {
        if (userPtr->getName() == s1)
            profileOne = userPtr;
    }
    for (User *userPtr : users_)
    {
        if (userPtr->getName() == s2)
            profileTwo = userPtr;
    }
    if (!(profileOne && profileTwo))
        return -1;
    profileOne->deleteFriend(profileTwo->getId());
    profileTwo->deleteFriend(profileOne->getId());

    return 0;
}
// Get the unique ID associated with a user by their name
// Pre: name is a valid user name in the network
// Post: Returns the unique ID of the user if found, or 0 if not found
int Network::getId(std::string name)
{
    for (User *userPtr : users_)
    {
        if (userPtr->getName() == name)

            return userPtr->getId();
    }
    return -1;
}
// Get the total number of users in the network
// Pre: None
// Post: Returns the number of users in the network
std::size_t Network::numUsers()
{
    return users_.size();
}
// Get a User pointer by their unique ID
// Pre: id is a valid user ID in the network
// Post: Returns a pointer to the User object if found, or nullptr if not found
User *Network::getUser(std::size_t id)
{
    for (User *userPtr : users_)
    {
        if (userPtr->getId() == id)
            return userPtr;
    }
    return nullptr;
}
// Read user data from a file and add users to the network
// Pre: fname is the name of a valid file containing user data
// Post: Reads user data from the file and adds users to the network, returns -1 if there is an error reading the file
int Network::readUsers(char *fname)
{

    std::ifstream myfile;
    myfile.open(fname);
    std::string firstLine;
    // so we can skip the first line
    std::getline(myfile, firstLine);
    std::string myline;
    int i = 0;
    if (!myfile.is_open())
    {
        return -1; // Indicate failure
    }
    User *userRead = new User();
    while (std::getline(myfile, myline))
    {
        std::stringstream ss(myline);
        switch (i % 5)
        {
        case 0:
        {
            int id;
            ss >> id;
            userRead->setId(id);
            break;
        }
        case 1:
        {
            std::string fullname;
            std::string name;
            bool isFirst = true; // Flag to track the first name
            // concatanate full name
            while (ss >> name)
            {
                if (!isFirst)
                {
                    fullname += " "; // Add a space between names
                }
                fullname += name;
                isFirst = false;
            }
            userRead->setName(fullname);

            break;
        }
        case 2:
        {
            int birthYear;
            ss >> birthYear;
            userRead->setBirthYear(birthYear);

            break;
        }
        case 3:
        {
            int zipCode;
            ss >> zipCode;
            userRead->setZipCode(zipCode);

            break;
        }
        case 4:
        {
            std::size_t friends;
            std::vector<std::size_t> result;
            while (ss >> friends)
            {
                result.push_back(friends);
            }
            userRead->setFriendsList(result);
            users_.push_back(userRead);
            userRead = new User();
            break;
        }
        default:
            // Code to handle any other case not covered by the above cases
            break;
        }
        i++;
    }

    return 0;
}
// Write user data from the network to a file
// Pre: fname is the name of a valid file where user data will be written
// Post: Writes user data from the network to the file, returns -1 if there is an error writing to the file
int Network::writeUsers(char *fname)
{
    std::ofstream myfile(fname);

    if (!myfile.is_open())
    {
        return -1; // Indicate failure
    }
    myfile << users_.size() << std::endl;

    // Loop through the network's users_
    for (const User *user : users_)
    {
        // Write user information to the file
        myfile << user->getId() << std::endl;
        myfile << "\t" << user->getName() << std::endl;
        myfile << "\t" << user->getBirthYear() << std::endl;
        myfile << "\t" << user->getZipCode() << std::endl;

        // Write the IDs of connected users (assuming you have a method to get them)

        for (int friends : user->getFriendsList())
        {
            myfile << friends << " ";
        }
        myfile << std::endl;
    }

    myfile.close();

    return 0; // Indicate success
}
std::vector<std::size_t> Network::shortestPath(std::size_t from, std::size_t to)
{
    std::vector<size_t> parent(users_.size(), -1);
    std::queue<size_t> q;
    std::vector<bool> visited(users_.size(), 0);

    q.push(from);
    visited[from] = true;

    while (q.size() > 0)
    {
        size_t current_id = q.front();
        q.pop();

        // if (visited[current_id])
        //     continue;
        // visited[current_id] = true;

        // add friends to queue
        User *currentUser = getUser(current_id);
        if (currentUser == nullptr)
        {
            throw std::runtime_error("User not found");
        }
        std::vector<size_t> friendsList = currentUser->getFriendsList();
        for (size_t friendId : friendsList)
        {
            if (!visited[friendId])
            {
                q.push(friendId);
                visited[friendId] = true;
                parent[friendId] = current_id;
            }
        }
    }
    std::vector<size_t> shortestPath;
    // edge case checking the distance to users self
    if (to == from)
    {
        shortestPath.push_back(from);
        return shortestPath;
    }
    else
    {
        size_t endUser = to;
        while (endUser != from)
        {
            shortestPath.push_back(endUser);
            endUser = parent[endUser];
        }
        shortestPath.push_back(from);
        std::reverse(shortestPath.begin(), shortestPath.end());
    }
    return shortestPath;
}
std::vector<std::size_t> Network::distanceUser(std::size_t from, std::size_t &to, std::size_t distance)
{
    std::vector<size_t> parent(users_.size(), -1);
    std::stack<size_t> stck;
    std::vector<bool> visited(users_.size(), false);
    stck.push(from);

    while (!stck.empty() && distance > 0)
    {
        size_t current_id = stck.top();
        stck.pop();
        if (visited[current_id])
        {
            continue;
        }
        visited[current_id] = true;
        User *currentUser = getUser(current_id);
        std::vector<size_t> friendsList = currentUser->getFriendsList();
        for (size_t friendId : friendsList)
        {
            if (!visited[friendId])
            {
                stck.push(friendId);
                parent[friendId] = current_id;
                if (distance == 1)
                {
                    to = friendId; // Update 'to' if this friend is at the required distance
                    break;
                }
            }
        }
        distance--;
    }
    if (distance > 0)
    {
        // No user found within the specified distance
        to = -1;
        return std::vector<std::size_t>();
    }

    std::vector<size_t> nearestNeighbor;
    size_t endUser = to;
    while (endUser != from)
    {
        nearestNeighbor.push_back(endUser);
        endUser = parent[endUser];
    }
    nearestNeighbor.push_back(from);
    std::reverse(nearestNeighbor.begin(), nearestNeighbor.end());
    return nearestNeighbor;
}
std::vector<std::size_t> Network::suggestFriends(std::size_t who, std::size_t &score)
{
    std::queue<size_t> q;
    std::vector<bool> visited(users_.size(), 0);
    std::vector<size_t> distance(users_.size(), -1);
    std::vector<size_t> vectorOfDepthTwo;
    vectorOfDepthTwo.clear();

    distance[who] = 0;
    q.push(who);

    while (q.size() > 0)
    {
        size_t current_id = q.front();
        q.pop();

        if (visited[current_id])
            continue;
        visited[current_id] = true;

        // add friends to queue
        User *currentUser = getUser(current_id);
        std::vector<std::size_t> friendsList = currentUser->getFriendsList();
        for (size_t friendId : friendsList)
        {
            q.push(friendId);
            if (distance[friendId] == -1)
            {
                distance[friendId] = distance[current_id] + 1;
                if (distance[friendId] == 2 && (!visited[friendId]))
                {
                    vectorOfDepthTwo.push_back(friendId);
                }
            }
        }
    }
    for (size_t v : vectorOfDepthTwo)
    {
        std::cout << v << " ";
    }

    std::vector<size_t> usersWithHighScore;
    usersWithHighScore.clear();
    User *whosProfile = getUser(who);
    std::vector<size_t> whoVector = whosProfile->getFriendsList();
    std::unordered_set<size_t> friendsSet(whoVector.begin(), whoVector.end());
    size_t commonCount = 0;
    score = 0;
    // loop through Users of depth two
    for (size_t friendsList : vectorOfDepthTwo)
    {
        commonCount = 0;
        User *currentUser = getUser(friendsList);
        // count number of common friends
        for (size_t num : currentUser->getFriendsList())
        {
            if (friendsSet.find(num) != friendsSet.end())
            {
                commonCount++;
            }
        }
        if (commonCount > score)
        {
            score = commonCount;
            usersWithHighScore.clear();
            usersWithHighScore.push_back(friendsList);
        }
        else if (commonCount == score)
        {
            usersWithHighScore.push_back(friendsList);
        }
    }

    return usersWithHighScore;
}
std::vector<std::vector<std::size_t>> Network::groups()
{
    std::stack<User *> stck;
    std::vector<bool> visited(users_.size(), false);
    std::vector<std::vector<size_t>> allDisJointSet;

    for (User *user : users_)
    {
        if (!visited[user->getId()])
        {
            std::vector<size_t> disJointSet;
            stck.push(user);
            while (!stck.empty())
            {
                User *current_user = stck.top();
                size_t current_id = current_user->getId();
                stck.pop();
                if (visited[current_id])
                {
                    continue;
                }
                else
                {
                    disJointSet.push_back(current_id);
                    visited[current_id] = true;
                }

                for (size_t friendId : user->getFriendsList())
                {
                    if (!visited[friendId])
                    {
                        User *friends = getUser(friendId);
                        stck.push(friends);
                    }
                }
            }
            allDisJointSet.push_back(disJointSet);
        }
    }
    return allDisJointSet;
}
void Network::addPost(std::size_t ownerId, std::string message, std::size_t likes, bool incoming, std::size_t author, bool isPublic)
{
    // get the current user and author
    User *currentUser = getUser(ownerId);
    User *currentAuthor = getUser(author);
    if (incoming)
    {
        // if incoming post construct a incoming post
        IncomingPost *newIncomingPost = new IncomingPost(numMessages++, message, likes, isPublic, currentAuthor->getName());
        currentUser->addPost(newIncomingPost);
    }
    else
    {
        // construct new post
        Post *newPost = new Post(numMessages++, message, likes);
        currentUser->addPost(newPost);
    }
}
std::string Network::displayPosts(std::string name, std::size_t howMany, bool showOnlyPublic)
{
    std::size_t userId = getId(name);
    User *currentUser = getUser(userId);
    std::string allPosts = "";
    std::string userPost = "";
    if (currentUser)
    {
        userPost = currentUser->displayPosts(howMany, showOnlyPublic);
        allPosts += userPost;
    }
    return allPosts;
}
int Network::readPosts(char *filename)
{
    std::ifstream file;
    file.open(filename);

    if (!file.is_open())
    {
        std::cout << "Error: Unable to open file: " << filename << std::endl;
        return -1; // file not open or not found
    }

    int n;
    file >> n;

    for (int i = 0; i < n; i++)
    {
        std::size_t messageId;
        std::string first_name, last_name, name;
        std::string messageContents;
        size_t likes;
        size_t ownerId;
        bool isPublic = false;
        std::string visibilityFlag;

        file >> messageId;
        // Read and discard the newline character
        std::getline(file, visibilityFlag);
        std::getline(file, messageContents);

        // erase tab
        messageContents.erase(std::remove(messageContents.begin(), messageContents.end(), '\t'), messageContents.end());

        file >> ownerId;

        file >> likes;

        getline(file, visibilityFlag);
        getline(file, visibilityFlag);

        // check if line contains a string or is empty
        if (!visibilityFlag.empty())
        {
            // erase tab
            visibilityFlag.erase(std::remove(visibilityFlag.begin(), visibilityFlag.end(), '\t'), visibilityFlag.end());

            if (visibilityFlag == "public")
            {
                isPublic = true;
            }

            // concatenate full name
            file >> first_name;

            file >> last_name;

            name = first_name + " " + last_name;

            // pointer to user
            User *currentUser = getUser(ownerId);
            IncomingPost *currentPost = new IncomingPost(messageId, messageContents, likes, isPublic, first_name);
            currentUser->addPost(currentPost);
        }
        else
        {
            User *currentUser = getUser(ownerId);
            Post *currentPost = new Post(messageId, messageContents, likes);
            currentUser->addPost(currentPost);
        }
    }
    file.close();
    return 0;
}
