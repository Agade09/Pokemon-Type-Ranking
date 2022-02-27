all:
	g++ Type_Ranking.cpp -o Type_Ranking -std=c++17 -Ofast -march=native -flto -lglpk -Wall -Wextra