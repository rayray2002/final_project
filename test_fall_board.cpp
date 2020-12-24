#include <iostream>
#include <vector>
#include <queue>
#include <ctime>
#include "test_initial_SDL.hpp"


using namespace std;

const bool DEBUG = true;
const int HEIGHT = 13;
const int WIDTH = 6;

enum Color {
	Empty, Red, Green, Blue, Yellow
};
struct Block {
	int x, y;
//	Color color;
};
SDL_Surface* surface_ba = SDL_LoadBMP("./img/banana.bmp");
SDL_Surface* surface_r = SDL_LoadBMP("./img/sample_red.bmp");
SDL_Surface* surface_g = SDL_LoadBMP("./img/sample_green.bmp");
SDL_Surface* surface_y = SDL_LoadBMP("./img/sample_yellow.bmp");



void show_board(Color board[][6]) {
    // SDL_SetTextureColorMod(texture, 0, 0, 0);
    // SDL_RenderCopy(Renderer, texture, NULL, NULL);
    /*SDL_Surface* surface_ba = SDL_LoadBMP("./img/banana.bmp");
    SDL_Surface* surface_r = SDL_LoadBMP("./img/sample_red.bmp");
	SDL_Surface* surface_g = SDL_LoadBMP("./img/sample_green.bmp");
	SDL_Surface* surface_y = SDL_LoadBMP("./img/sample_yellow.bmp");*/
	
    SDL_SetRenderDrawColor(Renderer,0,0,0,0);
    srand(time(0));
    for (int i = 0; i < 13; i++) {
        for (int j = 0; j < 6; j++) {
        	SDL_Texture* texture=NULL;
            switch (board[i][j]) {
            case 0:break; 
            case 1:
                if (rand() % 10 == 1) {
                    texture = SDL_CreateTextureFromSurface(Renderer, surface_ba); break;
                }
                else texture = SDL_CreateTextureFromSurface(Renderer, surface_r); break;
            case 2:
                texture = SDL_CreateTextureFromSurface(Renderer, surface_g); break;
            case 4:
                texture = SDL_CreateTextureFromSurface(Renderer, surface_y); break;

            }
            //SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0xFF, 0xFF, 0xFF));
            int size = 80;
            SDL_Rect a;
            a.x = 500 + size * j;
            a.y = size * i;
            a.w = size;
            a.h = size;

            SDL_RenderCopy(Renderer, texture, NULL, &a);
            SDL_DestroyTexture(texture);
        }
    }
    /*SDL_Event e;
    bool quit = false;
    while (!quit)
    {
        //Handle events on queue
        while (SDL_PollEvent(&e) != 0)
        {
            //User requests quit
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
        }
    }*/
	SDL_RenderPresent(Renderer);
    SDL_Delay(300);
    SDL_RenderClear(Renderer);
}

Color char_to_color(char in) {
	Color c;
	switch (in) {
		case 'R':
			c = Red;
			break;
		case 'G':
			c = Green;
			break;
		case 'B':
			c = Blue;
			break;
		case 'Y':
			c = Yellow;
			break;
		default:
			c = Empty;
			break;
	}
	return c;
}

char color_to_char(char in) {
	char c;
	switch (in) {
		case Red:
			c = 'R';
			break;
		case Green:
			c = 'G';
			break;
		case Blue:
			c = 'B';
			break;
		case Yellow:
			c = 'Y';
			break;
		default:
			c = ' ';
			break;
	}
	return c;
}

class Puyo {
public:
	Color board[HEIGHT][WIDTH] = {};

	Puyo();

	Puyo(char [][WIDTH]);

	Puyo(Color [][WIDTH]);

	void printer();

	bool update();

	int get_combo() const;

	int get_count() const;

	void reset();
	
	
private:
	vector<Block> check_chained(int, int);

	void remove(Block);

	void fill();

	int combo = 0;
	int count = 0;

};

Puyo::Puyo() {
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			Color c = Empty;
			board[i][j] = c;
		}
	}
}

Puyo::Puyo(char board_i[][WIDTH]) {
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			board[i][j] = char_to_color(board_i[i][j]);
		}
	}
}

Puyo::Puyo(Color board_i[][WIDTH]) {
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			board[i][j] = board_i[i][j];
		}
	}
}

void Puyo::printer() {
	cout << "######\n";
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			cout << color_to_char(board[i][j]);
		}
		cout << endl;
	}
	cout << "######\n";
}

