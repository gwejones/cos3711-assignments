#pragma once

#include <QObject>
#include <QString>

class QTextStream;

class Vehicle : public QObject
{
public:
    static constexpr int kMinYear = 1886;

    explicit Vehicle(QString model = defaultModel(),
                     int year = defaultYear(),
                     QObject *parent = nullptr);

    QString getModel() const;
    int getYear() const;

    void setModel(const QString &model);
    void setYear(int year);

    virtual void print(QTextStream &out) const;

    friend QTextStream &operator<<(QTextStream &out, const Vehicle &vehicle);

protected:
    static int defaultYear();
    static QString defaultModel();
    static bool isYearReasonable(int year);

private:
    QString m_model;
    int m_year = defaultYear();
};
