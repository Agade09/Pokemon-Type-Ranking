#include <bits/stdc++.h>
#include <glpk.h>   /* GNU GLPK linear/mixed integer solver */
using namespace std;

#define GENERATION 1
#if GENERATION==1
array<array<int,2>,33> LegalDoubleTypes{array<int,2>{0,0},array<int,2>{0,9},array<int,2>{1,1},array<int,2>{1,9},array<int,2>{2,2},array<int,2>{2,5},array<int,2>{2,6},array<int,2>{2,7},array<int,2>{2,9},array<int,2>{2,10},array<int,2>{2,12},array<int,2>{3,3},array<int,2>{3,7},array<int,2>{3,10},array<int,2>{3,11},array<int,2>{4,4},array<int,2>{4,9},array<int,2>{5,9},array<int,2>{5,10},array<int,2>{6,6},array<int,2>{7,7},array<int,2>{7,8},array<int,2>{7,9},array<int,2>{7,11},array<int,2>{7,13},array<int,2>{8,8},array<int,2>{8,12},array<int,2>{9,11},array<int,2>{9,12},array<int,2>{9,14},array<int,2>{10,10},array<int,2>{11,11},array<int,2>{14,14},};
#endif
#if GENERATION>=6
constexpr int Num_Types{18};
constexpr array<array<float,Num_Types>,Num_Types> Attack_Effectiveness{//https://upload.wikimedia.org/wikipedia/commons/9/97/Pokemon_Type_Chart.svg
array<float,Num_Types>{1,1,1,1,1,1,1,1,1,1,1,1,0.5,0,1,1,0.5,1}, // Normal
array<float,Num_Types>{1,0.5,0.5,2,1,2,1,1,1,1,1,2,0.5,1,0.5,1,2,1}, // Fire
array<float,Num_Types>{1,2,0.5,0.5,1,1,1,1,2,1,1,1,2,1,0.5,1,1,1}, // Water
array<float,Num_Types>{1,0.5,2,0.5,1,1,1,0.5,2,0.5,1,0.5,2,1,0.5,1,0.5,1}, // Grass
array<float,Num_Types>{1,1,2,0.5,0.5,1,1,1,0,2,1,1,1,1,0.5,1,1,1}, // Electric
array<float,Num_Types>{1,0.5,0.5,2,1,0.5,1,1,2,2,1,1,1,1,2,1,0.5,1}, // Ice
array<float,Num_Types>{2,1,1,1,1,2,1,0.5,1,0.5,0.5,0.5,2,0,1,2,2,0.5}, // Fighting
array<float,Num_Types>{1,1,1,2,1,1,1,0.5,0.5,1,1,1,0.5,0.5,1,1,0,2}, // Poison
array<float,Num_Types>{1,2,1,0.5,2,1,1,2,1,0,1,0.5,2,1,1,1,2,1}, // Ground
array<float,Num_Types>{1,1,1,2,0.5,1,2,1,1,1,1,2,0.5,1,1,1,0.5,1}, // Flying
array<float,Num_Types>{1,1,1,1,1,1,2,2,1,1,0.5,1,1,1,1,0,0.5,1}, // Psychic
array<float,Num_Types>{1,0.5,1,2,1,1,0.5,0.5,1,0.5,2,1,1,0.5,1,2,0.5,0.5}, // Bug
array<float,Num_Types>{1,2,1,1,1,2,0.5,1,0.5,2,1,2,1,1,1,1,0.5,1}, // Rock
array<float,Num_Types>{0,1,1,1,1,1,1,1,1,1,2,1,1,2,1,0.5,1,1}, // Ghost
array<float,Num_Types>{1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,0.5,0}, // Dragon
array<float,Num_Types>{1,1,1,1,1,1,0.5,1,1,1,2,1,1,2,1,0.5,1,0.5}, // Dark
array<float,Num_Types>{1,0.5,0.5,1,0.5,2,1,1,1,1,1,1,2,1,1,1,0.5,2}, // Steel
array<float,Num_Types>{1,0.5,1,1,1,1,2,0.5,1,1,1,1,1,1,2,2,0.5,1}, // Fairy
};
enum pokemon_type{
	NORMAL=0,FIRE=1,WATER=2,GRASS=3,ELECTRIC=4,ICE=5,FIGHTING=6,POISON=7,GROUND=8,FLYING=9,PSYCHIC=10,BUG=11,ROCK=12,GHOST=13,DRAGON=14,DARK=15,STEEL=16,FAIRY=17
};
constexpr array<string_view,Num_Types> TypeToString{"Normal","Fire","Water","Grass","Electric","Ice","Fighting","Poison","Ground","Flying","Psychic","Bug","Rock","Ghost","Dragon","Dark","Steel","Fairy"};
#elif GENERATION>=2
constexpr int Num_Types{17};
constexpr array<array<float,Num_Types>,Num_Types> Attack_Effectiveness{ //Followed changes listed in https://bulbapedia.bulbagarden.net/wiki/Type/Type_chart
array<float,Num_Types>{1,1,1,1,1,1,1,1,1,1,1,1,0.5,0,1,1,0.5}, // Normal
array<float,Num_Types>{1,0.5,0.5,2,1,2,1,1,1,1,1,2,0.5,1,0.5,1,2}, // Fire
array<float,Num_Types>{1,2,0.5,0.5,1,1,1,1,2,1,1,1,2,1,0.5,1,1}, // Water
array<float,Num_Types>{1,0.5,2,0.5,1,1,1,0.5,2,0.5,1,0.5,2,1,0.5,1,0.5}, // Grass
array<float,Num_Types>{1,1,2,0.5,0.5,1,1,1,0,2,1,1,1,1,0.5,1,1}, // Electric
array<float,Num_Types>{1,0.5,0.5,2,1,0.5,1,1,2,2,1,1,1,1,2,1,0.5}, // Ice
array<float,Num_Types>{2,1,1,1,1,2,1,0.5,1,0.5,0.5,0.5,2,0,1,2,2}, // Fighting
array<float,Num_Types>{1,1,1,2,1,1,1,0.5,0.5,1,1,1,0.5,0.5,1,1,0}, // Poison
array<float,Num_Types>{1,2,1,0.5,2,1,1,2,1,0,1,0.5,2,1,1,1,2}, // Ground
array<float,Num_Types>{1,1,1,2,0.5,1,2,1,1,1,1,2,0.5,1,1,1,0.5}, // Flying
array<float,Num_Types>{1,1,1,1,1,1,2,2,1,1,0.5,1,1,1,1,0,0.5}, // Psychic
array<float,Num_Types>{1,0.5,1,2,1,1,0.5,0.5,1,0.5,2,1,1,0.5,1,2,0.5}, // Bug
array<float,Num_Types>{1,2,1,1,1,2,0.5,1,0.5,2,1,2,1,1,1,1,0.5}, // Rock
array<float,Num_Types>{0,1,1,1,1,1,1,1,1,1,2,1,1,2,1,0.5,0.5}, // Ghost
array<float,Num_Types>{1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,0.5}, // Dragon
array<float,Num_Types>{1,1,1,1,1,1,0.5,1,1,1,2,1,1,2,1,0.5,0.5}, // Dark
array<float,Num_Types>{1,0.5,0.5,1,0.5,2,1,1,1,1,1,1,2,1,1,1,0.5}, // Steel
};
enum pokemon_type{
	NORMAL=0,FIRE=1,WATER=2,GRASS=3,ELECTRIC=4,ICE=5,FIGHTING=6,POISON=7,GROUND=8,FLYING=9,PSYCHIC=10,BUG=11,ROCK=12,GHOST=13,DRAGON=14,DARK=15,STEEL=16
};
constexpr array<string_view,Num_Types> TypeToString{"Normal","Fire","Water","Grass","Electric","Ice","Fighting","Poison","Ground","Flying","Psychic","Bug","Rock","Ghost","Dragon","Dark","Steel"};
#elif GENERATION==1
constexpr int Num_Types{15};
constexpr array<array<float,Num_Types>,Num_Types> Attack_Effectiveness{ //Followed changes listed in https://bulbapedia.bulbagarden.net/wiki/Type/Type_chart
array<float,Num_Types>{1,1,1,1,1,1,1,1,1,1,1,1,0.5,0,1}, // Normal
array<float,Num_Types>{1,0.5,0.5,2,1,2,1,1,1,1,1,2,0.5,1,0.5}, // Fire
array<float,Num_Types>{1,2,0.5,0.5,1,1,1,1,2,1,1,1,2,1,0.5}, // Water
array<float,Num_Types>{1,0.5,2,0.5,1,1,1,0.5,2,0.5,1,0.5,2,1,0.5}, // Grass
array<float,Num_Types>{1,1,2,0.5,0.5,1,1,1,0,2,1,1,1,1,0.5}, // Electric
array<float,Num_Types>{1,1,0.5,2,1,0.5,1,1,2,2,1,1,1,1,2}, // Ice
array<float,Num_Types>{2,1,1,1,1,2,1,0.5,1,0.5,0.5,0.5,2,0,1}, // Fighting
array<float,Num_Types>{1,1,1,2,1,1,1,0.5,0.5,1,1,2,0.5,0.5,1}, // Poison
array<float,Num_Types>{1,2,1,0.5,2,1,1,2,1,0,1,0.5,2,1,1}, // Ground
array<float,Num_Types>{1,1,1,2,0.5,1,2,1,1,1,1,2,0.5,1,1}, // Flying
array<float,Num_Types>{1,1,1,1,1,1,2,2,1,1,0.5,1,1,1,1}, // Psychic
array<float,Num_Types>{1,0.5,1,2,1,1,0.5,2,1,0.5,2,1,1,0.5,1}, // Bug
array<float,Num_Types>{1,2,1,1,1,2,0.5,1,0.5,2,1,2,1,1,1}, // Rock
array<float,Num_Types>{0,1,1,1,1,1,1,1,1,1,0,1,1,2,1}, // Ghost
array<float,Num_Types>{1,1,1,1,1,1,1,1,1,1,1,1,1,1,2}, // Dragon
};
enum pokemon_type{
	NORMAL=0,FIRE=1,WATER=2,GRASS=3,ELECTRIC=4,ICE=5,FIGHTING=6,POISON=7,GROUND=8,FLYING=9,PSYCHIC=10,BUG=11,ROCK=12,GHOST=13,DRAGON=14
};
constexpr array<string_view,Num_Types> TypeToString{"Normal","Fire","Water","Grass","Electric","Ice","Fighting","Poison","Ground","Flying","Psychic","Bug","Rock","Ghost","Dragon"};
#endif

