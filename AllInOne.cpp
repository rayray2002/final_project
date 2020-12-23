#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <vector>
#define NUMMENU 5
#define WIDTH 1000
#define HEIGHT 1000
using namespace std;


class Component;
class Entity;
class Manager;


class Vector2D {
public:
    double x;
    double y;

    Vector2D();
    Vector2D(double x, double y);

    Vector2D& Substract(const Vector2D& vec);
    Vector2D&  Multiply(const Vector2D& vec);
    Vector2D&    Divide(const Vector2D& vec);
    Vector2D&       Add(const Vector2D& vec);

    friend Vector2D& operator+(Vector2D& v1, const Vector2D& v2);
    friend Vector2D& operator-(Vector2D& v1, const Vector2D& v2);
    friend Vector2D& operator*(Vector2D& v1, const Vector2D& v2);
    friend Vector2D& operator/(Vector2D& v1, const Vector2D& v2);

    Vector2D& operator+=(const Vector2D& vec);
    Vector2D& operator-=(const Vector2D& vec);
    Vector2D& operator*=(const Vector2D& vec);
    Vector2D& operator/=(const Vector2D& vec);

    Vector2D& operator*(const int& i);
    Vector2D& Zero();

    friend ostream& operator<<(ostream& stream, const Vector2D& vec);
};

Vector2D::Vector2D() {
    x = 0.0;
    y = 0.0;
}


Vector2D::Vector2D(double x, double y) {
    this->x = x;
    this->y = y;
}

Vector2D& Vector2D::Add(const Vector2D& vec) {
    this->x += vec.x;
    this->y += vec.y;

    return *this;
}

Vector2D& Vector2D::Substract(const Vector2D& vec) {
    this->x -= vec.x;
    this->y -= vec.y;

    return *this;
}

Vector2D& Vector2D::Divide(const Vector2D& vec) {
    this->x /= vec.x;
    this->y /= vec.y;

    return *this;
}

Vector2D& Vector2D::Multiply(const Vector2D& vec) {
    this->x *= vec.x;
    this->y *= vec.y;

    return *this;
}

Vector2D& operator+(Vector2D& v1, const Vector2D& v2) {
    return v1.Add(v2);
}

Vector2D& operator-(Vector2D& v1, const Vector2D& v2) {
    return v1.Substract(v2);
}

Vector2D& operator*(Vector2D& v1, const Vector2D& v2) {
    return v1.Multiply(v2);
}

Vector2D& operator/(Vector2D& v1, const Vector2D& v2) {
    return v1.Divide(v2);
}

Vector2D& Vector2D::operator+=(const Vector2D& vec) {
    return this->Add(vec);
}

Vector2D& Vector2D::operator-=(const Vector2D& vec) {
    return this->Substract(vec);
}

Vector2D& Vector2D::operator*=(const Vector2D& vec) {
    return this->Multiply(vec);
}

Vector2D& Vector2D::operator/=(const Vector2D& vec) {
    return this->Divide(vec);
}

ostream& operator<<(ostream& stream, const Vector2D& vec) {
    stream << "(" << vec.x << ", " << vec.y << ")";
    return stream;
}

Vector2D& Vector2D::operator*(const int& i) {
    this->x *= i;
    this->y *= i;

    return *this;
}

Vector2D& Vector2D::Zero() {
    this->x = 0;
    this->y = 0;

    return *this;
}
 

using ComponentID = std::size_t;
using Group = std::size_t;


class TextureManager
{
public:
    static SDL_Texture* LoadTexture(const char* filename);
    static void Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest, SDL_RendererFlip flip);
};

SDL_Texture* TextureManager::LoadTexture(const char* texture)
{
    SDL_Surface* tmpSurface = SDL_LoadBMP("./img/miku.bmp");
    // SDL_Surface* tmpSurface = SDL_LoadBMP(texture);

    SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, tmpSurface);
    SDL_FreeSurface(tmpSurface);
    return tex;
}


