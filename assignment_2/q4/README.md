# Assignment 2 - Question 4

## Question
Extend the application in Question 3 using a Memento pattern to enable a backup/restore
facility. Allow the user to keep the state of the application at a user-indicated point, and return
the state of the application to that point (again, when the user chooses), and display the first
shape in the list. You need only allow for a single backup point.

## Build and Run
This project uses CMake and Qt6 (Widgets + Xml).

Build:

```bash
# From assignment_2/q4
cmake -S . -B build
cmake --build build
```

Run the executable:

```bash
./build/q4
```
