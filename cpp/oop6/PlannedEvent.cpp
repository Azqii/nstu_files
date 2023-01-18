//
// Created by dima on 04.01.23.
//

#include "PlannedEvent.h"


PlannedEvent::PlannedEvent(int year, int month, int day, int hour, int minute, std::string eventName) :
        DateTime(year, month, day, hour, minute) {
    this->eventName = eventName;
}

PlannedEvent::PlannedEvent() {
    this->eventName = "";
}

PlannedEvent::PlannedEvent(const PlannedEvent &other) : DateTime(other) {
    this->eventName = other.eventName;
}

void PlannedEvent::setEventName(std::string value) {
    this->eventName = value;
}

PlannedEvent::operator char *() {
    return this->eventName.data();
}

std::ostream &operator<<(std::ostream &os, const PlannedEvent &plannedEvent) {
    os << plannedEvent.day << "." << plannedEvent.month << "." << plannedEvent.year << " " << plannedEvent.hour << ":"
       << plannedEvent.minute << " " << plannedEvent.eventName;
    return os;
}

std::istream &operator>>(std::istream &is, PlannedEvent &plannedEvent) {
    int year, month, day, hour, minute;
    std::string eventName;
    is >> year >> month >> day >> hour >> minute >> eventName;
    plannedEvent = PlannedEvent(year, month, day, hour, minute, eventName);
    return is;
}

std::fstream &operator<<(std::fstream &os, PlannedEvent &plannedEvent) {
    os << plannedEvent.year << " " << plannedEvent.month << " " << plannedEvent.day << " " << plannedEvent.hour << " "
       << plannedEvent.minute << " " << plannedEvent.eventName;
    return os;
}