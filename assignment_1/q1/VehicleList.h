#pragma once

#include <QObject>
#include <QVector>

class QTextStream;
class Vehicle;

class VehicleList : public QObject
{
public:
    explicit VehicleList(QObject *parent = nullptr);
    void addVehicle(Vehicle *vehicle);
    QVector<Vehicle *> getVehicles() const;
    void printAll(QTextStream &out) const;
};