//const int Num_Type_Pairs{static_cast<int>(Num_Types*(Num_Types+1)/2)};
const int Num_Type_Pairs{static_cast<int>(LegalDoubleTypes.size())};
constexpr float Bonus_Coeff{1e-2};
constexpr int Rounding_Decimals{6};
constexpr float Softening_Parameter{1e-17};

template<int W> array<float,W> simplexMatrixSolverStrat(const array<array<float,W>,W> &payoffMatrix) {//From pb4
  glp_term_out(GLP_OFF);

  /* declare variables */
  glp_prob* lp;
  int       ia[1 + W*W], ja[1 + W*W];
  double    ar[1 + W*W];
  /* create problem */
  lp = glp_create_prob();
  glp_set_prob_name(lp, "matrixSolverGLPK");
  glp_set_obj_dir(lp, GLP_MIN);
  /* fill problem */
  glp_add_rows(lp, W);
  for (int i = 0; i < W; ++i) {
    std::string rowname = "p0_" + std::to_string(i);
    glp_set_row_name(lp, i + 1, rowname.c_str());   // OK
    glp_set_row_bnds(lp, i + 1, GLP_LO, 1.0, 0.0);  // OK
  }
  glp_add_cols(lp, W);
  for (int j = 0; j < W; ++j) {
    std::string colname = "x_p1_" + std::to_string(j);
    glp_set_col_name(lp, j + 1, colname.c_str());   // OK
    glp_set_col_bnds(lp, j + 1, GLP_LO, 0.0, 0.0);  // OK
    glp_set_obj_coef(lp, j + 1, 1.0);               // OK
  }
  int idx{1};
  for (int i = 0; i < W; ++i) {
    for (int j = 0; j < W; ++j) {
      ia[idx] = i + 1;
      ja[idx] = j + 1;
      ar[idx] = payoffMatrix[j][i] + 2.0;
      ++idx;
    }
  }

  glp_load_matrix(lp, W * W, ia, ja, ar);
  /* solve problem */
  glp_simplex(lp, NULL);
  /* recover and display results */
  // z  = glp_get_obj_val(lp);
  // x1 = glp_get_col_prim(lp, 1);
  // x2 = glp_get_col_prim(lp, 2);
  // printf("z = %g; x1 = %g; x2 = %g\n", z, x1, x2);
  float acc = 0.0f;
  for (int j = 0; j < W; ++j) {
    // printf("x%i = %g\n", j, glp_get_col_prim(lp, j + 1));
    acc += glp_get_col_prim(lp, j + 1);
  }
  array<float,W> rv;
  fill(rv.begin(),rv.end(),0);
  for (int j = 0; j < W; ++j) { rv[j] = glp_get_col_prim(lp, j + 1) / acc; }

  /* housekeeping */
  glp_delete_prob(lp);
  glp_free_env();
  return rv;
}

