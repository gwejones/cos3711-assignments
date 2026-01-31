#include <QCoreApplication>
#include <QTextStream>
#include "PassengerVehicle.h"
#include "TransportVehicle.h"
#include "VehicleList.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    QTextStream out(stdout);

    // Heap-allocate and parent to app so Qt manages lifetime safely.
    auto *list = new VehicleList(&app);
    list->addVehicle(new PassengerVehicle("Corolla", 2018, 5));
    list->addVehicle(new TransportVehicle("Sprinter", 2020, 2200));
    list->addVehicle(new PassengerVehicle());

    out << "Vehicle list:" << Qt::endl;
    list->printAll(out);

    return 0;
}
