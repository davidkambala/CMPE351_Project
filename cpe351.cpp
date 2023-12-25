//
// Created by david on 12/16/2023.
//
#include <iostream>
#include <fstream>
#include <string>
#define QUEUE_SIZE 100
using namespace std;
struct Process {
    int burst_time, arrival_time, priority;
    int wait_time = 0;
    int stop_time;
    int process_no;
};

int total_wait_time = 0, current;
double avg_wait_time;
struct CircularQueue {
    int front;
    int rear;
    int items[QUEUE_SIZE];
};

void initializeQueue(struct CircularQueue *c);
void insert(struct CircularQueue *c, int x);
int remove(struct CircularQueue *c);
int isQueueFull(struct CircularQueue *c);
int isQueueEmpty(struct CircularQueue *c);
void printQueue(struct CircularQueue *c);
void bubbleSort_burstTime(Process myProcesses[], int processesCount);
void bubbleSort_processNo(Process myProcesses[], int processesCount);
void swap(Process& a, Process& b);

void first_come(Process myProcesses[], int totalBurstTime, int processesCount);
void round_Robin (Process myProcesses[], int processesCount, int time_quantum);
void shortest_job_first_nonPreemptive(Process myProcesses[], int processesCount);

int main(int argc, char* argv[]) {
    //THE OUTPUT FILE SHOULD BE HANDLED BEFORE THE MENU IS LOADED
    //I SHOULD HAVE A CHECK FOR -f AND -O
    /*if(argc != 5){
        cout<<"ERROR!!! For the program to function correctly type ./cpe351 -f input.txt -o output.txt"<<endl;
        return 1;
    }*/
    int index = 0, count, totalBurstTime = 0;
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
        myProcesses[index].process_no = index + 1;
        index++;
    }
    //FIND THE TOTAL TIME THAT WILL USE TO CALCULATE AVERAGE WAITING TIME
    for (int i = 0; i < count; i++) {
        totalBurstTime += myProcesses[i].burst_time;
    }
    cout<<"Total burst time: "<<totalBurstTime<<endl;

    int choice_simulator, method_choice = 2, time_quantum = 2, burst;
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
                    first_come(myProcesses, totalBurstTime, count);
                }
                else if (method_choice == 4){
                    //ROUND ROBIN

                    round_Robin(myProcesses, count, time_quantum);
                }
                else if (!preemptive){
                    //Non Preemptive scheduling
                    if (method_choice == 2){
                        //SJFS
                        cout<<"Scheduling Method: Shortest Job First - Non-Preemptive"<<endl;
                        shortest_job_first_nonPreemptive(myProcesses, count);
                    } else if (method_choice == 3){
                        //PRIORITY
                    }
                } else{
                    //Preemptive Scheduling
                    if (method_choice == 2){
                        //SJFS
                    } else if (method_choice == 3){
                        //PRIORITY
                    }
                }
                for (int i = 0; i < count; i++) {
                    myProcesses[i].wait_time = 0;
                    myProcesses[i].stop_time = 0;
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
    inputFile.close();
    return 0;
}

void initializeQueue(struct CircularQueue *c){
    c->front = c->rear = QUEUE_SIZE-1;
}
void insert(struct CircularQueue *c, int x){
    if (c->rear == QUEUE_SIZE-1)
        c->rear = 0;
    else
        (c->rear)++;
    if (isQueueFull(c)){
        cout<<"Overflow queue is full"<<endl;
        exit(1);
    }
    else
        c->items[c->rear] = x;
}
int remove(struct CircularQueue *c){
    if (isQueueEmpty(c)){
        cout<<"Underflow: Queue is empty"<<endl;
        exit(1);
    }
    else{
        if (c->front == QUEUE_SIZE-1)
            c->front = 0;
        else
            (c->front)++;
        int x = c->items[c->front];
        return x;
    }
}
int isQueueFull(struct CircularQueue *c){
    if (c->front == c->rear)
        return 1;
    else
        return 0;
}
int isQueueEmpty(struct CircularQueue *c){
    if (c->front == c->rear)
        return 1;
    else
        return 0;
}
void printQueue(struct CircularQueue *c){
    int x;
    struct CircularQueue temp;
    initializeQueue(&temp);
    while (!isQueueEmpty(c)){
        x = remove(c);
        cout<<x<<endl;
        insert(&temp, x);
    }
    while (!isQueueEmpty(&temp)){
        x = remove(&temp);
        insert(c, x);
    }
}
void swap(Process& a, Process& b){
    Process temp = a;
    a = b;
    b = temp;
}
void bubbleSort_burstTime(Process myProcesses[], int processesCount){
    //I should make more test on that bubble sort with different values
    for (int i = 0; i < processesCount-1; i++) {
        for (int j = 1; j < processesCount - i - 1; j++) {
            if ((myProcesses[j].burst_time > myProcesses[j+1].burst_time)){
                swap(myProcesses[j], myProcesses[j+1]);
            }
        }
    }
    /*for (int i = 0; i < processesCount; ++i) {
        cout<<myProcesses[i].burst_time;
        cout<<myProcesses[i].arrival_time;
        cout<<myProcesses[i].priority<<endl;
    }*/
}
void bubbleSort_processNo(Process myProcesses[], int processesCount){
    for (int i = 0; i < processesCount-1; i++) {
        for (int j = 0; j < processesCount-i-1; j++) {
            if (myProcesses[j].process_no > myProcesses[j+1].process_no){
                swap(myProcesses[j], myProcesses[j+1]);
            }
        }
    }
}


