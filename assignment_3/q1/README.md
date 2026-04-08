# Assignment 3 - Question 1

## Question
Create a simple GUI that allows the user to enter a student number, module code, and mark.
These should then be output to the console in any format. This will be referred to as the
GetStudent application.

Include input masks and error checking (using regular expressions) so that information will be correctly entered.
- The student number is a 4-digit number.
- The module code is made up of 3 uppercase alphabetic characters, followed by a 1, 2, or 3
(for the year), and then a further 2 digits. The final character could be any character
(alphabetic or digit).
- The mark should be an integer between 0 and 100.

This program will be used in the next question as a separate process used to gather data from
the user.

## Build and Run
This project uses CMake and Qt6 (Widgets).

Build:

```bash
# From assignment_3/q1
cmake -S . -B build
cmake --build build
```

Run the executable:

```bash
./build/q1
```
