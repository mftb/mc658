/*******************************************************
 * MC658 - Projeto e Analise de Algoritmo III - 1s2017
 * Prof: Flavio Keidi Miyazawa
 * PED: Edson Ticona Zegarra
 ******************************************************/
#include "knapsack.h"

///Preencher aqui para facilitar a correcao. 
// Nome1: Matheus Ferreira Tavares Boy
// RA1: 103501
// Nome2: 
// RA2:
///
// Bactracking function: 
///
bool bt_search(int current_class, int current_element, int num_of_classes, vector<int> classes[], vector<int> &p, vector<int> &w, vector<int> &c, int n, int d, int B,  vector<int> &sol, int &best_P, vector<int> current_sol, int current_W, int current_P, int t, clock_t t_start){
    clock_t now, delta_t;
    now = clock();
    delta_t = now - t_start;
    //DEBUG
    cout << "current_class: " << current_class << " current_element: " << current_element << " num_of_classes: " << num_of_classes << endl;
    cout << "best_P: " << best_P << " current_P: " << current_P << endl;
    cout << "current_W: " << current_W << endl;
    cout << "classes[current_class][current_element]: " << classes[current_class][current_element] << endl;
    cout << "classes[current_class].size(): " << classes[current_class].size() << endl;
    cout << "partial solution: " << endl;
    for(int i=0; i<n; i++){
        cout << current_sol[i] << " ";
    }
    cout << endl;
    cout << "best solution: " << endl;
    for(int i=0; i<n; i++){
        cout << sol[i] << " ";
    }
    cout << endl;
    //Time limit test
    if((((float)delta_t)/CLOCKS_PER_SEC) > (float)t){
        return false;
    }
    else{
        //TODO: Check issues with this bound
        //Tests upper bound (bandwidth limit)
        if(current_W + w[classes[current_class][current_element]] > B){
            //Current element does not fit, set it as zero and call for next element
            current_sol[classes[current_class][current_element]] = 0;
            //Checks if is last element of last class
            if((current_class == num_of_classes - 1) && (current_element == classes[current_class].size() - 1)){
                if(current_P > best_P){
                    best_P = current_P;
                    for(int i=0; i<n; i++)
                        sol[i] = current_sol[i];
                }
            }
            //There are elements left in classes
            else{
                //Test whether there are remaining elements in current class
                if(current_element + 1 < classes[current_class].size()){
                    now = clock();
                    delta_t = now - t_start;
                    if((((float)delta_t)/CLOCKS_PER_SEC) > (float)t) return false;
                    bt_search(current_class, current_element + 1, num_of_classes, classes, p, w, c, n, d, B, sol, best_P, current_sol, current_W, current_P, t, t_start);
                    now = clock();
                    delta_t = now - t_start;
                    if((((float)delta_t)/CLOCKS_PER_SEC) > (float)t) return false;
                }
                //Last element in class, pick first element of next class and add d to current_W
                else{
                    now = clock();
                    delta_t = now - t_start;
                    if((((float)delta_t)/CLOCKS_PER_SEC) > (float)t) return false;
                    //TODO: Check issues with W
                    bt_search(current_class + 1, 0, num_of_classes, classes, p, w, c, n, d, B, sol, best_P, current_sol, current_W+d, current_P, t, t_start);
                    now = clock();
                    delta_t = now - t_start;
                    if((((float)delta_t)/CLOCKS_PER_SEC) > (float)t) return false;
                }
                //Checks if current solution is better than the best solution
                if(current_P > best_P){
                    best_P = current_P;
                    for(int i=0; i<n; i++)
                       sol[i] = current_sol[i];
                }
            }
        }
        else{
            //Current element fits, include it in current solution
                current_sol[classes[current_class][current_element]] = 1;
                current_P += p[classes[current_class][current_element]];
                current_W += w[classes[current_class][current_element]];
                //Checks if current solution is better than the best solution
                if(current_P > best_P){
                    best_P = current_P;
                    for(int i=0; i<n; i++)
                       sol[i] = current_sol[i];
                }
                //Checks if is last element of last class
                if((current_class == num_of_classes - 1) && (current_element == classes[current_class].size() - 1)){
                    //Checks if current solution is better than the best solution
                    if(current_P > best_P){
                        best_P = current_P;
                        for(int i=0; i<n; i++)
                           sol[i] = current_sol[i];
                    }
                }
                //There are elements left in classes
                else{
                    //Test whether there are remaining elements in current class
                    if(current_element + 1 < classes[current_class].size()){
                        now = clock();
                        delta_t = now - t_start;
                        if((((float)delta_t)/CLOCKS_PER_SEC) > (float)t) return false;
                        bt_search(current_class, current_element + 1, num_of_classes, classes, p, w, c, n, d, B, sol, best_P, current_sol, current_W, current_P, t, t_start);
                        now = clock();
                        delta_t = now - t_start;
                        if((((float)delta_t)/CLOCKS_PER_SEC) > (float)t) return false;
                    }
                    //Last element in class, pick first element of next class and add d to current_W
                    else{
                        now = clock();
                        delta_t = now - t_start;
                        if((((float)delta_t)/CLOCKS_PER_SEC) > (float)t) return false;
                        //TODO: Check issues with W
                        bt_search(current_class + 1, 0, num_of_classes, classes, p, w, c, n, d, B, sol, best_P, current_sol, current_W+d, current_P, t, t_start);
                        now = clock();
                        delta_t = now - t_start;
                        if((((float)delta_t)/CLOCKS_PER_SEC) > (float)t) return false;
                    }
                }
                //Current element might not improve best profit, lets not include it in the current solution and keep running
                current_sol[classes[current_class][current_element]] = 0;
                current_P -= p[classes[current_class][current_element]];
                current_W -= w[classes[current_class][current_element]];
                //Checks if current solution is better than the best solution
                if(current_P > best_P){
                    best_P = current_P;
                    for(int i=0; i<n; i++)
                       sol[i] = current_sol[i];
                }
                //Checks if is last element of last class
                if((current_class == num_of_classes - 1) && (current_element == classes[current_class].size() - 1)){
                    //Checks if current solution is better than the best solution
                    if(current_P > best_P){
                        best_P = current_P;
                        for(int i=0; i<n; i++)
                           sol[i] = current_sol[i];
                    }
                }
                //There are elements left in classes
                else{
                    //Test whether there are remaining elements in current class
                    if(current_element + 1 < classes[current_class].size()){
                        now = clock();
                        delta_t = now - t_start;
                        if((((float)delta_t)/CLOCKS_PER_SEC) > (float)t) return false;
                        bt_search(current_class, current_element + 1, num_of_classes, classes, p, w, c, n, d, B, sol, best_P, current_sol, current_W, current_P, t, t_start);
                        now = clock();
                        delta_t = now - t_start;
                       if((((float)delta_t)/CLOCKS_PER_SEC) > (float)t) return false;
                    }
                    //Last element in class, pick first element of next class and add d to current_W
                    else{
                        now = clock();
                        delta_t = now - t_start;
                        if((((float)delta_t)/CLOCKS_PER_SEC) > (float)t) return false;
                        bt_search(current_class + 1, 0, num_of_classes, classes, p, w, c, n, d, B, sol, best_P, current_sol, current_W, current_P, t, t_start);
                        now = clock();
                        delta_t = now - t_start;
                       if((((float)delta_t)/CLOCKS_PER_SEC) > (float)t) return false;
                    }
            }
        }
        return true;
    }
}

