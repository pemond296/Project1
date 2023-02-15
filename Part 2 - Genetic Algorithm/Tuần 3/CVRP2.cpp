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
    Population_size = 10;
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
        if(route[route.size() - 1] != 0)
            cout << "0";
            //  route.push_back(0);
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
        swap(offspring.route[i], parent2.route[i]);
        visited[offspring.route[i]] = true;
    }
    // Với các thành phố còn thiếu chúng ta sẽ điền vào tiếp
    for (int j = 0; j < customer; j++) {
        if (offspring.route[j] == -1) {
            int current = j;
            int parent_city = parent2.route[j];
            while (parent_city != -1 && visited[parent_city]) {
                swap(offspring.route[current], parent_city);
                current = find(parent2.route.begin(), parent2.route.end(), parent_city) - parent2.route.begin();
                visited[parent_city] = true;
            }
        }
    }
    replace_Depot(offspring);
    // Kiểm tra xem thành phố 0 (Depot) có xuất hiện ở vị trí khác không, nếu có thì loại bỏ
    for (int i = 1; i < offspring.route.size() - 1; i++) {
        if (offspring.route[i] == 0) {
            offspring.route.erase(offspring.route.begin() + i);
        }
    }
    return offspring;
    // Nếu thỏa mãn điều kiện của route
    if(check_Route(offspring.route, capacity)) return offspring;
    else return parent1;
}

// Hàm đột biến (mutation)
Solution mutate(Solution s) {
    if(s.route.size() == 3) {
        int idx = s.route[1];
        while(s.route[1] != idx){
            s.route[1] = 1 + rand() % customer;
        }
    }

    else{
        int pos1 = rand() % (s.route.size() - 1) + 1;
        int pos2 = rand() % (s.route.size() - 1) + 1;
        while (pos1 == pos2){
            pos2 = rand() % (s.route.size() - 1) + 1;
        }
        swap(s.route[pos1], s.route[pos2]);
    }
    return s;
}

// Hàm lựa chọn
vector<Solution> selection(vector<Solution> population) {
    vector<Solution> newPopulation;
    for(int i = 0; i < population.size(); i++) {
        int routeDemand = 0;
        vector<int> visited(customer + 1, 0);
        bool flag = true;
        for(int j = 0; j < population[i].route.size(); j++) {
            if(population[i].route[j] == 0) {
                if(j != 0 && j != population[i].route.size() - 1) {
                    flag = false;
                    break;
                }
                continue;
            }
            routeDemand += customers[population[i].route[j]].demand;
            if(routeDemand > capacity) {
                flag = false;
                break;
            }
            if(visited[population[i].route[j]]) {
                flag = false;
                break;
            }
            visited[population[i].route[j]] = true;
        }
        if(flag) {
            population[i].fitness = route_Distance(population[i].route);
            newPopulation.push_back(population[i]);
        }
    }

    return newPopulation;
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

// Hàm trả về số lượng xe sử dụng và tổng fitness của những solution được chọn ra
void vehicle_fitness(vector<Solution> &population) {
    memset(visited, false, sizeof(visited));
    TRY(0, population);
        for(int i = 0; i < solve.size(); i++){
            for(int j = 0; j < solve[i].size();j++){
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
            // population = selection(population);
            // newPopulation = population;
            // Solution offspring = crossover(population[rand() % population.size()],population[rand() % population.size()]);
            Solution offspring = mutate(offspring);
            newPopulation.push_back(offspring);
        }
        population = newPopulation;
        // newPopulation.clear();
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