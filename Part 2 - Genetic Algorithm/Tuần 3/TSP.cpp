#include <bits/stdc++.h>

using namespace std;

const int Num_Cities = 5;         // Số lượng thành phố trong bài toán TSP
int distances[100][100] = { { 0, 2, INT_MAX, 12, 5 },
                    { 2, 0, 4, 8, INT_MAX },
                    { INT_MAX, 4, 0, 3, 3 },
                    { 12, 8, 3, 0, 10 },
                    { 5, INT_MAX, 3, 10, 0 } };          // Mảng chứa các khoảng cách giữa các thành phố
const int Num_Generations = 5;      // Số lần lai (generations)
const int Population_size = 5;      // Số nhiễm sắc thể trong quần thể

// int Num_Cities;
// int distances[100][100];
// int Num_Generations;
// int Population_size;

// void input(){
//     cin >> Num_Cities;
//     for(int i = 0; i < Num_Cities; i++){
//         for(int j = 0; j < Num_Cities; j++){
//             cin >> distances[i][j];
//         }
//     }
//     cin >> Num_Generations;
//     cin >> Population_size;
// }

// Một cá thể trong quần thể di truyền
struct Chromosome {
    string cities;
    int fitness;
};

// Hàm tính độ tốt của cá thể dựa trên đường đi của nó
int calcFitness(string cities) {
    int fitness = 0;
    for (int i = 0; i < cities.size() - 1; i++){
        if(distances[cities[i] - 48][cities[i + 1] - 48] == INT_MAX)
            return INT_MAX;
        fitness += distances[cities[i] - 48][cities[i + 1] - 48];
    }
    return fitness;
}

// Hàm check thành phố đã xuất hiện trong string 
bool check(string s, char a){
    for (int i = 0; i < s.size(); i++){
        if (s[i] == a) return true;
    }
    return false;
}

string create_Chromosome(){
    string cities = "0";
    while(true){
        if (cities.size() == Num_Cities) {
            cities += cities[0];
            break;
        }
        int temp = rand() % Num_Cities;
        if(!check(cities, (char)(temp + 48)))
            cities += (char)(temp + 48);
    }
    return cities;
}

// Quần thể di truyền
vector<Chromosome> population;

// Hàm khởi tạo quần thể ban đầu
void initPopulation() {
    Chromosome c;
    for (int i = 0; i < Population_size; i++) {
        c.cities = create_Chromosome();
        c.fitness = calcFitness(c.cities);
        population.push_back(c);
    }
}

//Hàm lai ghép(crossover) 
string crossover(Chromosome c1, Chromosome c2) {
    Chromosome offspring;
    // Chọn ngẫu nhiên 2 điểm cắt
    int cut1 = 1 + rand() % (Num_Cities - 1);
    int cut2 = 1 + rand() % (Num_Cities - 1);
    // Điểm cắt đầu phải nhỏ hơn điểm cắt cuối
    if (cut1 > cut2) {
        swap(cut1, cut2);
    }
    // Lấy đoạn đường đi từ c1 từ vị trí cut1 đến cut2
    string str = c1.cities.substr(cut1, cut2 - cut1 + 1);
    // Xóa đoạn đường đi trùng lặp trong c2
    for (int i = 0; i < str.size(); i++) {
        int pos = c2.cities.find(str[i]);
        if (pos != string::npos) {
            c2.cities.erase(pos, 1);
        }
    }
    // Gắn đoạn đường đi từ c1 vào vị trí cut1 trong c2
    c2.cities.insert(cut1, str);
    return c2.cities;
}

// Hàm đột biến (mutation)
string mutate(string cities) {
    while (true){
        int idx1 = 1 + rand() % (Num_Cities - 1);
        int idx2 = 1 + rand() % (Num_Cities - 1);
        if(idx1 != idx2){
            int temp = cities[idx1];
            cities[idx1] = cities[idx2];
            cities[idx2] = temp;
        break;
        }
    }
  return cities;
}

bool less_sort(Chromosome c1, Chromosome c2){
    return c1.fitness < c2.fitness;
}


void TSP_GeneticAlgorithm(){
    // Khởi tạo quần thể
    initPopulation();
    cout << "Initial population: " << endl;
    cout << "Cities    Fitness" << endl;
    for (int i = 0; i < Population_size; i++)
        cout << population[i].cities << "    " << population[i].fitness << endl;
    // Những cá thể tốt nhất trong quần thể qua các thế hệ
    vector<Chromosome> best_eachgen;
    int gen = 0;
    while (++gen <= Num_Generations){
        sort(population.begin(), population.end(), less_sort);
        //Tìm fitness tốt nhất trong thế hệ hiện tại
        int index= 0;
        for (int i = 1; i < Population_size; i++) {
            if (population[i].fitness < population[index].fitness) {
                index = i;
            }
        }
        best_eachgen.push_back(population[index]);
        // Tạo quần thể mới bằng cách lai ghép và đột biến
        vector<Chromosome> newPopulation;
        for (int i = 0; i < Population_size; i++) {
            // Tạo thế hệ con
            Chromosome offspring;
            int parent1Idx = 1 + rand() % (Num_Cities - 1);
            int parent2Idx = 1 + rand() % (Num_Cities - 1);
            offspring.cities = crossover(population[parent1Idx], population[parent2Idx]);
            while (calcFitness(offspring.cities) > population[index].fitness)
                offspring.cities = mutate(offspring.cities);
            newPopulation.push_back(offspring);
        }
        population = newPopulation;
        // Tính toán lại fitness cho mỗi cá thể trong quần thể
        for (int i = 0; i < Population_size; i++) {
            population[i].fitness = calcFitness(population[i].cities);
        }
        cout << endl << "Generation " << gen << endl;
        cout << "Route     Fitness" << endl;
        for (int i = 0; i < Population_size; i++){
            cout << population[i].cities << "    " << population[i].fitness << endl;
        }
    }
    int idx = 0;
    for (int i = 1; i < Population_size; i++) {
        if (population[i].fitness < population[idx].fitness) {
            idx = i;
        }
    }
    best_eachgen.push_back(population[idx]);
    // In ra kết quả các cá thể tốt nhất qua các thế hệ
    cout << endl << "Best solutions found: ";
    for (int i = 0; i < best_eachgen.size() ; i++) {
        cout << endl;
        cout << "Gen " << i <<": ";
        cout << best_eachgen[i].cities << "   " << best_eachgen[i].fitness;
    }
}

int main() {
    // input();
    TSP_GeneticAlgorithm();
    return 0;
}