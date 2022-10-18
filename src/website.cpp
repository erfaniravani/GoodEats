#include "website.hpp"

Website::Website(){
	current_member = NULL;
	recipes_count = 0;
	shelves_count = 0;
	disable_filters();
}

Member* Website::find_member_by_id(Word username_){
	for(int i = 0 ; i < members.size() ; i++){
		if(members[i]->username_exist(username_))
			return members[i];
	}
	throw NotFound();
	return NULL;
}

int Website::min(int a , int b){
	if(a < b)
		return a;
	else 
		return b;
}

bool Website::does_member_exist(Word username_){
	for(int i = 0 ; i < members.size() ; i++){
		if(members[i]->username_exist(username_))
			return true;
	}
	return false;
}

Recipe* Website::find_recipe_by_title(Word title_){
	for(int i = 0 ; i < recipes.size() ; i++){
		if(recipes[i]->get_title() == title_)
			return recipes[i];
	}
	return NULL;
}

Recipe* Website::find_recipe_by_id(int id_){
	for(int i = 0 ; i < recipes.size() ; i++){
		if(recipes[i]->get_id() == id_)
			return recipes[i];
	}
	return NULL;
}

int Website::find_recipe_index_by_id(int id_){
	for(int i = 0 ; i < recipes.size() ; i++){
		if(recipes[i]->get_id() == id_)
			return i;
	}
	return -1;
}

Shelf* Website::find_shelf_by_id(int id_){
	for(int i = 0 ; i < shelves.size() ; i++){
		if(shelves[i]->get_id() == id_)
			return shelves[i];
	}
	return NULL;
}

void Website::disable_filters(){
	filter1 = NULL;
	filter2 = NULL;
	filter3 = NULL;
	filter4 = NULL;
}

