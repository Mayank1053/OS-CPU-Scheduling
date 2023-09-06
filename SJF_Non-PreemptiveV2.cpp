#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

struct Process {
    int id, arrival_time, burst_time, completion_time, turnaround_time, waiting_time;
};

bool compareArrivalTime(const Process& a, const Process& b) {
    return a.arrival_time < b.arrival_time;
}

int main() {
    int n;
    cout << "Enter no. of processes: ";
    cin >> n;

    vector<Process> processes(n);

    for (int i = 0; i < n; i++) {
        cout << "Enter AT of Process P" << (i + 1) << ": ";
        cin >> processes[i].arrival_time;
        cout << "Enter BT of Process P" << (i + 1) << ": ";
        cin >> processes[i].burst_time;
        processes[i].id = i + 1;
    }

    sort(processes.begin(), processes.end(), compareArrivalTime);

    int st = 0;
    float avgWT = 0, avgTAT = 0;

    cout << "\nProccesId\tAT\tBT\tCT\tTAT\tWT" << endl;
    for (int i = 0; i < n; i++) {
        if (processes[i].arrival_time > st) {
            st = processes[i].arrival_time;
        }

        processes[i].completion_time = st + processes[i].burst_time;
        processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;
        processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;

        avgWT += processes[i].waiting_time;
        avgTAT += processes[i].turnaround_time;

        cout << processes[i].id << "\t\t" << processes[i].arrival_time << "\t" << processes[i].burst_time << "\t" << processes[i].completion_time << "\t" << processes[i].turnaround_time << "\t" << processes[i].waiting_time << endl;

        st = processes[i].completion_time;
    }

    avgWT /= n;
    avgTAT /= n;

    cout << "\nAvg. WT: " << avgWT << "\nAvg. TAT: " << avgTAT << endl;

    return 0;
}
