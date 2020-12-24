# 計算機程式期末專題

## Ideas

    GameBoard GameBoard

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
    * #### Class GameBoard
      ##### Public members:
        * Color board \[13]\[6]
        * Constructor: GameBoard(Color array), GameBoard(char array), GameBoard()
        * void printer(): cout current board
        * vector\<int> update(): handle board refresh, return \[combo, remove_count]

      ##### Private members:
        * vector\<Block> check_chained(int x, int y): BFS chain detector, return the chain
        * void fill(): free fall
        * void remove(Block): remove assigned block

* ### 徐明皓
  character, falling queue management, menu interface design, main loop, user interface, object controlling, and ECS structure.

* ### 施文崴
  graphic update and menu interface design.

## Docs

[python2 example](https://github.com/hMatoba/puyopuyo "title")
