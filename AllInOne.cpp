//SDL2
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

//STL
#include <algorithm>
#include <array>
#include <bitset>
#include <fstream>
#include <iostream>
#include <memory>
#include <stdio.h>
#include <sstream>
#include <string>
#include <map>
#include <vector>


#define NUMMENU 5
#define WIDTH 1280
#define HEIGHT 720
using namespace std;


class Component;
class Entity;
class Manager;
class Game;
class Collision;
class GameObject;
class Map;
class TextureManager;
class Vector2D;



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
        groupBackGrounds,
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
};

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
}

using ComponentID = std::size_t;
using Group = std::size_t;

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
};

// class SpriteComponent : public Component;
// class KeyBoardController : public Component;
// class TileComponent : public Component;
// class TransformComponent : public Component;
// class ColliderComponent : public Component;

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
private:
    SDL_Texture* texture;
    SDL_Rect srcRect, destRect;

    const char* mapFilePath;

};

Map::Map(const char* mfp, int ms, int ts) : mapFilePath(mfp)//, mapScale(ms), tileSize(ts) 
{
    // scaledSize = ms * ts;

    // LoadMap(Lv1);

    // src.x = src.y = 0;
    // src.h = dest.h = 80;
    // src.w = dest.w = 80;

    // dest.x = dest.y = 0;
}

