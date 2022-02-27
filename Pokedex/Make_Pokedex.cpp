#include <bits/stdc++.h>
#include <curlpp/cURLpp.hpp>
#include <curlpp/Options.hpp>
#include <jsoncpp/json/json.h>
#include <jsoncpp/json/reader.h>
using namespace std;

const map<string,int> StringToType{{"normal",0},{"fire",1},{"water",2},{"grass",3},{"electric",4},{"ice",5},{"fighting",6},{"poison",7},{"ground",8},{"flying",9},{"psychic",10},{"bug",11},{"rock",12},{"ghost",13},{"dragon",14},{"dark",15},{"steel",16},{"fairy",17}};
constexpr array<string_view,18> TypeToString{"Normal","Fire","Water","Grass","Electric","Ice","Fighting","Poison","Ground","Flying","Psychic","Bug","Rock","Ghost","Dragon","Dark","Steel","Fairy"};

unordered_map<string,Json::Value> Json_Cache;

string TypeArrayToString(const array<int,2> &Types){
	string output;
	output+=TypeToString[Types[0]];
	if(Types[0]!=Types[1]){
		output+="/";
		output+=TypeToString[Types[1]];
	}
	return output;
}

Json::Value Get_Json(const string &URL){
	if(Json_Cache.find(URL)!=Json_Cache.end()){
		return Json_Cache[URL];
	}
	ostringstream oss;
	oss << curlpp::options::Url(URL);
	string raw_data{oss.str()};
	Json::Value value;
	Json::Reader reader;
	bool parsingSuccessful{reader.parse(raw_data.c_str(),value)};
	if(!parsingSuccessful){
		cerr << "Could not parse URL "+URL+" raw data to json" << endl;
		throw(0);
	}
	Json_Cache[URL]=value;
	return value;
}

map<int,int> Build_GameVersion_To_Generation(){
	map<int,int> GameVersion_To_Generation;
	for(int generation_id{1};generation_id<=8;++generation_id){
		Json::Value generation{Get_Json("https://pokeapi.co/api/v2/generation/"+to_string(generation_id))};
		for(const auto &vgroup:generation["version_groups"]){
			Json::Value version_group{Get_Json(vgroup["url"].asString())};
			for(const auto &v:version_group["versions"]){
				Json::Value version{Get_Json(v["url"].asString())};
				GameVersion_To_Generation[version["id"].asInt()]=generation_id;
			}
		}
	}
	return GameVersion_To_Generation;
}

array<int,2> Parse_Pokemon_Type(const Json::Value &pokemon,const int desired_generation){
	int type_gen{numeric_limits<int>::max()};
	auto types{pokemon["types"]};
	for(const auto &prev_type:pokemon["past_types"]){
		const Json::Value generation{Get_Json(prev_type["generation"]["url"].asString())};
		//cerr << generation << endl;
		const int generation_id{generation["id"].asInt()};
		if(desired_generation<=generation_id && generation_id<type_gen){
			type_gen=generation_id;
			//cerr << types << endl;
			types=prev_type["types"];
			//cerr << types << endl;
		}
	}
	array<int,2> Types;
	for(int i=0;i<static_cast<int>(types.size());++i){
		Types[i]=StringToType.at(types[i]["type"]["name"].asString());
	}
	if(types.size()==1){
		Types[1]=Types[0];
	}
	if(Types[0]>Types[1]){
		swap(Types[0],Types[1]);
	}
	return Types;
}

bool PokemonIsInGeneration(const Json::Value &pokemon,const int generation,const map<int,int> &GameVersion_To_Generation){
	for(const auto &g:pokemon["game_indices"]){
		const Json::Value &game{Get_Json(g["version"]["url"].asString())};
		if(GameVersion_To_Generation.at(game["id"].asInt())==generation){
			return true;
		}
	}
	return false;
}

void Gather_Legal_Types(const int desired_generation,const map<int,int> &GameVersion_To_Generation,map<array<int,2>,set<string>> &Legal_Type_To_Pokemon_Names){
	for(int gen=1;gen<=desired_generation;++gen){
		Json::Value pokedex{Get_Json("https://pokeapi.co/api/v2/pokedex/"+to_string(gen+1))};
		//cerr << "Pokedex of generation " << generation << " has " << pokedex["pokemon_entries"].size() << " entries" << endl;
		for(const auto &pkm_spec:pokedex["pokemon_entries"]){
			const Json::Value pokemon_species{Get_Json(pkm_spec["pokemon_species"]["url"].asString())};
			for(const auto &pkm:pokemon_species["varieties"]){
				const Json::Value pokemon{Get_Json(pkm["pokemon"]["url"].asString())};
				if(PokemonIsInGeneration(pokemon,desired_generation,GameVersion_To_Generation)){
					array<int,2> Types{Parse_Pokemon_Type(pokemon,desired_generation)};
					Legal_Type_To_Pokemon_Names[Types].insert(pokemon["name"].asString());
					//cerr << "In generation " << desired_generation << " " << pokemon["name"].asString() << " was of type " << TypeArrayToString(Types) << endl;
				}
			}
		}
	}
}

int main(){
	map<int,int> GameVersion_To_Generation{Build_GameVersion_To_Generation()};
	/*for(const auto &p:GameVersion_To_Generation){
		cerr << p.first << " " << p.second << endl;
	}*/
	for(int gen=1;gen<=8;++gen){
		map<array<int,2>,set<string>> Legal_Type_To_Pokemon_Names;
		Gather_Legal_Types(gen,GameVersion_To_Generation,Legal_Type_To_Pokemon_Names);
		ofstream NameTypesFile("Gen"+to_string(gen)+"_Types.txt",ios::trunc);
		NameTypesFile << "array<array<int,2>," << Legal_Type_To_Pokemon_Names.size() << "> LegalDoubleTypes{";
		for(const auto &p:Legal_Type_To_Pokemon_Names){
			NameTypesFile << "array<int,2>{" << p.first[0] << "," << p.first[1] << "},";
		}
		NameTypesFile << "};" << endl;
		for(const auto &p:Legal_Type_To_Pokemon_Names){
			NameTypesFile << TypeArrayToString(p.first) << ":";
			for(const string &name:p.second){
				NameTypesFile << " " << name;
			}
			NameTypesFile << endl;
		}
	}
}