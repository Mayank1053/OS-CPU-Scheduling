#include <iostream>
#include <algorithm>
#include <string>
#include <iomanip> // Include this for setw
using namespace std;

class FCFS {
private:
    int bt[100];
    int at[100];
    string pId[100];
    int noOfProcess;

public:
    void Data() {
        cout << "Enter number of Processes: ";
        cin >> noOfProcess;
        string st = "P";
        for (int i = 0; i < noOfProcess; i++) {
            pId[i] = st + to_string(i);
            cout << "Enter BT for process " << pId[i] << ": ";
            cin >> bt[i];
            cout << "Enter AT for process " << pId[i] << ": ";
            cin >> at[i];
        }
    }

    void sortProcesses() {
        for (int i = 0; i < noOfProcess; i++) {
            for (int j = 0; j < noOfProcess - i - 1; j++) {
                if (at[j] > at[j + 1]) {
                    swap(at[j], at[j + 1]);
                    swap(bt[j], bt[j + 1]);
                    swap(pId[j], pId[j + 1]);
                }
            }
        }
    }

    void fcfs() {
        int ct[100];
        int wt[100];
        int tat[100];
        sortProcesses();

        ct[0] = at[0] + bt[0];
        tat[0] = ct[0] - at[0];
        wt[0] = tat[0] - bt[0];

        for (int i = 1; i < noOfProcess; i++) {
            ct[i] = bt[i] + max(ct[i - 1], at[i]);
            tat[i] = ct[i] - at[i];
            wt[i] = tat[i] - bt[i];
        }

        float sum = 0;
        for (int i = 0; i < noOfProcess; i++) {
            sum += wt[i];
        }
        float avgWT = sum / noOfProcess;

        sum = 0;
        for (int i = 0; i < noOfProcess; i++) {
            sum += tat[i];
        }
        float avgTAT = sum / noOfProcess;

        cout << "\n";
        cout << setw(20) << "pId" << setw(20) << "BT" << setw(20) << "AT" << setw(20) << "CT" << setw(20) << "WT" << setw(20) << "TAT" << endl;

        for (int i = 0; i < noOfProcess; i++) {
            cout << setw(20) << pId[i] << setw(20) << bt[i] << setw(20) << at[i] << setw(20) << ct[i] << setw(20) << wt[i] << setw(20) << tat[i] << endl;
        }

        cout << setw(10) << "Average" << setw(20) << avgWT << setw(20) << avgTAT << endl;
    }
};

int main() {
    FCFS obj;
    obj.Data();
    obj.fcfs();
    return 0;
}
