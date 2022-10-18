#ifndef _WEBSITE_HPP
#define _WEBSITE_HPP "_WEBSITE_HPP"
#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include "member.hpp"
#include "recipe.hpp"
#include "exceptions.hpp"
#include "defines.hpp"
#include "shelf.hpp"
#include "filter.hpp"

class Website{
public:
	Website();
	void add_member(Word username_ , Word password_ , Word type);
	Word get_current_user_name();
	void login(Word username_ , Word password_);
	void logout();
	void add_recipes(Word title_ , Word ingredients_ , Word vegetarian_ , Word minutes_ , Word tags_ , Word image_);
	Word show_all_recipes();
	Word show_recipe(int id);
	void give_score(int id , float score);
	void change_score(int id , float score);
	void add_shelf(Word name_);
	Word show_shelves(Word username_ , int limit);
	void recipe_on_shelf(int shelf_id , int recipe_id);
	Word show_shelves_recipes(int shelf_id);
	void delete_shelf_recipe(int shelf_id , int recipe_id);
	void show_chefs();
	void show_chef(Word username_);
	void show_users();
	void delete_recipe(int id);
	Word show_chef_recipes();
	void tag_filter(Word tag_);
	void vegetarian_filter();
	void minutes_filter(int min , int max);
	void rate_filter(double min , double max);
	void delete_filters();
	bool member_user(Word username_);
	bool user_gave_score(int id);
	Word give_shelf_name(int id);
	bool tag_filter_on();
	bool vegetarian_filter_on();
	bool minutes_filter_on();
	bool rate_filter_on();
	Word get_recipe_image(int id_);
private:
	int recipes_count;
	int shelves_count;
	Filter* filter1;
	Filter* filter2;
	Filter* filter3;
	Filter* filter4;
	std::vector<Recipe*> recipes;
	std::vector<Recipe*> deleted_recipes;
	std::vector<Shelf*> shelves;
	Member* current_member;
	std::vector<Member*> members;

	int min(int a , int b);
	Member* find_member_by_id(Word username_);
	bool does_member_exist(Word username_);
	std::vector<Recipe*> sort_recipes(std::vector<Recipe*> recipe_list);
	std::vector<Member*> sort_members(std::vector<Member*> member_list);
	Recipe* find_recipe_by_title(Word title_);
	Recipe* find_recipe_by_id(int id_);
	int find_recipe_index_by_id(int id_);
	Shelf* find_shelf_by_id(int id_);
	std::vector<Recipe*> find_filtered_recipes();
	void disable_filters();
};

#endif