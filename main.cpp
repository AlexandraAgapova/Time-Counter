#include <iostream>

using namespace std;
class Time {
    int hours, minutes, seconds;
    static int objectCount;

public:
    // Конструктор по умолчанию
    Time() : hours(0), minutes(0), seconds(0) {
        ++objectCount; // Увеличиваем счётчик при создании объекта
        cout << "Default constructor called. Current object count: " << objectCount << endl;
    }

    // Конструктор с параметрами
    Time(int h, int m, int s) : hours(h), minutes(m), seconds(s) {
        Normalize();
        ++objectCount; // Увеличиваем счётчик при создании объекта
        cout << "Parameterized constructor called. Current object count: " << objectCount << endl;
    }

    // Конструктор копирования
    Time(const Time& other) : hours(other.hours), minutes(other.minutes), seconds(other.seconds) {
        ++objectCount; // Увеличиваем счётчик при создании объекта
        cout << "Copy constructor called. Current object count: " << objectCount << endl;
    }

    Time& operator += (int s) {
        seconds += s;
        Normalize();
        return *this;
    }

    // Деструктор
    ~Time() {
        --objectCount; // Уменьшаем счётчик при уничтожении объекта
        cout << "Destructor called. Current object count: " << objectCount << endl;
    }

    void Normalize() {
        if (seconds < 0) {
            int minute_decrement = (-seconds + 59) / 60;
            minutes -= minute_decrement;
            seconds += minute_decrement * 60;
        } else if (seconds >= 60) {
            minutes += seconds / 60;
            seconds %= 60;
        }

        if (minutes < 0) {
            int hour_decrement = (-minutes + 59) / 60;
            hours -= hour_decrement;
            minutes += hour_decrement * 60;
        } else if (minutes >= 60) {
            hours += minutes / 60;
            minutes %= 60;
        }

        if (hours < 0) {
            hours = 0;
            minutes = 0;
            seconds = 0;
        } else if (hours > 23) {
            hours = 23;
            minutes = 59;
            seconds = 59;
        }
    }

    static int getObjectCount() {
        return objectCount; // Возвращаем текущее значение счётчика объектов
    }

    int GetHours() const { return hours; }
    int GetMinutes() const { return minutes; }
    int GetSeconds() const { return seconds; }
};

int Time::objectCount = 0;

int main() {
    Time t1(1, 30, 45);
    Time t2(2, 45, 30);
    Time t3 = t2; // Используем конструктор копирования

    cout << "Current object count: " << Time::getObjectCount() << endl;

    {
        Time t4(5, 15, 25);
        cout << "Object count inside block: " << Time::getObjectCount() << endl;
    } // t4 уничтожается здесь

    cout << "Object count after block: " << Time::getObjectCount() << endl;

    return 0;
}
