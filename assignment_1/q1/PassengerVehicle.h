#pragma once

#include "Vehicle.h"

class QTextStream;

class PassengerVehicle : public Vehicle
{
public:
    explicit PassengerVehicle(QString model = defaultModel(),
                              int year = defaultYear(),
                              int passengers = defaultPassengers(),
                              QObject *parent = nullptr);

    int getPassengers() const;
    void setPassengers(int passengers);

    void print(QTextStream &out) const override;

private:
    static int defaultPassengers();

    int m_passengers = defaultPassengers();
};
