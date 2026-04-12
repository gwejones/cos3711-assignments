---
title: "COS3711 Assignment 4"
author: "50052578 Jones GWE"
date: "2026-04-12"
---

# Question 1

## 1.1

The partial UML class diagram is shown below.

![1.1 UML Class Diagram](uml/q1_1_rainfall_class_diagram.png)

## 1.2

Yes. The pattern used is the **Strategy** pattern, which is a **behavioural** pattern.

It is behavioural because the key variation is in behaviour (how the graph is drawn), not in object structure or object creation.

## 1.3

The class definition is shown below.

```cpp
class RainRecord : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString data READ getData)

private:
    QString stationCode;
    QDate date;
    int rainfallMm;

    QString getData() const;
};
```

# Question 2

## 2.1

## 2.2.1

## 2.2.2

## 2.3.1

## 2.3.2

## 2.3.3

## 2.4

# Question 3

## 3.1

## 3.2

## 3.3

## 3.4.1

## 3.4.2

## 3.5