vector<Block> Puyo::check_chained(int x, int y) {
	queue<Block> q;
	vector<Block> chain;
	q.push((Block) {x, y});
	bool visited[WIDTH][HEIGHT] = {};

	while (!q.empty()) {
		Block top = q.front();
		chain.push_back(top);
		visited[top.x][top.y] = true;
		q.pop();
//		cout << top.x << " " << top.y << endl;
		if (top.x - 1 >= 0 && board[top.y][top.x - 1] == board[y][x] && !visited[top.x - 1][top.y]) {
			q.push((Block) {top.x - 1, top.y});
			visited[top.x - 1][top.y] = true;
		}
		if (top.y - 1 >= 0 && board[top.y - 1][top.x] == board[y][x] && !visited[top.x][top.y - 1]) {
			q.push((Block) {top.x, top.y - 1});
			visited[top.x - 1][top.y] = true;
		}
		if (top.x + 1 < WIDTH && board[top.y][top.x + 1] == board[y][x] && !visited[top.x + 1][top.y]) {
			q.push((Block) {top.x + 1, top.y});
			visited[top.x + 1][top.y] = true;
		}
		if (top.y + 1 < HEIGHT && board[top.y + 1][top.x] == board[y][x] && !visited[top.x][top.y + 1]) {
			q.push((Block) {top.x, top.y + 1});
			visited[top.x][top.y + 1] = true;
		}
	}
	return chain;
}

void Puyo::remove(Block block) {
	board[block.y][block.x] = Empty;
}
bool needfall(Color board[13][6]){
	bool need=false;
	for(int i=0;i<HEIGHT-1;i++){
		for(int j=0;j<WIDTH;j++){
			if(board[i][j]!=Empty&&board[i+1][j]==Empty){
				need=true;
			}
		}
	}
	return need;
}
bool no(Color board[13][6]){
	bool quit = true;
	for (int i = 0; i < HEIGHT - 1; i++) {
		for (int j = 0; j < WIDTH; j++) {
			if (board[i][j] != Empty && board[i + 1][j] == Empty) {
				quit = false;	
			}
		}
	}
	return quit;
}
void show_fall(Color board1[13][6]) {
    Color board[13][6];
    for(int i=0;i<13;i++){
    	for(int j=0;j<6;j++){
    		board[i][j]=board1[i][j];
		}
	}
	while(!no(board)){
		bool stop[6] = {0,0,0,0,0,0};
    	int h[6] = {-1,-1,-1,-1,-1,-1};
   		for (int i = 0; i < 6; i++) {
    	    for (int j = 12; j >= 0; j--) {
    	        if (board[j][i] == Empty) {
    	            h[i] = j;
    	            break;
    	        }
				if(j==0) stop[i]=true;
    	    }
    	}
    	SDL_SetRenderDrawColor(Renderer, 0,0,0,0);
    	int times = 0;
    	int lowest[6] = {-1,-1,-1,-1,-1,-1};
    	for (int i = 0; i < 6; i++) {
     	   for (int j = h[i] ; j >= 0; j--) {
    	        if (board[j][i] != Empty) {
    	            lowest[i] = j;
    	            break;
    	        }
    	        else if (j == 0) {
    	            stop[i] = true;
    	        }
    	    }
    	}
    	int speed=10;
    	int t[6] = {};
    	bool quit;
    	do{
    	    for (int i = 0; i < 6; i++) {
    	        for (int j = 0; j < 13; j++) {
    	            if (j > h[i]) {
    	                SDL_Texture* texture = NULL;
    	                switch (board[j][i]) {
    	                case 1:
    	                    texture = SDL_CreateTextureFromSurface(Renderer, surface_r); break;
    	                case 2:
    	                    texture = SDL_CreateTextureFromSurface(Renderer, surface_g); break;
    	                case 4:
    	                    texture = SDL_CreateTextureFromSurface(Renderer, surface_y); break;
    	                }
        	            //SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0xFF, 0xFF, 0xFF));
            	        int size = 80;
            	        SDL_Rect a;
            	        a.x = 500 + size * i;
            	        a.y = size * j;
            	        a.w = size;
            	        a.h = size;
	
                	    SDL_RenderCopy(Renderer, texture, NULL, &a);
                	    SDL_DestroyTexture(texture);
                	}
                	else if (j < h[i]) {
                		if(board[j][i]==Empty) continue;
                	    SDL_Texture* texture = NULL;
                	    switch (board[j][i]) {
                	    case 1:
                	        texture = SDL_CreateTextureFromSurface(Renderer, surface_r); break;
                	    case 2:
                	        texture = SDL_CreateTextureFromSurface(Renderer, surface_g); break;
                	    case 4:
                	        texture = SDL_CreateTextureFromSurface(Renderer, surface_y); break;
                	    }
                	    int size = 80;
                	    SDL_Rect a;
                	    a.x = 500 + size * i;
                	    if (!stop[i]) {
                	        if (size * j + size* times / speed  >= size * h[i]) {
                	            stop[i] = true;
                	            a.y = size * h[i];
                	            t[i] = times;
                	        }
                	        else a.y = size * j + size / speed * times;
                	    }
                	    else {
                	        a.y = size * j + size / speed * t[i];
                	    }
                	    a.w = size;
                	    a.h = size;
                	    SDL_RenderCopy(Renderer, texture, NULL, &a);
                	    SDL_DestroyTexture(texture);
                	}
            	}
        	}
        	SDL_RenderPresent(Renderer);
        	SDL_Delay(1);
        	SDL_RenderClear(Renderer);
        
        	quit = true;
        	for (int i = 0; i < 6; i++) {
        	    if (!stop[i]) quit = false;
        	}
        
        	times++;
    	} while (!quit);
    	for(int i=0;i<6;i++){
    		if(lowest[i]==-1) continue;
    		for(int j=h[i];j>=0;j--){
    			if(j>=h[i]-lowest[i]) board[j][i]=board[j-h[i]+lowest[i]][i];
    			else board[j][i]=Empty;
			}
		}
	}
}
void Puyo::fill() {
	
	if(needfall(board)) show_fall(board);
	bool quit;
	do {
		quit = true;
		for (int i = 0; i < HEIGHT - 1; i++) {
			for (int j = 0; j < WIDTH; j++) {
				if (board[i][j] != Empty && board[i + 1][j] == Empty) {
					quit = false;
					board[i + 1][j] = board[i][j];
					board[i][j] = Empty;	
				}
			}
		}
	} while (!quit);
	
}