bool bt(int n, int d, int B, vector<int> &p, vector<int> &w, vector<int> &c, vector<int> &sol, int t, clock_t t_start){
    int biggest_class;
    biggest_class = 0;

    //Preprocessing to group elements by class

    //Compute the number of classes
    for(int i=0; i<n; i++){
        biggest_class = (c[i] > biggest_class) ? c[i] : biggest_class;
    }

    //Creates the array of classes
    vector<int> classes[biggest_class];

    //Initializes array of classes
    for(int i=0; i<n; i++){
        classes[c[i] - 1].push_back(i);
    }
    //DEBUG
    for(int i=0; i<biggest_class; i++){
        cout << "Class: " << i << endl;
        for(int j=0; j<classes[i].size(); j++){
            cout << p[classes[i][j]] << " " << w[classes[i][j]] << " " << c[classes[i][j]] << " position: " << classes[i][j] << endl;
        }
    }

    //Some setup before search
    vector<int> current_sol;
    for(int i=0; i<n; i++) current_sol.push_back(0);
    int best_P;
    best_P = 0;
    //Done preprocessing, begin BnB
    //return bt_search(0, 0, biggest_class, classes, p, w, c, n, d, B, sol, best_P, current_sol, 0, 0, t, t_start);

    //DEBUG
    if(!bt_search(0, 0, biggest_class, classes, p, w, c, n, d, B, sol, best_P, current_sol, 0, 0, t, t_start)){
        cout << "Time limit reached" << endl;
        cout << "Best solution: " << best_P << endl;
        cout << "-------" << endl;
        return false;
    }
    else {
        cout << "Best solution: " << best_P << endl;
        cout << "-------" << endl;
        return true;
    }
}

