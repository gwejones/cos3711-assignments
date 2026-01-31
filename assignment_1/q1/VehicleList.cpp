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

QObjectList VehicleList::getVehicles() const
{
    QObjectList list;
    const auto childObjects = children();
    list.reserve(childObjects.size());
    for (QObject *child : childObjects)
    {
        // Filter to only include Vehicle-derived children in the returned list.
        if (dynamic_cast<Vehicle *>(child))
        {
            list.push_back(child);
        }
    }
    return list;
}

void VehicleList::printAll(QTextStream &out) const
{
    const auto list = getVehicles();
    for (QObject *object : list)
    {
        if (auto *vehicle = dynamic_cast<Vehicle *>(object))
        {
            out << *vehicle;
        }
    }
}
