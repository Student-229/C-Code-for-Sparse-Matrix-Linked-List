#include <iostream>
#include <limits>
using namespace std;

// Node class for the Linked List
class Node {
public:
    int row, col, value;
    Node* next;

    Node(int r, int c, int val) : row(r), col(c), value(val), next(nullptr) {}
};

// SparseMatrix class
class SparseMatrix {
private:
    Node* head;

public:
    SparseMatrix() : head(nullptr) {}

    // Function to insert a new non-zero element
    void insert(int row, int col, int value) {
        if (value == 0) {
            cout << "Zero values are not stored in a sparse matrix.\n";
            return;
        }
        Node* newNode = new Node(row, col, value);
        if (!head) {
            head = newNode;
        } else {
            Node* temp = head;
            while (temp->next) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }

    // Function to display the sparse matrix in matrix form
    void display(int rows, int cols) {
        Node* temp = head;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (temp && temp->row == i && temp->col == j) {
                    cout << temp->value << " ";
                    temp = temp->next;
                } else {
                    cout << "0 ";
                }
            }
            cout << endl;
        }
    }

    // Function to search for an element at a specific row and column
    int search(int row, int col) {
        Node* temp = head;
        while (temp) {
            if (temp->row == row && temp->col == col) {
                return temp->value;
            }
            temp = temp->next;
        }
        return 0; // Return 0 if element not found
    }

    // Destructor to free memory
    ~SparseMatrix() {
        Node* temp;
        while (head) {
            temp = head;
            head = head->next;
            delete temp;
        }
    }
};

int main() {
    int rows, cols, numElements;
    cout << "Enter the number of rows: ";
    while (!(cin >> rows) || rows <= 0) {
        cout << "Invalid input. Please enter a positive integer for rows: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cout << "Enter the number of columns: ";
    while (!(cin >> cols) || cols <= 0) {
        cout << "Invalid input. Please enter a positive integer for columns: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    SparseMatrix sm;

    cout << "Enter the number of non-zero elements: ";
    while (!(cin >> numElements) || numElements < 0) {
        cout << "Invalid input. Please enter a non-negative integer for the number of non-zero elements: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cout << "Enter the non-zero elements in the format (row column value):\n";
    for (int i = 0; i < numElements; i++) {
        int r, c, val;
        cout << "Element " << i + 1 << ": ";
        cin >> r >> c >> val;

        if (r < 0 || r >= rows || c < 0 || c >= cols) {
            cout << "Invalid row/column index. Please enter valid indices within matrix dimensions.\n";
            i--; // Retry current element
            continue;
        }

        sm.insert(r, c, val);
    }

    cout << "\nThe Sparse Matrix is:\n";
    sm.display(rows, cols);

    // Search functionality
    int searchRow, searchCol;
    cout << "\nEnter the row and column to search for an element: ";
    cin >> searchRow >> searchCol;

    if (searchRow >= 0 && searchRow < rows && searchCol >= 0 && searchCol < cols) {
        int value = sm.search(searchRow, searchCol);
        cout << "Value at (" << searchRow << ", " << searchCol << "): " << value << endl;
    } else {
        cout << "Invalid indices for search. They must be within the matrix dimensions.\n";
    }

    return 0;
}