void TextureManager::Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest, SDL_RendererFlip flip)
{
    SDL_RenderCopyEx(Game::renderer, tex, /*&src,*/NULL, &dest, NULL, NULL, flip);
    cout << "copy" << endl;
    // SDL_Surface* tmpSurface = SDL_LoadBMP("./img/miku.bmp");
    // SDL_Texture* texx = SDL_CreateTextureFromSurface(Game::renderer, tmpSurface);
    // SDL_FreeSurface(tmpSurface);
    // SDL_RenderCopy(Game::renderer, tex, &src, &dest);
    // cout << "(" << dest.w << "," << dest.h << ")" << endl;
}

inline ComponentID getNewComponentTypeID() 
{
    static ComponentID lastID = 0u;
    return lastID++;
}

template <typename T> inline ComponentID getNewComponentTypeID() noexcept 
{
    static ComponentID typeID = getNewComponentTypeID();
    return typeID;
}

constexpr std::size_t maxComponents = 32;
constexpr std::size_t maxGroups = 32;

using ComponentBitSet = std::bitset<maxComponents>;
using GroupBitSet = std::bitset<maxGroups>;

using ComponentArray = std::array<Component*, maxComponents>;


class Component 
{
public:
    Entity* entity;

    virtual void init() {};
    virtual void update() {};
    virtual void draw() {};

    virtual ~Component() {};

private:


};


class Entity 
{
private:
    Manager& manager;
    bool active = true;
    vector<unique_ptr<Component>> components;

    ComponentArray componentArray;
    ComponentBitSet componentBitSet;
    GroupBitSet groupBitSet;
public:
    Entity(Manager& mManager) : manager(mManager) {}
    void update() 
    {
        for (auto &c : components) 
        {
            c->update();
        }
        for (auto &c : components) 
        {
            c->draw();
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


    template <typename T> bool hasComponent() const 
    {
        return componentBitSet[getNewComponentTypeID<T>()];
    }


    template <typename T, typename... TArgs>
    T& addComponent(TArgs&&... mArgs) 
    {
        T* c(new T(forward<TArgs>(mArgs)...));
        c->entity = this;
        unique_ptr<Component> uPtr{ c };
        components.emplace_back(move(uPtr));

        componentArray[getNewComponentTypeID<T>()] = c;
        componentBitSet[getNewComponentTypeID<T>()] = true;

        c->init();
        return *c;
    } 

    template<typename T> T& getComponent() const 
    {
        auto ptr(componentArray[getNewComponentTypeID<T>()]);
        return *static_cast<T*>(ptr);
    }


};

class Manager 
{
private:
    vector<unique_ptr<Entity>> entities;
    array<vector<Entity*>, maxGroups> groupedEntities;

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
            auto& v(groupedEntities[i]);
            v.erase(remove_if(begin(v), end(v), [i](Entity* mEntity) 
            {
                return !mEntity->isActive() || !mEntity->hasGroup(i);
            }), end(v));
        }
        entities.erase( remove_if( begin(entities), end(entities), 
            [](const unique_ptr<Entity> &mEntity) 
            {
            return !mEntity->isActive();
            } ),
            end(entities) );
    }

    void AddToGroup(Entity* mEntity, Group mGroup) 
    {
        groupedEntities[mGroup].emplace_back(mEntity);
    }

    vector<Entity*>& getGroup(Group mGroup) 
    {
        return groupedEntities[mGroup];
    }

    Entity& addEntity() 
    {
        Entity* e = new Entity(*this);
        unique_ptr<Entity> uPtr{ e };
        entities.emplace_back(move(uPtr));
        return *e;
    }
};

struct Animation 
{

    int index;
    int frames;
    int speed;

    Animation() {}
    Animation(int i, int f, int s) 
    {
        index = i;
        frames = f;
        speed = s;
    }
};

class ColliderComponent : public Component 
{
public:
    SDL_Rect collider;
    string tag;

    SDL_Texture* tex;
    SDL_Rect srcR, destR;

    TransformComponent* transform;

