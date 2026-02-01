#pragma once

#include <QObject>

class QTextStream;
class Vehicle;

class VehicleList : public QObject
{
    Q_OBJECT

public:
    // Creates an empty list of vehicles with optional parent ownership.
    explicit VehicleList(QObject *parent = nullptr);
    // Adds a vehicle and transfers parent ownership to this list.
    void addVehicle(Vehicle *vehicle);
    // Returns child objects filtered to vehicle instances.
    QObjectList getVehicles() const;
    // Writes all vehicle details to the stream.
    void printAll(QTextStream &out) const;
};
