#include "handlers.hpp"
using namespace std;

Word style_table_css()
{
  stringstream body;
  body << "<head>" << endl
      << "<style>" << endl
      << "table { border-collapse: collapse;" << endl
      << "width: 100%; }" << endl
      << "th, td { padding: 8px;" << endl
      << "text-align: left;" << endl
      << "border-bottom: 1px solid #ddd;}" << endl
      << "tr:nth-child(even){background-color: #f2f2f2}" << endl
      << "th { background-color: rgb(277,11,92); color: white; }" << endl
      << "</style>" << endl
      << "</head>" << endl;
  return body.str();
}

Word HomeHandler::tag_filter(){
  stringstream body;
  body << "<form action='/tagfilter' method='post'>" << endl
        << "<input name='tag' type='text' placeholder='Tag' />" << endl;
  if(website->tag_filter_on()){
    body << "<button style='background-color: rgb(277,11,92);type='submit' >Set Filter</button>" << endl;
  }
  else{
    body << "<button type='submit' >Set Filter</button>" << endl;
  }
  body << "</form>" << endl
      << "</div>" << endl;
  return body.str();
}

Word HomeHandler::minutes_filter(){
  stringstream body;
  body << "<form action='/minutesfilter' method='post'>" << endl
      << "<input name='min_minutes' type='text' placeholder='Min Minutes' />" << endl
      << "<input name='max_minutes' type='text' placeholder='Max Minutes' />" << endl;
  if(website->minutes_filter_on()){
    body << "<button style='background-color: rgb(277,11,92);type='submit' >Set Filter</button>" << endl;
  }
  else{
    body << "<button type='submit' >Set Filter</button>" << endl;
  }
  body << "</form>" << endl
      << "</div>" << endl;
  return body.str();
}

Word HomeHandler::rate_filter(){
  stringstream body;
  body << "<form action='/ratefilter' method='post'>" << endl
      << "<input name='min_rate' type='text' placeholder='Min Rate' />" << endl
      << "<input name='max_rate' type='text' placeholder='Max Rate' />" << endl;
  if(website->rate_filter_on()){
    body << "<button style='background-color: rgb(277,11,92);type='submit' >Set Filter</button>" << endl;
  }
  else{
    body << "<button type='submit' >Set Filter</button>" << endl;
  }
  body << "</form>" << endl
      << "</div>" << endl;
  return body.str();
}

Word HomeHandler::vegetarian_filter(){
  stringstream body;
  body << "<form action='/vegetarianfilter' method='get'>" << endl;
  if(website->vegetarian_filter_on()){
    body << "<button style='background-color: rgb(277,11,92);type='submit' >Vegetarian Filter</button>" << endl;
  }
  else{
    body << "<button type='submit' >Vegetarian Filter</button>" << endl;
  }
  body << "</form>" << endl
      << "</div>" << endl;
  return body.str();
}

Word HomeHandler::filter_stuff()
{
  stringstream body;
  body << "<div style='text-align: left;'>" << endl
      << tag_filter() << endl
      << "<div style='text-align: left;'>" << endl
      << rate_filter() << endl
      << "<div style='text-align: left;'>" << endl
      << minutes_filter() << endl
      << "<div style='text-align: left;'>" << endl
      << vegetarian_filter() << endl
      << "<div style='text-align: left;'>" << endl
      << "<form action='/deletefilters' method='get'>" << endl
      << "<button type='submit' >Delete Filters</button>" << endl
      << "</form>" << endl
      << "</div>" << endl;

  return body.str();
}

