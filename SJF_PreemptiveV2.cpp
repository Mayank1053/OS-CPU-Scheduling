#include <iostream>
#include <vector>

using namespace std;

struct Process {
    int id;
    int arrival_time;
    int burst_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
    int original_burst_time;
    bool completed;
};

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> processes(n);

    int st = 0;
    float avgWT = 0, avgTAT = 0;

    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        cout << "Enter AT of process P" << processes[i].id << ": ";
        cin >> processes[i].arrival_time;
        cout << "Enter BT of process P" << processes[i].id << ": ";
        cin >> processes[i].burst_time;
        processes[i].original_burst_time = processes[i].burst_time;
        processes[i].completed = false;
    }

    while (true) {
        int minBurstTime = INT_MAX;
        int currentProcess = -1;
        bool allCompleted = true;

        for (int i = 0; i < n; i++) {
            if (!processes[i].completed && processes[i].arrival_time <= st && processes[i].burst_time < minBurstTime) {
                minBurstTime = processes[i].burst_time;
                currentProcess = i;
            }
            if (!processes[i].completed) {
                allCompleted = false;
            }
        }

        if (allCompleted) {
            break;
        }

        if (currentProcess == -1) {
            st++;
        } else {
            processes[currentProcess].burst_time--;
            st++;
            if (processes[currentProcess].burst_time == 0) {
                processes[currentProcess].completion_time = st;
                processes[currentProcess].completed = true;
                processes[currentProcess].turnaround_time = processes[currentProcess].completion_time - processes[currentProcess].arrival_time;
                processes[currentProcess].waiting_time = processes[currentProcess].turnaround_time - processes[currentProcess].original_burst_time;
                avgWT += processes[currentProcess].waiting_time;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        avgTAT += processes[i].turnaround_time;
    }

    cout << "PID\tAT\tBT\tCT\tTAT\tWT\n";
    for (int i = 0; i < n; i++) {
        cout << processes[i].id << "\t" << processes[i].arrival_time << "\t" << processes[i].original_burst_time << "\t"
             << processes[i].completion_time << "\t" << processes[i].turnaround_time << "\t" << processes[i].waiting_time << "\n";
    }

    avgWT /= n;
    avgTAT /= n;

    cout << "Avg. TAT is " << avgTAT << "\n";

    return 0;
}
