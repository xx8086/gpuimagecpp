#pragma once

#include <vector>
#include "tetri_type.h"

namespace lh_gl {

    typedef enum BoundaryDetection {
        BoundaryFree = 0,
        BoundaryBothSides = 1,
        BoundaryGround = 2,
    } BOUNDARY_DETECTION;


    class dropdetection :
        protected color_cube
    {
    public:
        dropdetection();
        ~dropdetection();
    public:
        void get_current_cube(TeTriUniti&);
        TeTriUniti get_current_cube();
        bool set_current_cube(TeTriUniti&);
        void current_tetris_to_triangle(std::vector<float>&);
        void floor_gl_datas(std::vector<float>&);
        void add_curent_on_floor(std::vector<float>&);
        bool need_update_triangls();
        void update_triangle_complate();
        short get_current_color();
    public:
        UPDATE_OBJ left();
        UPDATE_OBJ right();
        UPDATE_OBJ up(TeTriUniti& up_cube);
        UPDATE_OBJ down(short& );
        
    private:
        void point_to_quad(std::vector<float>&, int x, int y, int = 0);
        void quad_to_triangle(std::vector<float>&, v3f&, v3f&, v3f&, v3f&, int = 0);
        void insert_point_on_triangle(std::vector<float>&, v3f&, v3f&,int = 0);
        void  calnormal(v3f  ver1, v3f ver2, v3f ver3, v3f& normal);
        bool the_line_is_full(short y);
        short clear_copmlete_check(const short maxy);
        void clean_line(const short y);
        bool auto_down(const short y);
        void move_down(std::vector<CubePostion>&, const short x,  const short y);
        void sign_update_gl_datas();
    private:
        typedef enum TouchObj {
            TOUCH_EMPTY = 0,
            TOUCH_WALL = 1,
            TOUCH_FLOOR = 2,
        }TOUCH_OBJ;
    private:
        short current_to_ground();
        inline bool pre_down();
        inline bool pre_left();
        inline bool pre_right();
        inline bool pre_up(TeTriUniti& up_cube);
    private:
        volatile bool _update_gl_datas = false;
        short _space_station[TETRI_WIDTH][TETRI_HIGHT] = { 0 };
 /*
        |_3_________________________|
        |_2_________________________|
        |_1_________________________|
        |_0__1__2__3__4__5__6__7__|
*/

        TeTriUniti _current_cube;
        //TeTriUniti _next_cube;
        float _depth_z = TETRI_DEPT_Z;
        float _z = TETRI_Z;

    };
}

