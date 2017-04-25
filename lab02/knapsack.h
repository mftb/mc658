/*******************************************************
 * MC658 - Projeto e Analise de Algoritmo III - 1s2017
 * Prof: Flavio Keidi Miyazawa
 * PED: Edson Ticona Zegarra
 ******************************************************/
#ifndef KNAPSACK_H
#define KNAPSACK_H
#include<string>
#include<vector>
#include<algorithm>
#include<set>
#include<time.h>
#include<iostream> //DEBUG
using namespace std;

struct class_element{
    float rel_profit;
    int class_num;
    int pos;
};

struct class_desc{
    vector<class_element> elements;
    float avg_rel_profit;
};

int read_knapsack(string);
int show_usage();
int show_input();
bool bt(int n, int d, int B, vector<int> &p, vector<int> &w, vector<int> &c, vector<int> &sol, int t, clock_t t_start);
bool bnb(int n, int d, int B, vector<int> &p, vector<int> &w, vector<int> &c, vector<int> &sol, int t, clock_t t_start);
bool bnb_search(int current_class, int current_element, int num_of_classes, class_desc classes[], vector<int> &p, vector<int> &w, vector<int> &c, int d, int B,  vector<int> &sol, int best_P, vector<int> current_sol, int current_W, int current_P, int t, clock_t t_start);
bool check_solution();
#endif
