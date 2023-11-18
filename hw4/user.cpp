#include "user.h"
#include <vector>
#include <cassert>
#include <cmath>
#include <iostream>
#include <algorithm>
// Default constructor
// Pre: None
// Post: Creates an empty User object with default values
User::User()
{
    id_ = 0;
    name_ = "";
    birthYear_ = 0;
    zipCode_ = 0;
    friendsList_ = std::vector<size_t>();
}
// Parameterized constructor
// Pre: None
// Post: Creates a User object with the given attributes
User::User(size_t id, std::string name, size_t birthyear, size_t zipcode, std::vector<size_t> friends)
{
    id_ = id;
    name_ = name;
    birthYear_ = birthyear;
    zipCode_ = zipcode;
    friendsList_ = friends;
}
// Add a friend to the user's friends list
// Pre: None
// Post: Adds the specified friend's ID to the user's friends list
void User::addFriend(std::size_t id)
{
    if (std::find(friendsList_.begin(), friendsList_.end(), id) != friendsList_.end())
        return;
    friendsList_.push_back(id);
}
// Delete a friend from the user's friends list
// Pre: None
// Post: Removes the specified friend's ID from the user's friends list
void User::deleteFriend(std::size_t id)
{
    // Check if the friend with the given ID exists in the friends list
    auto it = std::find(friendsList_.begin(), friendsList_.end(), id);

    // If found, erase it from the list
    if (it != friendsList_.end())
    {
        friendsList_.erase(it);
    }
    // Otherwise, the friend with the given ID is not in the list, so no action is taken.
}
// Overloaded << operator for printing User objects
// Pre: None
// Post: Outputs the User object's information to the given ostream
std::ostream &operator<<(std::ostream &os, const User &b)
{
    os << b.id_ << " " << b.name_ << " " << b.birthYear_ << " " << b.zipCode_ << std::endl;
    return os;
}
void User::addPost(Post *P)
{
    messages_.push_back(P);
}
std::string User::displayPosts(std::size_t howMany, bool showOnlyPublic)
{
    std::string allPosts;
    if (messages_.empty())
    {
        return "No posts to display.";
    }
    for (int i = messages_.size() - 1; i >= 0 && howMany > 0; i--, howMany--)
    {
        Post *currentPost = messages_[i];
        std::string checkPublic = currentPost->displayPost();
        if (showOnlyPublic)
        {
            // concatanate only public messages to string
            if (checkPublic[0] == 'P' && checkPublic[1] == 'r' && checkPublic[7] == ':')
            {
                continue;
            }
            else
            {
                allPosts += checkPublic + "\n\n";
            }
        }
        else
        {
            std::string stringOfPost = currentPost->displayPost();
            allPosts += stringOfPost + "\n\n";
        }
    }
    return allPosts;
}