bool compare_rel_profit(const bnb_class_element &a, const bnb_class_element &b){
    return a.rel_profit > b.rel_profit;
}

bool compare_avg_rel_profit(const bnb_class_desc &a, const bnb_class_desc &b){
    return a.avg_rel_profit > b.avg_rel_profit;
}

bool bnb_search(int current_class, int current_element, int num_of_classes, bnb_class_desc classes[], vector<int> &p, vector<int> &w, vector<int> &c, int n, int d, int B,  vector<int> &sol, int &best_P, vector<int> current_sol, int current_W, int current_P, int t, clock_t t_start){
    clock_t now, delta_t;
    now = clock();
    delta_t = now - t_start;
    /*
    //DEBUG
    cout << "Current class: " << current_class << " current element: " << current_element << endl;
    cout << "best_P: " << best_P << " current_P: " << current_P <<endl;
    cout << "sol: ";
    for(int i=0; i<sol.size(); i++)
        cout << sol[i] << " ";
    cout << endl;
    cout << "current_sol: ";
    for(int i=0; i<current_sol.size(); i++)
        cout << current_sol[i] << " ";
    cout << endl;
    */
    //Time limit test
    if((((float)delta_t)/CLOCKS_PER_SEC) > (float)t){
        return false;
    }
    else{
        //Tests upper bound (bandwidth limit)
        if(current_W + w[classes[current_class].elements[current_element].pos] > B){
            //Current element does not fit, set it as zero and call for next element
            current_sol[classes[current_class].elements[current_element].pos] = 0;
            //Checks if is last element of last class
            if((current_class == num_of_classes - 1) && (current_element == classes[current_class].elements.size() - 1)){
                if(current_P > best_P){
                    best_P = current_P;
                    for(int i=0; i<n; i++)
                        sol[i] = current_sol[i];
                }
            }
            //There are elements left in classes
            else{
                //Test whether there are remaining elements in current class
                if(current_element + 1 < classes[current_class].elements.size()){
                    now = clock();
                    delta_t = now - t_start;
                    if((((float)delta_t)/CLOCKS_PER_SEC) > (float)t) return false;
                    bnb_search(current_class, current_element + 1, num_of_classes, classes, p, w, c, n, d, B, sol, best_P, current_sol, current_W, current_P, t, t_start);
                    now = clock();
                    delta_t = now - t_start;
                    if((((float)delta_t)/CLOCKS_PER_SEC) > (float)t) return false;
                }
                //Last element in class, pick first element of next class and add d to current_W
                else{
                    now = clock();
                    delta_t = now - t_start;
                    if((((float)delta_t)/CLOCKS_PER_SEC) > (float)t) return false;
                    bnb_search(current_class + 1, 0, num_of_classes, classes, p, w, c, n, d, B, sol, best_P, current_sol, current_W+d, current_P, t, t_start);
                    now = clock();
                    delta_t = now - t_start;
                    if((((float)delta_t)/CLOCKS_PER_SEC) > (float)t) return false;
                }
                if(current_P > best_P){
                    best_P = current_P;
                    for(int i=0; i<n; i++)
                        sol[i] = current_sol[i];
                }
            }
        }
        //Current element fits
        //Tests lower bound (best expected profit margin)
        else{
            //Tests if the greedy add of current element improves the best profit
            if((float)current_P + (float)(B - current_W)*((float)p[classes[current_class].elements[current_element].pos])/((float)w[classes[current_class].elements[current_element].pos]) < (float)best_P){
                //Current element does not improve the best profit, set it as zero and call for next element
                current_sol[classes[current_class].elements[current_element].pos] = 0;
                //Checks if is last element of last class
                if((current_class == num_of_classes - 1) && (current_element == classes[current_class].elements.size() - 1)){
                    if(current_P > best_P){
                        best_P = current_P;
                        for(int i=0; i<n; i++)
                           sol[i] = current_sol[i];
                    }
                }
                //There are elements left in classes
                else{
                    //Test whether there are remaining elements in current class
                    if(current_element + 1 < classes[current_class].elements.size()){
                        now = clock();
                        delta_t = now - t_start;
                        if((((float)delta_t)/CLOCKS_PER_SEC) > (float)t) return false;
                        bnb_search(current_class, current_element + 1, num_of_classes, classes, p, w, c, n, d, B, sol, best_P, current_sol, current_W, current_P, t, t_start);
                        now = clock();
                        delta_t = now - t_start;
                        if((((float)delta_t)/CLOCKS_PER_SEC) > (float)t) return false;
                    }
                    //Last element in class, pick first element of next class and add d to current_W
                    else{
                        now = clock();
                        delta_t = now - t_start;
                        if((((float)delta_t)/CLOCKS_PER_SEC) > (float)t) return false;
                        bnb_search(current_class + 1, 0, num_of_classes, classes, p, w, c, n, d, B, sol, best_P, current_sol, current_W+d, current_P, t, t_start);
                        now = clock();
                        delta_t = now - t_start;
                        if((((float)delta_t)/CLOCKS_PER_SEC) > (float)t) return false;
                    }
                    if(current_P > best_P){
                        best_P = current_P;
                        for(int i=0; i<n; i++)
                            sol[i] = current_sol[i];
                    }
                }
            }
            else{
                //Current element might improve best profit, include it in the best solution and in the current solution
                current_sol[classes[current_class].elements[current_element].pos] = 1;
                current_P += p[classes[current_class].elements[current_element].pos];
                current_W += w[classes[current_class].elements[current_element].pos];
                //Checks if is last element of last class
                if((current_class == num_of_classes - 1) && (current_element = classes[current_class].elements.size() - 1)){
                    if(current_P > best_P){
                        best_P = current_P;
                        for(int i=0; i<n; i++)
                           sol[i] = current_sol[i];
                    }
                }
                //There are elements left in classes
                else{
                    //Test whether there are remaining elements in current class
                    if(current_element + 1 < classes[current_class].elements.size()){
                        now = clock();
                        delta_t = now - t_start;
                        if((((float)delta_t)/CLOCKS_PER_SEC) > (float)t) return false;
                        bnb_search(current_class, current_element + 1, num_of_classes, classes, p, w, c, n, d, B, sol, best_P, current_sol, current_W, current_P, t, t_start);
                        now = clock();
                        delta_t = now - t_start;
                        if((((float)delta_t)/CLOCKS_PER_SEC) > (float)t) return false;
                    }
                    //Last element in class, pick first element of next class and add d to current_W
                    else{
                        now = clock();
                        delta_t = now - t_start;
                        if((((float)delta_t)/CLOCKS_PER_SEC) > (float)t) return false;
                        bnb_search(current_class + 1, 0, num_of_classes, classes, p, w, c, n, d, B, sol, best_P, current_sol, current_W+d, current_P, t, t_start);
                        now = clock();
                        delta_t = now - t_start;
                        if((((float)delta_t)/CLOCKS_PER_SEC) > (float)t) return false;
                    }
                    if(current_P > best_P){
                        best_P = current_P;
                        for(int i=0; i<n; i++)
                           sol[i] = current_sol[i];
                    }
                }
                //Current element might not improve best profit, lets not include it in the best solution and keep running
                current_sol[classes[current_class].elements[current_element].pos] = 0;
                current_P -= p[classes[current_class].elements[current_element].pos];
                current_W -= w[classes[current_class].elements[current_element].pos];
                //Checks if is last element of last class
                if((current_class == num_of_classes - 1) && (current_element == classes[current_class].elements.size() - 1)){
                    if(current_P > best_P){
                        best_P = current_P;
                        for(int i=0; i<n; i++)
                           sol[i] = current_sol[i];
                    }
                }
                //There are elements left in classes
                else{
                    //Test whether there are remaining elements in current class
                    if(current_element + 1 < classes[current_class].elements.size()){
                        now = clock();
                        delta_t = now - t_start;
                        if((((float)delta_t)/CLOCKS_PER_SEC) > (float)t) return false;
                        bnb_search(current_class, current_element + 1, num_of_classes, classes, p, w, c, n, d, B, sol, best_P, current_sol, current_W, current_P, t, t_start);
                        now = clock();
                        delta_t = now - t_start;
                       if((((float)delta_t)/CLOCKS_PER_SEC) > (float)t) return false;
                    }
                    //Last element in class, pick first element of next class and add d to current_W
                    else{
                        now = clock();
                        delta_t = now - t_start;
                        if((((float)delta_t)/CLOCKS_PER_SEC) > (float)t) return false;
                        bnb_search(current_class + 1, 0, num_of_classes, classes, p, w, c, n, d, B, sol, best_P, current_sol, current_W, current_P, t, t_start);
                        now = clock();
                        delta_t = now - t_start;
                       if((((float)delta_t)/CLOCKS_PER_SEC) > (float)t) return false;
                    }
                    if(current_P > best_P){
                        best_P = current_P;
                        for(int i=0; i<n; i++)
                           sol[i] = current_sol[i];
                    }
                }
            }
        }
        return true;
    }
}

