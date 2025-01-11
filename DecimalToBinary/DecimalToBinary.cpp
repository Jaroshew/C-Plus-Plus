#include <iostream>
#include <iomanip>
using namespace std;

#define DEFAULT_SIZE 50

// Define the Stack class
class Stack {
private:
    int size;    // Size of the stack
    int top;     // Index for the top element
    int* values; // Pointer to store stack values

public:
    // Constructor to initialize stack size and top index
    Stack(int size) {
        this->size = size;
        values = new int[size]; 
        top = -1;
    }

    // Destructor to deallocate memory
    ~Stack() {
        delete[] values;
    };

    // Push a value onto the stack
    void push(int value) {
        if (!isFull()) { 
            top++;
            values[top] = value;
        } else {
            cout << "Stack is full, cannot push " << value << "." << endl;
        }
    }

    // Pop a value from the stack
    int pop() {
        int temporaryValue = 0;
        if (!isEmpty()) {
            temporaryValue = values[top]; 
            top--;    
            return temporaryValue;       
        } else {
            cout << "Stack is empty, cannot pop." << endl;
            return -1;
        }
    }

    // Check if the stack is full
    bool isFull() const {
        return top >= size - 1; 
    }

    // Check if the stack is empty
    bool isEmpty() const {
        return top == -1; 
    }
};

int main() {
    Stack myStack(DEFAULT_SIZE); // Create a stack of size DEFAULT_SIZE

    int inputValue;
    cout << "Enter a number: ";  
    cin >> inputValue;          
    cout << "\n";

    int originalValue = inputValue; 

    // Special case for zero, as its binary equivalent is simply 0
    if (inputValue == 0) {
        cout << "Binary number: 0" << endl;
        return 0;
    }

    // Output header and start the conversion process
    cout << "Result:\n";
    cout << "x = " << setw(5) << originalValue << "\n";

    // Loop to convert decimal number to binary by dividing by 2
    while (inputValue > 0) {
        int remainder = inputValue % 2;
        myStack.push(remainder);
        inputValue /= 2;          

        cout << "x = " << setw(5) << inputValue << "    ";
        cout << "remainder = " << setw(2) << remainder << "\n";
    }

    // Output the result by popping the binary digits from the stack
    cout << "\nDecimal number " << originalValue << " = ";
    while (!myStack.isEmpty()) { 
        cout << myStack.pop();
    }

    cout << endl;
    return 0;
}