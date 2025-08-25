//
// Created by aki on 8/25/2025.
//

#ifndef NEXUS_EVENT_HPP
#define NEXUS_EVENT_HPP
#include <string>
#include <utility>

template <typename T>
class Event
{
public:
    std::string eventName;
    T eventValue;

    explicit Event(std::string  eventName, T eventValue)
        : eventName(std::move(eventName)), eventValue(eventValue) {}

    T getEventValue()
    {
        return eventValue;
    }
};

#endif //NEXUS_EVENT_HPP