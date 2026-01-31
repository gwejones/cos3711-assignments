# Assignment 1 - Question 1

## Question
For this question you need to ensure that you design the appropriate classes needed to address
the specification below.
Create a console application to handle vehicle details. Considering the required functionality
that is required and OOP design principles (avoiding anti-patterns and having minimal
redundant code), create and implement the appropriate classes necessary to achieve the
following.

* A vehicle needs to have a model and a year (which should be a reasonable value). There
are basically 2 types of vehicles: passenger vehicles (that can carry a specified number
of passengers) and transport vehicles (that have a set carrying capacity expressed in
kilograms). Vehicles that are created without the necessary details should have default
values.

* Ensure all appropriate getters and setters are included.

* Include a function that can output the details of the vehicle.

* Use Qt’s parent-child facility to implement a list of vehicles.

* Test your solution by creating some passenger and transport vehicles (at least one of
which is created using the default constructor), adding them to the list, and then
outputting the values in the list to the console.

## Build and Run
This project uses CMake and Qt6 (Core).

Build:

```bash
# From assignment_1/q1
cmake -S . -B build
cmake --build build
```

Run the executable:

```bash
./build/q1
```