Map::~Map() {

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

Manager manager;

void Map::AddTile(int srcX, int srcY, int xpos, int ypos) 
{
    auto& tile(manager.addEntity());
    tile.addComponent<TileComponent>(srcX, srcY, xpos, ypos/*, tileSize, mapScale*/, mapFilePath);
    tile.addGroup(Game::groupMap);
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

Game* game = nullptr;

SDL_Renderer* Game::renderer = nullptr;
// Map* mmap;
SDL_Event Game::event;

SDL_Rect Game::camera = { 10, 10, 1800, 1600 };

bool Game::isRunning = false;

auto& player(manager.addEntity());
auto& back(manager.addEntity());

// auto& colliders(manager.addEntity());//
//
//

Game::Game() 
{
    Character[0] = "Miku";
    Character[1] = "Kirito";
    Character[2] = "Asuna";
    Character[3] = "Hung";
    Character[4] = "Heish";
}

Game::~Game() 
{

}

void Game::init(const char* title, int xMenuPos, int yMenuPos, int width, int height, bool fullscreen) {

    int flags = 0;

    if (fullscreen) 
    {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) 
    {
        cout << "Subsystem Initialised!..." << endl;

        window = SDL_CreateWindow(title, xMenuPos, yMenuPos, width, height, flags);
        if (window) 
        {
            cout << "Window Created!" << endl;
            SDL_Surface* ICON = IMG_Load("./img/kirito1.ico");
            SDL_SetWindowIcon(window, ICON);
            SDL_FreeSurface(ICON);
        }

        Game::renderer = SDL_CreateRenderer(window, -1, 0);
        if (Game::renderer)
        {
            SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, 255);
            cout << "Renderer Created!" << endl;
        }

        isRunning = true;
    } 
    else 
    {
        isRunning = false;
    }


class BackGroundComponent : public Component
{
public:
    SDL_Texture* texture;
    SDL_Rect srcR, destR;
    map<int, const char*> MIKUGIF;
 
    // static int num;
    // static int order;

    BackGroundComponent()
    {
        srcR.x = 0;
        srcR.y = 0;
        srcR.h = 720;
        srcR.w = 1280;
        destR.x = 0;
        destR.y = 0;
        destR.h = 720;
        destR.w = 1280;
        // num = 0;
        // order = 0;
        MIKUGIF[1]  = "../img/miku/0001.bmp";
        MIKUGIF[2]  = "../img/miku/0002.bmp";
        MIKUGIF[3]  = "../img/miku/0003.bmp";
        MIKUGIF[4]  = "../img/miku/0004.bmp";
        MIKUGIF[5]  = "../img/miku/0005.bmp";
        MIKUGIF[6]  = "../img/miku/0006.bmp";
        MIKUGIF[7]  = "../img/miku/0007.bmp";
        MIKUGIF[8]  = "../img/miku/0008.bmp";
        MIKUGIF[9]  = "../img/miku/0009.bmp";
        MIKUGIF[10] = "../img/miku/0010.bmp";
        MIKUGIF[11] = "../img/miku/0011.bmp";
        MIKUGIF[12] = "../img/miku/0012.bmp";
        MIKUGIF[13] = "../img/miku/0013.bmp";
        MIKUGIF[14] = "../img/miku/0014.bmp";
        MIKUGIF[15] = "../img/miku/0015.bmp";
        MIKUGIF[16] = "../img/miku/0016.bmp";
        MIKUGIF[17] = "../img/miku/0017.bmp";
        MIKUGIF[18] = "../img/miku/0018.bmp";
        MIKUGIF[19] = "../img/miku/0019.bmp";
        MIKUGIF[20] = "../img/miku/0020.bmp";
        MIKUGIF[21] = "../img/miku/0021.bmp";
        MIKUGIF[22] = "../img/miku/0022.bmp";
        MIKUGIF[23] = "../img/miku/0023.bmp";
        MIKUGIF[24] = "../img/miku/0024.bmp";
        MIKUGIF[25] = "../img/miku/0025.bmp";
        MIKUGIF[26] = "../img/miku/0026.bmp";
        MIKUGIF[27] = "../img/miku/0027.bmp";
        MIKUGIF[28] = "../img/miku/0028.bmp";
        MIKUGIF[29] = "../img/miku/0029.bmp";
        MIKUGIF[30] = "../img/miku/0030.bmp";
        MIKUGIF[31] = "../img/miku/0031.bmp";
        MIKUGIF[32] = "../img/miku/0032.bmp";
        MIKUGIF[33] = "../img/miku/0033.bmp";
        MIKUGIF[34] = "../img/miku/0034.bmp";
        MIKUGIF[35] = "../img/miku/0035.bmp";
        MIKUGIF[36] = "../img/miku/0036.bmp";
        MIKUGIF[37] = "../img/miku/0037.bmp";
        MIKUGIF[38] = "../img/miku/0038.bmp";
        MIKUGIF[39] = "../img/miku/0039.bmp";
        MIKUGIF[40] = "../img/miku/0040.bmp";
        MIKUGIF[41] = "../img/miku/0041.bmp";
        MIKUGIF[42] = "../img/miku/0042.bmp";
        MIKUGIF[43] = "../img/miku/0043.bmp";
        MIKUGIF[44] = "../img/miku/0044.bmp";
        MIKUGIF[45] = "../img/miku/0045.bmp";
        MIKUGIF[46] = "../img/miku/0046.bmp";
        MIKUGIF[47] = "../img/miku/0047.bmp";
        MIKUGIF[48] = "../img/miku/0048.bmp";
        MIKUGIF[49] = "../img/miku/0049.bmp";
        MIKUGIF[50] = "../img/miku/0050.bmp";
        MIKUGIF[51] = "../img/miku/0051.bmp";
        MIKUGIF[52] = "../img/miku/0052.bmp";
        MIKUGIF[53] = "../img/miku/0053.bmp";
        MIKUGIF[54] = "../img/miku/0054.bmp";
    }
    ~BackGroundComponent()
    {

    }

    void init() override
    {
        // num = 0;
        texture = TextureManager::LoadTexture(MIKUGIF[1]);
    }

    void update() override
    {
        // static int num = 0;
        // static int i = 1;
        // num++;
        // if (num % 3 == 0) 
        // {
        //     texture = TextureManager::LoadTexture(MIKUGIF[i]);
        // }
        // if (num > 200) num = 0;
        // if (i >= 54) i = 1;
    }

    void draw() override
    {
        // SDL_RenderCopyEx(Game::renderer, texture, &srcR, &destR, NULL, NULL, SDL_FLIP_NONE);
        // SDL_RenderPresent(Game::renderer);
        // SDL_DestroyTexture(texture);
        static int num = 0;
        static int i = 1;
        num++;
        i++;
        //texture = TextureManager::LoadTexture(MIKUGIF[i]);
        //texture = TextureManager::LoadTexture(MIKUGIF[1]);
        // SDL_Surface* tmpSurface = SDL_LoadBMP(MIKUGIF[i]);
        // SDL_Surface* 
        // texture = SDL_CreateTextureFromSurface(Game::renderer, tmpSurface);
        // SDL_FreeSurface(tmpSurface);
        // cout << i << endl;
        // if (num % 1 == 0) 
        // {
            
        // }
        SDL_Surface* tmpSurface;
    // static int i = 1;
        SDL_RenderClear(Game::renderer);
        cout << "i = " << i<<endl;
    if (i == 1)
        tmpSurface = SDL_LoadBMP("./img/miku/0001.bmp");
    if (i == 2)
        tmpSurface = SDL_LoadBMP("./img/miku/0002.bmp");
    if (i == 3)
        tmpSurface = SDL_LoadBMP("./img/miku/0003.bmp");
    if (i == 4)
         tmpSurface = SDL_LoadBMP("./img/miku/0004.bmp");
    if (i == 5)
         tmpSurface = SDL_LoadBMP("./img/miku/0005.bmp");
    if (i == 6)
         tmpSurface = SDL_LoadBMP("./img/miku/0006.bmp");
    if (i == 7)
         tmpSurface = SDL_LoadBMP("./img/miku/0007.bmp");
    if (i == 8)
        tmpSurface = SDL_LoadBMP("./img/miku/0008.bmp");
    if (i == 9)
        tmpSurface = SDL_LoadBMP("./img/miku/0009.bmp");
    if (i == 10)
        tmpSurface = SDL_LoadBMP("./img/miku/0010.bmp");
    if (i == 11)
        tmpSurface = SDL_LoadBMP("./img/miku/0011.bmp");
    if (i == 12)
         tmpSurface = SDL_LoadBMP("./img/miku/0012.bmp");
    if (i == 13)
         tmpSurface = SDL_LoadBMP("./img/miku/0013.bmp");
    if (i == 14)
         tmpSurface = SDL_LoadBMP("./img/miku/0014.bmp");
    if (i == 15)
         tmpSurface = SDL_LoadBMP("./img/miku/0015.bmp");
    if (i == 16)
         tmpSurface = SDL_LoadBMP("./img/miku/0016.bmp");
    if (i == 17)
         tmpSurface = SDL_LoadBMP("./img/miku/0017.bmp");
    if (i == 18)
         tmpSurface = SDL_LoadBMP("./img/miku/0018.bmp");
    if (i == 19)
         tmpSurface = SDL_LoadBMP("./img/miku/0019.bmp");
    if (i == 20)
         tmpSurface = SDL_LoadBMP("./img/miku/0020.bmp");
    if (i == 21)
         tmpSurface = SDL_LoadBMP("./img/miku/0021.bmp");
    if (i == 22)
         tmpSurface = SDL_LoadBMP("./img/miku/0022.bmp");
    if (i == 23)
         tmpSurface = SDL_LoadBMP("./img/miku/0023.bmp");
    if (i == 24)
         tmpSurface = SDL_LoadBMP("./img/miku/0024.bmp");
    if (i == 25)
         tmpSurface = SDL_LoadBMP("./img/miku/0025.bmp");
    if (i == 26)
         tmpSurface = SDL_LoadBMP("./img/miku/0026.bmp");
    if (i == 27)
         tmpSurface = SDL_LoadBMP("./img/miku/0027.bmp");
    if (i == 28)
         tmpSurface = SDL_LoadBMP("./img/miku/0028.bmp");
    if (i == 29)
         tmpSurface = SDL_LoadBMP("./img/miku/0029.bmp");
    if (i == 30)
         tmpSurface = SDL_LoadBMP("./img/miku/0030.bmp");
    if (i == 31)
         tmpSurface = SDL_LoadBMP("./img/miku/0031.bmp");
    if (i == 32)
         tmpSurface = SDL_LoadBMP("./img/miku/0032.bmp");
    if (i == 33)
         tmpSurface = SDL_LoadBMP("./img/miku/0033.bmp");
    if (i == 34)
         tmpSurface = SDL_LoadBMP("./img/miku/0034.bmp");
    if (i == 35)
         tmpSurface = SDL_LoadBMP("./img/miku/0035.bmp");
    if (i == 36)
         tmpSurface = SDL_LoadBMP("./img/miku/0036.bmp");
    if (i == 37)
         tmpSurface = SDL_LoadBMP("./img/miku/0037.bmp");
    if (i == 38)
         tmpSurface = SDL_LoadBMP("./img/miku/0038.bmp");
    if (i == 39)
         tmpSurface = SDL_LoadBMP("./img/miku/0039.bmp");
    if (i == 40)
         tmpSurface = SDL_LoadBMP("./img/miku/0040.bmp");
    if (i == 41)
         tmpSurface = SDL_LoadBMP("./img/miku/0041.bmp");
    if (i == 42)
         tmpSurface = SDL_LoadBMP("./img/miku/0042.bmp");
    if (i == 43)
         tmpSurface = SDL_LoadBMP("./img/miku/0043.bmp");
    if (i == 44)
         tmpSurface = SDL_LoadBMP("./img/miku/0044.bmp");
    if (i == 45)
         tmpSurface = SDL_LoadBMP("./img/miku/0045.bmp");
    if (i == 46)//
         tmpSurface = SDL_LoadBMP("./img/miku/0046.bmp");
    if (i == 47)
         tmpSurface = SDL_LoadBMP("./img/miku/0047.bmp");
    if (i == 48)
         tmpSurface = SDL_LoadBMP("./img/miku/0048.bmp");
    if (i == 49)
         tmpSurface = SDL_LoadBMP("./img/miku/0049.bmp");
    if (i == 50)
         tmpSurface = SDL_LoadBMP("./img/miku/0050.bmp");
    if (i == 51)
         tmpSurface = SDL_LoadBMP("./img/miku/0051.bmp");
    if (i == 52)
         tmpSurface = SDL_LoadBMP("./img/miku/0052.bmp");
    if (i == 53)
         tmpSurface = SDL_LoadBMP("./img/miku/0053.bmp");
    if (i == 54)
         tmpSurface = SDL_LoadBMP("./img/miku/0054.bmp");
    i++;
    texture = SDL_CreateTextureFromSurface(Game::renderer, tmpSurface);
    SDL_FreeSurface(tmpSurface);
    SDL_Delay(120);

        //  SDL_Delay(30);
    if (i > 54) i = 1;
        if (num > 200) num = 0;
        cout << "draw - back" << endl;
        //TextureManager::Draw(texture, srcR, destR, SDL_FLIP_NONE);
        SDL_RenderCopyEx(Game::renderer, texture, &srcR, &destR, NULL, NULL, SDL_FLIP_NONE);
        SDL_RenderPresent(Game::renderer);
        SDL_DestroyTexture(texture);
    }
};
    // mmap = new Map("./img/1.bmp", 3, 32);
    // mmap->LoadMap("./img/1.bmp", 16, 16);

    player.addComponent<TransformComponent>(100);
    player.addComponent<SpriteComponent>("./img/miku.bmp", true);
    player.addComponent<KeyBoardController>();
    player.addComponent<ColliderComponent>("player");
    player.addGroup(groupPlayers);
    back.addComponent<BackGroundComponent>();
    back.addGroup(groupBackGrounds);

    //Music
    MusicPlay("./mp3/miku.wav", 32);
    // cout << "good1111111111111" << endl;
    // SDL_Texture* ttexture = NULL;
    // SDL_Surface* ssurface = NULL;
    // ssurface = SDL_LoadBMP("./img/miku.bmp");
    // int size = 80;
    // SDL_Rect a;
    // a.x = 50;
    // a.y = size;
    // a.w = size;
    // a.h = size;
            
    // ttexture = SDL_CreateTextureFromSurface(Game::renderer, ssurface);
    // if (!ttexture) 
    // {
    //     SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create texture from surface: %s", SDL_GetError());
    // }
    // SDL_FreeSurface(ssurface);
    // ssurface = NULL;
    // SDL_RenderClear(Game::renderer);
    // SDL_RenderCopy(Game::renderer, ttexture, NULL, &a);
    // SDL_RenderPresent(renderer);
    SDL_Delay(2000);

    //LinkStart
    // LinkStart("Game Initailizing...", 1000, 100, 600);
    // LinkStart("Game Initailized!", 1000, 100, 600);
    // LinkStart("Link Start!", 2000, 200, 600);
    //LinkStart

}

auto& tiles(manager.getGroup(Game::groupMap));
auto& players(manager.getGroup(Game::groupPlayers));
auto& colliders(manager.getGroup(Game::groupColliders));
auto& backs(manager.getGroup(Game::groupBackGrounds));


void Game::handleEveants() 
{
    // SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type) 
    {
        case SDL_QUIT:
            isRunning = false;
            break;
        case SDLK_ESCAPE:
            SDL_Delay(-1);
        default:
            break;
    }
}

void Game::update() 
{
    // LinkStart("good",1000,100,600);
    SDL_Rect playerCol = player.getComponent<ColliderComponent>().collider;
    Vector2D playerPos = player.getComponent<TransformComponent>().position;
    cout << playerCol.w << ' ' << playerCol.h << endl;
    cout << playerPos.x << ' ' << playerPos.y << endl;
    manager.refresh();
    manager.update();
    // manager.draw();
    for (auto& c : colliders)
    {
        SDL_Rect cCol = c->getComponent<ColliderComponent>().collider;
        if (Collision::AABB(cCol, playerCol))
        {
            cout << "hit\n";
            player.getComponent<TransformComponent>().position = playerPos;
        }
    }
    camera.x = player.getComponent<TransformComponent>().position.x;// - 400;
    camera.y = player.getComponent<TransformComponent>().position.y;// - 320;

    if (camera.x < 0) 
    {
        camera.x = 0;
    }

    if (camera.y < 0) 
    {
        camera.y = 0;
    }

    if (camera.x > camera.w) 
    {
        camera.x = camera.w;
    }

    if (camera.y > camera.h) 
    {
        camera.y = camera.h;
    }

}


void Game::render() 
{
    // SDL_RenderClear(Game::renderer);
    for (auto& t : tiles) 
    {
        t->draw();
    }

    for (auto& c : colliders)
    {
       c->draw();
    }

    int kkk = 0;
    for (auto& p : players) 
    {
        p->draw();
        // cout << p->getComponent<Animation
        ++kkk;

    }
    cout << "KKK: " << kkk <<endl;
    
    SDL_RenderPresent(Game::renderer);
    cout << "draw - done" << endl;
    // SDL_Delay(3000);
}

void Game::clean() 
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    Mix_CloseAudio();
    SDL_Quit();
    Mix_Quit();
    IMG_Quit();
    cout << "Game Cleaned!" << endl;
}


