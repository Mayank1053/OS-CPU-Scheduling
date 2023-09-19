#include <iostream>
#include <algorithm>
#include <string>
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
            cout << "Enter BT and AT for process " << pId[i] << ": ";
            cin >> bt[i] >> at[i];
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
        cout << "    " << "pId" << "   " << "BT" << "   " << "AT" << "   " << "CT" << "    " << "WT" << "    " << "TAT" << endl;

        for (int i = 0; i < noOfProcess; i++) {
            cout << "    " << pId[i] << "    " << bt[i] << "    " << at[i] << "    " << ct[i] << "    " << wt[i] << "    " << tat[i] << endl;
        }

        cout << "   " << "Average WT:" << " " << avgWT << "    " << "Average TAT:" << " " << avgTAT << endl;
    }
};

int main() {
    FCFS obj;
    obj.Data();
    obj.fcfs();
    return 0;
}
