#ifndef USER_H
#define USER_H
#include <cstddef>
#include <vector>
#include <string>
#include "post.h"
class User
{
public:
    // Default constructor
    // Pre: None
    // Post: Creates an empty User object with default values
    User();

    // Parameterized constructor
    // Pre: None
    // Post: Creates a User object with the given attributes
    User(size_t id, std::string name, size_t birthyear, size_t zipcode, std::vector<size_t> friends);

    // Add a friend to the user's friends list
    // Pre: None
    // Post: Adds the specified friend's ID to the user's friends list
    void addFriend(std::size_t id);

    // Delete a friend from the user's friends list
    // Pre: None
    // Post: Removes the specified friend's ID from the user's friends list
    void deleteFriend(std::size_t id);

    // Get the user's ID
    // Pre: None
    // Post: Returns the user's ID
    std::size_t getId() const { return id_; }

    // Get the user's name
    // Pre: None
    // Post: Returns the user's name
    std::string getName() const { return name_; }

    // Get the user's birth year
    // Pre: None
    // Post: Returns the user's birth year
    std::size_t getBirthYear() const { return birthYear_; }

    // Get the user's ZIP code
    // Pre: None
    // Post: Returns the user's ZIP code
    std::size_t getZipCode() const { return zipCode_; }

    // Get the list of user's friends
    // Pre: None
    // Post: Returns a vector containing the user's friends' IDs
    std::vector<size_t> getFriendsList() const { return friendsList_; }
    std::vector<Post *> getMessagesList() const { return messages_; }
    // Setter functions for all private variables
    void setId(std::size_t id) { id_ = id; }
    void setName(const std::string &name) { name_ = name; }
    void setBirthYear(std::size_t birthYear) { birthYear_ = birthYear; }
    void setZipCode(std::size_t zipCode) { zipCode_ = zipCode; }
    void setFriendsList(const std::vector<std::size_t> &friendsList) { friendsList_ = friendsList; }

    // Overloaded << operator for printing User objects
    // Pre: None
    // Post: Outputs the User object's information to the given ostream
    friend std::ostream &operator<<(std::ostream &os, const User &b);
    // Adds a post to the user's profile.
    // Pre: post points to a valid Post object.
    // Post: Adds the Post object to the user's profile.
    void addPost(Post *post);
    // Displays posts from the user's profile.
    // Pre: howMany is a valid number, and showOnlyPublic is a valid boolean value.
    // Post: Returns a string containing the user's posts, limited to 'howMany' posts and filtered based on 'showOnlyPublic'.
    std::string displayPosts(std::size_t howMany, bool showOnlyPublic);

private:
    size_t id_;
    std::string name_;
    size_t birthYear_;
    size_t zipCode_;
    std::vector<size_t> friendsList_;
    std::vector<Post *> messages_;
};

#endif
