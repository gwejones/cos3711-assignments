#pragma once

#include "Vehicle.h"

class QTextStream;

class TransportVehicle : public Vehicle
{
    Q_OBJECT

public:
    // Creates a transport vehcile with optional model/year/capacity.
    explicit TransportVehicle(QString model = defaultModel(),
                              int year = defaultYear(),
                              int capacityKg = defaultCapacityKg(),
                              QObject *parent = nullptr);

    // Returns the load capacity in kilograms.
    int getCapacityKg() const;
    // Sets the load capacity, applying default if invalid.
    void setCapacityKg(int capacityKg);

    // Writes transport vehicle details to the stream.
    void print(QTextStream &out) const override;

private:
    // Returns the default load capacity in kilograms.
    static int defaultCapacityKg();

    int m_capacityKg = defaultCapacityKg();
};
