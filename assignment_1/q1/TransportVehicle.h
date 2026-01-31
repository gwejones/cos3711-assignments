#pragma once

#include "Vehicle.h"

class QTextStream;

class TransportVehicle : public Vehicle
{
public:
    explicit TransportVehicle(QString model = defaultModel(),
                              int year = defaultYear(),
                              int capacityKg = defaultCapacityKg(),
                              QObject *parent = nullptr);

    int getCapacityKg() const;
    void setCapacityKg(int capacityKg);

    void print(QTextStream &out) const override;

private:
    static int defaultCapacityKg();

    int m_capacityKg = defaultCapacityKg();
};