///
// Branch and Bound function
///
bool bnb(int n, int d, int B, vector<int> &p, vector<int> &w, vector<int> &c, vector<int> &sol, int t, clock_t t_start){
    vector<float> e_rel_profit;
    vector<int> e_rel_profit_class;
    vector<int> e_rel_profit_pos;
    int biggest_class;
    biggest_class = 0;

    //Preprocessing to search in a greedier order

    //Compute the relative profit of each element of each class
    for(int i=0; i<n; i++){
        e_rel_profit.push_back((float)p[i]/(float)w[i]);
        e_rel_profit_class.push_back(c[i]);
        biggest_class = (c[i] > biggest_class) ? c[i] : biggest_class;
        e_rel_profit_pos.push_back(i);
    }

    //Creates the array of classes
    bnb_class_desc classes[biggest_class];

    //Initializes array of classes
    for(int i=0; i<n; i++){
        classes[e_rel_profit_class[i] - 1].elements.push_back(bnb_class_element());
        classes[e_rel_profit_class[i] - 1].elements[classes[e_rel_profit_class[i]-1].elements.size() - 1].rel_profit = e_rel_profit[i];
        classes[e_rel_profit_class[i] - 1].elements[classes[e_rel_profit_class[i]-1].elements.size() - 1].class_num = e_rel_profit_class[i];
        classes[e_rel_profit_class[i] - 1].elements[classes[e_rel_profit_class[i]-1].elements.size() - 1].pos = e_rel_profit_pos[i];
    }

    //Compute the average relative profit for each class and order each class by the relative profit of its elements, in descending order
    float avg;
    for(int i=0; i<biggest_class; i++){
        //Computing the average relative profit for current class
        avg = 0.0;
        for(int j=0; j<classes[i].elements.size(); j++){
            avg += classes[i].elements[j].rel_profit;
        }
        avg = avg / (float)classes[i].elements.size();
        classes[i].avg_rel_profit = avg;
        //Sorting classes by its most profitable elements
        std::sort(classes[i].elements.begin(), classes[i].elements.end(), compare_rel_profit);
    }

    //Order the classes by the average relative profit, in descending order
    std::sort(classes, classes+biggest_class, &compare_avg_rel_profit);

    //Some setup before search
    vector<int> current_sol;
    for(int i=0; i<n; i++) current_sol.push_back(0);
    int best_P;
    best_P = 0;
    //Done preprocessing, begin BnB
    //return bnb_search(0, 0, biggest_class, classes, p, w, c, n, d, B, sol, best_P, current_sol, 0, 0, t, t_start);

    //DEBUG
    if(!bnb_search(0, 0, biggest_class, classes, p, w, c, n, d, B, sol, best_P, current_sol, 0, 0, t, t_start)){
        cout << "Time limit reached" << endl;
        cout << "Best solution: " << best_P << endl;
        cout << "-------" << endl;
        return false;
    }
    else {
        cout << "Best solution: " << best_P << endl;
        cout << "-------" << endl;
        return true;
    }
}








