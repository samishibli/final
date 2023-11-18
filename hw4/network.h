#ifndef NETWORK_H
#define NETWORK_H

#include <cstddef>
#include <vector>
#include <string>
#include "user.h" // Include the necessary header file for User

class Network
{
public:
    // Default constructor
    // Pre: None
    // Post: Creates an empty Network object
    Network();

    // Destructor
    // Pre: None
    // Post: Cleans up allocated resources when the Network object is destroyed
    ~Network();

    // Add a User pointer to the network
    // Pre: userPointer is a valid pointer to a User object
    // Post: Adds the User to the network
    void addUser(User *userPointer);

    // Add a connection between two users in the network
    // Pre: s1 and s2 are valid user names in the network
    // Post: Adds a connection between the users if they exist, returns -1 if not
    int addConnection(std::string s1, std::string s2);

    // Remove a connection between two users in the network
    // Pre: s1 and s2 are valid user names in the network
    // Post: Removes the connection between the users if it exists, returns -1 if not
    int removeConnection(std::string s1, std::string s2);

    // Get the unique ID associated with a user by their name
    // Pre: name is a valid user name in the network
    // Post: Returns the unique ID of the user if found, or 0 if not found
    int getId(std::string name);

    // Read user data from a file and add users to the network
    // Pre: fname is the name of a valid file containing user data
    // Post: Reads user data from the file and adds users to the network, returns -1 if there is an error reading the file
    int readUsers(char *fname);

    // Write user data from the network to a file
    // Pre: fname is the name of a valid file where user data will be written
    // Post: Writes user data from the network to the file, returns -1 if there is an error writing to the file
    int writeUsers(char *fname);

    // Get the total number of users in the network
    // Pre: None
    // Post: Returns the number of users in the network
    std::size_t numUsers();

    // Get a User pointer by their unique ID
    // Pre: id is a valid user ID in the network
    // Post: Returns a pointer to the User object if found, or nullptr if not found
    User *getUser(std::size_t id);

    // Get a vector containing pointers to all users in the network
    // Pre: None
    // Post: Returns a vector of User pointers representing all users in the network
    std::vector<User *> getUsers() { return users_; }

    // Returns a vector of user IDs representing the shortest path from user from to user to.
    // Pre: from and to are valid user IDs in the network.
    std::vector<std::size_t> shortestPath(std::size_t from, std::size_t to);

    // Returns a vector of user IDs representing users at the specified distance from user from.
    // Modifies to to the user ID found at exactly distance steps away from from.
    // Pre: from is a valid user ID in the network, to is a user ID to find distance to, and distance is the maximum distance allowed for the search.
    std::vector<std::size_t> distanceUser(std::size_t from, std::size_t &to, std::size_t distance);

    // Returns a vector of user IDs representing potential friends for the user who.
    // Modifies score to the score indicating the strength of the friendship suggestion.
    // Pre: who is a valid user ID in the network.
    std::vector<std::size_t> suggestFriends(std::size_t who, std::size_t &score);

    // Returns a vector of vectors of user IDs representing groups of users in the network.
    // Each inner vector represents a group of connected users.
    // Pre: None.
    std::vector<std::vector<std::size_t>> groups();

    // Adds a post to the network.
    // Pre: ownerId is a valid user ID, message is a non-empty string, likes is a valid number, author is a valid user ID, and incoming is a valid boolean value.
    void addPost(std::size_t ownerId, std::string message, std::size_t likes, bool incoming, std::size_t author, bool isPublic);

    // Displays posts from the specified user or group.
    // Pre: name is a non-empty string, howMany is a valid number, and showOnlyPublic is a valid boolean value.
    // Post: Returns a string containing posts from the specified user or group, limited to 'howMany' posts and filtered based on 'showOnlyPublic'.
    std::string displayPosts(std::string name, std::size_t howMany, bool showOnlyPublic);

    // Reads posts from a file and populates the network.
    // Pre: filename is a valid C-style string.
    // Post: Returns an integer indicating the success status of reading posts from the file.
    int readPosts(char *filename);

private:
    std::vector<User *> users_;
    std::size_t numMessages;
};

#endif