bool Puyo::update() {
	vector<Block> chain;
	bool is_updated = false;
	//if(needfall(board)) show_fall(board);
	show_board(board);
	if (DEBUG) fill();
	
	vector<vector<Block> > to_remove;
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			if (board[i][j] != Empty) {
				chain = check_chained(j, i);
				if (chain.size() >= 4) {
					to_remove.push_back(chain);
				}
			}
		}
	}
	if (!to_remove.empty()) {
		combo++;
		is_updated = true;
		if (DEBUG) cout << "combo" << combo << endl;
		for (int i = 0; i < to_remove.size(); i++) {
			for (int j = 0; j < to_remove[i].size(); j++) {
				remove(to_remove[i][j]);
			}
		}
	}
	if (DEBUG) printer();

	return is_updated;
}

int Puyo::get_combo() const {
	return combo;
}

int Puyo::get_count() const {
	return count;
}

void Puyo::reset() {
	combo = 0;
	count = 0;
}

int main(int argc, char* argv[]) {
//	char test_board[13][6] = {{'G', ' ', 'G', 'Y', 'R', 'R'},
//	                          {'R', 'Y', 'Y', 'G', 'Y', 'G'},
//	                          {'G', 'Y', 'G', 'Y', 'R', 'R'},
//	                          {'R', 'Y', 'G', 'Y', 'R', 'G'},
//	                          {'Y', 'G', 'Y', 'R', 'Y', 'G'},
//	                          {'G', 'Y', 'R', 'Y', 'R', 'G'},
//	                          {'Y', 'G', 'Y', 'R', 'Y', 'R'},
//	                          {'Y', 'G', 'Y', 'R', 'Y', 'R'},
//	                          {'Y', 'R', 'R', 'G', 'R', 'G'},
//	                          {'R', 'Y', 'G', 'Y', 'G', 'G'},
//	                          {'G', 'R', 'Y', 'G', 'Y', 'R'},
//	                          {'G', 'R', 'Y', 'G', 'Y', 'R'},
//	                          {'G', 'R', 'Y', 'G', 'Y', 'R'}};
	char test_board[13][6] = {{'G', 'G', 'G', 'G', 'R', 'R'},
	                          {'R', 'Y', 'Y', 'G', 'Y', 'G'},
	                          {'G', 'Y', 'G', 'Y', 'Y', 'R'},
	                          {'R', 'Y', 'G', 'Y', 'R', 'R'},
	                          {'Y', 'G', 'Y', 'R', 'Y', 'G'},
	                          {'G', 'Y', 'R', 'Y', 'R', 'G'},
	                          {'Y', 'Y', 'Y', 'R', 'Y', 'R'},
	                          {'Y', 'G', 'Y', 'R', 'Y', 'R'},
	                          {'Y', 'R', 'R', 'G', 'R', 'G'},
	                          {'R', 'Y', 'G', 'Y', 'G', 'G'},
	                          {'G', 'R', 'Y', 'G', 'G', 'R'},
	                          {'G', 'R', 'Y', 'G', 'Y', 'R'},
	                          {'G', 'R', 'Y', 'G', 'Y', 'R'}};
	
	init();
	Puyo puyo(test_board);
	puyo.reset();

	while (puyo.update()) {
		puyo.printer();
	}
	
	puyo.printer();
	cout << "combo:" << puyo.get_combo() << ", count:" << puyo.get_count();
	close();
	return 0;
}
