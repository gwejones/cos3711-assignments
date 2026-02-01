#include <QCoreApplication>
#include <QTextStream>
#include "FileWriter.h"
#include "PassengerVehicle.h"
#include "TransportVehicle.h"
#include "VehicleList.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    QTextStream out(stdout);

    // Heap-allocate and parent to app so Qt manages lifetime safely.
    VehicleList *list = new VehicleList(&app);
    list->addVehicle(new PassengerVehicle("Corolla", 2018, 5));
    list->addVehicle(new TransportVehicle("Sprinter", 2020, 2200));
    list->addVehicle(new PassengerVehicle());
    out << "Vehicle list:" << Qt::endl;
    list->printAll(out);

    QObjectList objectList = list->getVehicles();
    FileWriter writer(&objectList, QStringLiteral("vehicles.txt"));
    const int recordsWritten = writer.write();
    out << "Records written: " << recordsWritten << Qt::endl;


    return 0;
}
