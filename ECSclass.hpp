#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>


class Component;
class Entity;

using ComponentID = std::size_t;

inline ComponentID getComponentID() {
    static ComponentID lastID = 0;
    return lastID++;
}

template <typename T> inline ComponentID() noexcept {
    static ComponentID typeID = getComponentID();
    return typeID;
}

constexpr std::size_t maxComponents = 32;