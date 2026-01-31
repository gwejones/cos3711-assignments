#include "Vehicle.h"
#include <QDate>
#include <QTextStream>

Vehicle::Vehicle(QString model, int year, QObject *parent)
    : QObject(parent)
{
    setModel(model);
    setYear(year);
}

QString Vehicle::getModel() const
{
    return m_model;
}

int Vehicle::getYear() const
{
    return m_year;
}

void Vehicle::setModel(const QString &model)
{
    const QString trimmed = model.trimmed();
    m_model = trimmed.isEmpty() ? defaultModel() : trimmed;
}

void Vehicle::setYear(int year)
{
    m_year = isYearReasonable(year) ? year : defaultYear();
}

int Vehicle::defaultYear()
{
    return QDate::currentDate().year();
}

QString Vehicle::defaultModel()
{
    return QStringLiteral("Unknown");
}

bool Vehicle::isYearReasonable(int year)
{
    const int currentYear = QDate::currentDate().year();
    return year >= kMinYear && year <= currentYear + 1;
}

void Vehicle::print(QTextStream &out) const
{
    out << "Vehicle | Model: " << getModel()
        << " | Year: " << getYear() << Qt::endl;
}

QTextStream &operator<<(QTextStream &out, const Vehicle &vehicle)
{
    vehicle.print(out);
    return out;
}
