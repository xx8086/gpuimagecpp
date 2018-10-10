//#pragma once
#ifndef tetri_type_h
#define tetri_type_h

#define TIMER_ID 1
#define AI_TIMER_ID 2

typedef enum GameDif
{
    SIMPLE = 1,
    GENERAL,
    DIFFICULT,
    DIFFICULTEST
} GAME_DIF;

typedef enum CubeType {
    CUBE_TYPE_LINE = 0,
    CUBE_TYPE_T = 1,
    CUBE_TYPE_Z = 2,
    CUBE_TYPE_L = 3,
    CUBE_TYPE_SIDE_Z = 4,
    CUBE_TYPE_SIDE_L = 5,
    CUBE_TYPE_BLOCK = 6,
    CUBE_TYPE_NUMS = 7,
}CUBETYPE;

#define TETRI_UNIT_LENGTH (1)
#define TETRI_SCALE  (0.2)

#define TETRI_DEPT 1.0
#define TETRI_Z (0.0)
#define TETRI_DEPT_Z (TETRI_Z - TETRI_DEPT)
#define TETRI_WIDTH 10
#define TETRI_HIGHT 16
#define TETRI_WIDTH_HALF 5
#define CUBE_ITEM_NUMS 4

#define TETRI_DEPTH_F 5.0

#define ROATE_DEGREES_0 (0)
#define ROATE_DEGREES_90 (90)
#define ROATE_DEGREES_180 (180)
#define ROATE_DEGREES_270 (270)

typedef enum GameStatus {
    GAME_GOON = 0,
    GAME_SUSPEND = 1,
    GAME_OVER = 2,
}GAME_STATUS;

typedef enum UpdateObj {
    UPDATE_EMPTY = 0,
    UPDATE_CURRENT_OBJ = 1,
    UPDATE_FLOOR = 2,
}UPDATE_OBJ;

typedef enum CubeFace {
    FACE_BCAK = 0,
    FACE_FRONT = 1,
    FACE_LEFT = 2,
    FACE_RIGHT = 3,
    FACE_DOWN = 4,
    FACE_UP = 5,
    FACE_NUMS = 6,
}CUBE_FACE;

typedef struct TeTriUniti {
    short postion[CUBE_ITEM_NUMS][2] = { 0 };
    short color = 0;
    short type = 0;

    TeTriUniti() {}
    TeTriUniti(TeTriUniti& other) {
        color = other.color;
        type = other.type;
        for (int i = 0; i < CUBE_ITEM_NUMS; i++) {
            postion[i][0] = other.postion[i][0];
            postion[i][1] = other.postion[i][1];
        }
    }
    
    TeTriUniti& operator= (const TeTriUniti& other) {
        color = other.color;
        type = other.type;
        for (int i = 0; i < CUBE_ITEM_NUMS; i++) {
            postion[i][0] = other.postion[i][0];
            postion[i][1] = other.postion[i][1];
        }
        return *this;
    }

} TETRI_UNITI;


class CubePostion {
public:
    CubePostion() {}
    CubePostion(const CubePostion& other) {
        x = other.x;
        y = other.y;
        color = other.color;
    };
    
    CubePostion(short a, short b, short c) {
        x = a;
        y = b;
        color = c;
    };
    
    CubePostion& operator= (const CubePostion& other) {
        x = other.x;
        y = other.y;
        color = other.color;
        return *this;
    }
    
    ~CubePostion(){}
public:
    short x = 0;
    short y = 0;
    short color = 0;
};

struct v3f {
    float x;
    float y;
    float z;

    v3f() {}

    v3f(float a, float b, float c) :
        x(a), y(b), z(c) {}

    v3f& operator= (const v3f& other) {
        x = other.x;
        y = other.y;
        z = other.z;
        return *this;
    }
};

typedef enum Color_Value {
    COLOR_0 = 0,

    COLOR_1 = 1,
    COLOR_2 = 2,
    COLOR_3 = 3,
    COLOR_4 = 4,
    COLOR_5 = 5,
    COLOR_6 = 6,
    COLOR_7 = 7,
    COLOR_END,
}COLOR_VALUE;

class color_cube {
protected:
    float _colors[COLOR_END][3] = {
        1.0f, 0.0f, 0.0f,
        1.0f, 0.078f, 0.576f,//FF1493
        0.933f, 0.933f, 0.0f,//EEEE00
        0.933f, 0.172f, 0.172f,//EE2C2C
        0.608f, 0.188f, 1.0f,//9B30FF
        0.498f, 1.0f, 0.0f,//7FFF00
        0.255f, 0.412f, 0.882f,//4169E1
        0.0f, 0.804f, 0.0f//00CD00
    };
};

#endif