Response *HomeHandler::callback(Request *req)
{
  Response *res = new Response;
  try
  {
    res->setHeader("Content-Type", "text/html");
    stringstream body;
    body << "<!DOCTYPE html>" << endl
        << "<html>" << endl
        << "<body style='background-color: rgb(255,245,238);text-align: center;'>" << endl
        << "<h1>Home Page GoodEats</h1>" << endl
        << "<img src='/uni.png' style='width:20%;'>" << endl;

    if(req->getSessionId() == "" )
    {
      body << "<br>" << endl
          << "<a href='/login'>Login</a>" << endl
          << "<br>" << endl
          << "<a href='/signup'>Signup</a>" << endl;
    }
    else
    {
      if(website->member_user(req->getSessionId())){
        body << "<br>" << endl
            << "<h2>Welcome " << req->getSessionId() << "</h2>" << endl
            << "<a href='/logout'>Logout</a>" << endl
            << "<div>" << endl
            << "<form action='/shelvespage' method='get'>" << endl
            << "<button type='submit' >My Shelves</button>" << endl
            << "</form>" << endl
            << "</div>" << endl
            << "<div>" << endl
            << filter_stuff() << endl
            << "<div style='text-align: center;'>" << endl
            << style_table_css()
            << website->show_all_recipes() << endl
            << "</div>" << endl;
      }
      else{
        body << "<br>" << endl
            << "<h2>Welcome " << req->getSessionId() << "</h2>" << endl
            << "<a href='/logout'>Logout</a>" << endl
            << "<div>" << endl
            << "<form action='/addrecipe' method='get'>" << endl
            << "<button type='submit' >Add Recipe</button>" << endl
            << "</form>" << endl
            << "</div>" << endl
            << "<div>" << endl
            << "<form action='/deleterecipe' method='get'>" << endl
            << "<button type='submit' >Delete Recipe</button>" << endl
            << "</form>" << endl
            << "</div>" << endl
            << "<div style='text-align: center;'>" << endl
            << style_table_css()
            << website->show_chef_recipes() << endl
            << "</div>" << endl;
      }
    }
    
    body << "</body>" << endl
        << "</html>" << endl;
    res->setBody(body.str());
  }
  catch(const Exception& ex)
  {
    std::cerr << ex.what() << '\n';
    res = Response::redirect(ex.path());
  }
  return res;
}

Response *SignUpHandler::callback(Request *req) {
  string username = req->getBodyParam("username");
  string password = req->getBodyParam("password");
  string type = req->getBodyParam("type");
  Response *res = new Response;
  try
  {
    website->add_member(username, password, type);
    res = Response::redirect("/");
    res->setSessionId(website->get_current_user_name());
  }
  catch(const Exception& ex)
  {
    std::cerr << ex.what() << '\n';
    res = Response::redirect(ex.path());
  }
  return res;
}

Response *LoginHandler::callback(Request *req) {
  string username = req->getBodyParam("username");
  string password = req->getBodyParam("password");
  Response *res = new Response;
  try
  {
    website->login(username, password);
    res = Response::redirect("/");
    res->setSessionId(website->get_current_user_name());
  }
  catch(const Exception& ex)
  {
    std::cerr << ex.what() << '\n';
    res = Response::redirect(ex.path());
  }
  return res;
}

Response *LogoutHandler::callback(Request *req) {
  Response *res = new Response;
  try
  {
    website->logout();
    res = Response::redirect("/");
    res->setSessionId("");
  }
  catch(const Exception& ex)
  {
    std::cerr << ex.what() << '\n';
    res = Response::redirect(ex.path());
  }
  return res;
}

Response *TagFilterHandler::callback(Request *req) {
  Response *res = new Response;
  try
  {
    string tag = req->getBodyParam("tag");
    website->tag_filter(tag);
    res = Response::redirect("/");
  }
  catch(const Exception& ex)
  {
    std::cerr << ex.what() << '\n';
    res = Response::redirect(ex.path());
  }
  return res;
}

Response *RateFilterHandler::callback(Request *req) {
  Response *res = new Response;
  try
  {
    string min_rate = req->getBodyParam("min_rate");
    string max_rate = req->getBodyParam("max_rate");
    website->rate_filter(stod(min_rate), stod(max_rate));
    res = Response::redirect("/");
  }
  catch(const Exception& ex)
  {
    std::cerr << ex.what() << '\n';
    res = Response::redirect(ex.path());
  }
  catch(...)
  {
    res = Response::redirect(PATH_BAD_REQUEST);
  }
  return res;
}

Response *MinutesFilterHandler::callback(Request *req) {
  Response *res = new Response;
  try
  {
    string min_minutes = req->getBodyParam("min_minutes");
    string max_minutes = req->getBodyParam("max_minutes");
    website->minutes_filter(stoi(min_minutes), stoi(max_minutes));
    res = Response::redirect("/");
  }
  catch(const Exception& ex)
  {
    std::cerr << ex.what() << '\n';
    res = Response::redirect(ex.path());
  }
  catch(...)
  {
    res = Response::redirect(PATH_BAD_REQUEST);
  }
  return res;
}

Response *VegetarianFiltersHandler::callback(Request *req) {
  Response *res = new Response;
  try
  {
    website->vegetarian_filter();
    res = Response::redirect("/");
  }
  catch(const Exception& ex)
  {
    std::cerr << ex.what() << '\n';
    res = Response::redirect(ex.path());
  }
  return res;
}

