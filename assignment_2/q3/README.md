# Assignment 2 - Question 3

## Question
Using the XML file below, import the shapes contained in it when the application starts up
(using DOM), and display the first one. You should then be able to navigate through the 4
shapes and add new ones to the list.

```xml
<shapeList>
  <shape type="Square" pw="1" pc="Red" fc="Black" p1="110" p2="" />
  <shape type="Circle" pw="2" pc="Green" fc="Blue" p1="75" p2="" />
  <shape type="Ellipse" pw="3" pc="Black" fc="Red" p1="140" p2="55" />
  <shape type="Rectangle" pw="4" pc="Blue" fc="Green" p1="75" p2="120" />
</shapeList>
```

Ensure that all necessary file checks are implemented.

## Build and Run
This project uses CMake and Qt6 (Widgets + Xml).

Build:

```bash
# From assignment_2/q3
cmake -S . -B build
cmake --build build
```

Run the executable:

```bash
./build/q3
```