    ColliderComponent(string t) 
    {
        tag = t;
    }

    ColliderComponent(string t, int xpos, int ypos, int size)
    {
        tag = t;
        collider.x = xpos;
        collider.y = ypos;
        collider.h = collider.w = size;
    }

    void init() override 
    {
        if (entity->hasComponent<TransformComponent>()) 
        {
            entity->addComponent<TransformComponent>();
        }
        transform = &entity->getComponent<TransformComponent>();

        tex = TextureManager::LoadTexture("./img/miku.bmp");
        srcR.x = 0;
        srcR.y = 0;
        srcR.h = 32;
        srcR.w = 32;
        // destR = { collider.x , collider.y, collider.w, collider.h };
        destR.x = 0;
        destR.y = 0;
        destR.w = 100;
        destR.h = 100;
        // Game::colliders.push_back(this);
    }

    void update() override 
    {

        // if (tag != "miku") 
        // {
        //     collider.x = static_cast<int>(transform->position.x);
        //     collider.y = static_cast<int>(transform->position.y);
        //     collider.w = transform->width * transform->scale;
        //     collider.h = transform->height * transform->scale;
        // }
        // collider.x = static_cast<int>(transform->position.x);
        // collider.y = static_cast<int>(transform->position.y);
        // collider.w = transform->width * transform->scale;
        // collider.h = transform->height * transform->scale;
        collider.x = 0;
        collider.y = 0;
        collider.w = 100;
        collider.h = 100;


        destR.x = collider.x;// - Game::camera.x;
        destR.y = collider.y;// - Game::camera.y;
    }

    void draw() override 
    {
        cout << "draw - collider" << endl;
        TextureManager::Draw(tex, srcR, destR, SDL_FLIP_NONE);
    }
};

void Entity::addGroup(Group mGroup) 
{
    groupBitSet[mGroup] = true;
    manager.AddToGroup(this, mGroup);
}

class KeyBoardController : public Component {
public:
    TransformComponent *transform;
    SpriteComponent *sprite;

    void init() override 
    {
        transform = &entity->getComponent<TransformComponent>();
        sprite = &entity->getComponent<SpriteComponent>();
    }

    void update() override 
    {
        if (Game::event.type == SDL_KEYDOWN) 
        {
            switch (Game::event.key.keysym.sym) 
            {
            case SDLK_w:
                transform->velocity.y = -1;
                sprite->Play("Walk");
                break;
            case SDLK_a:
                transform->velocity.x = -1;
                sprite->Play("Walk");
                sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
                break;
            case SDLK_s:
                transform->velocity.y = 1;
                sprite->Play("Walk");
                break;
            case SDLK_d:
                transform->velocity.x = 1;
                sprite->Play("Walk");
                break;
            default:
                break;
            }
        }

        if (Game::event.type == SDL_KEYUP) 
        {
            switch (Game::event.key.keysym.sym) 
            {
            case SDLK_w:
                transform->velocity.y = 0;
                sprite->Play("Idle");
                break;
            case SDLK_a:
                transform->velocity.x = 0;
                sprite->Play("Idle");
                sprite->spriteFlip = SDL_FLIP_NONE;
                break;
            case SDLK_s:
                transform->velocity.y = 0;
                sprite->Play("Idle");
                break;
            case SDLK_d:
                transform->velocity.x = 0;
                sprite->Play("Idle");
                break;
            case SDLK_ESCAPE:
                Game::isRunning = false;
            default:
                break;
            }
        }
    }
};

class SpriteComponent : public Component 
{
private:
    TransformComponent *transform;
    SDL_Texture *texture;
    SDL_Rect srcRect, destRect;

    bool animated = false;
    int frames = 0;
    int speed = 100;

public:

    int animIndex = 0;

    map<const char*, Animation> animations;

    SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

    SpriteComponent() = default;

    SpriteComponent(const char* path) 
    {
        setTex(path);
    }

