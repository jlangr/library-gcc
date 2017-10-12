#ifndef Vote_H
#define Vote_H

struct Vote {
    static Vote upvote(unsigned int messageId, unsigned int clientId) {
        return Vote(true, messageId, clientId);
    }

    static Vote downvote(unsigned int messageId, unsigned int clientId) {
        return Vote(false, messageId, clientId);
    }

    Vote(bool isUpvote, unsigned int messageId, unsigned int clientId) 
        : _isUpvote{isUpvote}
        , _messageId{messageId}
        , _clientId{clientId} {}
    virtual ~Vote() {}

    bool _isUpvote;
    unsigned int _messageId;
    unsigned int _clientId;
};

#endif
