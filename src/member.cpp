#include "member.hpp"

Member::Member(Word username_ , Word password_){
	username = username_;
	password = password_;
}

void Member::save_shelf_id(int id){
	shelf_id.push_back(id);
	print_shelf_id();
}

std::vector<int> Member::get_shelf_id(){
	return shelf_id;
}

void Member::print_shelf_id(){
	std::cout << shelf_id.back() << std::endl;
}

Word Member::get_username(){
	return username;
}

bool Member::username_exist(Word username_){
	if(username_ == username)
		return true;
	else
		return false;
}

bool Member::correct_info(Word username_ , Word password_){
	if(username_ == username && password_ == password)
		return true;
	else
		return false;
}


User::User(Word u_username , Word u_password) : Member(u_username , u_password){}

bool User::is_user(){
	return true;
}
void User::add_deleted_recipes(Recipe* deleted){}
void User::save_recipe(Recipe* recipe){
	throw PermissionDenied();
}

void User::save_recipe_id(int id){
	throw PermissionDenied();
}

int User::print_chefs(){
	return 0;
}

void User::print_chef(){}

void User::for_user(){}

void User::for_chefs(){
	throw PermissionDenied();
}

int User::print_users(){
	std::cout << username << std::endl;
	return 1;
}

std::vector<Recipe*> User::get_recipes(){
	throw PermissionDenied();
}

void User::delete_chef_recipe(int id_){
	throw PermissionDenied();
}

Chef::Chef(Word c_username , Word c_password) : Member(c_username , c_password){}
void Chef::for_user(){
	throw PermissionDenied();
}

float Chef::calculate_rate(){
	float rate_sum = 0;
	float rate_avg = 0;
	int not_rated = 0;
	int rate_size = 0;
	if(recipes.size() != 0){
		for(int i = 0 ; i < recipes.size() ; i++){
			std::vector<float> all_rates = recipes[i]->get_rate_vector();
			rate_size += all_rates.size();
			for(int j = 0 ; j < all_rates.size() ; j++){
				rate_sum += all_rates[j];
			}
			if(std::stod(recipes[i]->get_rate()) == 0)
				not_rated++;
		}
		if(recipes.size() == not_rated)
			rate_avg = 0;
		else{
			rate_avg = rate_sum / rate_size;
			rate_avg = ceil(rate_avg*10)/10;
		}
	}
	return rate_avg;
}

void Chef::for_chefs() {}
bool Chef::is_user(){
	return false;
}
int Chef::print_chefs(){
	float rate_avg = calculate_rate();
	std::cout << username << " " << rate_avg << std::endl;
	return 1;
}

int Chef::print_users(){
	return 0;
}

void Chef::delete_chef_recipe(int id_){
	int index = find_recipe_by_id(id_);
	recipes.erase(recipes.begin()+index);
}

void Chef::print_chef(){
	float rate_avg = calculate_rate();
	std::cout << username << std::endl << rate_avg << std::endl << "recipes:" << std::endl;
	std::vector<Recipe*> sorted_recipes = sort_recipes(recipes);
	for(int i = 0 ; i < sorted_recipes.size() ; i++){
		if(std::find(deleted_recipes.begin(), deleted_recipes.end(), sorted_recipes[i]) != deleted_recipes.end())
			continue;
		sorted_recipes[i]->print_chef_recipe();
	}
}

void Chef::save_recipe_id(int id){
	recipe_id.push_back(id);
	print_recipe_id();
}

void Chef::save_recipe(Recipe* recipe){
	recipes.push_back(recipe);
}

void Chef::print_recipe_id(){
	std::cout << recipe_id.back() << std::endl;
}

std::vector<Recipe*> Chef::get_recipes(){
	return recipes;
}


void Chef::add_deleted_recipes(Recipe* deleted){
	deleted_recipes.push_back(deleted);
}

std::vector<Recipe*> Chef::sort_recipes(std::vector<Recipe*> recipe_list){
	List recipe_titles;
	std::vector<Recipe*> sorted_recipes;
	for(int i = 0 ; i < recipe_list.size() ; i++){
		recipe_titles.push_back(recipe_list[i]->get_title());
	}
	sort(recipe_titles.begin(), recipe_titles.end());
	for(int i = 0 ; i < recipe_titles.size() ; i++){
		sorted_recipes.push_back(find_recipe_by_title(recipe_titles[i]));
	}
	return sorted_recipes;
}

Recipe* Chef::find_recipe_by_title(Word title_){
	for(int i = 0 ; i < recipes.size() ; i++){
		if(recipes[i]->get_title() == title_)
			return recipes[i];
	}
	return NULL;
}

int Chef::find_recipe_by_id(int id_){
	for(int i = 0 ; i < recipes.size() ; i++){
		if(recipes[i]->get_id() == id_)
			return i;
	}
	return -1;
}