float Effectiveness_To_Score(const float attack_effectiveness0,const float attack_effectiveness1){
	float bonus{1+(max(attack_effectiveness0/(attack_effectiveness1+Softening_Parameter),attack_effectiveness1/(attack_effectiveness0+Softening_Parameter))>2?Bonus_Coeff:0)};
	if(attack_effectiveness0>attack_effectiveness1){
		return 1*bonus;//Win
	}
	else if(attack_effectiveness0==attack_effectiveness1){
		return 0;//Draw
	}
	else{//attack_effectiveness0<attack_effectiveness1
		return -1*bonus;//Loss
	}
}

float Matchup_Reward(const int type0,const int type1){
	const float attack_effectiveness0{Attack_Effectiveness[type0][type1]};
	const float attack_effectiveness1{Attack_Effectiveness[type1][type0]};
	return Effectiveness_To_Score(attack_effectiveness0,attack_effectiveness1);
};

array<int,2> TypeInt_To_Array(const int type){
	return array<int,2>{type/Num_Types,type%Num_Types};
}

float DoubleTypedEffectiveness(const array<int,2> Attacker_Types,const array<int,2> Defender_Types){
	if(Defender_Types[0]!=Defender_Types[1]){
		return max(Attack_Effectiveness[Attacker_Types[0]][Defender_Types[0]]*Attack_Effectiveness[Attacker_Types[0]][Defender_Types[1]],Attack_Effectiveness[Attacker_Types[1]][Defender_Types[0]]*Attack_Effectiveness[Attacker_Types[1]][Defender_Types[1]]);
	}
	else{
		return max(Attack_Effectiveness[Attacker_Types[0]][Defender_Types[0]],Attack_Effectiveness[Attacker_Types[1]][Defender_Types[0]]);
	}
}