Response *DeleteFiltersHandler::callback(Request *req) {
  Response *res = new Response;
  try
  {
    website->delete_filters();
    res = Response::redirect("/");
  }
  catch(const Exception& ex)
  {
    std::cerr << ex.what() << '\n';
    res = Response::redirect(ex.path());
  }
  return res;
}

Word RecipeHandler::rate_stuff(int recipe_id)
{
  stringstream body;
  if(website->user_gave_score(recipe_id))
  {
    body << "<form action='/changerate' method='post'>" << endl
      << "<input type='hidden' name='recipe_id' value='" << recipe_id << "'/>"
      << "<input name='score' type='text' placeholder='score' />" << endl
      << "<button type='submit' >Change Score</button>" << endl
      << "</form>"
      << "</div>";
  }
  else
  {
    body << "<form action='/giverate' method='post'>" << endl
      << "<input type='hidden' name='recipe_id' value='" << recipe_id << "'/>"
      << "<input name='score' type='text' placeholder='score' />" << endl
      << "<button type='submit' >Give Score</button>" << endl
      << "</form>"
      << "</div>";
  }
  return body.str();
}

Response *RecipeHandler::callback(Request *req) {
  Response *res = new Response;
  try
  {
    res->setHeader("Content-Type", "text/html");
    int recipe_id = stoi(req->getQueryParam("id"));
    stringstream body;
    body << "<!DOCTYPE html>" << endl
        << "<html>" << endl
        << "<body style='background-color: rgb(255,245,238);text-align: center;'>" << endl
        << "<h1>Recipe Info</h1>" << endl
        << "<a href='/logout'>Logout</a>" << endl
        << "<div style='text-align: center;'>" << endl
        << style_table_css()
        << website->show_recipe(recipe_id) << endl
        << "</div>"
        << "<div>" << endl
        << rate_stuff(recipe_id) << endl
        << "</div" << endl
        << "<div>" << endl
        << "<form action='/' method='get'>" << endl
        << "<button type='submit' >Main Page</button>" << endl
        << "</form>" << endl
        << "</div>" << endl
        << "</body>" << endl
        << "</html>" << endl;
    res->setBody(body.str());
  }
  catch(const Exception& ex)
  {
    std::cerr << ex.what() << '\n';
    res = Response::redirect(ex.path());
  }
  catch(...)
  {
    res = Response::redirect(PATH_BAD_REQUEST);
  }
  return res;
}

Response *GiveRateHandler::callback(Request *req) {
  Response *res = new Response;
  try
  {
    string recipe_id = req->getBodyParam("recipe_id");
    website->give_score(stoi(recipe_id) , stof(req->getBodyParam("score")));
    res = Response::redirect("/recipe?id=" + recipe_id);
  }
  catch(const Exception& ex)
  {
    std::cerr << ex.what() << '\n';
    res = Response::redirect(ex.path());
  }
  catch(...)
  {
    res = Response::redirect(PATH_BAD_REQUEST);
  }
  return res;
}

Response *ChangeRateHandler::callback(Request *req) {
  Response *res = new Response;
  try
  {
    string recipe_id = req->getBodyParam("recipe_id");
    website->change_score(stoi(recipe_id) , stof(req->getBodyParam("score")));
    res = Response::redirect("/recipe?id=" + recipe_id);
  }
  catch(const Exception& ex)
  {
    std::cerr << ex.what() << '\n';
    res = Response::redirect(ex.path());
  }
  catch(...)
  {
    res = Response::redirect(PATH_BAD_REQUEST);
  }
  return res;
}

