# Assignment 3 - Question 4

## Question
Each time you restart the application, you have to re-enter student details. Serialize the
`StudentList` instance to XML using the DOM approach so that when the application is closed
the list is written to XML automatically; ensure that there are no problems (like odd file
contents) if the student list is empty when the application closes. Below is an example of what
the file should look like.

```xml
<StudentList>
  <student>
    <number>1234</number>
    <modules>
      <module>
        <code>COS3711</code>
        <mark>67</mark>
      </module>
      <module>
        <code>COS1511</code>
        <mark>67</mark>
      </module>
    </modules>
  </student>
  <student>
    <number>4321</number>
    <modules>
      <module>
        <code>COS3711</code>
        <mark>90</mark>
      </module>
    </modules>
  </student>
</StudentList>
```

## Build and Run
This project uses CMake and Qt6 (Widgets).

Build both questions:

```bash
# Build q1 first (GetStudent producer)
# From assignment_3/q1
cmake -S . -B build
cmake --build build

# Build q4
# From assignment_3/q4
cmake -S . -B build
cmake --build build
```

Question 4 starts Question 1 as a separate process. Before running `q4`, ensure the `q1` executable is available in q4's runtime folder.

Run the executable:

```bash
./build/q4
```
