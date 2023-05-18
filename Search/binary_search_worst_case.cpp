#include<iostream>
#include<fstream>
#include<chrono>
#include<cmath>
using namespace std;

int binary_search(int *numbers, int N, int a){
    int i_lower=0, i_upper=N-1, i_mid;
    while (i_lower != i_upper){
        i_mid = (i_lower+i_upper)/2;
        if (numbers[i_mid] >= a) i_upper = i_mid;
        else i_lower = i_mid+1;
    }
    if (numbers[i_lower] == a) return i_lower;
    else return -1;
}

int main(){
    ofstream file("data/binary_search_worst_case.txt");
    unsigned T = 100000000;
    int *numbers = new int[1000000];
    for (int i=0; i!=1000000; i++){
        numbers[i] = i;
    }
    auto t0 = std::chrono::steady_clock::now();
    for (unsigned i=0; i!=100; i++){
        unsigned N = round(pow(10, 2 + 0.04*i));
        auto begin = std::chrono::steady_clock::now();
        for (int i=0; i!=T; i++){
            binary_search(numbers, N, -1);
        }
        auto end = std::chrono::steady_clock::now();
        auto t = std::chrono::duration_cast<std::chrono::milliseconds>(end - t0);
        float percentage = (i+1)*(1+i/50.0)/303.0;
        int time_left = round((t.count()*(1/percentage - 1))/1000);
        cout<<"\r"<<round(percentage*10000.0)/100.0<<"% completed. Time left "<<time_left/3600<<"h "<<(time_left/60)%60<<"m "<<time_left%60<<"s"<<flush;
        auto time_span = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
        file<<N<<','<<time_span.count()<<endl;
    }
    delete[] numbers;
    return 0;
}

