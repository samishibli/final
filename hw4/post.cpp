#include "post.h"
#include "user.h"
#include "network.h"
#include <string>

Post::Post()
{
    id_ = 0;
    message_ = "";
    likes_ = 0;
}
Post::Post(std::size_t id, std::string message, std::size_t likes)
{
    id_ = id;
    message_ = message;
    likes_ = likes;
}
std::string Post::displayPost()
{
    std::string postString = "";
    postString = message_ + "\nLiked By " + std::to_string(likes_) + " people";
    return postString;
}
IncomingPost::IncomingPost()
{
    isPublic_ = false;
}
IncomingPost::IncomingPost(std::size_t id, std::string message, std::size_t likes, bool isPublic, std::string author) : Post(id, message + " From: " + author, likes)
{
    isPublic_ = isPublic;
}
std::string IncomingPost::displayPost()
{
    std::string incomingPostString = "";
    if (isPublic_)
    {
        incomingPostString = "Public: " + Post::displayPost();
    }
    else
    {
        incomingPostString = "Private: " + Post::displayPost();
    }
    return incomingPostString;
}