std::vector<Recipe*> Website::sort_recipes(std::vector<Recipe*> recipe_list){
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

std::vector<Member*> Website::sort_members(std::vector<Member*> member_list){
	List member_names;
	std::vector<Member*> sorted_members;
	for(int i = 0 ; i < member_list.size() ; i++){
		member_names.push_back(member_list[i]->get_username());
	}
	sort(member_names.begin(), member_names.end());
	for(int i = 0 ; i < member_names.size() ; i++){
		sorted_members.push_back(find_member_by_id(member_names[i]));
	}
	return sorted_members;
}

void Website::add_member(Word username_ , Word password_ , Word type){
	disable_filters();
	if(does_member_exist(username_))
		throw BadRequest();
	else if(type == USER_TYPE){
		User* new_user = new User(username_ , password_);
		members.push_back(new_user);
		current_member = new_user;
	}
	else if(type == CHEF_TYPE){
		Chef* new_chef = new Chef(username_ , password_);
		members.push_back(new_chef);
		current_member = new_chef;
	}
	else
		throw BadRequest();
}

Word Website::get_current_user_name(){
	if(current_member == NULL)
        throw PermissionDenied();
    return current_member->get_username();
}

void Website::login(Word username_ , Word password_){
	Member* member = find_member_by_id(username_);
	if(member->correct_info(username_ , password_) == true)
		current_member = member;
	else
		throw BadRequest();
	disable_filters();
}

void Website::logout(){
	if(current_member == NULL)
		throw PermissionDenied();
	else
		current_member = NULL;
	disable_filters();
}

void Website::add_recipes(Word title_ , Word ingredients_ , Word vegetarian_ , Word minutes_ , Word tags_ , Word image_){
	if(current_member == NULL)
		throw PermissionDenied();
	else{
		current_member->for_chefs();
		Recipe* new_recipe = new Recipe(title_ , ingredients_ , vegetarian_ , minutes_ , tags_ , image_ , recipes_count+1);
		recipes_count++;
		recipes.push_back(new_recipe);
		current_member->save_recipe_id(recipes_count);
		current_member->save_recipe(new_recipe);
	}
}

Word Website::show_all_recipes(){
	std::stringstream output_stream;
	if(current_member == NULL)
		throw PermissionDenied();
	else{
		current_member->for_user();
		if(recipes.size() != 0){
			std::vector<Recipe*> filtered = find_filtered_recipes();
			std::vector<Recipe*> sorted_recipes = sort_recipes(filtered);
			std::vector<Recipe*> final_sorted_recipes;
			if(sorted_recipes.size() == 0)
					output_stream << "<p1>Empty</p1>" << std::endl;
			for(int i = 0 ; i < sorted_recipes.size() ; i++){
				if(std::find(deleted_recipes.begin(), deleted_recipes.end(), sorted_recipes[i]) != deleted_recipes.end())
					continue;
				else
					final_sorted_recipes.push_back(sorted_recipes[i]);					
			}
			if(final_sorted_recipes.size() != 0){
        		output_stream << "<table>" << std::endl
            	<< "<tr>" << std::endl
            	<< "<th>" << "Recipe" << "</th>" << std::endl
            	<< "<th>" << "Vegetarian" << "</th>" << std::endl
            	<< "<th>" << "Minutes Ready" << "</th>" << std::endl
            	<< "</tr>" << std::endl;
        		for(Recipe* recipe : final_sorted_recipes){
            		output_stream << "<tr>" << std::endl
                    << recipe->print_recipe_summery_html()
                    << "</tr>" << std::endl;
        		}
        		output_stream << "</table>" << std::endl;
    		}
    		else
        		output_stream << "<p1>Empty</p1>" << std::endl;
		}
		else
			output_stream << "<p1>Empty</p1>" << std::endl;
	}
	return output_stream.str();
}

Word Website::show_recipe(int id){
	std::stringstream output_stream;
	if(current_member == NULL)
		throw PermissionDenied();
	else{
		current_member->for_user();
		if(find_recipe_by_id(id) == NULL)
			throw NotFound();
		else{
			Recipe* wanted_recipe = find_recipe_by_id(id);
			if(std::find(deleted_recipes.begin(), deleted_recipes.end(), wanted_recipe) != deleted_recipes.end())
				throw NotFound();
			else{
				output_stream << "<table>" << std::endl
            	<< "<tr>" << std::endl
            	<< "<th>" << "Recipe ID" << "</th>" << std::endl
            	<< "<th>" << "Recipe Name" << "</th>" << std::endl
            	<< "<th>" << "Vegetarian" << "</th>" << std::endl
            	<< "<th>" << "Minutes Ready" << "</th>" << std::endl
            	<< "<th>" << "Ingredients" << "</th>" << std::endl
            	<< "<th>" << "tags" << "</th>" << std::endl
            	<< "<th>" << "rate" << "</th>" << std::endl
            	<< "</tr>" << std::endl;
        		output_stream << "<tr>" << std::endl
                << wanted_recipe->print_recipe_infos_html()
                << "</tr>" << std::endl;
        		
        		output_stream << "</table>" << std::endl;
			}
		}

	}
	return output_stream.str();
}

void Website::give_score(int id , float score){
	if(current_member == NULL)
		throw PermissionDenied();

	else{
		current_member->for_user();
		if(find_recipe_by_id(id) == NULL)
			throw NotFound();
		else if((score > 5) or (score < 1))
			throw BadRequest();
		else{
			Recipe* wanted_recipe = find_recipe_by_id(id);
			if(std::find(deleted_recipes.begin(), deleted_recipes.end(), wanted_recipe) != deleted_recipes.end())
				throw NotFound();
			else
				wanted_recipe->record_score(score , current_member->get_username());
		}
	}
}

void Website::change_score(int id , float score){
	if(current_member == NULL)
		throw PermissionDenied();

	else{
		current_member->for_user();
		if(find_recipe_by_id(id) == NULL)
			throw NotFound();
		else if((score > 5) or (score < 1))
			throw BadRequest();
		else{
			Recipe* wanted_recipe = find_recipe_by_id(id);
			if(std::find(deleted_recipes.begin(), deleted_recipes.end(), wanted_recipe) != deleted_recipes.end())
				throw NotFound();
			else
				wanted_recipe->new_score(score , current_member->get_username());
		}
	}
}

bool Website::user_gave_score(int id){
	bool score_given = false;
	if(current_member == NULL)
		throw PermissionDenied();
	else{
		current_member->for_user();
		if(find_recipe_by_id(id) == NULL)
			throw NotFound();
		else{
			Recipe* wanted_recipe = find_recipe_by_id(id);
			if(std::find(deleted_recipes.begin(), deleted_recipes.end(), wanted_recipe) != deleted_recipes.end())
				throw NotFound();
			else
				score_given = wanted_recipe->has_given_score(current_member->get_username());
		}
	}
	return score_given;
}

void Website::add_shelf(Word name_){
	if(current_member == NULL)
		throw PermissionDenied();
	else{
		current_member->for_user();
		Shelf* new_shelf = new Shelf(name_ , shelves_count+1);
		shelves.push_back(new_shelf);
		current_member->save_shelf_id(shelves_count+1);
		shelves_count++;
	}

}

Word Website::show_shelves(Word username_ , int limit){
	std::stringstream output_stream;
	if(current_member == NULL)
		throw PermissionDenied();
	else{
		current_member->for_user();
		Member* wanted_member = find_member_by_id(username_);
		std::vector<int> member_shelves = wanted_member->get_shelf_id();
		sort(member_shelves.begin(), member_shelves.end());
		int minimum = min(limit , member_shelves.size());
		if(member_shelves.size() == 0)
			output_stream << "<p1>Empty</p1>" << std::endl;
		else{
			output_stream << "<table>" << std::endl
            << "<tr>" << std::endl
           	<< "<th>" << "Shelf" << "</th>" << std::endl
           	<< "</tr>" << std::endl;
			for(int i = 0 ; i < minimum ; i++){
				Shelf* wanted_shelf = find_shelf_by_id(member_shelves[i]);
				
        		output_stream << "<tr>" << std::endl
                << wanted_shelf->print_shelf()
                << "</tr>" << std::endl;        		
			}
			output_stream << "</table>" << std::endl;
		}
	}
	return output_stream.str();
}

void Website::recipe_on_shelf(int shelf_id , int recipe_id){
	if(current_member == NULL)
		throw PermissionDenied();
	else{
		current_member->for_user();
		std::vector<int> member_shelves = current_member->get_shelf_id();
		if(std::find(member_shelves.begin(), member_shelves.end(), shelf_id) != member_shelves.end()){
			Recipe* wanted_recipe = find_recipe_by_id(recipe_id);
			if(std::find(deleted_recipes.begin(), deleted_recipes.end(), wanted_recipe) != deleted_recipes.end())
				throw NotFound();
			else{
				Shelf* wanted_shelf = find_shelf_by_id(shelf_id);
				if(wanted_shelf == NULL || wanted_recipe == NULL)
					throw BadRequest();
				else
					wanted_shelf->push_recipes(wanted_recipe);
			}
		}
		else{
			if(shelf_id > shelves_count)
				throw NotFound();
			else
				throw PermissionDenied();
		}
	}
}

Word Website::show_shelves_recipes(int shelf_id){
	std::stringstream output_stream;
	if(current_member == NULL)
		throw PermissionDenied();
	else{
		current_member->for_user();
		Shelf* wanted_shelf = find_shelf_by_id(shelf_id);
		if(wanted_shelf == NULL)
			throw BadRequest();
		else{
			std::vector<Recipe*> wanted_recipes = wanted_shelf->get_recipes();
			if(wanted_recipes.size() == 0)
				output_stream << "<p1>Empty</p1>" << std::endl;
			else{
				std::vector<Recipe*> sorted_recipes = sort_recipes(wanted_recipes);
				output_stream << "<table>" << std::endl
            	<< "<tr>" << std::endl
            	<< "<th>" << "title" << "</th>" << std::endl
            	<< "<th>" << "Vegetarian" << "</th>" << std::endl
            	<< "<th>" << "Minutes Ready" << "</th>" << std::endl
            	<< "</tr>" << std::endl;
				for(int i = 0 ; i < sorted_recipes.size() ; i++){
					output_stream << "<tr>" << std::endl
					<< sorted_recipes[i]->print_recipe_summery_html()
					<< "</tr>" << std::endl;
				}
				output_stream << "</table>" << std::endl;
			}
		}
	}
	return output_stream.str();
}

void Website::delete_shelf_recipe(int shelf_id , int recipe_id){
	if(current_member == NULL)
		throw PermissionDenied();
	else{
		current_member->for_user();
		std::vector<int> member_shelves = current_member->get_shelf_id();
		if(std::find(member_shelves.begin(), member_shelves.end(), shelf_id) != member_shelves.end()){
			Shelf* wanted_shelf = find_shelf_by_id(shelf_id);
			if(wanted_shelf == NULL)
				throw BadRequest();
			else
				wanted_shelf->delete_recipe(recipe_id);
		}
		else
			throw PermissionDenied();
	}
}

void Website::show_chefs(){
	if(current_member == NULL)
		throw PermissionDenied();
	else{
		current_member->for_user();
		int chef_count = 0;
		std::vector<Member*> sorted_members = sort_members(members);
		for(int i = 0 ; i < sorted_members.size() ; i++){
			chef_count += sorted_members[i]->print_chefs();
		}
		if(chef_count == 0)
			throw Empty();
	}
}

void Website::show_chef(Word username_){
	if(current_member == NULL)
		throw PermissionDenied();
	else{
		current_member->for_user();
		Member* chef = find_member_by_id(username_);
		if(chef == NULL or chef->is_user())
			throw NotFound();
		else
			chef->print_chef();
	}
}

void Website::show_users(){
	if(current_member == NULL)
		throw PermissionDenied();
	else{
		current_member->for_user();
		int user_cout = 0;
		std::vector<Member*> sorted_members = sort_members(members);
		for(int i = 0 ; i < sorted_members.size() ; i++){
			if(current_member->get_username() != sorted_members[i]->get_username())
				user_cout += sorted_members[i]->print_users();
		}
		if(user_cout == 0)
			throw Empty();
	}
}

void Website::delete_recipe(int id){
	if(current_member == NULL)
		throw PermissionDenied();
	else{
		current_member->for_chefs();
		std::vector<Recipe*> chef_recipes = current_member->get_recipes();
		Recipe* wanted_recipe = find_recipe_by_id(id);
		if(std::find(chef_recipes.begin(), chef_recipes.end(), wanted_recipe) != chef_recipes.end()){
			if(std::find(deleted_recipes.begin(), deleted_recipes.end(), wanted_recipe) != deleted_recipes.end())
				throw NotFound();
			else{
				int index = find_recipe_index_by_id(id);
				std::cout << OK_RESPONSE << std::endl;
				deleted_recipes.push_back(recipes[index]);
				current_member->add_deleted_recipes(recipes[index]);
			}
		}

		else
			throw PermissionDenied();

	}
}


Word Website::show_chef_recipes(){
	std::stringstream output_stream;
	if(current_member == NULL)
		throw PermissionDenied();
	else{

		current_member->for_chefs();
		std::vector<Recipe*> chef_recipes = current_member->get_recipes();
		std::vector<Recipe*> final_chef_recipes;
		if(chef_recipes.size() != 0){
			for(int i = 0 ; i < chef_recipes.size() ; i++){
				if(std::find(deleted_recipes.begin(), deleted_recipes.end(), chef_recipes[i]) != deleted_recipes.end())
					continue;
				final_chef_recipes.push_back(chef_recipes[i]);
			}
    		if(final_chef_recipes.size() != 0){
        		output_stream << "<table>" << std::endl
            	<< "<tr>" << std::endl
            	<< "<th>" << "Recipe ID" << "</th>" << std::endl
            	<< "<th>" << "Recipe Name" << "</th>" << std::endl
            	<< "<th>" << "Vegetarian" << "</th>" << std::endl
            	<< "<th>" << "Minutes Ready" << "</th>" << std::endl
            	<< "<th>" << "Ingredients" << "</th>" << std::endl
            	<< "<th>" << "tags" << "</th>" << std::endl
            	<< "<th>" << "rate" << "</th>" << std::endl
            	<< "</tr>" << std::endl;
        		for(Recipe* recipe : final_chef_recipes){
            		output_stream << "<tr>" << std::endl
                    << recipe->print_recipe_infos_html()
                    << "</tr>" << std::endl;
        		}
        		output_stream << "</table>" << std::endl;
    		}
    		else
        		output_stream << "<p1>Empty</p1>" << std::endl;
		}
		else
			output_stream << "<p1>Empty</p1>" << std::endl;
	}
	return output_stream.str();
}
std::vector<Recipe*> Website::find_filtered_recipes(){
	std::vector<Recipe*> filtered_by_filter1 = recipes;
    if(filter1 != NULL)
    {
        filter1->filter_recipes(recipes);
        filtered_by_filter1 = filter1->get_filtered_recipes();
    }
    std::vector<Recipe*> filtered_by_filter2 = filtered_by_filter1;
    if(filter2 != NULL)
    {
        filter2->filter_recipes(filtered_by_filter1);
        filtered_by_filter2 = filter2->get_filtered_recipes();
    }
    std::vector<Recipe*> filtered_by_filter3 = filtered_by_filter2;
    if(filter3 != NULL)
    {
        filter3->filter_recipes(filtered_by_filter2);
        filtered_by_filter3 = filter3->get_filtered_recipes();
    }
    std::vector<Recipe*> filtered_by_filter4 = filtered_by_filter3;
    if(filter4 != NULL)
    {
        filter4->filter_recipes(filtered_by_filter3);
        filtered_by_filter4 = filter4->get_filtered_recipes();
    }
    return filtered_by_filter4;
}

void Website::tag_filter(Word tag_){
	if(current_member == NULL)
		throw PermissionDenied();
	else{
		current_member->for_user();
		filter1 = new TagFilter(tag_);
		std::cout << OK_RESPONSE << std::endl;
	}
}
void Website::vegetarian_filter(){
	if(current_member == NULL)
		throw PermissionDenied();
	else{
		current_member->for_user();
		filter2 = new VegetarianFilter();
		std::cout << OK_RESPONSE << std::endl;
	}
}
void Website::minutes_filter(int min , int max){
	if(current_member == NULL)
		throw PermissionDenied();
	else{
		current_member->for_user();
		filter3 = new MinutesFilter(min , max);
		std::cout << OK_RESPONSE << std::endl;
	}
}
void Website::rate_filter(double min , double max){
	if(current_member == NULL)
		throw PermissionDenied();

	else if((min > 5) or (min < 1) or (max > 5) or (max < 1) or (min > max))
			throw BadRequest();
	else{
		current_member->for_user();
		filter4 = new RateFilter(min , max);
		std::cout << OK_RESPONSE << std::endl;
	}
}

void Website::delete_filters(){
	current_member->for_user();
	disable_filters();
	std::cout << OK_RESPONSE << std::endl;
}

bool Website::member_user(Word username_){
	Member* wanted_member = find_member_by_id(username_);
	return wanted_member->is_user();
}

Word Website::give_shelf_name(int id){
	Shelf* wanted_shelf = find_shelf_by_id(id);
	return wanted_shelf->get_name();
}

bool Website::tag_filter_on(){
	if(filter1 == NULL)
		return false;
	else
		return true;
}

bool Website::vegetarian_filter_on(){
	if(filter2 == NULL)
		return false;
	else
		return true;
}

bool Website::minutes_filter_on(){
	if(filter3 == NULL)
		return false;
	else
		return true;
}

bool Website::rate_filter_on(){
	if(filter4 == NULL)
		return false;
	else
		return true;
}

Word Website::get_recipe_image(int id_){
	Recipe* wanted_recipe = find_recipe_by_id(id_);
	return wanted_recipe->get_image_address();
}
