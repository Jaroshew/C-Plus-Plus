#include <iostream>
#include <iomanip>
using namespace std;

#define DEFAULT_SIZE 50

class Stack {
private:
    int size;
    int top;
    int* values;

public:
    Stack(int size) {
        this->size = size;
        values = new int[size];
        top = -1;
    }

    ~Stack() {
        delete[] values;
    };

    void push(int value) {
        if (!isFull()) {
            top++;
            values[top] = value;
        } else {
            cout << "Stack is full, cannot push " << value << "." << endl;
        }
    }

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

    bool isFull() const {
        return top >= size - 1;
    }

    bool isEmpty() const {
        return top == -1;
    }
};

int main() {
    Stack myStack(DEFAULT_SIZE);

    int inputValue;
    cout << "Enter a number: ";
    cin >> inputValue;
    cout << "\n";

    int originalValue = inputValue;

    if (inputValue == 0) {
        cout << "Binary number: 0" << endl;
        return 0;
    }

    cout << "Result:\n";
    cout << "x = " << setw(5) << originalValue << "\n";
    while (inputValue > 0) {
        int remainder = inputValue % 2;
        myStack.push(remainder);
        inputValue /= 2;

        cout << "x = " << setw(5) << inputValue << "    ";
        cout << "remainder = " << setw(2) << remainder << "\n";
    }

    cout << "\nDecimal number " << originalValue << " = ";
    while (!myStack.isEmpty()) {
        cout << myStack.pop();
    }

    cout << endl;
    return 0;
};