float DoubleTyped_Matchup_Reward(const int type0,const int type1){
	const array<array<int,2>,2> Type{TypeInt_To_Array(type0),TypeInt_To_Array(type1)};
	const float attack_effectiveness0{DoubleTypedEffectiveness(Type[0],Type[1])};
	const float attack_effectiveness1{DoubleTypedEffectiveness(Type[1],Type[0])};
	return Effectiveness_To_Score(attack_effectiveness0,attack_effectiveness1);
}

void Matrix_To_CSV(const array<array<float,Num_Types>,Num_Types> &Matrix,const string &filename){
	ofstream csv_file(filename);
	csv_file << ",";
	for(int type=0;type<Num_Types;++type){
		csv_file << TypeToString[type] << ",";
	}
	csv_file << endl;
	for(int type0=0;type0<Num_Types;++type0){
		csv_file << TypeToString[type0];
		for(int type1=0;type1<Num_Types;++type1){
			csv_file << "," << Matrix[type0][type1];
		}
		csv_file << endl;
	}
}

string TypeArrayToString(const array<int,2> &Types){
	string output;
	output+=TypeToString[Types[0]];
	if(Types[0]!=Types[1]){
		output+="/";
		output+=TypeToString[Types[1]];
	}
	return output;
}

string DoubleTypeToString(const int type){
	const array<int,2> Types{TypeInt_To_Array(type)};
	return TypeArrayToString(Types);
}

void DoubleTypeMatrix_To_CSV(const array<array<float,Num_Type_Pairs>,Num_Type_Pairs> &Matrix,const array<int,Num_Type_Pairs> DoubleTypes,const string &filename){
	ofstream csv_file(filename);
	csv_file << ",";
	for(int i=0;i<Num_Type_Pairs;++i){
		const int type{DoubleTypes[i]};
		csv_file << DoubleTypeToString(type);
	}
	csv_file << endl;
	for(int i=0;i<Num_Type_Pairs;++i){
		const int type{DoubleTypes[i]};
		csv_file << DoubleTypeToString(type);
		for(int j=0;j<Num_Type_Pairs;++j){
			csv_file << "," << Matrix[i][j];
		}
		csv_file << endl;
	}
}

void PayoffMatrix_To_String(const array<array<float,Num_Types>,Num_Types> &Payoff_Matrix){
	for(int type0=0;type0<Num_Types;++type0){
		for(int type1=0;type1<Num_Types;++type1){
			cerr << Payoff_Matrix[type0][type1] << " ";
		}
		cerr << endl;
	}
}

float Round_To(const float f,const int decimal_places){
	const float multiplier{powf(10,decimal_places)};
	return round(f*multiplier)/multiplier;
}