void Game::showmenu() 
{
    
    const int FPS = 60;
    const int frameDelay = 1000 / FPS;
    Uint32 frameStart;
    int frameTime; //int
    MenuisRunning = true;
    if (TTF_Init() == -1) 
    {

    }
    

    //Set Character Position Here (Start)
    int CharacterHeight = 160;
    for (int i = 0; i < NUMMENU; i++) 
    {
        MenuCharacterPos[i].y = HEIGHT - 80 - CharacterHeight;
        MenuCharacterPos[i].h = CharacterHeight;
        MenuCharacterPos[i].w = 100;
    }

    MenuCharacterPos[0].x =  30;
    for (int i = 1; i < NUMMENU; i++) 
    {
        MenuCharacterPos[i].x = MenuCharacterPos[i - 1].x + 130;
    }
    //Set Character Position Here (End)


    //Set Menu Font (Start)
    MenuFont = TTF_OpenFont("./fonts/SAOUITT-Regular.ttf", 1000);
    TTF_SetFontStyle(MenuFont, /*TTF_STYLE_BOLD|*/TTF_STYLE_ITALIC);
    //Set Menu Font (End)

    bool selected[NUMMENU] = {0};

    //Set Menu Position Here (Start)
    for (int i = 0; i < NUMMENU; i++) 
    {
        MenuPos[i].h = 50;
        MenuPos[i].w = 100;
    }

    int UP    = HEIGHT - 130;
    int DOWN  = HEIGHT -  30;
    int LEFT[NUMMENU]  = {  30, 160, 290, 420, 550 };
    int RIGHT[NUMMENU] = { 130, 260, 390, 520, 650 };
    for (int i = 0; i < NUMMENU; i++) 
    {
        MenuLabel[i] << Character[i];
    }
    
    for (int i = 0; i < NUMMENU; i++) 
    {
        MenuChoice[i] = TTF_RenderText_Solid(MenuFont, MenuLabel[i].str().c_str(), MenuColor[0]);
        MenuPos[i].y = HEIGHT - 60;
    }

    MenuPos[0].x =  30;
    for (int i = 1; i < NUMMENU; i++) 
    {
        MenuPos[i].x = MenuPos[i - 1].x + 130;
    }
    //Set Menu Position Here (End)

    //Title (Character) Basic Setting (Start)
    for (int i = 0; i < NUMMENU; i++) {
        CharacterTextRect[i].h = 70;
        CharacterTextRect[i].w = 600;
        CharacterTextRect[i].x = 50;
        CharacterTextRect[i].y = 200 + 80 * i;
    }
        
    CharacterTextFont = TTF_OpenFont("./fonts/SAOUITT-Regular.ttf", 1000);
    TTF_SetFontStyle(CharacterTextFont, TTF_STYLE_ITALIC);
    for (int i = 0; i < NUMMENU; i++) {
        CharacterTextText[i].str( "" );
    }
    CharacterTextText[0] << "Miku: Miku Yu Yu!!!";
    CharacterTextText[1] << "Kirito: Star Burst Stream!!!";
    CharacterTextText[2] << "Shark: AAAAA!!!";
    CharacterTextText[3] << "Hung: Miku 39 Is Answer!!!";
    CharacterTextText[4] << "Heish: I'm Your Muji!!!";
    // for (int i = 0; i < NUMMENU; i++) {
    //     CharacterTextSurface[i] = TTF_RenderText_Solid(CharacterTextFont, CharacterTextText[i].str().c_str(), CharacterTextColor);
    // }
    //Title (Character) Basic Setting (End)

    //Main Loop (Start)
    SDL_Event event;
    while (1) {
        SDL_Delay(1000);
        //Title Basic Setting (Start)
        SDL_Texture *LinkStartTexture = NULL;
        SDL_Surface *LinkStartSurface = NULL;
        SDL_Rect dst;
        dst.h = 150;
        dst.w = 600;
        dst.x = 30;
        dst.y = 30;
        if(TTF_Init() == -1) {
            cout << "TTF_Init: " << TTF_GetError() << endl;
        }
        TTF_Font *font;
        font = TTF_OpenFont("./fonts/SAOUITT-Regular.ttf", 1000);
        if(!font) {
            cout << "TTF_OpenFont: " << TTF_GetError() << endl;
        }
        TTF_SetFontStyle(font, TTF_STYLE_ITALIC);
        //SDL_Color color = { 0, 255, 235 };
        SDL_Color color = { 255, 223,   0 };
        stringstream LinkStartText;
        LinkStartText.str( "" );
        LinkStartText << "Choose Character";
        LinkStartSurface = TTF_RenderText_Solid(font, LinkStartText.str().c_str(), color);
        LinkStartTexture = SDL_CreateTextureFromSurface(renderer, LinkStartSurface);
        if (!LinkStartTexture) {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create texture from surface: %s", SDL_GetError());
        }
        SDL_FreeSurface(LinkStartSurface);
        TTF_CloseFont(font);
        font = NULL;
        //Title Basic Setting (End)

        
        //Title (Character) Basic Setting (Start)
        for (int i = 0; i < NUMMENU; i++) {
            SDL_FreeSurface(CharacterTextSurface[i]);
        }
        for (int i = 0; i < NUMMENU; i++) {
            CharacterTextSurface[i] = TTF_RenderText_Solid(CharacterTextFont, CharacterTextText[i].str().c_str(), CharacterTextColor);
        }
        
        //Title (Character) Basic Setting (End)

        //Character Setting (Start)
        frameStart = SDL_GetTicks();

        for (int i = 0; i < NUMMENU; i++) {
            SDL_FreeSurface(MenuCharacterSurface[i]);
        }
        MenuCharacterSurface[0] = SDL_LoadBMP("./img/miku.bmp");
        MenuCharacterSurface[1] = SDL_LoadBMP("./img/miku.bmp");
        MenuCharacterSurface[2] = SDL_LoadBMP("./img/miku.bmp");
        MenuCharacterSurface[3] = SDL_LoadBMP("./img/miku.bmp");
        MenuCharacterSurface[4] = SDL_LoadBMP("./img/miku.bmp");       
        //Character Setting (End)
        for (int i = 0; i < NUMMENU; i++) {
            MenuChoice[i] = TTF_RenderText_Solid(MenuFont, MenuLabel[i].str().c_str(), MenuColor[1]);
        }
        

        //Event Loop (Start)
        while (SDL_PollEvent( &event ) != 0) {
            switch (event.type) {
                case SDL_QUIT:
                    for (int i = 0; i < NUMMENU; i++) {
                        SDL_FreeSurface(MenuChoice[i]);
                        MenuisRunning = false;
                    }
                    break;
                case SDL_MOUSEMOTION:
                    X_MENU_MOUSE = event.motion.x;
                    Y_MENU_MOUSE = event.motion.y;
                    
                    
                    for (int i = 0; i < NUMMENU; i++) {
                        if (X_MENU_MOUSE >= LEFT[i] && X_MENU_MOUSE <= RIGHT[i] && Y_MENU_MOUSE >= UP && Y_MENU_MOUSE <= DOWN) {
                            if (!selected[i]) {
                                selected[i] = 1;
                                SDL_FreeSurface(MenuChoice[i]);
                                MenuChoice[i] = TTF_RenderText_Solid(MenuFont, MenuLabel[i].str().c_str(), MenuColor[1]);
                            }
                            else {
                                if (selected[i]) {
                                    selected[i] = 0;
                                    SDL_FreeSurface(MenuChoice[i]);
                                    MenuChoice[i] = TTF_RenderText_Solid(MenuFont, MenuLabel[i].str().c_str(), MenuColor[0]);
                                }
                            }
                        }
                        else {
                            selected[i] = 0;
                            SDL_FreeSurface(MenuChoice[i]);
                            MenuChoice[i] = TTF_RenderText_Solid(MenuFont, MenuLabel[i].str().c_str(), MenuColor[0]);
                        }
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    X_MENU_MOUSE = event.motion.x;
                    Y_MENU_MOUSE = event.motion.y;
                    for (int i = 0; i < NUMMENU; i++) {
                        if (X_MENU_MOUSE >= MenuPos[i].x && X_MENU_MOUSE <= MenuPos[i].x + MenuPos[i].w && Y_MENU_MOUSE >= MenuPos[i].y && Y_MENU_MOUSE <= MenuPos[i].y + MenuPos[i].h) {
                            for (int j = 0; j < NUMMENU; j++) {
                                SDL_FreeSurface(MenuChoice[j]); 
                            }
                        }
                    }
                    break;
                case SDL_KEYDOWN:
                    if (event.key.keysym.sym == SDLK_ESCAPE) {
                        for (int i = 0; i < NUMMENU; i++) {
                            SDL_FreeSurface(MenuChoice[i]);
                        }
                        MenuisRunning = false;
                    }
                    break;
            }
        }
        if (!MenuisRunning) {
            for (int i = 0; i < NUMMENU; i++) {
                SDL_DestroyTexture(MenuTex[i]);
                SDL_DestroyTexture(MenuCharacterTex[i]);
                SDL_DestroyTexture(CharacterTextTexture[i]);
            }
            break;
        }
        //Event Loop (End)

        //Render (Start)
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
        SDL_RenderClear(renderer);
        for (int i = 0; i < NUMMENU; i++) {

            MenuCharacterTex[i] = SDL_CreateTextureFromSurface(renderer, MenuCharacterSurface[i]);
            CharacterTextTexture[i] = SDL_CreateTextureFromSurface(renderer, CharacterTextSurface[i]);
            MenuTex[i] = SDL_CreateTextureFromSurface(renderer, MenuChoice[i]);
            // SDL_FreeSurface(MenuCharacterSurface[i]);
            SDL_FreeSurface(MenuChoice[i]);
            // SDL_FreeSurface(CharacterTextSurface[i]);
            SDL_RenderCopy(renderer, MenuTex[i], NULL, &MenuPos[i]);
            SDL_RenderCopy(renderer, CharacterTextTexture[i], NULL, &CharacterTextRect[i]);
            SDL_RenderCopy(renderer, MenuCharacterTex[i], NULL, &MenuCharacterPos[i]);
            SDL_DestroyTexture(MenuTex[i]);
            SDL_DestroyTexture(CharacterTextTexture[i]);
            SDL_DestroyTexture(MenuCharacterTex[i]);

        }
        SDL_RenderCopy(renderer, LinkStartTexture, NULL, &dst);
        SDL_DestroyTexture(LinkStartTexture);
        SDL_RenderPresent(renderer);
        //Render (End)

        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime) { //make the screen more smooth
            SDL_Delay(frameDelay - frameTime);
        }
    }
    //Main Loop (End)
}

