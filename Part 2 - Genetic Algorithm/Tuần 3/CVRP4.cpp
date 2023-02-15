#include <bits/stdc++.h>

using namespace std;

int customer;               // Lượng khách hàng
int vehicle;                // Lượng xe    
int capacity;               // Dung lượng mỗi xe
// int distances[100][100];    // Khoảng cách giữa các thành phố 
bool visited[100];          // Đánh dấu thành phố đã có trong 1 lộ trình khác
int Num_Generations;        // Số lần lai
int Population_size;        // Số NST trong quần thể
int distances[100][100] = { { 0, 1, 2, 3, 4, 5, 6},
                            { 0, 0, 2, INT_MAX, 12, 5, 5 },
                            { 0, 2, 0, 4, 8, INT_MAX, 9 },
                            { 0, INT_MAX, 4, 0, 3, 3, 12 },
                            { 0, 12, 8, 3, 0, 10, 13 },
                            { 0, 5, INT_MAX, 3, 10, 0, 5 },
                            { 0, 5, 9, 12 ,13, 5, 0} }; 


// Cấu trúc một khách hàng
struct Customer {
    int city;            // Tên thành phố  
    int demand;          // Lượng hàng yêu cầu
};

vector<Customer> customers;

void input(){
    memset(visited, false, sizeof(visited));
    customer = 6;
    customers.resize(customer + 1);
    customers[0].city = 0;
    customers[0].demand = 0;
    for(int i = 1; i <= customer; i++){
        customers[i].city = customers[i].demand = i;
    }    
    capacity = 8;
    vehicle = 3;
    Num_Generations = 10;
    Population_size = 20;
}

// void input(){
//     cin >> customer >> vehicles;
//     customers.resize(customer + 1);
//     // Depot
//     customers[0].city = 0;
//     customers[0].demand = 0;
//     // Lượng hàng yêu cầu của các thành phố
//     for(int i = 1; i <= customer; i++){
//         customers[i].city = i;
//         cin >> customers[i].demand;
//     }
//     for(int i = 0; i <= customer; i++){
//         for(int j = 0; j <= customer; j++){
//             cin >> distances[i][j];
//         }
//     }
//     cout << endl;
//     cin >> capacity >> vehicle;
//     cin >> Num_Generations >> Population_size;
// }

// 1 giải pháp trong quần thể
struct Solution {
    vector<int> route;
    int fitness;
    void output(){
        for(int i = 0; i < route.size(); i++){
            cout << route[i];
        }
    }
};

// Tính tổng khoảng cách của một tuyến đường
int route_Distance(vector<int> route) {
    int fitness = 0;
    for (int i = 0; i < route.size() - 1; i++) {
        if(distances[route[i]][route[i + 1]] == INT_MAX)
            return INT_MAX;
        fitness += distances[route[i]][route[i + 1]];
    }
    return fitness;
}

// Kiểm tra tính hợp lệ của một tuyến đường
bool check_Route(vector<int> route, int capacity) {
    int currentCapacity = 0;
    for (int i = 0; i < route.size(); i++) {
        currentCapacity += customers[route[i]].demand;
        if (currentCapacity > capacity) {
            return false;
        }
    }
    return true;
}

// Hàm khởi tạo quần thể
vector<Solution> initPopulation() {
    vector<Solution> population;
    for (int i = 0; i < Population_size; i++) {
        Solution s;
        s.route.push_back(0); // Thêm thành phố bắt đầu (Depot) vào tuyến đường
        int temp = 1 + rand() % customer;
        if(visited[temp] == false){
            s.route.push_back(temp);
            visited[temp] = true;
        }
        // Kiểm tra xem có thể thêm thành phố vào route
        for(int i = 1 + rand() % 3; i <= customer; i++){
            if(!visited[i]){
                Solution a(s);
                a.route.push_back(i);
                if(check_Route(a.route, capacity)){
                    s.route.push_back(i);
                    visited[i] = true;
                }
            }
        }
        s.route.push_back(0); // Thêm thành phố kết thúc (Depot) vào tuyến đường
        s.fitness = route_Distance(s.route);
        population.push_back(s);
        int count = 0;
        for(int i = 1; i <= customer; i++){
            if(visited[i] == true) count++;
        }
        if (count == customer) memset(visited, false, sizeof(visited));
    }
    return population; 
}

