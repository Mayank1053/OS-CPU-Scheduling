#include <iostream>
#include <vector>
using namespace std;

// Define a structure to represent a memory block
struct MemoryBlock {
    int id;
    int size;
    bool allocated;
};

// Function to allocate memory using First Fit strategy
int firstFit(vector<MemoryBlock>& memory, int size) {
    for (int i = 0; i < memory.size(); i++) {
        if (!memory[i].allocated && memory[i].size >= size) {
            memory[i].allocated = true;
            return i;
        }
    }
    return -1; // Memory allocation failed
}

// Function to allocate memory using Best Fit strategy
int bestFit(vector<MemoryBlock>& memory, int size) {
    int bestFitIndex = -1;
    int minFragmentation = INT_MAX;

    for (int i = 0; i < memory.size(); i++) {
        if (!memory[i].allocated && memory[i].size >= size) {
            int fragmentation = memory[i].size - size;
            if (fragmentation < minFragmentation) {
                minFragmentation = fragmentation;
                bestFitIndex = i;
            }
        }
    }

    if (bestFitIndex != -1) {
        memory[bestFitIndex].allocated = true;
        return bestFitIndex;
    } else {
        return -1; // Memory allocation failed
    }
}

// Function to allocate memory using Worst Fit strategy
int worstFit(vector<MemoryBlock>& memory, int size) {
    int worstFitIndex = -1;
    int maxFragmentation = -1;

    for (int i = 0; i < memory.size(); i++) {
        if (!memory[i].allocated && memory[i].size >= size) {
            int fragmentation = memory[i].size - size;
            if (fragmentation > maxFragmentation) {
                maxFragmentation = fragmentation;
                worstFitIndex = i;
            }
        }
    }

    if (worstFitIndex != -1) {
        memory[worstFitIndex].allocated = true;
        return worstFitIndex;
    } else {
        return -1; // Memory allocation failed
    }
}

// Function to deallocate memory
void deallocateMemory(vector<MemoryBlock>& memory, int index) {
    if (index >= 0 && index < memory.size()) {
        memory[index].allocated = false;
    }
}

// Function to display the memory status
void displayMemory(const vector<MemoryBlock>& memory) {
    cout << "Memory Status:" << endl;
    for (const MemoryBlock& block : memory) {
        cout << "Block " << block.id << ": ";
        if (block.allocated) {
            cout << "Allocated (Size: " << block.size << ")" << endl;
        } else {
            cout << "Free (Size: " << block.size << ")" << endl;
        }
    }
    cout << endl;
}

int main() {
    int memorySize, choice;
    cout << "Enter the total memory size: ";
    cin >> memorySize;

    int blockId = 0;
    vector<MemoryBlock> memory;

    // Initialize memory with a single block
    MemoryBlock initialBlock = {blockId++, memorySize, false};
    memory.push_back(initialBlock);

    do {
        cout << "Choose an option:" << endl;
        cout << "1. Allocate Memory (First Fit)" << endl;
        cout << "2. Allocate Memory (Best Fit)" << endl;
        cout << "3. Allocate Memory (Worst Fit)" << endl;
        cout << "4. Deallocate Memory" << endl;
        cout << "5. Display Memory Status" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
            case 2:
            case 3: {
                int size;
                cout << "Enter the size of the memory block to allocate: ";
                cin >> size;

                int allocatedBlockIndex = -1;
                if (choice == 1) {
                    allocatedBlockIndex = firstFit(memory, size);
                } else if (choice == 2) {
                    allocatedBlockIndex = bestFit(memory, size);
                } else {
                    allocatedBlockIndex = worstFit(memory, size);
                }

                if (allocatedBlockIndex != -1) {
                    cout << "Memory allocated successfully in Block " << allocatedBlockIndex << endl;
                } else {
                    cout << "Memory allocation failed. No suitable block available." << endl;
                }
                break;
            }

            case 4: {
                int index;
                cout << "Enter the block index to deallocate: ";
                cin >> index;
                deallocateMemory(memory, index);
                cout << "Memory deallocated from Block " << index << endl;
                break;
            }

            case 5:
                displayMemory(memory);
                break;

            case 6:
                cout << "Exiting the program." << endl;
                break;

            default:
                cout << "Invalid choice. Please enter a valid option." << endl;
        }

    } while (choice != 6);

    return 0;
}
