#ifndef POST_H
#define POST_H
#include <string>

class Post
{
public:
    // Default constructor
    // Pre: None
    // Post: Creates a Post object with default values
    Post();

    // Parameterized constructor
    // Pre: id, message, and likes are valid values
    // Post: Creates a Post object with specified id, message, and likes
    Post(std::size_t id, std::string message, std::size_t likes);

    // Virtual function to display post
    // Pre: None
    // Post: Returns a string representation of the post
    virtual std::string displayPost();

    // Getter for post ID
    std::size_t getId() { return id_; }

    // Getter for post message
    std::string getMessage() { return message_; }

    // Getter for post likes
    std::size_t getLikes() { return likes_; }

    // Setter for post ID
    void setId(std::size_t id) { id_ = id; }

    // Setter for post message
    void setMessage(std::string message) { message_ = message; }

    // Setter for post likes
    void setLikes(std::size_t likes) { likes_ = likes; }

private:
    std::size_t id_;
    std::string message_;
    std::size_t likes_;
};

class IncomingPost : public Post
{
public:
    // Default constructor
    // Pre: None
    // Post: Creates an IncomingPost object with default values
    IncomingPost();

    // Parameterized constructor
    // Pre: id, message, likes, isPublic, and author are valid values
    // Post: Creates an IncomingPost object with specified id, message, likes, isPublic, and author
    IncomingPost(std::size_t id, std::string message, std::size_t likes, bool isPublic, std::string author);

    // Function to display post
    // Pre: None
    // Post: Returns a string representation of the incoming post
    std::string displayPost();

    // Getter for post privacy status
    bool getIsPublic() { return isPublic_; }

    // Setter for post privacy status
    void setIsPublic(bool value) { isPublic_ = value; }

private:
    bool isPublic_;
};

#endif
