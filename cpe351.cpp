//
// Created by david kambala on 12/16/2023.
// Student Number : 22102897
//
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
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
string inputFileName;
string outputFileName;
fstream inputFile;
fstream outputFile;
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
void bubbleSort_burstTime(Process myProcesses[], int processesCount, int currentTime, int num);
void bubbleSort_processNo(Process myProcesses[], int processesCount);
void bubbleSort_priority(Process myProcesses[], int processesCount, int currentTime, int num);
void swap(Process& a, Process& b);
int getShortestProcAvailable(Process myProcesses[], int processesCount, int currentTime);
int getHighPriorityIndex(Process myProcesses[], int processesCount, int currentTime);

void first_come(Process myProcesses[], int totalBurstTime, int processesCount);
void round_Robin (Process myProcesses[], int processesCount, int time_quantum);
void shortest_job_first_nonPreemptive(Process myProcesses[], int processesCount);
void shortest_job_first_Preemptive(Process myProcesses[], int processesCount, int totalBurstTime);
void priority_nonPreemptive(Process myProcesses[], int processesCount);
void priority_Preemptive(Process myProcesses[], int processesCount, int totalBurstTime);

int main(int argc, char* argv[]) {
    //THE OUTPUT FILE SHOULD BE HANDLED BEFORE THE MENU IS LOADED
    //I SHOULD HAVE A CHECK FOR -f AND -O
    if(argc != 5){
        cout<<"ERROR!!! For the program to function correctly respect this syntax: type ./cpe351 -f input.txt -o output.txt"<<endl;
        return 1;
    }
    if (strcmp(argv[1], "-f") != 0 || strcmp(argv[3], "-o") != 0){
        cout<<"ERROR!!! You did not use the correct parameters respect this syntax: type ./cpe351 -f input.txt -o output.txt"<<endl;
        return 1;
    }
    inputFileName = argv[2];
    outputFileName = argv[4];
    int index = 0, count = 0, totalBurstTime = 0;
    outputFile.open(outputFileName, ios::out);
    outputFile.close();
    inputFile.open(inputFileName,ios::in);
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
        for (int i = 0; i < line.length(); i++) {
            char current_Character = line[i];
            if(i==0){
                //BURST TIME
                myProcesses[index].burst_time = stoi(string(1, current_Character));
            }
            if(i==2){
                //ARRIVAL TIME
                myProcesses[index].arrival_time = stoi(string(1,current_Character));
            }
            if(i==4){
                //PRIORITY
                myProcesses[index].priority = stoi(string(1,current_Character));
            }
        }
        myProcesses[index].process_no = index + 1;
        index++;
    }
    inputFile.clear();
    inputFile.seekg(ios::beg);
    //FIND THE TOTAL TIME THAT WILL USE TO CALCULATE AVERAGE WAITING TIME
    for (int i = 0; i < count; i++) {
        totalBurstTime += myProcesses[i].burst_time;
    }
    cout<<"Total burst time: "<<totalBurstTime<<endl;

    int choice_simulator, method_choice = 1, time_quantum = 2;
    bool preemptive = true;
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
                        //First Come First Served
                        cout<<"You chose First Come First Served Scheduling Method"<<endl;
                        break;
                    case 2:
                        //Shortest Job First Scheduling
                        cout<<"You chose Shortest Job First Scheduling Method"<<endl;
                        break;
                    case 3:
                        //PRIORITY
                        cout<<"You chose Priority Scheduling Method"<<endl;
                        break;
                    case 4:
                        //Round Robin
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
                //SHOW RESULT
                if(method_choice == 1){
                    //First Come
                    first_come(myProcesses, totalBurstTime, count);
                }
                else if (method_choice == 4){
                    //ROUND ROBIN
                    round_Robin(myProcesses, count, time_quantum);
                }
                else if (!preemptive){
                    //Non Preemptive scheduling
                    if (method_choice == 2){
                        //Shortest Job First Scheduling Non preemptive
                        shortest_job_first_nonPreemptive(myProcesses, count);
                    } else if (method_choice == 3){
                        //PRIORITY Non preemptive
                        priority_nonPreemptive(myProcesses, count);
                    }
                } else{
                    //Preemptive Scheduling
                    if (method_choice == 2){
                        //Shortest Job First Scheduling preemptive
                        shortest_job_first_Preemptive(myProcesses, count, totalBurstTime);
                    } else if (method_choice == 3){
                        //PRIORITY preemptive
                        priority_Preemptive(myProcesses, count, totalBurstTime);
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
void swap(Process& a, Process& b){
    Process temp = a;
    a = b;
    b = temp;
}
void bubbleSort_burstTime(Process myProcesses[], int processesCount, int currentTime, int num){
    for (int i = 0; i < processesCount-1; i++) {
        for (int j = num + 1; j < processesCount - i - 1; j++) {
            if (myProcesses[j+1].arrival_time <= currentTime){
                if ((myProcesses[j].burst_time > myProcesses[j+1].burst_time)){
                    swap(myProcesses[j], myProcesses[j+1]);
                }
            }
        }
    }
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
void bubbleSort_priority(Process myProcesses[], int processesCount, int currentTime, int num){
    for (int i = 0; i < processesCount-1; i++) {
        for (int j = num + 1; j < processesCount-i-1; j++) {
            if ((myProcesses[j].arrival_time <= currentTime) && myProcesses[j+1].arrival_time <= currentTime)
                if (myProcesses[j].priority > myProcesses[j+1].priority){
                    swap(myProcesses[j], myProcesses[j+1]);
                }
        }
    }
}
int getShortestProcAvailable(Process myProcesses[], int processesCount, int currentTime){
    int min = 10000;
    int min_index = -1;
    for (int i = 0; i < processesCount; i++) {
        if ((myProcesses[i].arrival_time <= currentTime) && (myProcesses[i].burst_time > 0)){
            if (myProcesses[i].burst_time < min){
                min_index = i;
                min = myProcesses[i].burst_time;
            }
        }
    }
    if (min_index == -1)
        return min_index;
    return min_index;
}
int getHighPriorityIndex(Process myProcesses[], int processesCount, int currentTime){
    int min = 10000;
    int min_index = -1;
    for (int i = 0; i < processesCount; i++) {
        if ((myProcesses[i].arrival_time <= currentTime) && (myProcesses[i].burst_time > 0)){
            if (myProcesses[i].priority < min){
                min_index = i;
                min = myProcesses[i].priority;
            }
        }
    }
    if (min_index == -1)
        return min_index;
    return min_index;
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
    outputFile.open(outputFileName, ios::app);
    cout<<"Scheduling Method: First Come First Served"<<endl;
    outputFile<<"Scheduling Method: First Come First Served"<<endl;
    cout<<"Process Waiting Times:"<<endl;
    outputFile<<"Process Waiting Times:"<<endl;
    for (int i = 0; i < processesCount; i++){
        cout<<"P"<<i+1<<": "<<myProcesses[i].wait_time<<" ms"<<endl;
        outputFile<<"P"<<i+1<<": "<<myProcesses[i].wait_time<<" ms"<<endl;
    }
    cout<<"Average Waiting Time: "<<avg_wait_time<<" ms"<<endl;
    outputFile<<"Average Waiting Time: "<<avg_wait_time<<" ms"<<endl;
    outputFile.close();
}

void round_Robin (Process myProcesses[], int processesCount, int time_quantum){
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
    outputFile.open(outputFileName, ios::app);
    cout<<"Scheduling Method: Round Robin Scheduling - time_quantum = "<< time_quantum<<endl;
    outputFile<<"Scheduling Method: Round Robin Scheduling - time_quantum = "<< time_quantum<<endl;
    cout<<"Process Waiting Times:"<<endl;
    outputFile<<"Process Waiting Times:"<<endl;
    for (int i = 0; i < processesCount; i++){
        cout<<"P"<<i+1<<": "<<myProcesses[i].wait_time<<" ms"<<endl;
        outputFile<<"P"<<i+1<<": "<<myProcesses[i].wait_time<<" ms"<<endl;
    }
    cout<<"Average Waiting Time: "<<avg_wait_time<<" ms"<<endl;
    outputFile<<"Average Waiting Time: "<<avg_wait_time<<" ms"<<endl;
    outputFile.close();
}
void shortest_job_first_nonPreemptive(Process myProcesses[], int processesCount){
    int currentTime = 0;
    total_wait_time = 0;
    bubbleSort_burstTime(myProcesses, processesCount, currentTime, -1);
    Process running_Process;
    for (int i = 0; i < processesCount; i++) {
        running_Process = myProcesses[i];
        currentTime += running_Process.burst_time;
        for (int j = 0; j < processesCount; j++) {
            if (i != j)
                myProcesses[j].wait_time += running_Process.burst_time;
        }
        myProcesses[i].stop_time = myProcesses[i].wait_time;
        bubbleSort_burstTime(myProcesses, processesCount, currentTime, i);
    }
    for (int i = 0; i < processesCount; i++)
        myProcesses[i].wait_time = myProcesses[i].stop_time - myProcesses[i].arrival_time;
    bubbleSort_processNo(myProcesses, processesCount);
    for (int i = 0; i < processesCount; i++)
        total_wait_time += myProcesses[i].wait_time;
    avg_wait_time = static_cast<double>(total_wait_time)/processesCount;
    outputFile.open(outputFileName, ios::app);
    cout<<"Scheduling Method: Shortest Job First - Non-Preemptive"<<endl;
    outputFile<<"Scheduling Method: Shortest Job First - Non-Preemptive"<<endl;
    cout<<"Process Waiting Times:"<<endl;
    outputFile<<"Process Waiting Times:"<<endl;
    for (int i = 0; i < processesCount; i++){
        cout<<"P"<<i+1<<": "<<myProcesses[i].wait_time<<" ms"<<endl;
        outputFile<<"P"<<i+1<<": "<<myProcesses[i].wait_time<<" ms"<<endl;
    }
    cout<<"Average Waiting Time: "<<avg_wait_time<<" ms"<<endl;
    outputFile<<"Average Waiting Time: "<<avg_wait_time<<" ms"<<endl;
    outputFile.close();

}
void shortest_job_first_Preemptive(Process myProcesses[], int processesCount, int totalBurstTime){
    int currentTime = 0;
    total_wait_time = 0;
    struct Process processesToExecute [processesCount];
    for (int i = 0; i < processesCount; i++) {
        processesToExecute[i].burst_time = myProcesses[i].burst_time;
        processesToExecute[i].arrival_time = myProcesses[i].arrival_time;
        processesToExecute[i].priority = myProcesses[i].priority;
    }
    int index = getShortestProcAvailable(processesToExecute, processesCount, currentTime);
    while (currentTime < totalBurstTime){
        if (index != -1){
            processesToExecute[index].burst_time--;
            if (processesToExecute[index].burst_time == 0){
                processesToExecute[index].stop_time = currentTime;
            }
            for (int i = 0; i < processesCount; i++) {
                if ((i != index) && (processesToExecute[i].arrival_time <= currentTime) && (processesToExecute[i].burst_time > 0)){
                    processesToExecute[i].wait_time++;
                }
            }
        }
        currentTime++;
        index = getShortestProcAvailable(processesToExecute, processesCount, currentTime);
    }
    for (int i = 0; i < processesCount; i++)
        total_wait_time += processesToExecute[i].wait_time;
    avg_wait_time = static_cast<double>(total_wait_time)/processesCount;
    outputFile.open(outputFileName, ios::app);
    cout<<"Scheduling Method: Shortest Job First - Preemptive"<<endl;
    outputFile<<"Scheduling Method: Shortest Job First - Preemptive"<<endl;
    cout<<"Process Waiting Times:"<<endl;
    outputFile<<"Process Waiting Times:"<<endl;
    for (int i = 0; i < processesCount; i++){
        cout<<"P"<<i+1<<": "<<processesToExecute[i].wait_time<<" ms"<<endl;
        outputFile<<"P"<<i+1<<": "<<processesToExecute[i].wait_time<<" ms"<<endl;
    }
    cout<<"Average Waiting Time: "<<avg_wait_time<<" ms"<<endl;
    outputFile<<"Average Waiting Time: "<<avg_wait_time<<" ms"<<endl;
    outputFile.close();
}

void priority_nonPreemptive(Process myProcesses[], int processesCount){
    int currentTime = 0;
    bubbleSort_priority(myProcesses, processesCount, currentTime, -1);
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
        bubbleSort_priority(myProcesses, processesCount, currentTime, i);
    }
    for (int i = 0; i < processesCount; i++)
        myProcesses[i].wait_time = myProcesses[i].stop_time - myProcesses[i].arrival_time;
    bubbleSort_processNo(myProcesses, processesCount);
    for (int i = 0; i < processesCount; i++)
        total_wait_time += myProcesses[i].wait_time;
    avg_wait_time = static_cast<double>(total_wait_time)/processesCount;
    outputFile.open(outputFileName, ios::app);
    cout<<"Scheduling Method: Priority Scheduling - Non-Preemptive"<<endl;
    outputFile<<"Scheduling Method: Priority Scheduling - Non-Preemptive"<<endl;
    cout<<"Process Waiting Times:"<<endl;
    outputFile<<"Process Waiting Times:"<<endl;
    for (int i = 0; i < processesCount; i++){
        cout<<"P"<<i+1<<": "<<myProcesses[i].wait_time<<" ms"<<endl;
        outputFile<<"P"<<i+1<<": "<<myProcesses[i].wait_time<<" ms"<<endl;
    }
    cout<<"Average Waiting Time: "<<avg_wait_time<<" ms"<<endl;
    outputFile<<"Average Waiting Time: "<<avg_wait_time<<" ms"<<endl;
    outputFile.close();
}
void priority_Preemptive(Process myProcesses[], int processesCount, int totalBurstTime){
    int currentTime = 0;
    total_wait_time = 0;
    struct Process processesToExecute [processesCount];
    for (int i = 0; i < processesCount; i++) {
        processesToExecute[i].burst_time = myProcesses[i].burst_time;
        processesToExecute[i].arrival_time = myProcesses[i].arrival_time;
        processesToExecute[i].priority = myProcesses[i].priority;
    }
    int index = getHighPriorityIndex(processesToExecute, processesCount, currentTime);
    while (currentTime < totalBurstTime){
        if (index != -1){
            processesToExecute[index].burst_time--;
            if (processesToExecute[index].burst_time == 0){
                processesToExecute[index].stop_time = currentTime;
            }
            for (int i = 0; i < processesCount; i++) {
                if ((i != index) && (processesToExecute[i].arrival_time <= currentTime) && (processesToExecute[i].burst_time > 0)){
                    processesToExecute[i].wait_time++;
                }
            }
        }
        currentTime++;
        index = getHighPriorityIndex(processesToExecute, processesCount, currentTime);
    }
    for (int i = 0; i < processesCount; i++)
        total_wait_time += processesToExecute[i].wait_time;
    avg_wait_time = static_cast<double>(total_wait_time)/processesCount;
    outputFile.open(outputFileName, ios::app);
    cout<<"Scheduling Method: Priority Scheduling - Preemptive"<<endl;
    outputFile<<"Scheduling Method: Priority Scheduling - Preemptive"<<endl;
    cout<<"Process Waiting Times:"<<endl;
    outputFile<<"Process Waiting Times:"<<endl;
    for (int i = 0; i < processesCount; i++){
        cout<<"P"<<i+1<<": "<<processesToExecute[i].wait_time<<" ms"<<endl;
        outputFile<<"P"<<i+1<<": "<<processesToExecute[i].wait_time<<" ms"<<endl;
    }
    cout<<"Average Waiting Time: "<<avg_wait_time<<" ms"<<endl;
    outputFile<<"Average Waiting Time: "<<avg_wait_time<<" ms"<<endl;
    outputFile.close();
}