void Game::LinkStart(string text, int second, int h, int w) {
    SDL_Texture *LinkStartTexture = NULL;
    SDL_Surface *LinkStartSurface = NULL;
    SDL_Rect dst;
    dst.h = h;
    dst.w = w;
    dst.x = WIDTH / 2 - dst.w / 2;
    dst.y = HEIGHT / 2 - dst.h / 2;
    if(TTF_Init() == -1) {
        cout << "TTF_Init: " << TTF_GetError() << endl;
    }
    TTF_Font *font;
    font = TTF_OpenFont("./fonts/SAOUITT-Regular.ttf", 1000);
    if(!font) {
        cout << "TTF_OpenFont: " << TTF_GetError() << endl;
    }
    TTF_SetFontStyle(font, 0/*TTF_STYLE_BOLD|TTF_STYLE_ITALIC*/);
    //SDL_Color color = { 0, 255, 235 };
    SDL_Color color = { 255, 223,   0 };
    stringstream LinkStartText;
    LinkStartText.str( "" );
    LinkStartText << text;
    LinkStartSurface = TTF_RenderText_Solid(font, LinkStartText.str().c_str(), color);
    LinkStartTexture = SDL_CreateTextureFromSurface(renderer, LinkStartSurface);
    if (!LinkStartTexture) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create texture from surface: %s", SDL_GetError());
    }
    SDL_FreeSurface(LinkStartSurface);
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, LinkStartTexture, NULL, &dst);
    SDL_DestroyTexture(LinkStartTexture);
    SDL_RenderPresent(renderer);
    SDL_Delay(second);
    TTF_CloseFont(font);
    font = NULL;
    cout << text << endl;
}

void Game::MusicPlay(const char* Music, int volume) {
    // load support for the MP3 sample/music formats
    int mflags = MIX_INIT_MP3;
    if( (Mix_Init(mflags) & mflags) != mflags ) {
        // cout << "Mix_Init: Failed to init required ogg and mod support!\n";
        // cout << "Mix_Init: %s\n" << Mix_GetError() << endl;
    }

    if(Mix_OpenAudio(128000, MIX_DEFAULT_FORMAT, 2, 2048) == -1) {
        // cout << "Mix_OpenAudio: %s\n" << Mix_GetError() << endl;
    }


    // load the MP3 file to play as music
    Mix_Music *music;
    music = Mix_LoadMUS(Music);
    //Mix_LoadMUS
    if(!music) {
        cout << "Mix_LoadMUS(\"miku.mp3\"): %s\n" << Mix_GetError();
    }
    Mix_VolumeMusic(volume);
    Mix_PlayMusic( music, -1 );
    cout << "Music Loaded!\n";
}



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