// // Hàm thay thế thành phố Depot
void replace_Depot(Solution & offspring) {
    for(int i = 1; i < offspring.route.size() - 1; i++){
        visited[i] = true;
    }
    // Tìm vị trí của thành phố Depot trong solution
    int pos = find(offspring.route.begin(), offspring.route.end() - 1, 0) - offspring.route.begin();
    // Lặp qua tất cả các thành phố khác để tìm thành phố thay thế
    for (int i = 1; i <= customer; i++) {
        if (i != 0 && !visited[i]){
            // Thay thế thành phố 0 bằng thành phố i
            offspring.route[pos] = i;
            // Kiểm tra xem lộ trình sau khi thay thế có thỏa mãn điều kiện không
            if (check_Route(offspring.route, capacity)) {
                return;
            }
        }
    }
}

void replace_city(Solution &offspring){
    vector<int> pos;
    for(int i = 1; i < offspring.route.size() - 1; i++){
        visited[i] = true;
        for(int j = i + 1; j < offspring.route.size(); j++){
            if(visited[j] == true){
                pos.push_back(j);
            }
        }
    }
    // Tìm vị trí của thành phố bị trùng trong solution
    // Lặp qua tất cả các thành phố khác để tìm thành phố thay thế
    for (int i = 1; i <= customer; i++) {
        for(int j = 0; j < pos.size() - 1; j++){
            if (!visited[i]){
            // Thay thế thành phố bị trùng bằng thành phố i
                offspring.route[pos[j]] = i;
            // Kiểm tra xem lộ trình sau khi thay thế có thỏa mãn điều kiện không
                if (check_Route(offspring.route, capacity)) {
                    return;
                }
            }
        }
    }
}
// Hàm lai ghép (crossover)
Solution crossover(Solution parent1, Solution parent2) {
    memset(visited, false, sizeof(visited));
    Solution offspring;
    int start = 1 + rand() % (parent1.route.size() - 1);
    int end = 1 + rand() % (parent1.route.size() - 1);
    if (start > end) {
        swap(start, end);
    }
    offspring.route = parent1.route;
    // Đẩy các thành phố từ start đến end trong parent2 vào offsping
    for (int i = start; i < end; i++) {
        int city = parent2.route[i];
        if (!visited[city]) {
            visited[city] = true;
            offspring.route[i] = city;
        } 
        else {
        // Tìm thành phố chưa được xuất hiện trong offspring
            for (int j = 1; j < customer; j++) {
                if (!visited[j]) {
                    visited[j] = true;
                    offspring.route[i] = j;
                    break;
                }
            }
        }
    }
    replace_Depot(offspring);
    // Kiểm tra xem thành phố 0 (Depot) có xuất hiện ở vị trí khác không, nếu có thì loại bỏ
    for (int i = 1; i < offspring.route.size() - 1; i++) {
        if (offspring.route[i] == 0) {
        offspring.route.erase(offspring.route.begin() + i);
        i--;
        }
    } 
    for(int  i = 1; i < offspring.route.size() - 1; i++) {
        for(int j = i+1; j < offspring.route.size() - 1; j++) {
            if(offspring.route[i] == offspring.route[j]) {
                offspring.route.erase(offspring.route.begin() + j);
            }
        }
    }
    for(int  i = 1; i < parent1.route.size() - 1; i++) {
        for(int j = i+1; j < parent1.route.size() - 1; j++) {
            if(parent1.route[i] == parent1.route[j]) {
                parent1.route.erase(parent1.route.begin() + j);
            }
        }
    }
    if(offspring.route.front() != 0){
        offspring.route.insert(offspring.route.begin(), 0);
    }
    // Nếu thỏa mãn điều kiện của route
    if (check_Route(offspring.route, capacity)) {
        return offspring;
    } 
    else  return parent1;
}

