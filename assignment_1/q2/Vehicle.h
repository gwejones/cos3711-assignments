#pragma once

#include <QObject>
#include <QString>

class QTextStream;

class Vehicle : public QObject
{
    Q_OBJECT

public:
    static constexpr int kMinYear = 1886; // First car created in this year.

    // Creates a vehicle with optional model/year and parent ownership.
    explicit Vehicle(QString model = defaultModel(),
                     int year = defaultYear(),
                     QObject *parent = nullptr);

    // Returns the vehicle model name.
    QString getModel() const;
    // Returns the vehicle model year.
    int getYear() const;

    // Sets the model name, applying default if empty.
    void setModel(const QString &model);
    // Sets the model year, applying default if out of range.
    void setYear(int year);

    // Writes a textual description of the vehicle to the output stream.
    virtual void print(QTextStream &out) const;

    // Streams vehicle details using the virtual print() implementation.
    friend QTextStream &operator<<(QTextStream &out, const Vehicle &vehicle);

protected:
    // Returns the default year for new vehicles.
    static int defaultYear();
    // Returns the default model name for new vehicles.
    static QString defaultModel();
    // Validates a year against reasonble bounds.
    static bool isYearReasonable(int year);

private:
    QString m_model;
    int m_year = defaultYear();
};
