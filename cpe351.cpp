//
// Created by david on 12/16/2023.
//
#include <iostream>
#include <fstream>
#include <queue>
#include <string>
using namespace std;
struct Process {
    int burst_time, arrival_time, priority;
};
struct Scheduler {
    string scheduling_method;
    bool preemptive_mode;
};


int main(int argc, char* argv[]) {
    //THE OUTPUT FILE SHOULD BE HANDLED BEFORE THE MENU IS LOADED
    //I SHOULD HAVE A CHECK FOR -f AND -O
    /*if(argc != 5){
        cout<<"ERROR!!! For the program to function correctly type ./cpe351 -f input.txt -o output.txt"<<endl;
        return 1;
    }*/
    int count = 0, index = 0;
    fstream inputFile;
    inputFile.open("C:\\Users\\david\\CLionProjects\\CMPE35122102897\\input.txt",ios::in);
    if(inputFile.is_open()){
        cout<<"file opened"<<endl;
        string line, numberOfLines;
        while (getline(inputFile, numberOfLines)){
            count++;
        }
        inputFile.clear();
        inputFile.seekg(ios::beg);
        struct Process myProcesses[count];
        while (getline(inputFile, line)){
            cout<<line<<endl;
            cout<<"Process "<< index + 1<<"\n";
            for (int i = 0; i < line.length(); i++) {
                char current_Character = line[i];
                if(i==0){
                    //BURST TIME
                    myProcesses[index].burst_time = stoi(string(1, current_Character));
                    cout<<"burst time: "<<myProcesses[index].burst_time<<endl;
                }
                if(i==2){
                    //ARRIVAL TIME
                    myProcesses[index].arrival_time = stoi(string(1,current_Character));
                    cout<<"arrival time: "<<myProcesses[index].arrival_time<<endl;
                }
                if(i==4){
                    //PRIORITY
                    myProcesses[index].priority = stoi(string(1,current_Character));
                    cout<<"Priority: "<<myProcesses[index].priority<<endl;
                }
            }
            index++;
        }
    }else{
        cout<<"Could not open the file"<<endl;
        return 1;
    }



    int choice_simulator, method_choice, time_quantum;
    cout<<"CPU Scheduler Simulator\n";
    cout<<"1) Set Scheduling Method"<<endl;
    cout<<"2) Set Preemptive Mode"<<endl;
    cout<<"3) Show Result"<<endl;
    cout<<"4) End Program"<<endl;
    cout<<"Option > ";
    cin>>choice_simulator;
    while(choice_simulator != 4){
        //START OF THE SIMULATION
        switch(choice_simulator){
            case 1:
                cout<<"Choose scheduling method, none by default: "<<endl; //current is!!!
                cout<<"1) First Come, First Served Scheduling"<<endl;
                cout<<"2) Shortest-Job-First Scheduling"<<endl;
                cout<<"3) Priority Scheduling"<<endl;
                cout<<"4) Round-Robin Scheduling"<<endl; //case 4 ask time quantum
                cout<<"Option > ";
                cin>>method_choice;
                switch(method_choice){
                    case 1:
                        //FCFS
                        break;
                    case 2:
                        //SJFS
                        break;
                    case 3:
                        //PRIORITY
                        break;
                    case 4:
                        //RR
                        break;
                    default:
                        cout<<"INVALID CHOICE"<<endl;
                        break;
                }
                break;
            case 2:
                //PREEMPTIVE MODE
                break;
            case 3:
                //SHOW RESULT
                break;
            default:
                cout<<"INVALID OPTION"<<endl;
                break;
        }


        cout<<"CPU Scheduler Simulator\n";
        cout<<"1) Set Scheduling Method"<<endl;
        cout<<"2) Set Preemptive Mode"<<endl;
        cout<<"3) Show Result"<<endl;
        cout<<"4) End Program"<<endl;
        cout<<"Option > ";
        cin>>choice_simulator;
    }
    return 0;
}

