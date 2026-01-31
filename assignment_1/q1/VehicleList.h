#pragma once

#include <QObject>

class QTextStream;
class Vehicle;

class VehicleList : public QObject
{
public:
    explicit VehicleList(QObject *parent = nullptr);
    void addVehicle(Vehicle *vehicle);
    QObjectList getVehicles() const;
    void printAll(QTextStream &out) const;
};
