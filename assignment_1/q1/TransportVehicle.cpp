#include "TransportVehicle.h"
#include <QTextStream>

TransportVehicle::TransportVehicle(QString model, int year, int capacityKg, QObject *parent)
    : Vehicle(model, year, parent)
{
    setCapacityKg(capacityKg);
}

int TransportVehicle::getCapacityKg() const
{
    return m_capacityKg;
}

void TransportVehicle::setCapacityKg(int capacityKg)
{
    m_capacityKg = capacityKg > 0 ? capacityKg : defaultCapacityKg();
}

void TransportVehicle::print(QTextStream &out) const
{
    out << "Transport Vehicle | Model: " << getModel()
        << " | Year: " << getYear()
        << " | Capacity: " << getCapacityKg() << " kg\n";
}

int TransportVehicle::defaultCapacityKg()
{
    return 1000;
}
