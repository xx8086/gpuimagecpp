#include "dropdetection.h"

namespace lh_gl {

    dropdetection::dropdetection() {
    }

    dropdetection::~dropdetection()
    {
    }

    bool  dropdetection::pre_left() {
        bool linesecurity = true;
        for (int i = 0; i < CUBE_ITEM_NUMS; i++) {
            if (0 != _space_station[_current_cube.postion[i][0] - 1][_current_cube.postion[i][1]] ||
                -1 == _current_cube.postion[i][0] - 1) {
                linesecurity = false;
                break;
            }
        }
        return linesecurity;
    }

    bool dropdetection::pre_right() {
        bool linesecurity = true;
        for (int i = 0; i < CUBE_ITEM_NUMS; i++) {
            if (0 != _space_station[_current_cube.postion[i][0] + 1][_current_cube.postion[i][1]] ||
                TETRI_WIDTH == _current_cube.postion[i][0] + 1) {
                linesecurity = false;
                break;
            }
        }
        return linesecurity;
    }

    bool dropdetection::pre_down() {
        bool linesecurity = true;
        for (int i = 0; i < CUBE_ITEM_NUMS; i++) {
            if (0 != _space_station[_current_cube.postion[i][0]][_current_cube.postion[i][1] - 1] ||
                -1 == _current_cube.postion[i][1] - 1) {
                linesecurity = false;
                break;
            }
        }
        return linesecurity;
    }

    bool dropdetection::pre_up(TeTriUniti& up_cube) {
        bool linesecurity = true;
        for (int i = 0; i < CUBE_ITEM_NUMS; i++) {
            if (0 != _space_station[up_cube.postion[i][0]][up_cube.postion[i][1]] ||//和已有floor块重合
                0 == up_cube.postion[i][1] || //倒底部
                TETRI_WIDTH == _current_cube.postion[i][0] || //碰到右边墙
                -1 == _current_cube.postion[i][0]) {//碰到左边墙
                linesecurity = false;
                break;
            }
        }
        return linesecurity;
    }

    UPDATE_OBJ dropdetection::up(TeTriUniti& up_cube) {
        if (pre_up(up_cube)) {
            _current_cube = up_cube;
            return UPDATE_CURRENT_OBJ;
        }

        return  UPDATE_EMPTY;
    }

    UPDATE_OBJ dropdetection::left() {
        if (pre_left()) {
            for (int i = 0; i < CUBE_ITEM_NUMS; i++) {
                _current_cube.postion[i][0] -= 1;
            }
            return UPDATE_CURRENT_OBJ;
        }

        return  UPDATE_EMPTY;
    }

    UPDATE_OBJ dropdetection::right() {
        if (pre_right()) {
            for (int i = 0; i < CUBE_ITEM_NUMS; i++) {
                _current_cube.postion[i][0] += 1;
            }
            return UPDATE_CURRENT_OBJ;
        }

        return  UPDATE_EMPTY;
    }

    UPDATE_OBJ dropdetection::down(short& clear_lines) {
        if (pre_down()) {
            for (int i = 0; i < CUBE_ITEM_NUMS; i++) {
                _current_cube.postion[i][1] -= 1;
            }
            //floor没影响，current_cube移动一下，不需要更新
            return UPDATE_CURRENT_OBJ;
        }

        clear_lines = current_to_ground();
        return UPDATE_FLOOR;
    }

    short dropdetection::current_to_ground() {
        short maxy = _current_cube.postion[0][1];
        short miny = _current_cube.postion[0][1];
        for (int i = 0; i < CUBE_ITEM_NUMS; i++) {
            _space_station[_current_cube.postion[i][0]][_current_cube.postion[i][1]] = _current_cube.color;
            if (miny > _current_cube.postion[i][1]) {
                miny = _current_cube.postion[i][1];
            }
            if (maxy < _current_cube.postion[i][1]) {
                maxy = _current_cube.postion[i][1];
            }
        }

        short down_line = -1;
        short down_line_nums = 0;
        for (short y = maxy; y >= miny; y--) {
            if (the_line_is_full(y)) {
                clean_line(y);
                down_line = y;
                down_line_nums++;
            }
        }

        sign_update_gl_datas();
        if (down_line >= 0) {
            auto_down(down_line);
            down_line_nums += clear_copmlete_check(maxy);
        }

        return down_line_nums;
    }

