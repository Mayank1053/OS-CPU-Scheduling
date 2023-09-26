#include <iostream>
#include <algorithm> // Include the algorithm library for sorting
using namespace std;

struct Process {
    int pid, at, bt, ct, tat, wt, rt, priority;
};

bool compareArrivalTime(const Process &a, const Process &b) {
    return a.at < b.at; // Compare processes based on arrival time
}

int main() {
    int n;
    cout << "Enter no. of processes: ";
    cin >> n;
    
    Process processes[n];
    int currentTime = 0, total = 0;
    float avgWT = 0, avgTAT = 0;

    for (int i = 0; i < n; i++) {
        cout << "Enter AT, BT, and Priority of process P" << (i + 1);
        cin >> processes[i].at >> processes[i].bt >> processes[i].priority;
        processes[i].rt = processes[i].bt;
        processes[i].pid = i + 1;
    }

    // Sort processes based on arrival time
    sort(processes, processes + n, compareArrivalTime);

    while (total != n) {
        int maxPriority = INT_MAX;
        int maxP = -1;

        for (int i = 0; i < n; i++) {
            if (processes[i].at <= currentTime && processes[i].priority < maxPriority && processes[i].rt > 0) {
                maxPriority = processes[i].priority;
                maxP = i;
            }
        }

        if (maxP != -1) {
            processes[maxP].rt--;
            currentTime++;

            if (processes[maxP].rt == 0) {
                total++;
                processes[maxP].ct = currentTime;
                processes[maxP].tat = processes[maxP].ct - processes[maxP].at;
                processes[maxP].wt = processes[maxP].tat - processes[maxP].bt;

                avgTAT += processes[maxP].tat;
                avgWT += processes[maxP].wt;
            }
        } else {
            currentTime++;
        }
    }

    avgTAT /= n;
    avgWT /= n;

    cout << "PID\tAT\tPriority\tBT\tCT\tTAT\tWT" << endl;
    for (int i = 0; i < n; i++) {
        cout << processes[i].pid << "\t" << processes[i].at << "\t" << processes[i].priority << "\t\t" << processes[i].bt << "\t" <<
                processes[i].ct << "\t" << processes[i].tat << "\t" << processes[i].wt << endl;
    }
    cout << "Average TAT: " << avgTAT << endl;
    cout << "Average WT: " << avgWT << endl;

    return 0;
}
