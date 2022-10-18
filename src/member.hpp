#ifndef _MEMBER_HPP
#define _MEMBER_HPP "_MEMBER_HPP"
#include <string>
#include <vector>
#include <iostream>
#include <math.h>
#include "defines.hpp"
#include "exceptions.hpp"
#include "recipe.hpp"

class Member{
public:
	Member(Word username_ , Word password_);
	bool username_exist(Word username_);
	bool correct_info(Word username_ , Word password_);
	virtual void save_recipe_id(int id) = 0;
	virtual void save_recipe(Recipe* recipe) = 0;
	virtual int print_chefs() = 0;
	virtual void print_chef() = 0;
	virtual int print_users() = 0;
	virtual std::vector<Recipe*> get_recipes() = 0;
	virtual void delete_chef_recipe(int id_) = 0;
	virtual void for_user() = 0;
	virtual void for_chefs() = 0;
	virtual void add_deleted_recipes(Recipe* deleted) = 0;
	virtual bool is_user() = 0;
	void save_shelf_id(int id);
	Word get_username();
	std::vector<int> get_shelf_id();
protected:
	Word username;
	Word password;
	std::vector<int> shelf_id;
	std::vector<Recipe*> deleted_recipes;
	void print_shelf_id();
};

class User : public Member{
public:
	User(Word u_username , Word u_password);
	virtual void save_recipe_id(int id);
	virtual void save_recipe(Recipe* recipe);
	virtual int print_chefs();
	virtual void print_chef();
	virtual int print_users();
	virtual std::vector<Recipe*> get_recipes();
	virtual void delete_chef_recipe(int id_);
	virtual void for_user();
	virtual void for_chefs();
	virtual void add_deleted_recipes(Recipe* deleted);
	virtual bool is_user();
};

class Chef : public Member{
public:
	Chef(Word c_username , Word c_password);
	virtual void save_recipe_id(int id);
	virtual void save_recipe(Recipe* recipe);
	virtual int print_chefs();
	virtual void print_chef();
	virtual int print_users();
	virtual std::vector<Recipe*> get_recipes();
	virtual void delete_chef_recipe(int id_);
	virtual void for_user();
	virtual void for_chefs();
	virtual void add_deleted_recipes(Recipe* deleted);
	virtual bool is_user();
private:
	void print_recipe_id();
	int find_recipe_by_id(int id_);
	Recipe* find_recipe_by_title(Word title_);
	float calculate_rate();
	std::vector<Recipe*> sort_recipes(std::vector<Recipe*> recipe_list);
	std::vector<Recipe*> recipes;
	std::vector<int> recipe_id;

	
};



#endif