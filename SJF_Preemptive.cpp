#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<int> pid(n);
    vector<int> at(n);
    vector<int> bt(n);
    vector<int> ct(n);
    vector<int> tat(n);
    vector<int> wt(n);
    vector<int> f(n, 0);
    vector<int> k(n);

    int i, st = 0, total = 0;
    float avgwt = 0, avgtat = 0;

    for (i = 0; i < n; i++) {
        pid[i] = i + 1;
        cout << "Enter AT of process P" << (i + 1) << ": ";
        cin >> at[i];
        cout << "Enter BT of process P" << (i + 1) << ": ";
        cin >> bt[i];
        k[i] = bt[i];
        f[i] = 0;
    }

    while (true) {
        int min = INT_MAX, c = n;
        bool allCompleted = true;

        for (i = 0; i < n; i++) {
            if (at[i] <= st && f[i] == 0 && bt[i] < min) {
                min = bt[i];
                c = i;
            }
            if (f[i] == 0) {
                allCompleted = false;
            }
        }

        if (allCompleted) {
            break;
        }

        if (c == n) {
            st++;
        } else {
            bt[c]--;
            st++;
            if (bt[c] == 0) {
                ct[c] = st;
                f[c] = 1;
                tat[c] = ct[c] - at[c];
            }
        }
    }

    for (i = 0; i < n; i++) {
        wt[i] = tat[i] - k[i];
        avgtat += tat[i];
    }

    cout << "PID\tAT\tBT\tCT\tTAT\tWT\n";
    for (i = 0; i < n; i++) {
        cout << pid[i] << "\t" << at[i] << "\t" << k[i] << "\t" << ct[i] << "\t" << tat[i] << "\t" << wt[i] << "\n";
    }

    cout << "Avg. TAT is " << (float)(avgtat / n) << "\n";
    
    return 0;
}
