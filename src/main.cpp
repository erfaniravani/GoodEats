#include <iostream>
#include "handlers.hpp"
#include "my_server.hpp"
#include "website.hpp"
#include "exceptions.hpp"
#include "defines.hpp"
using namespace std;

int main(){
  try
  {
    Website* website = new Website();
    
    Server server(8080);
    server.get("/" , new HomeHandler(website));
    server.get("/uni.png" , new ShowImage("static/uni.png"));
    server.get("/signup", new ShowPage("static/sign_up.html"));
    server.post("/signup", new SignUpHandler(website));
    server.get("/login", new ShowPage("static/login.html"));
    server.post("/login", new LoginHandler(website));
    server.get("/logout", new LogoutHandler(website));
    server.post("/tagfilter", new TagFilterHandler(website));
    server.post("/ratefilter", new RateFilterHandler(website));
    server.post("/minutesfilter", new MinutesFilterHandler(website));
    server.get("/vegetarianfilter", new VegetarianFiltersHandler(website));
    server.get("/deletefilters", new DeleteFiltersHandler(website));
    server.get(PATH_EMPTY, new ShowPage("static/empty_err.html"));
    server.get(PATH_NOT_FOUND, new ShowPage("static/not_found_err.html"));
    server.get(PATH_BAD_REQUEST, new ShowPage("static/bad_req_err.html"));
    server.get(PATH_PERMISSION_DENIED, new ShowPage("static/permition_err.html"));
    server.get("/addrecipe", new ShowPage("static/add_recipe.html"));
    server.post("/addrecipe", new AddRecipeHandler(website));
    server.get("/deleterecipe", new ShowPage("static/delete_recipe.html"));
    server.post("/deleterecipe", new DeleteRecipeHandler(website));
    server.get("/recipe", new RecipeHandler(website));

    server.post("/giverate", new GiveRateHandler(website));
    server.post("/changerate", new ChangeRateHandler(website));
    
    server.get("/shelvespage", new ShelvesPageHandler(website));
    server.get("/addshelf", new ShowPage("static/add_shelf.html"));
    server.post("/addshelf", new AddShelfHandler(website));
    server.get("/shelf", new ShelfHandler(website));
    server.post("/addrecipeshelf", new AddRecipeShelfHandler(website));
    

    server.run();
  }
  catch(Server::Exception ex)
  {
    cerr << ex.getMessage() << endl;
  }

  return 0;
}