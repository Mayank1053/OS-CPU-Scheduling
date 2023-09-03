#include <iostream>
using namespace std;

class BankerAlgo {
public:
    int **need, **allocate, **max, **available, no_p, no_r;

    void input() {
        cout << "Enter the number of processes and resources: ";
        cin >> no_p >> no_r;

        allocate = new int*[no_p];
        max = new int*[no_p];
        need = new int*[no_p];
        available = new int*[1];

        for (int i = 0; i < no_p; i++) {
            allocate[i] = new int[no_r];
            max[i] = new int[no_r];
            need[i] = new int[no_r];
        }
        
        available[0] = new int[no_r];

        cout << "Enter allocation matrix:\n";
        for (int i = 0; i < no_p; i++)
            for (int j = 0; j < no_r; j++)
                cin >> allocate[i][j];

        cout << "Enter max matrix:\n";
        for (int i = 0; i < no_p; i++)
            for (int j = 0; j < no_r; j++)
                cin >> max[i][j];

        cout << "Enter available matrix:\n";
        for (int j = 0; j < no_r; j++)
            cin >> available[0][j];
    }

    int** calc_need() {
        for (int i = 0; i < no_p; i++)
            for (int j = 0; j < no_r; j++)
                need[i][j] = max[i][j] - allocate[i][j];
        return need;
    }

    bool check(int i) {
        for (int j = 0; j < no_r; j++)
            if (available[0][j] < need[i][j])
                return false;

        return true;
    }

    void issafe() {
        input();
        need = new int*[no_p];
        for (int i = 0; i < no_p; i++)
            need[i] = new int[no_r];
        
        calc_need();
        bool *done = new bool[no_p];
        int j = 0;
        while (j < no_p) {
            bool allocate = false;
            for (int i = 0; i < no_p; i++)
                if (!done[i] && check(i)) {
                    for (int k = 0; k < no_r; k++)
                        available[0][k] = available[0][k] - need[i][k] + max[i][k];
                    cout << "Allocated Process " << i << "\n";
                    allocate = done[i] = true;
                    j++;
                }
            if (!allocate) break;
        }
        if (j == no_p)
            cout << "\nSafely executed\n";
        else
            cout << "All processes can't be safely executed\n";
    }
};

int main() {
    BankerAlgo banker;
    banker.issafe();
    return 0;
}
