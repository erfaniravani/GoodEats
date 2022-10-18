#ifndef _HANDLERS_HPP
#define _HANDLERS_HPP

#include "../server/server.hpp"
#include <iostream>
#include <sstream>
#include "website.hpp"
#include "defines.hpp"
#include "exceptions.hpp"

class HomeHandler : public RequestHandler
{
private:
  Website* website;
  Word filter_stuff();
  Word tag_filter();
  Word minutes_filter();
  Word rate_filter();
  Word vegetarian_filter();
public:
  HomeHandler(Website* wbs) : website(wbs) {}
  Response *callback(Request *);
};

class SignUpHandler : public RequestHandler
{
private:
  Website* website;
public:
  SignUpHandler(Website* wbs) : website(wbs) {}
  Response *callback(Request *);
};

class LoginHandler : public RequestHandler
{
private:
  Website* website;
public:
  LoginHandler(Website* wbs) : website(wbs) {}
  Response *callback(Request *);
};

class LogoutHandler : public RequestHandler
{
private:
  Website* website;
public:
  LogoutHandler(Website* wbs) : website(wbs) {}
  Response *callback(Request *);
};

class TagFilterHandler : public RequestHandler
{
private:
  Website* website;
public:
  TagFilterHandler(Website* wbs) : website(wbs) {}
  Response *callback(Request *);
};

class RateFilterHandler : public RequestHandler
{
private:
  Website* website;
public:
  RateFilterHandler(Website* wbs) : website(wbs) {}
  Response *callback(Request *);
};

class MinutesFilterHandler : public RequestHandler
{
private:
  Website* website;
public:
  MinutesFilterHandler(Website* wbs) : website(wbs) {}
  Response *callback(Request *);
};

class VegetarianFiltersHandler : public RequestHandler
{
private:
  Website* website;
public:
  VegetarianFiltersHandler(Website* wbs) : website(wbs) {}
  Response *callback(Request *);
};

class DeleteFiltersHandler : public RequestHandler
{
private:
  Website* website;
public:
  DeleteFiltersHandler(Website* wbs) : website(wbs) {}
  Response *callback(Request *);
};

class RecipeHandler : public RequestHandler
{
private:
  Website* website;
  Word rate_stuff(int recipe_id);
public:
  RecipeHandler(Website* wbs) : website(wbs) {}
  Response *callback(Request *);
};

class GiveRateHandler : public RequestHandler
{
private:
  Website* website;
public:
  GiveRateHandler(Website* wbs) : website(wbs) {}
  Response *callback(Request *);
};

class ChangeRateHandler : public RequestHandler
{
private:
  Website* website;
public:
  ChangeRateHandler(Website* wbs) : website(wbs) {}
  Response *callback(Request *);
};

class ShelfHandler : public RequestHandler
{
private:
  Website* website;
public:
  ShelfHandler(Website* wbs) : website(wbs) {}
  Response *callback(Request *);
};

class ShelvesPageHandler : public RequestHandler
{
private:
  Website* website;
public:
  ShelvesPageHandler(Website* wbs) : website(wbs) {}
  Response *callback(Request *);
};

class AddRecipeHandler : public RequestHandler
{
private:
  Website* website;
public:
  AddRecipeHandler(Website* wbs) : website(wbs) {}
  Response *callback(Request *);
};

class DeleteRecipeHandler : public RequestHandler
{
private:
  Website* website;
public:
  DeleteRecipeHandler(Website* wbs) : website(wbs) {}
  Response *callback(Request *);
};

class AddShelfHandler : public RequestHandler
{
private:
  Website* website;
public:
  AddShelfHandler(Website* wbs) : website(wbs) {}
  Response *callback(Request *);
};

class AddRecipeShelfHandler : public RequestHandler
{
private:
  Website* website;
public:
  AddRecipeShelfHandler(Website* wbs) : website(wbs) {}
  Response *callback(Request *);
};

#endif