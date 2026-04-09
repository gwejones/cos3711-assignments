# Assignment 3 - Question 3

## Question
You will now extend Question 2, saving the information that the user adds in a list of students.
You will firstly need a Student class that stores a student number and an appropriate container
to store a student’s modules and marks.

The Student class should contain the following functions.
- `average()` finds the average of all marks of the modules that the student has done.
- `graduate()` returns true if the student has passed 5 modules, of which at most 2 are 1st year modules and at least 1 is a 3rd year module. These values have been reduced to make testing simpler.
- `setNumber()` sets a student number in the class.
- `getNumber()` access the student number in the class.
- `addModule()` adds a module to the container.
- `getModules()` returns the container to the user.

You must also create a `StudentList` class that keeps a pointer to a list of students implemented
as a list of pointers to `Student` instances. Ensure that there can only one be instance of this list.

You will need to include the following functionality.
- Ability to add a Student to the list.
- Ability to return the whole list.
- Ability to check whether a student number exists, returning its index in the list.
- Ability to get a Student instance based on an index in the list.
- Ability to query the size of the list.

The GUI should continue to allow users to add new students as well as display a student record,
to get the average of a student’s module marks, and to find out if they qualify for graduation.
Note that you should always be checking whether a required student exits before attempting to
display any details of that student. Note also that if a user adds a student, module, and module
mark, that you should check whether that student is already in the student list. If this is a new
student, then the detail can simply be added to the list. If the student already exists, then this
new module should simply be added to the list of modules already completed by that student.
Below is an example of a GUI, and you may use it’s layout as a guideline; it is not a set
requirement.

## Build and Run
This project uses CMake and Qt6 (Widgets).

Build both questions:

```bash
# Build q1 first (GetStudent producer)
# From assignment_3/q1
cmake -S . -B build
cmake --build build

# Build q3
# From assignment_3/q3
cmake -S . -B build
cmake --build build
```

Question 3 starts Question 1 as a separate process. Before running `q3`, ensure the `q1` executable is available in q3's runtime folder.

Run the executable:

```bash
./build/q3
```
