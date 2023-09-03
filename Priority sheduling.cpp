#include <iostream>
using namespace std;

int main() {
    int n;
    cout << "Enter no. of processes: ";
    cin >> n;
    
    int pid[n], at[n], bt[n], ct[n], tat[n], wt[n], rt[n], priority[n];
    int currentTime = 0, total = 0;
    float avgWT = 0, avgTAT = 0;

    for (int i = 0; i < n; i++) {
        cout << "Enter arrival time of process P" << (i + 1) << ": ";
        cin >> at[i];
        
        cout << "Enter burst time of process P" << (i + 1) << ": ";
        cin >> bt[i];
        rt[i] = bt[i];

        cout << "Enter priority of process P" << (i + 1) << ": ";
        cin >> priority[i];

        pid[i] = i + 1;
    }

    while (total != n) {
        int maxPriority = INT_MAX;
        int maxP = -1;

        for (int i = 0; i < n; i++) {
            if (at[i] <= currentTime && priority[i] < maxPriority && rt[i] > 0) {
                maxPriority = priority[i];
                maxP = i;
            }
        }

        if (maxP != -1) {
            rt[maxP]--;
            currentTime++;

            if (rt[maxP] == 0) {
                total++;
                ct[maxP] = currentTime;
                tat[maxP] = ct[maxP] - at[maxP];
                wt[maxP] = tat[maxP] - bt[maxP];

                avgTAT += tat[maxP];
                avgWT += wt[maxP];
            }
        } else {
            currentTime++;
        }
    }

    avgTAT /= n;
    avgWT /= n;

    cout << "PID\tAT\tPriority\tBT\tCT\tTAT\tWT" << endl;
    for (int i = 0; i < n; i++) {
        cout << pid[i] << "\t" << at[i] << "\t" << priority[i] << "\t\t" << bt[i] << "\t" <<
                ct[i] << "\t" << tat[i] << "\t" << wt[i] << endl;
    }
    cout << "Average TAT: " << avgTAT << endl;
    cout << "Average WT: " << avgWT << endl;

    return 0;
}