    SpriteComponent(const char* path, bool isAnimated) 
    {
        // animated = isAnimated;

        // Animation idle = Animation(0, 3, 20); //0 index 3 picture number 100 frame size
        // Animation walk = Animation(1, 8, 20);

        // animations.emplace("Idle", idle);
        // animations.emplace("Walk", walk);

        // Play("Idle");

        // speed = mSpeed;
        // frames = nFrames;
        setTex(path);
    }

    ~SpriteComponent()
    {
        SDL_DestroyTexture(texture);
    }

    void setTex(const char* path)
    {
        texture = TextureManager::LoadTexture(path);
    }

    void init() override
    {
        transform = &entity->getComponent<TransformComponent>();

        srcRect.x = srcRect.y = 0;
        srcRect.h = transform->width;
        srcRect.w = transform->height;
    }

    void update() override
    {
        if (animated)
        {
            srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / speed) % frames); // put actions in a picture
            //Then if we need animation, we only need to move the camera.
        }

        srcRect.y = animIndex * transform->height;

        // destRect.x = static_cast<int>(transform->position.x) - Game::camera.x;
        // destRect.y = static_cast<int>(transform->position.y) - Game::camera.y;
        // destRect.h = transform->width * transform->scale;
        // destRect.w = transform->height * transform->scale;
        destRect.x = 0;
        destRect.y = 0;
        destRect.h = 100;
        destRect.w = 100;
    }

    void draw() override
    {
        cout << "draw" << endl;
        TextureManager::Draw(texture, srcRect, destRect, spriteFlip);
        //SDL_RenderPresent(Game::renderer);
        

    }

    void Play(const char* animName)
    {
        frames    = animations[animName].frames;
        animIndex =  animations[animName].index;
        speed     =  animations[animName].speed;
    }
};

class TileComponent : public Component
{
public:
    SDL_Texture* texture;
    SDL_Rect srcRect, destRect;
    Vector2D position;
    // TransformComponent* transform;
    // SpriteComponent* sprite;

    // SDL_Rect tileRect;
    // int tileID;
    // char* path;

    TileComponent() = default;

    ~TileComponent()
    {
        SDL_DestroyTexture(texture);
    }

    TileComponent(int srcX, int srcY, int xpos, int ypos, /*int tsize, int tscale, */const char* path) {

        texture = TextureManager::LoadTexture(path);

        position.x = xpos;
        position.y = ypos;

        srcRect.x = srcX;
        srcRect.y = srcY;
        // srcRect.h = srcRect.w = tsize;
        srcRect.h = srcRect.w = 100;

        destRect.x = xpos;
        destRect.y = ypos;
        // destRect.w = destRect.h = tsize * tscale;
        destRect.w = destRect.h = 100;
        // tileRect.x = x;
        // tileRect.y = y;
        // tileRect.h = h;
        // tileRect.w = w;
        // tileID = id;

        // switch (tileID) {
        // case 0:
        //     path = "./img/sample_red.bmp";
        //     break;
        // case 1:
        //     path = "./img/sample_green.bmp";
        //     break;
        // case 2:
        //     path = "./img/sample_yellow.bmp";
        //     break;
        // default:
        //     break;
    }

    void update() override
    {
        destRect.x = position.x;// - Game::camera.x;
        destRect.y = position.y;// - Game::camera.y;
    }

    void draw() override
    {
        cout << "draw" << endl;
        TextureManager::Draw(texture, srcRect, destRect, SDL_FLIP_NONE);
    }
};

class TransformComponent : public Component
{
public:
    Vector2D position;
    Vector2D velocity;

    int height = 32;
    int  width = 32;
    int  scale =  1;
    int  speed =  3;

    TransformComponent()
    {
        // position.Zero();
                position.x = 0;
        position.y = 0;
        height = 100;
        width = 100;
    }

    TransformComponent(int sc)
    {
        // position.x = 400;
        // position.y = 320;
        position.x = 0;
        position.y = 0;

        scale = sc;
    }

