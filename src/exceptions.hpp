#ifndef _EXCEPTIONS_HPP
#define _EXCEPTIONS_HPP "_EXCEPTIONS_HPP"
#include <exception>
#include "defines.hpp"

class Exception : public std::exception
{
public:
    virtual std::string path() const = 0;
};

class NotFound : public Exception
{
public:
    virtual char const*
    what() const throw()
    { return ERROR_NOT_FOUND; }
    virtual std::string path() const { return PATH_NOT_FOUND; }
};

class BadRequest : public Exception
{
public:
    virtual char const*
    what() const throw()
    { return ERROR_BAD_REQUEST; }
    virtual std::string path() const { return PATH_BAD_REQUEST; }
};

class PermissionDenied : public Exception
{
public:
    virtual char const*
    what() const throw()
    { return ERROR_PERMISSION_DENIED; }
    virtual std::string path() const { return PATH_PERMISSION_DENIED; }
};

class Empty : public Exception
{
public:
    virtual char const*
    what() const throw()
    { return ERROR_EMPTY; }
    virtual std::string path() const { return PATH_EMPTY; }
};

#endif