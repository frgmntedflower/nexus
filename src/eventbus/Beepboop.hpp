//
// Created by FrgmntedFlower on 8/25/2025.
//

#pragma once
#ifndef NEXUS_BEEPBOOP_H
#define NEXUS_BEEPBOOP_H
#include <functional>
#include <map>
#include <queue>

#include "Event.hpp"

// TODO: IMPLEMENT WHEN NEEDED
template <typename T>
class BeepBoop {
    std::map<Event<T>, std::function<void()>> eventMap;

public:
    void subscribe(const std::string& event, const std::function<void()>& callback) {
        eventMap[event] = callback;
    }

    void publish(const std::string& event) {

    }

    void unsubscribe(const std::string& event) {

    }

    void registerEvent(const std::string& event)
    {

    }

};

#endif //NEXUS_BEEPBOOP_H