void Single_Type_Analysis(){
	array<array<float,Num_Types>,Num_Types> Payoff_Matrix;
	for(int type0=0;type0<Num_Types;++type0){
		for(int type1=0;type1<Num_Types;++type1){
			Payoff_Matrix[type0][type1]=Matchup_Reward(type0,type1);
		}
	}
	//Matrix_To_CSV(Payoff_Matrix,"payoff.csv");
	//Matrix_To_CSV(Attack_Effectiveness,"effectiveness.csv");
	//PayoffMatrix_To_String(Payoff_Matrix);
	array<float,Num_Types> Nash_Strategy{simplexMatrixSolverStrat<Num_Types>(Payoff_Matrix)};
	array<float,Num_Types> Nash_Values;
	fill(Nash_Values.begin(),Nash_Values.end(),0);
	for(int type0=0;type0<Num_Types;++type0){
		for(int type1=0;type1<Num_Types;++type1){
			Nash_Values[type0]+=Nash_Strategy[type1]*Payoff_Matrix[type0][type1];
		}
	}
	for(int type=0;type<Num_Types;++type){
		Nash_Strategy[type]=Round_To(Nash_Strategy[type],Rounding_Decimals);
		Nash_Values[type]=Round_To(Nash_Values[type],Rounding_Decimals);
	}
	array<int,Num_Types> Ranked_Types;
	iota(Ranked_Types.begin(),Ranked_Types.end(),0);
	sort(Ranked_Types.begin(),Ranked_Types.end(),[&](const int type_a,const int type_b){return Nash_Strategy[type_a]!=Nash_Strategy[type_b]?Nash_Strategy[type_a]>Nash_Strategy[type_b]:Nash_Values[type_a]>Nash_Values[type_b];});
	ofstream type_ranking_file("Type_Ranking.csv");
	type_ranking_file << "Type,Frequency,Value" << endl;
	for(int i=0;i<Num_Types;++i){
		const int type{Ranked_Types[i]};
		cerr << TypeToString[type] << " " << Nash_Strategy[type] << " " << Nash_Values[type] << endl;
		type_ranking_file << TypeToString[type] << "," << Round_To(Nash_Strategy[type],6) << "," << Round_To(Nash_Values[type],6) << endl;
	}
}

void Double_Type_Analysis(){
	array<int,Num_Type_Pairs> DoubleTypesToRank;
	for(int i=0;i<Num_Type_Pairs;++i){
		DoubleTypesToRank[i]=LegalDoubleTypes[i][0]*Num_Types+LegalDoubleTypes[i][1];
	}
	/*int running_idx{0};
	for(int type0=0;type0<Num_Types;++type0){
		for(int type1=type0;type1<Num_Types;++type1){
			DoubleTypesToRank[running_idx]=type0*Num_Types+type1;
			++running_idx;
		}
	}*/
	array<array<float,Num_Type_Pairs>,Num_Type_Pairs> Payoff_Matrix;
	for(int i=0;i<Num_Type_Pairs;++i){
		for(int j=0;j<Num_Type_Pairs;++j){
			Payoff_Matrix[i][j]=DoubleTyped_Matchup_Reward(DoubleTypesToRank[i],DoubleTypesToRank[j]);
		}
	}
	//DoubleTypeMatrix_To_CSV(Payoff_Matrix,DoubleTypesToRank,"payoff.csv");
	array<float,Num_Type_Pairs> Nash_Strategy{simplexMatrixSolverStrat<Num_Type_Pairs>(Payoff_Matrix)};
	array<float,Num_Type_Pairs> Nash_Values;
	fill(Nash_Values.begin(),Nash_Values.end(),0);
	for(int i=0;i<Num_Type_Pairs;++i){
		for(int j=0;j<Num_Type_Pairs;++j){
			Nash_Values[i]+=Nash_Strategy[j]*Payoff_Matrix[i][j];
		}
	}
	array<int,Num_Type_Pairs> Ranked_Types;
	iota(Ranked_Types.begin(),Ranked_Types.end(),0);
	sort(Ranked_Types.begin(),Ranked_Types.end(),[&](const int idx_a,const int idx_b){return Nash_Strategy[idx_a]!=Nash_Strategy[idx_b]?Nash_Strategy[idx_a]>Nash_Strategy[idx_b]:Nash_Values[idx_a]>Nash_Values[idx_b];});
	ofstream type_ranking_file("DoubleType_Ranking.csv");
	type_ranking_file << "Type,Frequency,Value" << endl;
	for(int i=0;i<Num_Type_Pairs;++i){
		const int type_idx{Ranked_Types[i]};
		const int type{DoubleTypesToRank[type_idx]};
		cerr << DoubleTypeToString(type) << " " << Nash_Strategy[type_idx] << " " << Nash_Values[type_idx] << endl;
		type_ranking_file << DoubleTypeToString(type) << "," << Round_To(Nash_Strategy[type_idx],6) << "," << Round_To(Nash_Values[type_idx],6) << endl;
	}
}

int main(){
	//Single_Type_Analysis();
	Double_Type_Analysis();
}