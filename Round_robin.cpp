#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct Process {
    int id;
    int burstTime;
    int arrivalTime;
};

int main() {
    int n, quantum;
    cout << "Enter the number of processes: ";
    cin >> n;
    
    vector<Process> processes(n);
    vector<int> remainingTime(n);
    
    cout << "Enter burst time and arrival time for each process:\n";
    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        cout << "Process " << i + 1 << " (BT AT): ";
        cin >> processes[i].burstTime >> processes[i].arrivalTime;
        remainingTime[i] = processes[i].burstTime;
    }
    
    cout << "Enter time quantum: ";
    cin >> quantum;
    
    int currentTime = 0;
    queue<int> readyQueue;
    vector<int> completionTime(n, -1);
    
    while (true) {
        bool allCompleted = true;
        
        for (int i = 0; i < n; i++) {
            if (processes[i].arrivalTime <= currentTime && remainingTime[i] > 0) {
                allCompleted = false;
                
                if (remainingTime[i] > quantum) {
                    currentTime += quantum;
                    remainingTime[i] -= quantum;
                } else {
                    currentTime += remainingTime[i];
                    remainingTime[i] = 0;
                    completionTime[i] = currentTime;
                }
                
                readyQueue.push(i);
            }
        }
        
        if (allCompleted)
            break;
    }
    
    double totalWaitingTime = 0;
    double totalTurnaroundTime = 0;
    
    cout << "\nProcess\tBurst Time\tArrival Time\tCompletion Time\tWaiting Time\tTurnaround Time\n";
    
    for (int i = 0; i < n; i++) {
        int turnaroundTime = completionTime[i] - processes[i].arrivalTime;
        int waitingTime = turnaroundTime - processes[i].burstTime;
        
        totalWaitingTime += waitingTime;
        totalTurnaroundTime += turnaroundTime;
        
        cout << processes[i].id << "\t\t" << processes[i].burstTime << "\t\t" << processes[i].arrivalTime << "\t\t" << completionTime[i] << "\t\t" << waitingTime << "\t\t" << turnaroundTime << endl;
    }
    
    double averageWaitingTime = totalWaitingTime / n;
    double averageTurnaroundTime = totalTurnaroundTime / n;
    
    cout << "\nAverage Waiting Time: " << averageWaitingTime << endl;
    cout << "Average Turnaround Time: " << averageTurnaroundTime << endl;
    
    return 0;
}
