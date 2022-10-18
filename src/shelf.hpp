#ifndef _SHELF_HPP
#define _SHELF_HPP "_SHELF_HPP"
#include <string>
#include <vector>
#include <iostream>
#include "recipe.hpp"
#include "exceptions.hpp"

class Shelf{
public:
	Shelf(Word name_ , int id_);
	void push_recipes(Recipe* recipe);
	std::vector<Recipe*> get_recipes();
	Word print_shelf();
	int get_id();
	Word get_name();
	void delete_recipe(int recipe_id);
	void erase_recipe_by_chef(int recipe_id);
private:
	Word name;
	int id;
	std::vector<Recipe*> recipes;
	void print_ok();
	int find_recipe(int recipe_id);
};

#endif