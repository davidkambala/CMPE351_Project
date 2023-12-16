//
// Created by david on 12/16/2023.
//
#include <iostream>
#include <fstream>
#include <queue>
#include <string>
using namespace std;
struct Process {
    int burst_time;
    int arrival_time;
    int priority;
};
struct Scheduler {
    string scheduling_method;
    bool preemptive_mode;
};


int main(int argc, char* argv[]) {
    int choice;
    cout<<"CPU Scheduler Simulator\n";
    cout<<"1) Scheduling Method (None by Default)"<<endl;
    cout<<"2) Preemptive Mode (Off)"<<endl;
    cout<<"3) Show Result"<<endl;
    cout<<"4) End Program"<<endl;
    cin>>choice;
    while(choice != 4){
        cout<<"CPU Scheduler Simulator\n";
        cout<<"1) Scheduling Method (None by Default)"<<endl;
        cout<<"2) Preemptive Mode (Off)"<<endl;
        cout<<"3) Show Result"<<endl;
        cout<<"4) End Program"<<endl;

    }
    return 0;
}