    short dropdetection::clear_copmlete_check(const short maxy) {
        if (0 > maxy || maxy > TETRI_HIGHT) {
            return 0;
        }

        int clearline = 0;
        for (int h = 0; h < maxy; h++) {
            bool have_fullline = true;
            for (int w = 0; w < TETRI_WIDTH; w++) {
                if (0 == _space_station[w][h]) {
                    have_fullline = false;
                    break;
                }
            }
            if (have_fullline) {
                clean_line(h);
                auto_down(h);
                clearline++;
            }
        }

        if (clearline > 0) {
            clearline += clear_copmlete_check(maxy - clearline);
        }

        return clearline;
    }

    bool dropdetection::the_line_is_full(short y) {
        bool rt = true;
        for (int i = 0; i < TETRI_WIDTH; i++) {
            if (0 == _space_station[i][y]) {
                rt = false;
                break;
            }
        }
        return rt;
    }

    void dropdetection::sign_update_gl_datas() {
        _update_gl_datas = true;
    }

    bool dropdetection::need_update_triangls() {
        return _update_gl_datas;
    }

    void dropdetection::update_triangle_complate() {
        _update_gl_datas = false;
    }

    short dropdetection::get_current_color() {
        return _current_cube.color;
    }

    void dropdetection::get_current_cube(TeTriUniti& cuu_tetri){
        cuu_tetri = _current_cube;
    }
    
    TeTriUniti dropdetection::get_current_cube(){
        return _current_cube;
    }
    bool dropdetection::set_current_cube(TeTriUniti& cuu_tetri) {
        _current_cube = cuu_tetri;
        return pre_down();
    }

    void  dropdetection::calnormal(v3f  ver1, v3f ver2, v3f ver3, v3f& normal)
    {
        float temp1[3];
        float temp2[3];
        float length = 0.0f;
        temp1[0] = ver1.x - ver2.x;
        temp1[1] = ver1.y - ver2.y;
        temp1[2] = ver1.z - ver2.z;
        temp2[0] = ver2.x - ver3.x;
        temp2[1] = ver2.y - ver3.y;
        temp2[2] = ver2.z - ver3.z;

        //计算法线
        normal.x = temp1[1] * temp2[2] - temp1[2] * temp2[1];
        normal.y = temp1[0] * temp2[2] - temp1[2] * temp2[0];
        normal.z = temp1[0] * temp2[1] - temp1[1] * temp2[0];

/*
//法线单位化
        length = sqrt(normal[0] * normal[0] + normal[1] * normal[1] + normal[2] * normal[2]);
        if (length == 0.0f)
            length = 1.0f;
        normal[0] /= length;
        normal[1] /= length;
        normal[2] /= length;
*/
    }

    void dropdetection::point_to_quad(std::vector<float>& triangl, int x, int y, int color) {
        v3f a0((float)x, (float)y, _z);
        v3f b0(a0.x + 1, a0.y, _z);
        v3f c0(b0.x, b0.y + 1, _z);
        v3f d0(a0.x, a0.y + 1, _z);
        quad_to_triangle(triangl, a0, b0, c0, d0, color);

        v3f a_left(a0), b_left(a0), c_left(d0), d_left(d0);
        a_left.z = _depth_z;
        d_left.z = _depth_z;
        quad_to_triangle(triangl, a_left, b_left, c_left, d_left, color);

        v3f a_right(b0), b_right(b0), c_right(c0), d_right(c0);
        b_right.z = _depth_z;
        c_right.z = _depth_z;
        quad_to_triangle(triangl, a_right, b_right, c_right, d_right, color);

        v3f a_up(d0), b_up(c0), c_up(c0), d_up(d0);
        d_up.z = _depth_z;
        c_up.z = _depth_z;
        quad_to_triangle(triangl, a_up, b_up, c_up, d_up, color);

        v3f a_down(a0), b_down(b0), c_down(b0), d_down(a0);
        a_down.z = _depth_z;
        b_down.z = _depth_z;
        quad_to_triangle(triangl, a_down, b_down, c_down, d_down, color);

        v3f a_depth(a0), b_depth(b0), c_depth(c0), d_depth(d0);
        a_depth.z = _depth_z;
        b_depth.z = _depth_z;
        c_depth.z = _depth_z;
        d_depth.z = _depth_z;
        quad_to_triangle(triangl, a_depth, b_depth, c_depth, d_depth, color);
    }

