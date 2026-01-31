#include "VehicleList.h"
#include "Vehicle.h"
#include <QTextStream>

VehicleList::VehicleList(QObject *parent)
    : QObject(parent)
{
}

void VehicleList::addVehicle(Vehicle *vehicle)
{
    if (!vehicle)
    {
        return;
    }
    vehicle->setParent(this);
}

QVector<Vehicle *> VehicleList::getVehicles() const
{
    QVector<Vehicle *> list;
    const auto childObjects = children();
    list.reserve(childObjects.size());
    for (QObject *child : childObjects)
    {
        if (auto *vehicle = dynamic_cast<Vehicle *>(child))
        {
            list.push_back(vehicle);
        }
    }
    return list;
}

void VehicleList::printAll(QTextStream &out) const
{
    const auto list = getVehicles();
    for (Vehicle *vehicle : list)
    {
        out << *vehicle;
    }
}
