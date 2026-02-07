# Assignment 1 - Question 4

## Question
This question looks at validating user input.
Extend the application developed in question 3 so that only valid input is allowed in the cases
where strings have been used to input data. Remember that such validation should take place
both when data is input and when it is edited.

Note the following:

* An author’s name could be names like “SZ Mbanjwa-Mhlana”. You should assume that
no full stops will be used with author initials, and that no other special characters should
be allowed.

* Assume (for this exercise) that article and journal titles can allow letters of the alphabet
(“Journal”, for example), numbers, and spaces. However, do not allow a word in the
title to contain both alphabetic characters and numbers in the same word – that is, 3D
should not be allowed.

* The page numbers should be of the form “12-15” or “121 - 155”.

## Build and Run
This project uses CMake and Qt6 (Widgets).

Build:

```bash
# From assignment_1/q4
cmake -S . -B build
cmake --build build
```

Run the executable:

```bash
./build/q4
```
