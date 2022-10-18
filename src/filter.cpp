#include "filter.hpp"

std::vector<Recipe*> Filter::get_filtered_recipes(){
	return filtered_recipes;
}
TagFilter::TagFilter(std::string tag_){
	tag = tag_;
}
void TagFilter::filter_recipes(std::vector<Recipe*> recipes){
	filtered_recipes.clear();
	for(int i = 0 ; i < recipes.size() ; i++){
		List recipe_tags = recipes[i]->get_tags();
		if(std::find(recipe_tags.begin(), recipe_tags.end(), tag) != recipe_tags.end())
			filtered_recipes.push_back(recipes[i]);
	}
}

void VegetarianFilter::filter_recipes(std::vector<Recipe*> recipes){
	filtered_recipes.clear();
	for(int i = 0 ; i < recipes.size() ; i++){
		Word recipe_vegetarian = recipes[i]->get_vegetarian();
		if(recipe_vegetarian == YES_EXPRETION)
			filtered_recipes.push_back(recipes[i]);
	}
}

MinutesFilter::MinutesFilter(int min_ , int max_){
	min = min_;
	max = max_;
}
void MinutesFilter::filter_recipes(std::vector<Recipe*> recipes){
	filtered_recipes.clear();
	for(int i = 0 ; i < recipes.size() ; i++){
		Word recipe_minutes = recipes[i]->get_minutes();
		if((std::stoi(recipe_minutes) >= min) && (std::stoi(recipe_minutes) <= max))
			filtered_recipes.push_back(recipes[i]);
	}
}

RateFilter::RateFilter(double min_ , double max_){
	min = min_;
	max = max_;
}
void RateFilter::filter_recipes(std::vector<Recipe*> recipes){
	filtered_recipes.clear();
	for(int i = 0 ; i < recipes.size() ; i++){
		Word recipe_minutes = recipes[i]->get_rate();
		if((std::stod(recipe_minutes) >= min) && (std::stod(recipe_minutes) <= max))
			filtered_recipes.push_back(recipes[i]);
	}
}
