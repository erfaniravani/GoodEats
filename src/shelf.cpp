#include "shelf.hpp"

Shelf::Shelf(Word name_ , int id_){
	name = name_;
	id = id_;
}

void Shelf::print_ok(){
	std::cout << "OK" << std::endl;
}

void Shelf::push_recipes(Recipe* recipe){
	recipes.push_back(recipe);
	print_ok();
}

std::vector<Recipe*> Shelf::get_recipes(){
	return recipes;
}

Word Shelf::print_shelf(){
	std::stringstream output_stream;
	Word name_ = std::to_string(id) + ". " + name;
    output_stream << "<td>" 
        << "<a href='/shelf?id=" << id << "'>" << name_ << "</a>"
        << "</td>";
    return output_stream.str();
}

int Shelf::get_id(){
	return id;
}

Word Shelf::get_name(){
	return name;
}

void Shelf::delete_recipe(int recipe_id){
	int index = find_recipe(recipe_id);
	if(index == -1)
		throw BadRequest();
	else{
		recipes.erase(recipes.begin()+index);
		print_ok();
	}
}

void Shelf::erase_recipe_by_chef(int recipe_id){
	int index = find_recipe(recipe_id);
	if(index != -1){
		recipes.erase(recipes.begin()+index);
	}
}

int Shelf::find_recipe(int recipe_id){
	for(int i = 0 ; i < recipes.size() ; i++){
		if(recipe_id == recipes[i]->get_id())
			return i;
	}
	return -1;
}