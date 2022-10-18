#ifndef _FILTER_HPP
#define _FILTER_HPP "_FILTER_HPP"
#include <string>
#include <vector>
#include <iostream>
#include "member.hpp"
#include "recipe.hpp"
#include "defines.hpp"

class Filter{
protected:
	std::vector<Recipe*> filtered_recipes;
public:
	virtual void filter_recipes(std::vector<Recipe*> recipes) = 0;
	std::vector<Recipe*> get_filtered_recipes();
};

class TagFilter : public Filter{
public:
	TagFilter(std::string tag_);
	virtual void filter_recipes(std::vector<Recipe*> recipes);
private:
	std::string tag;
};

class VegetarianFilter : public Filter{
public:
	virtual void filter_recipes(std::vector<Recipe*> recipes);
};

class MinutesFilter : public Filter{
public:
	MinutesFilter(int min_ , int max_);
	virtual void filter_recipes(std::vector<Recipe*> recipes);
private:
	int min;
	int max;
};

class RateFilter : public Filter{
public:
	RateFilter(double min_ , double max_);
	virtual void filter_recipes(std::vector<Recipe*> recipes);
private:
	double min;
	double max;
};
#endif