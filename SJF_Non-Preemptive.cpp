#include <iostream>
using namespace std;

void sort(int ProccesId[], int brust_time[], int arrival_time[], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - (i + 1); j++) {
            if (arrival_time[j] > arrival_time[j + 1]) {
                int temp = arrival_time[j];
                arrival_time[j] = arrival_time[j + 1];
                arrival_time[j + 1] = temp;

                temp = brust_time[j];
                brust_time[j] = brust_time[j + 1];
                brust_time[j + 1] = temp;

                temp = ProccesId[j];
                ProccesId[j] = ProccesId[j + 1];
                ProccesId[j + 1] = temp;
            }
        }
    }
}

int main() {
    int n;
    cout << "Enter no. of processes: ";
    cin >> n;

    int ProccesId[n], arrival_time[n], brust_time[n], completion_time[n];
    int st = 0, total = 0;
    float avgWT = 0, avgTAT = 0;
    int f[n] = {0};

    for (int i = 0; i < n; i++) {
        cout << "Enter AT of Process P" << (i + 1) << ": ";
        cin >> arrival_time[i];
        cout << "Enter BT of Process P" << (i + 1) << ": ";
        cin >> brust_time[i];
        ProccesId[i] = i + 1;
    }

    sort(ProccesId, brust_time, arrival_time, n);

    while (true) {
        int minBrust_time = n, minVal = 999999;
        if (total == n) break;

        for (int i = 0; i < n; i++) {
            if ((arrival_time[i] <= st) && (f[i] == 0) && (brust_time[i] < minVal)) {
                minVal = brust_time[i];
                minBrust_time = i;
            }
        }

        if (minBrust_time == n) st++;
        else {
            completion_time[minBrust_time] = st + brust_time[minBrust_time];
            st += brust_time[minBrust_time];
            int TAT = completion_time[minBrust_time] - arrival_time[minBrust_time];
            int waiting_time = TAT - brust_time[minBrust_time];
            f[minBrust_time] = 1;
            ProccesId[total] = minBrust_time + 1;
            total++;
            avgWT += waiting_time;
            avgTAT += TAT;
        }
    }

    cout << "\nProccesId\tAT\tBT\tCT\tTAT\tWT" << endl;
    for (int i = 0; i < n; i++) {
        cout << ProccesId[i] << "\t\t" << arrival_time[i] << "\t" << brust_time[i] << "\t" << completion_time[i] << "\t" << (completion_time[i] - arrival_time[i]) << "\t" << (completion_time[i] - arrival_time[i] - brust_time[i]) << endl;
    }

    avgWT /= n;
    avgTAT /= n;

    cout << "\nAvg. WT: " << avgWT << "\nAvg. TAT: " << avgTAT << endl;

    return 0;
}