    void dropdetection::add_curent_on_floor(std::vector<float>& floor_datas) {
        for (int i = 0; i < CUBE_ITEM_NUMS; i++) {
            point_to_quad(floor_datas,
                _current_cube.postion[i][0],
                _current_cube.postion[i][1],
                _current_cube.color);
        }
    }

    void dropdetection::floor_gl_datas(std::vector<float>& floor_datas) {
        floor_datas.clear();

        for (int w = 0; w < TETRI_WIDTH; w++) {
            for (int h = 0; h < TETRI_HIGHT; h++) {
                if (0 == _space_station[w][h]) {
                    continue;
                }

                point_to_quad(floor_datas, w, h, _space_station[w][h]);
            }
        }
    }

    void dropdetection::current_tetris_to_triangle(std::vector<float>& current_tetris) {
        current_tetris.clear();

        for (int i = 0; i < CUBE_ITEM_NUMS; i++) {
            point_to_quad(current_tetris,
                _current_cube.postion[i][0],
                _current_cube.postion[i][1]);
        }
    }

    void dropdetection::insert_point_on_triangle(std::vector<float>& triangl, v3f& point, v3f& normal, int color) {
        triangl.emplace_back(point.x);
        triangl.emplace_back(point.y);
        triangl.emplace_back(point.z);//postion
        triangl.emplace_back(normal.x);
        triangl.emplace_back(normal.y);
        triangl.emplace_back(normal.z);//normal
        if (0 < color) {
            triangl.emplace_back(_colors[color][0]);
            triangl.emplace_back(_colors[color][1]);
            triangl.emplace_back(_colors[color][2]);//color
        }
    }
    void dropdetection::quad_to_triangle(std::vector<float>&triangl, v3f& a, v3f& b, v3f& c, v3f& d, int color) {
        
        v3f normal;
        calnormal(d, a, b, normal);

        insert_point_on_triangle(triangl, d, normal, color);
        insert_point_on_triangle(triangl, a, normal, color);
        insert_point_on_triangle(triangl, b, normal, color);//dab

        insert_point_on_triangle(triangl, d, normal, color);
        insert_point_on_triangle(triangl, b, normal, color);
        insert_point_on_triangle(triangl, c, normal, color);//dbc
    }

    bool dropdetection::auto_down(const short y) {
        if (y < 0 || TETRI_HIGHT < y) {
            return false;
        }

        bool rt = false;
        for (short current_x = 0; current_x < TETRI_WIDTH; current_x++) {
            std::vector<CubePostion> vecy;
            vecy.clear();

            for (short j = y; j < TETRI_HIGHT; j++) {
                if (0 != _space_station[current_x][j]) {
                    vecy.emplace_back(current_x, j, _space_station[current_x][j]);
                    _space_station[current_x][j] = COLOR_0;
                }
            }

            if (!vecy.empty()) {
                if (0 == y) {
                    move_down(vecy, current_x, 0);
                }
                else if (0 < y) {
                    for (short j = y - 1 ; j >= 0; j--) {
                        if (0 != _space_station[current_x][j]) {//从y朝下找第一个非空位
                            move_down(vecy, current_x, j + 1);
                            rt = true;
                            break;
                        }
                    }
                    if (0 == _space_station[current_x][0]) {
                        move_down(vecy, current_x, 0);
                    }

                }
            }
        }

        return rt;
    }

    void dropdetection::move_down(std::vector<CubePostion>& vecy, const short x, const short y) {
        short down_dance = vecy[0].y - y;
        for (std::vector<CubePostion>::iterator iter = vecy.begin();
            iter != vecy.end();
            iter++) {
            iter->y -= down_dance;
            _space_station[x][iter->y] = iter->color;//颜色值非零，表示次位置有cube
        }
    }

    void dropdetection::clean_line(const short y) {
        if (y < 0 || TETRI_HIGHT < y) {
            return;
        }
        for (short i = 0; i < TETRI_WIDTH; i++) {
            _space_station[i][y] = COLOR_0;
        }
    }
}