// Hàm đột biến (mutation)
Solution mutate(Solution s) {

    for(int  i = 1; i < s.route.size() - 1; i++) {
        for(int j = i+1; j < s.route.size() - 1; j++) {
            if(s.route[i] == s.route[j]) {
                s.route.erase(s.route.begin() + j);
            }
        }
    }
    if(route_Distance(s.route) == INT_MAX) {
        int pos1 = rand() % (s.route.size() - 2) + 1;
        int pos2 = rand() % (s.route.size() - 2) + 1;
        while (pos1 == pos2){
            pos2 = rand() % (s.route.size() - 2) + 1;
        }
        swap(s.route[pos1], s.route[pos2]);
    }
    
    return s;
}

bool less_sort(Solution c1, Solution c2){
    return c1.fitness < c2.fitness;
}

vector<vector<Solution>> solve;
vector<Solution> x;

bool check_city(vector<int> route){
    for(int i = 1; i < route.size() - 1; i++){
        if(visited[route[i]] == true) return false;
    }
    return true;
}

bool check_stop(){
    for(int i = 1; i <= customer; i++){
        if(visited[i] == false)
            return false;
    }
    return true;
}

void TRY(int i, vector<Solution> &population){
    for(int j = 0; j < population.size(); j++) {
        if(check_city(population[j].route)){
            x.push_back(population[j]);
            for(int k = 1; k < population[j].route.size() - 1; k++){
                visited[population[j].route[k]] = true;
            }
            if(check_stop()){
                solve.push_back(x);
                x.pop_back();
                break;
            }
            else{
                TRY(i+1, population);
                }
            for(int k = 1; k < population[j].route.size() - 1; k++){
                visited[population[j].route[k]] = false;
            }
            x.pop_back();
        }
    }
}

vector<Solution> joker;

// Hàm trả về số lượng xe sử dụng và tổng fitness của những solution được chọn ra
void vehicle_fitness(vector<Solution> &population) {
    memset(visited, false, sizeof(visited));
    TRY(0, population);
    for(int i = 0; i < solve.size(); i++){
        for(int j = 0; j < solve[i].size();j++){
            joker.push_back(solve[i][j]);
            solve[i][j].output();
            // cout << setw(19) << right << solve[i][j].fitness << endl;
            cout << " ";
        }
        solve.clear();
        cout << endl;
    }
}


void solve_CVRP(){
    input();
    vector<Solution> population = initPopulation();
    cout << "Initial population: " << endl; 
    cout << "Route" << setw(20) << right <<     "Fitness" << endl;
    for (int i = 0; i < Population_size; i++){
        population[i].output();
        cout << setw(19) << right << population[i].fitness << endl;
    }
    cout << endl;
    vehicle_fitness(population);
    int gen = 0;
    while(++gen <= Num_Generations){
        sort(population.begin(), population.end(), less_sort);
        vector<Solution> newPopulation;
        for (int i = 0; i < Population_size; i++){
            Solution parent1 = population[rand() % population.size()];
            Solution parent2 = population[rand() % population.size()];
            Solution offspring = crossover(parent1, parent2);
            offspring = mutate(offspring);
            newPopulation.push_back(offspring);
            if(joker.size() == Population_size - newPopulation.size()){
                for(int i = 0; i < joker.size(); i++){
                    newPopulation.push_back(joker[i]);
                }
            }
        }
        joker.clear();
        population = newPopulation;
        // Tính toán lại fitness cho mỗi cá thể trong quần thể
        for (int i = 0; i < Population_size; i++) {
            population[i].fitness = route_Distance(population[i].route);
        }
        cout << endl << "Generation " << gen << endl;
        cout << "Route" << setw(20) << right <<     "Fitness" << endl;
        for (int i = 0; i < Population_size; i++){
            population[i].output();
            cout << setw(19) << right << population[i].fitness << endl;
        }
        cout << endl;
        vehicle_fitness(population);
    }
}

int main(){
    srand(time(NULL));
    solve_CVRP();
    return 0;
}