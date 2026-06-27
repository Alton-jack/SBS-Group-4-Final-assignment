#include <iostream>
#include <string>
#include <vector>

using namespace std;

// ==========================================
// Pass Criteria P1 & Merit Criteria M3
// Encapsulation and Information Hiding
// ==========================================
class Goods {
private:
    double weight; // Private attribute to protect cargo data

public:
    string name;
    string type;

    // Constructor to initialize goods
    Goods(string n, string t, double w) {
        name = n;
        type = t;
        setWeight(w); // Use setter for validation
    }

    // Public setter to prevent invalid weight values
    void setWeight(double w) {
        if (w > 0) {
            weight = w;
        } else {
            cout << "Error: Weight must be greater than 0!" << endl;
        }
    }

    // Public getter to retrieve weight safely
    double getWeight() {
        return weight;
    }

    // Operation to display information
    void displayInfo() {
        cout << "Item: " << name << " | Type: " << type << " | Weight: " << weight << " kg" << endl;
    }
};

// ==========================================
// Merit Criteria M2: Basic Algorithm
// Bubble Sort (Time Complexity: O(n^2))
// ==========================================
void bubbleSortDescending(vector<double>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] < arr[j + 1]) {
                // Swap the elements
                double temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// ==========================================
// Merit Criteria M2: Advanced Algorithm
// QuickSort (Time Complexity: O(n log n))
// ==========================================
int partitionDescending(vector<double>& arr, int low, int high) {
    double pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        // Change to > for descending order
        if (arr[j] > pivot) {
            i++;
            double temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    double temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return (i + 1);
}

void quickSortDescending(vector<double>& arr, int low, int high) {
    if (low < high) {
        int pi = partitionDescending(arr, low, high);
        quickSortDescending(arr, low, pi - 1);
        quickSortDescending(arr, pi + 1, high);
    }
}

// Helper function to print arrays
void printArray(const vector<double>& arr) {
    for (double val : arr) {
        cout << val << " ";
    }
    cout << endl;
}

// ==========================================
// Main Execution File
// ==========================================
int main() {
    cout << "--- GOODS ADT IMPLEMENTATION ---" << endl;
    Goods g1("Vaccine Cooler", "Medical", 12.5);
    g1.displayInfo();
    
    cout << "Updating weight..." << endl;
    g1.setWeight(3.0);
    g1.displayInfo();
    cout << "\n--------------------------------\n" << endl;

    // TODO: Change this array for Member 1, Member 2, and Member 3
    vector<double> cargoWeights ={115, 50, 82, 195, 28, 140, 94, 61, 175, 70, 85, 125} ;
    
    vector<double> weightsForBubble = cargoWeights;
    vector<double> weightsForQuick = cargoWeights;

    cout << "--- SORTING CARGO WEIGHTS ---" << endl;
    cout << "Original Weights: ";
    printArray(cargoWeights);

    cout << "\nBubble Sort (Descending):" << endl;
    bubbleSortDescending(weightsForBubble);
    printArray(weightsForBubble);

    cout << "\nQuickSort (Descending):" << endl;
    quickSortDescending(weightsForQuick, 0, weightsForQuick.size() - 1);
    printArray(weightsForQuick);

    return 0;
}