#pragma once

#include "Vehicle.h"

class QTextStream;

class PassengerVehicle : public Vehicle
{
    Q_OBJECT
    Q_PROPERTY(int passengers READ getPassengers)

public:
    // Creates a passenger vehicle with optional model/year/passenger count.
    explicit PassengerVehicle(QString model = defaultModel(),
                              int year = defaultYear(),
                              int passengers = defaultPassengers(),
                              QObject *parent = nullptr);

    // Returns the passenger capacity.
    int getPassengers() const;
    // Sets the passenger capacity, applying default if invalid.
    void setPassengers(int passengers);

    // Writes passenger vehicle details to the stream.
    void print(QTextStream &out) const override;

private:
    // Returns the default passenger capacity.
    static int defaultPassengers();

    int m_passengers = defaultPassengers();
};