void first_come(Process myProcesses[], int totalBurstTime, int processesCount){
    current = 0;
    total_wait_time = 0;
    int elapsed_Time = totalBurstTime;
    int sched_queue_burst[processesCount];
    for (int i = 0; i < processesCount; i++)
        sched_queue_burst[i] = myProcesses[i].burst_time;
    while (elapsed_Time != 0){
        if(sched_queue_burst[current] == 0){
            current++;
        }
        for (int i = current+1; i < processesCount; i++) {
            myProcesses[i].wait_time++;
        }
        sched_queue_burst[current]--;
        elapsed_Time--;
    }
    for (int i = 0; i < processesCount; i++)
        myProcesses[i].wait_time -= myProcesses[i].arrival_time;
    for (int i = 0; i < processesCount; i++)
        total_wait_time += myProcesses[i].wait_time;
    avg_wait_time = static_cast<double>(total_wait_time)/processesCount;
    cout<<"Process Waiting Times:"<<endl;
    for (int i = 0; i < processesCount; i++){
        cout<<"P"<<i+1<<": "<<myProcesses[i].wait_time<<" ms"<<endl;
    }
    cout<<"Average Waiting Time: "<<avg_wait_time<<" ms"<<endl;
}

void round_Robin (Process myProcesses[], int processesCount, int time_quantum){
    cout<<"Scheduling Method: Round Robin Scheduling - time_quantum = " + time_quantum<<endl;
    struct CircularQueue processes_Queue;
    initializeQueue(&processes_Queue);
    int currentTime = 0;
    total_wait_time = 0;
    int currentProcessBurstTime;
    int time_executed;
    int flag = 0;
    for (int i = 0; i < processesCount; i++) {
        insert(&processes_Queue, myProcesses[i].burst_time);
    }
    //printQueue(&processes_Queue);
    while (!isQueueEmpty(&processes_Queue)){
        if (flag == processesCount)
            flag = 0;
        currentProcessBurstTime = remove(&processes_Queue);
        if (time_quantum < currentProcessBurstTime)
            time_executed = time_quantum;
        else
            time_executed = currentProcessBurstTime;
        currentProcessBurstTime -= time_executed;
        currentTime += time_executed;
        for (int i = 0; i < processesCount; i++) {
            myProcesses[i].wait_time += time_executed;
        }
        myProcesses[flag].wait_time -= time_executed;
        if (currentProcessBurstTime > 0)
            insert(&processes_Queue, currentProcessBurstTime);
        else
            myProcesses[flag].stop_time = myProcesses[flag].wait_time;
        flag++;
    }
    for (int i = 0; i < processesCount; i++)
        myProcesses[i].wait_time = myProcesses[i].stop_time - myProcesses[i].arrival_time;
    for (int i = 0; i < processesCount; i++)
        total_wait_time += myProcesses[i].wait_time;
    avg_wait_time = static_cast<double>(total_wait_time)/processesCount;
    cout<<"Process Waiting Times:"<<endl;
    for (int i = 0; i < processesCount; i++){
        cout<<"P"<<i+1<<": "<<myProcesses[i].wait_time<<" ms"<<endl;
    }
    cout<<"Average Waiting Time: "<<avg_wait_time<<" ms"<<endl;
}
void shortest_job_first_nonPreemptive(Process myProcesses[], int processesCount){
    /*cout<<"Current order: "<<endl;
    for (int i = 0; i < processesCount; ++i) {
        cout<<"P"<<myProcesses[i].process_no<<" ";
    }*/
    bubbleSort_burstTime(myProcesses, processesCount);
    /*cout<<"Order after Bubble sort: "<<endl;
    for (int i = 0; i < processesCount; ++i) {
        cout<<"P"<<myProcesses[i].process_no<<" ";
    }*/
    int currentTime = 0;
    total_wait_time = 0;
    Process running_Process;
    for (int i = 0; i < processesCount; i++) {
        running_Process = myProcesses[i];
        currentTime += running_Process.burst_time;
        for (int j = 0; j < processesCount; j++) {
            if (i != j)
                myProcesses[j].wait_time += running_Process.burst_time;
        }
        myProcesses[i].stop_time = myProcesses[i].wait_time;
    }
    for (int i = 0; i < processesCount; i++)
        myProcesses[i].wait_time = myProcesses[i].stop_time - myProcesses[i].arrival_time;
    bubbleSort_processNo(myProcesses, processesCount);
    for (int i = 0; i < processesCount; i++)
        total_wait_time += myProcesses[i].wait_time;
    avg_wait_time = static_cast<double>(total_wait_time)/processesCount;
    cout<<"Process Waiting Times:"<<endl;
    for (int i = 0; i < processesCount; i++){
        cout<<"P"<<i+1<<": "<<myProcesses[i].wait_time<<" ms"<<endl;
    }
    cout<<"Average Waiting Time: "<<avg_wait_time<<" ms"<<endl;

}
//tag every process ie: P1 P2 P3...
