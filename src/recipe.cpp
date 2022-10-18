#include "recipe.hpp"

Recipe::Recipe(Word title_ , Word ingredients_ , Word vegetarian_ , Word minuets_ , Word tags_ , Word image_ , int id_){
	id = id_;
	title = title_;
	ingredients = seperate_comma(ingredients_);
	vegetarian = vegetarian_;
	minutes = minuets_;
	tags = seperate_comma(tags_);
	image_address = image_;
	rate = "0";
}

int Recipe::get_id(){
	return id;
}
Word Recipe::get_title(){
	return title;
}
Word Recipe::get_vegetarian(){
	return vegetarian;
}
Word Recipe::get_minutes(){
	return minutes;
}
Word Recipe::get_rate(){
	return rate;
}
std::vector<float> Recipe::get_rate_vector(){
	return rate_vector;
}
List Recipe::get_tags(){
	return tags;
}
Word Recipe::get_image_address(){
	return image_address;
}

float Recipe::average_score(){
	float sum = 0;
	for(int i = 0 ; i < rate_vector.size() ; i++){
		sum = sum + rate_vector[i];
	}
	float average = sum / float(rate_vector.size());
	average = ceil(average*10)/10;
	return average;
}

void Recipe::record_score(float score , Word username_){
	if (std::find(members_gave_rate.begin(), members_gave_rate.end(), username_) != members_gave_rate.end())
		throw BadRequest();
	else{
		score = ceil(score*10)/10;
		rate_vector.push_back(score);
		members_gave_rate.push_back(username_);
		std::stringstream sstream;
		sstream << average_score();
		std::string num_str = sstream.str();
		rate = num_str;
	}
}

void Recipe::new_score(float score , Word username_){
	std::vector<std::string>::iterator it = std::find(members_gave_rate.begin(), members_gave_rate.end(), username_);
	if (it != members_gave_rate.end()){
		score = ceil(score*10)/10;
		rate_vector[it - members_gave_rate.begin()] = score;
		rate = std::to_string(average_score());
	}
	else
		throw BadRequest();
}

bool Recipe::has_given_score(Word username_){
	if (std::find(members_gave_rate.begin(), members_gave_rate.end(), username_) != members_gave_rate.end())
		return true;
	else
		return false;
}

void Recipe::print_recipe(){
	std::cout << id << std::endl << title << std::endl << "vegetarian: " << vegetarian << std::endl << "ingredients: [" ;
	for(int i = 0 ; i < ingredients.size() ; i++){
		if(i == ingredients.size()-1)
			std::cout << ingredients[i] << "]" << std::endl;
		else
			std::cout << ingredients[i] << ", ";
	}
	std::cout << "minutes to ready: " << minutes << std::endl << "tags: [";
	for(int i = 0 ; i < tags.size() ; i++){
		if(i == tags.size()-1)
			std::cout << tags[i] << "]" << std::endl;
		else
			std::cout << tags[i] << ", ";
	}
	float rate_float = ceil(std::stof(rate)*10)/10;
	std::cout << "rating: ";
	std::cout << std::fixed;
    std::cout << std::setprecision(1) << rate_float << std::endl;
}

void Recipe::print_recipes_summery(){
	std::cout << id << " " << title << " " << vegetarian << " " << minutes << std::endl;
}
void Recipe::print_chef_recipe(){
	float rate_float = ceil(std::stof(rate)*10)/10;
	std::cout << id << " " << title << " " << vegetarian << " " << minutes << " " << rate_float << std::endl;	
}

List Recipe::seperate_comma(Word str){
	List words; 
    Word word = ""; 
    for (auto x : str)  { 
    	if (x == ','){ 
            if(word != "")  
                words.push_back(word);
            word = ""; 
        } 
        else{ 
            word = word + x; 
        } 
    }    
    words.push_back(word);
    return words;
}

Word Recipe::print_recipe_infos_html(){
    std::stringstream output_stream;
    Word ingredients_string;
    Word tags_string;
    for(int i = 0 ; i < ingredients.size() ; i++){
    	if(i == ingredients.size()-1)
    		ingredients_string = ingredients_string + ingredients[i];
    	else
    		ingredients_string = ingredients_string + ingredients[i] + ", ";
    }
    for(int i = 0 ; i < tags.size() ; i++){
    	if(i == tags.size()-1)
    		tags_string = tags_string + tags[i];
    	else
    		tags_string = tags_string + tags[i] + ", ";
    }
    float rate_float = ceil(std::stof(rate)*10)/10;
	output_stream << "<td>" 
            << std::to_string(id) << "</td>"
            << "<td>" << title << "</td>"
            << "<td>" << vegetarian << "</td>"
            << "<td>" << minutes << "</td>"
            << "<td>" << ingredients_string << "</td>"
            << "<td>" << tags_string << "</td>"
            << "<td>" << std::fixed << std::setprecision(1) << rate_float << "</td>";
    return output_stream.str();
}

Word Recipe::print_recipe_summery_html(){
	std::stringstream output_stream;
    Word name = std::to_string(id) + ". " + title;
    output_stream << "<td>" 
            << "<a href='/recipe?id=" << id << "'>" << name << "</a>"
            << "</td>"
            << "<td>" << vegetarian << "</td>"
            << "<td>" << minutes << "</td>";
    return output_stream.str();
}



