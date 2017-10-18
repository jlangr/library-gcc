#ifndef CLASSIFICATION_SERVICE_H
#define CLASSIFICATION_SERVICE_H

#include <string>
#include <stdexcept>

#include "Book.h"

class ClassificationService {
public:
    ClassificationService(void);
    ~ClassificationService(void);

    Book retrieveDetails(const std::string& classification) const;
};

class ClassificationNotFoundException: public std::runtime_error
{
public:
    ClassificationNotFoundException(const std::string& classification) 
        : std::runtime_error("classification " + classification + " not found") {}

    ~ClassificationNotFoundException() {}

private:
    std::string mClassification;
};

#endif
