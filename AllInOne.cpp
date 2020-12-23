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
#define WIDTH 1000
#define HEIGHT 1000
using namespace std;


class Component;
class Entity;
class Manager;
class Game;
class ColliderComponent : public Component;
class Collision;
class GameObject;
class Map;
class TextureManager;
class Vector2D;
class SpriteComponent : public Component;
class KeyBoardController : public Component;
class TileComponent : public Component;
class TransformComponent : public Component;

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

void Map::AddTile(int srcX, int srcY, int xpos, int ypos) {

    auto& tile(manager.addEntity());
    tile.addComponent<TileComponent>(srcX, srcY, xpos, ypos/*, tileSize, mapScale*/, mapFilePath);
    tile.addGroup(Game::groupMap);

}

Game* game = nullptr;

SDL_Renderer* Game::renderer = nullptr;
// Map* mmap;
Manager manager;
SDL_Event Game::event;

SDL_Rect Game::camera = { 10, 10, 1800, 1600 };

bool Game::isRunning = false;

auto& player(manager.addEntity());
// auto& colliders(manager.addEntity());//

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
    // mmap = new Map("./img/1.bmp", 3, 32);
    // mmap->LoadMap("./img/1.bmp", 16, 16);

    player.addComponent<TransformComponent>(100);
    player.addComponent<SpriteComponent>("./img/miku.bmp", true);
    player.addComponent<KeyBoardController>();
    player.addComponent<ColliderComponent>("player");
    player.addGroup(groupPlayers);

    // colliders.addComponent<SpriteComponent>()


    //Music
    MusicPlay("./mp3/miku.wav", 32);

    cout << "good1111111111111" << endl;
    SDL_Texture* ttexture = NULL;

    SDL_Surface* ssurface = NULL;
    ssurface = SDL_LoadBMP("./img/miku.bmp");
    // SDL_UpdateWindowSurface(window);
    // cout << "good1111111111111" << endl;

    int size = 80;
    SDL_Rect a;
    a.x = 50;
    a.y = size;
    a.w = size;
    a.h = size;
            
    ttexture = SDL_CreateTextureFromSurface(Game::renderer, ssurface);
    if (!ttexture) 
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create texture from surface: %s", SDL_GetError());
    }
    SDL_FreeSurface(ssurface);
    ssurface = NULL;
    SDL_RenderClear(Game::renderer);
    SDL_RenderCopy(Game::renderer, ttexture, NULL, &a);
    SDL_RenderPresent(renderer);
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
    // SDL_DestroyRenderer(renderer);
    // Game::renderer = SDL_CreateRenderer(window, -1, 0);
    // SDL_Texture* TT = TextureManager::LoadTexture("./img/miku.bmp");
    // SDL_Rect a, b;
    // a.x = 0;
    // a.y = 0;
    // a.h = 100;
    // a.w = 100;
    // b.x = 0;
    // b.y = 0;
    // b.h = 100;
    // b.w = 100;
    // TextureManager::Draw(TT, b, a, SDL_FLIP_NONE);
    // SDL_RenderPresent(renderer);

    // cout << "render" << endl;
    SDL_RenderClear(Game::renderer);
    for (auto& t : tiles) 
    {
        t->draw();
    }

    //for (auto& c : colliders)
    //{
    //    c->draw();
    //}

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
    SDL_Delay(3000);
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