Response *ShelfHandler::callback(Request *req) {
  Response *res = new Response;
  try
  {
    res->setHeader("Content-Type", "text/html");
    int shelf_id = stoi(req->getQueryParam("id"));
    stringstream body;
    body << "<!DOCTYPE html>" << endl
        << "<html>" << endl
        << "<body style='background-color: rgb(255,245,238);text-align: center;'>" << endl
        << "<h1>Shelf ID: " << shelf_id << "   Shelf Name: " << website->give_shelf_name(shelf_id) << "</h1>" << endl
        << "<a href='/logout'>Logout</a>" << endl
        << "<div style='text-align: center;'>" << endl
        << style_table_css()
        << website->show_shelves_recipes(shelf_id) << endl
        << "</div>" << endl
        << "<div>" << endl
        << "<form action='/addrecipeshelf' method='post'>" << endl
        << "<input type='hidden' name='id' value='" << shelf_id << "'/>"
        << "<input name='recipe_id' type='text' placeholder='Recipe id' />" << endl
        << "<button type='submit' >Add recipe</button>" << endl
        << "</form>" << endl
        << "</div" << endl
        << "<div>" << endl
        << "<form action='/' method='get'>" << endl
        << "<button type='submit' >Main Page</button>" << endl
        << "</form>" << endl
        << "</div>" << endl
        << "</body>" << endl
        << "</html>" << endl;
    res->setBody(body.str());
  }
  catch(const Exception& ex)
  {
    std::cerr << ex.what() << '\n';
    res = Response::redirect(ex.path());
  }
  catch(...)
  {
    res = Response::redirect(PATH_BAD_REQUEST);
  }
  return res;
}

Response *ShelvesPageHandler::callback(Request *req) {
  Response *res = new Response;
  try
  {
    res->setHeader("Content-Type", "text/html");
    stringstream body;
    body << "<!DOCTYPE html>" << endl
        << "<html>" << endl
        << "<body style='background-color: rgb(255,245,238);text-align: center;'>" << endl
        << "<h1>Shelves Page</h1>" << endl
        << "<a href='/logout'>Logout</a>" << endl
        << "<div style='text-align: center;'>" << endl
        << style_table_css()
        << website->show_shelves(website->get_current_user_name() , 20) << endl
        << "</div>" << endl
        << "<div>" << endl
        << "<form action='/addshelf' method='get'>" << endl
        << "<button type='submit' >New Shelf</button>" << endl
        << "</form>" << endl
        << "</div>" << endl
        << "<div>" << endl
        << "<form action='/' method='get'>" << endl
        << "<button type='submit' >Main Page</button>" << endl
        << "</form>" << endl
        << "</div>" << endl
        << "<div style='text-align: center;'>" << endl
        << "</div>" << endl
        << "</body>" << endl
        << "</html>" << endl;
    res->setBody(body.str());
  }
  catch(const Exception& ex)
  {
    std::cerr << ex.what() << '\n';
    res = Response::redirect(ex.path());
  }
  return res;
}

Response *AddRecipeHandler::callback(Request *req) {
  Response *res = new Response;
  Word title = req->getBodyParam("title");
  Word ingredients = req->getBodyParam("ingredients");
  Word minutes_to_ready = req->getBodyParam("minutes_to_ready");
  Word tags = req->getBodyParam("tags");
  Word image_address = req->getBodyParam("image_address");
  try
  {
    Word vegetarian;
    if(req->getBodyParam("vegetarian") == "Yes")
      vegetarian = "Yes";
    else
      vegetarian = "No";
    website->add_recipes(title , ingredients , vegetarian , minutes_to_ready , tags , image_address);
    res = Response::redirect("/");
  }
  catch(const Exception& ex)
  {
    std::cerr << ex.what() << '\n';
    res = Response::redirect(ex.path());
  }
  return res;
}

Response *DeleteRecipeHandler::callback(Request *req) {
  Response *res = new Response;
  Word id = req->getBodyParam("id");
  try
  {
    website->delete_recipe(stoi(id));
    res = Response::redirect("/");
  }
  catch(const Exception& ex)
  {
    std::cerr << ex.what() << '\n';
    res = Response::redirect(ex.path());
  }
  return res;
}

Response *AddShelfHandler::callback(Request *req) {
  Response *res = new Response;
  Word name = req->getBodyParam("name");
  try
  {
    website->add_shelf(name);
    res = Response::redirect("/shelvespage");
  }
  catch(const Exception& ex)
  {
    std::cerr << ex.what() << '\n';
    res = Response::redirect(ex.path());
  }
  return res;
}

Response *AddRecipeShelfHandler::callback(Request *req) {
  Response *res = new Response;
  try
  {
    string shelf_id = req->getBodyParam("id");
    website->recipe_on_shelf(stoi(shelf_id) , stoi(req->getBodyParam("recipe_id")));
    res = Response::redirect("/shelf?id=" + shelf_id);
  }
  catch(const Exception& ex)
  {
    std::cerr << ex.what() << '\n';
    res = Response::redirect(ex.path());
  }
  catch(...)
  {
    res = Response::redirect(PATH_BAD_REQUEST);
  }
  return res;
}

