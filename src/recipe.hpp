#ifndef _RECIPE_HPP
#define _RECIPE_HPP "_RECIPE_HPP"
#include <string>
#include <algorithm>
#include <math.h>
#include "defines.hpp"
#include "exceptions.hpp"
#include <iostream>
#include <sstream>
#include <iomanip>
class Recipe{
public:
	Recipe(Word title_ , Word ingredients_ , Word vegetarian_ , Word minuets_ , Word tags_ , Word image_ , int id_);
	void print_recipe();
	void print_recipes_summery();
	void print_chef_recipe();
	int get_id();
	Word get_rate();
	Word get_title();
	Word get_vegetarian();
	Word get_minutes();
	List get_tags();
	Word get_image_address();
	std::vector<float> get_rate_vector();
	void record_score(float score , Word username_);
	void new_score(float score , Word username_);
	Word print_recipe_infos_html();
	Word print_recipe_summery_html();
	bool has_given_score(Word username_);
private:
	List seperate_comma(Word str);
	float average_score();
	int id;
	Word title;
	List ingredients;
	Word vegetarian;
	Word minutes;
	List tags;
	Word image_address;
	Word rate;
	std::vector<float> rate_vector;
	List members_gave_rate;
};

#endif