    TransformComponent(double x, double y, int h, int w, int sc)
    {
        // position.x = x;
        // position.y = y;
        // height = h;
        // width = h;
        position.x = 0;
        position.y = 0;
        height = 100;
        width = 100;

        scale = sc;
    }

    int x() { return position.x; }
    int y() { return position.y; }

    void init() override
    {
        velocity.Zero();    
    }

    void update() override 
    {
        // position.x += velocity.x * speed;
        // position.y += velocity.y * speed;

    }
};

class ColliderComponent;

class Collision
{
public:
    static bool AABB(const SDL_Rect& recA, const SDL_Rect& recB);
    static bool AABB(const ColliderComponent& colA, ColliderComponent& colB);
};

bool Collision::AABB(const SDL_Rect& recA, const SDL_Rect& recB)
{
    if (recA.x + recA.w >= recB.x
     && recB.x + recB.w >= recA.x
     && recA.y + recA.h >= recB.y
     && recB.y + recB.h >= recA.y)
    {
        return true;
    }
    return false;
}

bool Collision::AABB(const ColliderComponent& colA, ColliderComponent& colB)
{
    if ( AABB(colA.collider, colB.collider) )
    {
        return true;
    }
    else
    {
        return false;
    }
}

class ColliderComponent;

class Game
{
public:
    Game();
    ~Game();

    void handleEveants();
    void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
    void update();
    void render();
    void clean();
    void showmenu();
    void LinkStart(string text, int second, int h, int w);
    void MusicPlay(const char* Music, int volume);
    int FirstMenu();

    bool running() { return isRunning; };

    // static void AddTile(int id, int x, int y);
    // static void AddTile(int srcX, int srcY, int xpos, int ypos);

    static SDL_Renderer* renderer;
    static SDL_Event event;
    // static vector<ColliderComponent*> colliders;
    static bool isRunning;
    static SDL_Rect camera;

    enum groupLabels : std::size_t
    {
        groupMap,
        groupPlayers,
        // groupEnemies,
        groupColliders
    };


private:
    int cnt = 64; //count
    // bool isRunning;
    SDL_Window* window;
    
    
    //Character
    map<int, const char*> Character;
    
    

    //Menu
    int X_MENU_MOUSE, Y_MENU_MOUSE;
    bool MenuisRunning;
    // const char* MenuLabel[NUMMENU] = {"Kirito"};
    stringstream MenuLabel[NUMMENU];
    SDL_Surface* MenuChoice[NUMMENU];
    SDL_Surface* MenuCharacterSurface[NUMMENU];
    SDL_Texture* MenuTex[NUMMENU];
    SDL_Texture* MenuCharacterTex[NUMMENU];
    SDL_Color MenuColor[2] = {{255, 255, 255},
                              {255, 223, 0}  // unselected
                              /*,{  0, 255, 235}*/}; // selected
    SDL_Rect MenuPos[NUMMENU];
    SDL_Rect MenuCharacterPos[NUMMENU];
    TTF_Font* MenuFont;
    

    SDL_Texture *CharacterTextTexture[NUMMENU];
    SDL_Surface *CharacterTextSurface[NUMMENU];
    SDL_Rect CharacterTextRect[NUMMENU];
    TTF_Font *CharacterTextFont;
    //SDL_Color CharacterTextColor = {0, 255, 235};
    SDL_Color CharacterTextColor = {255, 223, 0};
    stringstream CharacterTextText[NUMMENU];


    //Menu

};

class GameObject {


public:
    GameObject(const char* texturesheet, int x, int y);
    ~GameObject();

    void Update();
    void Render();


private:
    
    int xpos;
    int ypos;

    SDL_Texture* objTexture;
    SDL_Rect srcRect, destRect;


};

GameObject::GameObject(const char* texturesheet, int x, int y)
{
    xpos = x;
    ypos = y;
    objTexture = TextureManager::LoadTexture(texturesheet);
}

void GameObject::Update()
{
    srcRect.h = 32;
    srcRect.w = 32;
    srcRect.x = 0;
    srcRect.y = 0;

    destRect.h = xpos;
    destRect.w = ypos;
    destRect.x = srcRect.x * 2;
    destRect.y = srcRect.y * 2;
}


