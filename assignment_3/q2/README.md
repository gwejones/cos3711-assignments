# Assignment 3 - Question 2

## Question
Create a simple GUI application (that you will extend in the next question) that, when a
button is clicked, the program that you created in Question 1 (GetStudent) is started as a
separate process. When the user clicks the add button in this second process, the data should
be displayed on the GUI.

Hints:
- Have a look at the `QProcess` class documentation, specifically at the
  `readyReadStandardOutput()` signal.
- You will need to read this output, and display it in the window.
- Remember to move the executable from Question 1's build folder to Question 2's build folder.

## Build and Run
This project uses CMake and Qt6 (Widgets).

Build:

```bash
# From assignment_3/q2
cmake -S . -B build
cmake --build build
```

Run the executable:

```bash
./build/q2
```
