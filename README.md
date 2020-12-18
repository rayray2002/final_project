# 計算機程式期末專題

## Ideas

    Puyo Puyo

## Library

    SDL2
    SDL2_ttf
    SDL_bgi
    SDL_image
    iostream
    vector
    queue

## 分工

* ### 黃柏睿

  Board update
    * #### Data types
        * enum Color
        * struct Block: x, y
    * #### Class Puyo
      ##### Public members:
        * Color board \[13]\[6]
        * Constructor: Puyo(Color array), Puyo(char array), Puyo()
        * void printer(): cout current board
        * vector\<int> update(): handle board refresh, return \[combo, remove_count]

      ##### Private members:
        * vector\<Block> check_chained(int x, int y): BFS chain detector, return the chain
        * void fill(): free fall
        * void remove(Block): remove assigned block

* ### 徐明皓
  character, falling queue manage, and main loop

* ### 施文崴
  graphic update

## Docs

[python2 example](https://github.com/hMatoba/puyopuyo "title")