void GameObject::Render()
{
    SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
}
class Map {
public:
    Map(const char* mfp, int ms, int ts);
    ~Map();

    void LoadMap(std::string path, int sizeX, int sizeY);
    void AddTile(int srcX, int srcY, int xpos, int ypos);

    // void DrawMap();

private:
    SDL_Texture* texture;
    SDL_Rect srcRect, destRect;

    const char* mapFilePath;
    // int mapScale;
    // int tileSize;
    // int scaledSize;

    // // SDL_Rect src, dest;
    // // SDL_Texture* dirt;
    // // SDL_Texture* grass;
    // // SDL_Texture* water;


    // // int map[6][13];
};

Map::Map(const char* mfp, int ms, int ts) : mapFilePath(mfp)//, mapScale(ms), tileSize(ts) 
{
    // scaledSize = ms * ts;
    // dirt = TextureManager::LoadTexture("./img/miku.bmp");
    // grass = TextureManager::LoadTexture("./img/miku.bmp");
    // water = TextureManager::LoadTexture("./img/miku.bmp");

    // LoadMap(Lv1);

    // src.x = src.y = 0;
    // src.h = dest.h = 80;
    // src.w = dest.w = 80;

    // dest.x = dest.y = 0;
}

Map::~Map() {
    // SDL_DestroyTexture(grass);
    // SDL_DestroyTexture(dirt);
    // SDL_DestroyTexture(water);
}

void Map::LoadMap(std::string path, int sizeX, int sizeY) {
    texture = TextureManager::LoadTexture("./img/sample_green.bmp");
    srcRect.x = 0;
    srcRect.y = 0;
    srcRect.h = 100;
    srcRect.w = 100;
    destRect.w = 100;
    destRect.h = 100;
    destRect.x = 0;
    destRect.y = 0;
    // char c;
    // fstream mapFile;
    // mapFile.open(path);

    // int srcX, srcY;

    // for (int y = 0; y < sizeY; y++) {
    //     for (int x = 0; x < sizeX; x++) {
    //         mapFile.get(c);
    //         srcY = atoi(&c) * tileSize;
    //         mapFile.get(c);
    //         srcX = atoi(&c) * tileSize;
    //         AddTile(srcX, srcY, x * scaledSize, y * scaledSize);
    //         mapFile.ignore();
    //     }
    // }

    // for (int y = 0; y < sizeY; y++)
    // {
    //     for (int x = 0; x < sizeX; x++)
    //     {
    //         mapFile.get(c);
    //         if (c == '1')
    //         {
    //             auto& tcol(manager.addEntity());
    //             tcol.addComponent<ColliderComponent>("miku", x * scaledSize, y * scaledSize, scaledSize);
    //             mapFile.ignore();
    //         }
    //         mapFile.ignore();
    //     }
    // }

    // mapFile.close();

}

void Map::AddTile(int srcX, int srcY, int xpos, int ypos) {

    auto& tile(manager.addEntity());
    tile.addComponent<TileComponent>(srcX, srcY, xpos, ypos/*, tileSize, mapScale*/, mapFilePath);
    tile.addGroup(Game::groupMap);

}

Game* game = nullptr;



int main(int argc, const char* argv[]) {

    const int FPS = 60;
    const int frameDelay = 1000 / FPS;

    Uint32 frameStart;
    int frameTime; //int


    game = new Game();

    game->init("The Seed", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, false);
    //game->FirstMenu();
    //game->showmenu();
    
    while (game->running()) {
        cout << "OK" << endl;
        // SDL_Delay(1000);
        frameStart = SDL_GetTicks();


        game->handleEveants();
        game->update();
        game->render();

        frameTime = SDL_GetTicks() - frameStart;

        if (frameDelay > frameTime) { //make the screen more smooth
            SDL_Delay(frameDelay - frameTime);
        }
    }

    game->clean();

    return 0;
}

