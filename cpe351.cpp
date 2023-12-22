//
// Created by david on 12/16/2023.
//
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
using namespace std;
struct Process {
    int burst_time, arrival_time, priority;
    int wait_time = 0;
};
int count;
int totalBurstTime;
/*struct LinearQueue {
    int front;
    int rear;
    int items[count];
};*/

void FCFS_Scheduler();

int main(int argc, char* argv[]) {
    //THE OUTPUT FILE SHOULD BE HANDLED BEFORE THE MENU IS LOADED
    //I SHOULD HAVE A CHECK FOR -f AND -O
    /*if(argc != 5){
        cout<<"ERROR!!! For the program to function correctly type ./cpe351 -f input.txt -o output.txt"<<endl;
        return 1;
    }*/
    int index = 0;
    fstream inputFile;
    inputFile.open("C:\\Users\\david\\CLionProjects\\CMPE35122102897\\input.txt",ios::in);
    if(inputFile.is_open()){
        cout<<"file opened"<<endl;
        string numberOfLines;
        while (getline(inputFile, numberOfLines)){
            count++;
        }
        inputFile.clear();
        inputFile.seekg(ios::beg);

    }else{
        cout<<"Could not open the file"<<endl;
        return 1;
    }
    string line;
    struct Process myProcesses[count];
    while (getline(inputFile, line)){
//        cout<<line<<endl;
//        cout<<"Process "<< index + 1<<"\n";
        for (int i = 0; i < line.length(); i++) {
            char current_Character = line[i];
            if(i==0){
                //BURST TIME
                myProcesses[index].burst_time = stoi(string(1, current_Character));
//                cout<<"burst time: "<<myProcesses[index].burst_time<<endl;
            }
            if(i==2){
                //ARRIVAL TIME
                myProcesses[index].arrival_time = stoi(string(1,current_Character));
//                cout<<"arrival time: "<<myProcesses[index].arrival_time<<endl;
            }
            if(i==4){
                //PRIORITY
                myProcesses[index].priority = stoi(string(1,current_Character));
//                cout<<"Priority: "<<myProcesses[index].priority<<endl;
            }
        }
        index++;
    }
    //FIND THE TOTAL TIME THAT WILL USE TO CALCULATE AVERAGE WAITING TIME
    for (int i = 0; i < count; i++) {
        totalBurstTime += myProcesses[i].burst_time;
    }
    cout<<"Total burst time: "<<totalBurstTime<<endl;

    int choice_simulator, method_choice = 1, time_quantum, current, burst, total_wait_time = 0;
    double avg_wait_time;
    bool preemptive = false;
    char preemptive_choice;
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
                        cout<<"You chose First Come First Served Scheduling Method"<<endl;
                        break;
                    case 2:
                        //SJFS
                        cout<<"You chose Shortest Job First Scheduling Method"<<endl;
                        break;
                    case 3:
                        //PRIORITY
                        cout<<"You chose Priority Scheduling Method"<<endl;
                        break;
                    case 4:
                        //RR
                        cout<<"You chose Round Robin Method"<<endl;
                        cout<<"Enter the time quantum: ";
                        cin>>time_quantum;
                        break;
                    default:
                        cout<<"INVALID CHOICE"<<endl;
                        break;
                }
                break;
            case 2:
                //PREEMPTIVE MODE
                cout<<"Do you want Preemptive Mode (ANSWER: Y/N) ?"<<endl;
                cin>>preemptive_choice;
                switch (toupper(preemptive_choice)) {
                    case 'Y':
                        preemptive = true;
                        cout<<"Preemptive Mode is ON"<<endl;
                        break;
                    case 'N':
                        preemptive = false;
                        cout<<"Preemptive Mode is OFF"<<endl;
                        break;
                    default:
                        cout<<"Invalid input, try again"<<endl;
                }
                break;
            case 3:
                //SHOW RESULT I should put first come out side of the !preemptive
                if(method_choice == 1){
                    cout<<"Scheduling Method: First Come First Served"<<endl;
                    current = 0;
                    int elapsed_Time = totalBurstTime;
                    int sched_queue_burst[count];
                    for (int i = 0; i < count; i++)
                        sched_queue_burst[i] = myProcesses[i].burst_time;
                    while (elapsed_Time != 0){
                        if(sched_queue_burst[current] == 0){
                            current++;
                        }
                        for (int i = current+1; i < count; i++) {
                            myProcesses[i].wait_time++;
                        }
                        sched_queue_burst[current]--;
                        elapsed_Time--;
                    }
                    for (int i = 0; i < count; i++)
                        myProcesses[i].wait_time -= myProcesses[i].arrival_time;
                    for (int i = 0; i < count; i++)
                        total_wait_time += myProcesses[i].wait_time;
                    avg_wait_time = total_wait_time/count;
                    cout<<"Process Waiting Times:"<<endl;
                    for (int i = 0; i < count; i++){
                        cout<<"P"<<i+1<<": "<<myProcesses[i].wait_time<<" ms"<<endl;
                    }
                    cout<<"Average Waiting Time: "<<avg_wait_time<<" ms"<<endl;
                }
                else if (!preemptive){
                    //Non Preemptive scheduling
                    if (method_choice == 2){
                        //SJFS
                    } else if (method_choice == 3){
                        //PRIORITY
                    } else if (method_choice == 4){
                        //ROUND ROBIN
                    }
                } else{
                    //Preemptive Scheduling
                    if (method_choice == 2){
                        //SJFS
                    } else if (method_choice == 3){
                        //PRIORITY
                    } else if (method_choice == 4){
                        //ROUND ROBIN
                    }
                }
                break;
            default:
                cout<<"INVALID OPTION"<<endl;
                break;
        }


        cout<<"\n\n\nCPU Scheduler Simulator\n";
        cout<<"1) Set Scheduling Method"<<endl;
        cout<<"2) Set Preemptive Mode"<<endl;
        cout<<"3) Show Result"<<endl;
        cout<<"4) End Program"<<endl;
        cout<<"Option > ";
        cin>>choice_simulator;
    }
    return 0;
}

void FCFS_Scheduler(){
    
}