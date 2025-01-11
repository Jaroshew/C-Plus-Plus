# Decimal to Binary Conversion using a Stack

This program converts a decimal number into a binary number using a **stack (LIFO - Last In, First Out)** principle.  

## 📌 Features
- Uses a **stack** to store binary digits.
- Implements basic **stack operations**: push, pop, isFull, isEmpty.
- Displays the step-by-step process of conversion.
- Outputs the **binary equivalent** of a given decimal number.

## 🚀 How It Works
1. The user enters a **decimal number**.
2. The program repeatedly **divides the number by 2**, storing the remainders in a stack.
3. The binary number is obtained by **popping elements** from the stack in **reverse order**.