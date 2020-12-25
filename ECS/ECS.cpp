#include "ECS.h"

void Entity::addGroup(Group mGroup) 
{
    groupBitSet[mGroup] = true;
    manager.AddToGroup(this, mGroup);
}




// Entity::Entity(Manager& mManager) : manager(mManager) {}
// void Entity::update() 
// {
//     for (auto &c : components) 
//     {
//         c->update();
//     }
//     for (auto &c : components) 
//     {
//         c->draw();
//     }
// } 
// void Entity::draw() {}
// bool Entity::isActive() const 
// {
//     return active;
// }
// void Entity::destroy() 
// {
//     active = false;
// }
// bool Entity::hasGroup(Group mGroup) 
// {
//     return groupBitSet[mGroup];
// }
// void Entity::delGroup(Group mGroup) 
// {
//     groupBitSet[mGroup] = false;
// }
// template <typename T> bool Entity::hasComponent() const 
// {
//     return componentBitSet[getNewComponentTypeID<T>()];
// }
// template <typename T, typename... TArgs>
// T& Entity::addComponent(TArgs&&... mArgs) 
// {
//     T* c(new T(forward<TArgs>(mArgs)...));
//     c->entity = this;
//     unique_ptr<Component> uPtr{ c };
//     components.emplace_back(move(uPtr));
//     componentArray[getNewComponentTypeID<T>()] = c;
//     componentBitSet[getNewComponentTypeID<T>()] = true;
//     c->init();
//     return *c;
// } 
// template<typename T> T& Entity::getComponent() const 
// {
//     auto ptr(componentArray[getNewComponentTypeID<T>()]);
//     return *static_cast<T*>(ptr);
// }
// ntity::Entity(Manager& mManager) : manager(mManager) {}
// oid Entity::update() 
// 
//     for (auto &c : components) 
//     {
//         c->update();
//     }
//     for (auto &c : components) 
//     {
//         c->draw();
//     }
// } 

// bool Entity::isActive() const 
// {
//     return active;
// }

// void Entity::destroy() 
// {
//     active = false;
// }
