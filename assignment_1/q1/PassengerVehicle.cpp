#include "PassengerVehicle.h"
#include <QTextStream>

PassengerVehicle::PassengerVehicle(QString model, int year, int passengers, QObject *parent)
    : Vehicle(model, year, parent)
{
    setPassengers(passengers);
}

int PassengerVehicle::getPassengers() const
{
    return m_passengers;
}

void PassengerVehicle::setPassengers(int passengers)
{
    m_passengers = passengers > 0 ? passengers : defaultPassengers();
}

void PassengerVehicle::print(QTextStream &out) const
{
    out << "Passenger Vehicle | Model: " << getModel()
        << " | Year: " << getYear()
        << " | Passengers: " << getPassengers() << Qt::endl;
}

int PassengerVehicle::defaultPassengers()
{
    return 4;
}
