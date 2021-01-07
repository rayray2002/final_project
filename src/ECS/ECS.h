#ifndef _ECS_H
#define _ECS_H
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>
#include "../TextureManager.h"
using namespace std;

class Component;
class Entity;
class Manager;

using ComponentID = std::size_t;
using Group = std::size_t;

inline ComponentID getNewComponentTypeID()
{
    static ComponentID lastID = 0u;
    return lastID++;
}

template <typename T>
inline ComponentID getNewComponentTypeID() noexcept
{
    static ComponentID typeID = getNewComponentTypeID();
    return typeID;
}

constexpr std::size_t maxComponents = 32;
constexpr std::size_t maxGroups = 32;

using ComponentBitSet = std::bitset<maxComponents>;
using GroupBitSet = std::bitset<maxGroups>;

using ComponentArray = std::array<Component *, maxComponents>;

class Component
{
public:
    Entity *entity;

    virtual void init(){};
    virtual void update(){};
    virtual void draw(){};

    virtual ~Component(){};

private:
};

class Entity
{
private:
    Manager &manager;
    bool active = true;
    vector<unique_ptr<Component>> components;

    ComponentArray componentArray;
    ComponentBitSet componentBitSet;
    GroupBitSet groupBitSet;

public:
    Entity(Manager &mManager) : manager(mManager) {}
    void update()
    {
        for (auto &c : components)
        {
            c->update();
        }
    }

    void draw() {}

    bool isActive() const
    {
        return active;
    }

    void destroy()
    {
        active = false;
    }

    bool hasGroup(Group mGroup)
    {
        return groupBitSet[mGroup];
    }

    void addGroup(Group mGroup);

    void delGroup(Group mGroup)
    {
        groupBitSet[mGroup] = false;
    }

    template <typename T>
    bool hasComponent() const
    {
        return componentBitSet[getNewComponentTypeID<T>()];
    }

    template <typename T, typename... TArgs>
    T &addComponent(TArgs &&... mArgs)
    {
        T *c(new T(forward<TArgs>(mArgs)...));
        c->entity = this;
        unique_ptr<Component> uPtr{c};
        components.emplace_back(move(uPtr));

        componentArray[getNewComponentTypeID<T>()] = c;
        componentBitSet[getNewComponentTypeID<T>()] = true;

        c->init();
        return *c;
    }

    template <typename T>
    T &getComponent() const
    {
        auto ptr(componentArray[getNewComponentTypeID<T>()]);
        return *static_cast<T *>(ptr);
    }
};

class Manager
{
private:
    vector<unique_ptr<Entity>> entities;
    array<vector<Entity *>, maxGroups> groupedEntities;

public:
    void update()
    {
        for (auto &e : entities)
        {
            e->update();
        }
    }

    void draw()
    {
        for (auto &e : entities)
        {
            e->draw();
        }
    }

    void refresh()
    {
        for (auto i(0U); i < maxGroups; i++)
        {
            auto &v(groupedEntities[i]);
            v.erase(remove_if(begin(v), end(v), [i](Entity *mEntity) {
                        return !mEntity->isActive() || !mEntity->hasGroup(i);
                    }),
                    end(v));
        }
        entities.erase(remove_if(begin(entities), end(entities),
                                 [](const unique_ptr<Entity> &mEntity) {
                                     return !mEntity->isActive();
                                 }),
                       end(entities));
    }

    void AddToGroup(Entity *mEntity, Group mGroup)
    {
        groupedEntities[mGroup].emplace_back(mEntity);
    }

    vector<Entity *> &getGroup(Group mGroup)
    {
        return groupedEntities[mGroup];
    }

    Entity &addEntity()
    {
        Entity *e = new Entity(*this);
        unique_ptr<Entity> uPtr{e};
        entities.emplace_back(move(uPtr));
        return *e;
    }
};

#endif