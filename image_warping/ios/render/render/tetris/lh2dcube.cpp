#include "lh2dcube.h"

namespace lh_gl {
    lh2dcube::lh2dcube()
    {
    }


    lh2dcube::~lh2dcube()
    {
    }

    void lh2dcube::get_tetri(CUBETYPE type, TeTriUniti& tetri) {
        switch (type)
        {
        case CUBE_TYPE_BLOCK:
            get_block(tetri);
            break;
        case CUBE_TYPE_SIDE_Z:
            get_side_z(tetri);
            break;
        case CUBE_TYPE_SIDE_L:
            get_side_l(tetri);
            break;
        case CUBE_TYPE_Z:
            get_z(tetri);
            break;
        case CUBE_TYPE_L:
            get_l(tetri);
            break;
        case CUBE_TYPE_T:
            get_t(tetri);
            break;
        case CUBE_TYPE_LINE:
            get_line(tetri);
            break;
        default:
            break;
        }
    }
    void lh2dcube::get_line(TeTriUniti& tetri) {
        /*
         abcd
        */
        for (int i = 0; i < 4; i++) {
            tetri.postion[i][0] = TETRI_WIDTH_HALF + i;
            tetri.postion[i][1] = TETRI_HIGHT -1;
        }
        tetri.type = CUBE_TYPE_LINE;
    }
    void lh2dcube::get_t(TeTriUniti& tetri) {
        /*
          d
        abc
        */
        for (int i = 0; i < 3; i++) {
            tetri.postion[i][0] = TETRI_WIDTH_HALF + i;
            tetri.postion[i][1] = TETRI_HIGHT - 1;
        }

        tetri.postion[3][0] = TETRI_WIDTH_HALF + 1;
        tetri.postion[3][1] = TETRI_HIGHT;
        tetri.type = CUBE_TYPE_T;
    }
    void lh2dcube::get_l(TeTriUniti& tetri) {
        /*
            d
        abc
        */
        for (int i = 0; i < 3; i++) {
            tetri.postion[i][0] = TETRI_WIDTH_HALF + i;
            tetri.postion[i][1] = TETRI_HIGHT - 1;
        }

        tetri.postion[3][0] = TETRI_WIDTH_HALF + 2;
        tetri.postion[3][1] = TETRI_HIGHT;
        tetri.type = CUBE_TYPE_L;
    }

    void lh2dcube::get_side_l(TeTriUniti& tetri) {
        /*
        d
        abc
        */
        for (int i = 0; i < 3; i++) {
            tetri.postion[i][0] = TETRI_WIDTH_HALF + i;
            tetri.postion[i][1] = TETRI_HIGHT - 1;
        }

        tetri.postion[3][0] = TETRI_WIDTH_HALF;
        tetri.postion[3][1] = TETRI_HIGHT;
        tetri.type = CUBE_TYPE_SIDE_L;
    }
    
    void lh2dcube::get_z(TeTriUniti& tetri) {
        /*
        ab
          cd
        */
        tetri.postion[0][0] = TETRI_WIDTH_HALF;
        tetri.postion[0][1] = TETRI_HIGHT;

        tetri.postion[1][0] = TETRI_WIDTH_HALF + 1;
        tetri.postion[1][1] = TETRI_HIGHT;

        tetri.postion[2][0] = TETRI_WIDTH_HALF + 1;
        tetri.postion[2][1] = TETRI_HIGHT - 1;

        tetri.postion[3][0] = TETRI_WIDTH_HALF + 2;
        tetri.postion[3][1] = TETRI_HIGHT - 1;
        tetri.type = CUBE_TYPE_Z;
    }
    void lh2dcube::get_side_z(TeTriUniti& tetri) {
        /*
          cd
        ab
        */
        tetri.postion[0][0] = TETRI_WIDTH_HALF;
        tetri.postion[0][1] = TETRI_HIGHT - 1;

        tetri.postion[1][0] = TETRI_WIDTH_HALF + 1;
        tetri.postion[1][1] = TETRI_HIGHT - 1;

        tetri.postion[2][0] = TETRI_WIDTH_HALF + 1;
        tetri.postion[2][1] = TETRI_HIGHT;

        tetri.postion[3][0] = TETRI_WIDTH_HALF + 2;
        tetri.postion[3][1] = TETRI_HIGHT;
        tetri.type = CUBE_TYPE_SIDE_Z;
    }

    void lh2dcube::get_block(TeTriUniti& tetri) {
        /*
        cd
        ab
        */
        tetri.postion[0][0] = TETRI_WIDTH_HALF;
        tetri.postion[0][1] = TETRI_HIGHT - 1;

        tetri.postion[1][0] = TETRI_WIDTH_HALF + 1;
        tetri.postion[1][1] = TETRI_HIGHT - 1;

        tetri.postion[2][0] = TETRI_WIDTH_HALF;
        tetri.postion[2][1] = TETRI_HIGHT;

        tetri.postion[3][0] = TETRI_WIDTH_HALF + 1;
        tetri.postion[3][1] = TETRI_HIGHT;
        tetri.type = CUBE_TYPE_BLOCK;
    }
    void lh2dcube::get_roate(short degrees, TeTriUniti& tetri) {
        switch (tetri.type)
        {
            case CUBE_TYPE_BLOCK:
                break;
            case CUBE_TYPE_SIDE_Z:
                get_roate_z(degrees, tetri);
                break;
            case CUBE_TYPE_SIDE_L:
                get_roate_l(degrees, tetri);
                break;
            case CUBE_TYPE_Z:
                get_roate_z_side(degrees, tetri);
                break;
            case CUBE_TYPE_L:
                get_roate_l_side(degrees, tetri);
                break;
            case CUBE_TYPE_T:
                get_roate_t(degrees, tetri);
                break;
            case CUBE_TYPE_LINE:
                get_roate_line(degrees, tetri);
                break;
        default:
            break;
        }
    }

    //b点作为轴心不动点
    void lh2dcube::get_roate_t(short degrees, TeTriUniti& tetri) {
        switch (degrees)
        {
        case ROATE_DEGREES_0:
        {
            tetri.postion[0][0] = tetri.postion[1][0] - 1;
            tetri.postion[0][1] = tetri.postion[1][1];

            tetri.postion[2][0] = tetri.postion[1][0] + 1;
            tetri.postion[2][1] = tetri.postion[1][1];

            tetri.postion[3][0] = tetri.postion[1][0];
            tetri.postion[3][1] = tetri.postion[1][1] + 1;
        }
        break;
        case ROATE_DEGREES_90:
        {
            tetri.postion[0][0] = tetri.postion[1][0];
            tetri.postion[0][1] = tetri.postion[1][1] - 1;

            tetri.postion[2][0] = tetri.postion[1][0];
            tetri.postion[2][1] = tetri.postion[1][1] + 1;

            tetri.postion[3][0] = tetri.postion[1][0] - 1;
            tetri.postion[3][1] = tetri.postion[1][1];
        }
        break;
        case ROATE_DEGREES_180:
        {
            tetri.postion[0][0] = tetri.postion[1][0] + 1;
            tetri.postion[0][1] = tetri.postion[1][1];

            tetri.postion[2][0] = tetri.postion[1][0] - 1;
            tetri.postion[2][1] = tetri.postion[1][1];

            tetri.postion[3][0] = tetri.postion[1][0];
            tetri.postion[3][1] = tetri.postion[1][1] - 1;
        }
        break;
        case ROATE_DEGREES_270:
        {
            tetri.postion[0][0] = tetri.postion[1][0];
            tetri.postion[0][1] = tetri.postion[1][1] + 1;

            tetri.postion[2][0] = tetri.postion[1][0];
            tetri.postion[2][1] = tetri.postion[1][1] - 1;

            tetri.postion[3][0] = tetri.postion[1][0] + 1;
            tetri.postion[3][1] = tetri.postion[1][1];
        }
        break;
        default:
            break;
        }
    }
    void lh2dcube::get_roate_z(short degrees, TeTriUniti& tetri) {
        switch (degrees)
        {
        case ROATE_DEGREES_0:
        case ROATE_DEGREES_180:
        {
            tetri.postion[0][0] = tetri.postion[1][0] - 1;
            tetri.postion[0][1] = tetri.postion[1][1];

            tetri.postion[2][0] = tetri.postion[1][0];
            tetri.postion[2][1] = tetri.postion[1][1] - 1;

            tetri.postion[3][0] = tetri.postion[1][0] + 1;
            tetri.postion[3][1] = tetri.postion[1][1] - 1;
        }
        break;
        case ROATE_DEGREES_90:
        case ROATE_DEGREES_270:
        {
            tetri.postion[0][0] = tetri.postion[1][0];
            tetri.postion[0][1] = tetri.postion[1][1] - 1;

            tetri.postion[2][0] = tetri.postion[1][0] + 1;
            tetri.postion[2][1] = tetri.postion[1][1];

            tetri.postion[3][0] = tetri.postion[1][0] + 1;
            tetri.postion[3][1] = tetri.postion[1][1] + 1;
        }
        break;
        default:
            break;
        }
    }
    void lh2dcube::get_roate_l(short degrees, TeTriUniti& tetri) {
        switch (degrees)
        {
        case ROATE_DEGREES_0:
        {
            tetri.postion[0][0] = tetri.postion[1][0] - 1;
            tetri.postion[0][1] = tetri.postion[1][1];

            tetri.postion[2][0] = tetri.postion[1][0] + 1;
            tetri.postion[2][1] = tetri.postion[1][1];

            tetri.postion[3][0] = tetri.postion[1][0] + 1;
            tetri.postion[3][1] = tetri.postion[1][1] + 1;
        }
        break;
        case ROATE_DEGREES_90:
        {
            tetri.postion[0][0] = tetri.postion[1][0];
            tetri.postion[0][1] = tetri.postion[1][1] - 1;

            tetri.postion[2][0] = tetri.postion[1][0];
            tetri.postion[2][1] = tetri.postion[1][1] + 1;

            tetri.postion[3][0] = tetri.postion[1][0] - 1;
            tetri.postion[3][1] = tetri.postion[1][1] + 1;
        }
        break;
        case ROATE_DEGREES_180:
        {
            tetri.postion[0][0] = tetri.postion[1][0] + 1;
            tetri.postion[0][1] = tetri.postion[1][1];

            tetri.postion[2][0] = tetri.postion[1][0] - 1;
            tetri.postion[2][1] = tetri.postion[1][1];

            tetri.postion[3][0] = tetri.postion[1][0] - 1;
            tetri.postion[3][1] = tetri.postion[1][1] + 1;
        }
        break;
        case ROATE_DEGREES_270:
        {
            tetri.postion[0][0] = tetri.postion[1][0];
            tetri.postion[0][1] = tetri.postion[1][1] + 1;

            tetri.postion[2][0] = tetri.postion[1][0];
            tetri.postion[2][1] = tetri.postion[1][1] - 1;

            tetri.postion[3][0] = tetri.postion[1][0] + 1;
            tetri.postion[3][1] = tetri.postion[1][1] - 1;
        }
        break;
        default:
            break;
        }
    }
    void lh2dcube::get_roate_z_side(short degrees, TeTriUniti& tetri) {
        switch (degrees)
        {
        case ROATE_DEGREES_0:
        case ROATE_DEGREES_180:
        {
            tetri.postion[0][0] = tetri.postion[1][0] - 1;
            tetri.postion[0][1] = tetri.postion[1][1];

            tetri.postion[2][0] = tetri.postion[1][0];
            tetri.postion[2][1] = tetri.postion[1][1] + 1;

            tetri.postion[3][0] = tetri.postion[1][0] + 1;
            tetri.postion[3][1] = tetri.postion[1][1] + 1;
        }
        break;
        case ROATE_DEGREES_90:
        case ROATE_DEGREES_270:
        {
            tetri.postion[0][0] = tetri.postion[1][0];
            tetri.postion[0][1] = tetri.postion[1][1] - 1;

            tetri.postion[2][0] = tetri.postion[1][0] - 1;
            tetri.postion[2][1] = tetri.postion[1][1];

            tetri.postion[3][0] = tetri.postion[1][0] - 1;
            tetri.postion[3][1] = tetri.postion[1][1] + 1;
        }
        break;
        default:
            break;
        }
    }
    void lh2dcube::get_roate_l_side(short degrees, TeTriUniti& tetri) {
        switch (degrees)
        {
        case ROATE_DEGREES_0:
        {
            tetri.postion[0][0] = tetri.postion[1][0] - 1;
            tetri.postion[0][1] = tetri.postion[1][1];

            tetri.postion[2][0] = tetri.postion[1][0] + 1;
            tetri.postion[2][1] = tetri.postion[1][1];

            tetri.postion[3][0] = tetri.postion[1][0] - 1;
            tetri.postion[3][1] = tetri.postion[1][1] + 1;
        }
        break;
        case ROATE_DEGREES_90:
        {
            tetri.postion[0][0] = tetri.postion[1][0];
            tetri.postion[0][1] = tetri.postion[1][1] - 1;

            tetri.postion[2][0] = tetri.postion[1][0];
            tetri.postion[2][1] = tetri.postion[1][1] + 1;

            tetri.postion[3][0] = tetri.postion[1][0] - 1;
            tetri.postion[3][1] = tetri.postion[1][1] - 1;
        }
        break;
        case ROATE_DEGREES_180:
        {
            tetri.postion[0][0] = tetri.postion[1][0] + 1;
            tetri.postion[0][1] = tetri.postion[1][1];

            tetri.postion[2][0] = tetri.postion[1][0] - 1;
            tetri.postion[2][1] = tetri.postion[1][1];

            tetri.postion[3][0] = tetri.postion[1][0] + 1;
            tetri.postion[3][1] = tetri.postion[1][1] - 1;
        }
        break;
        case ROATE_DEGREES_270:
        {
            tetri.postion[0][0] = tetri.postion[1][0];
            tetri.postion[0][1] = tetri.postion[1][1] + 1;

            tetri.postion[2][0] = tetri.postion[1][0];
            tetri.postion[2][1] = tetri.postion[1][1] - 1;

            tetri.postion[3][0] = tetri.postion[1][0] + 1;
            tetri.postion[3][1] = tetri.postion[1][1] + 1;
        }
        break;
        default:
            break;
        }
    }

    void lh2dcube::get_roate_line(short degrees, TeTriUniti& tetri) {
        /*
        abcd
        */
        switch (degrees)
        {
        case ROATE_DEGREES_0:
        case ROATE_DEGREES_180:
        {
            tetri.postion[0][0] = tetri.postion[1][0] - 1;
            tetri.postion[0][1] = tetri.postion[1][1];

            tetri.postion[2][0] = tetri.postion[1][0] + 1;
            tetri.postion[2][1] = tetri.postion[1][1];

            tetri.postion[3][0] = tetri.postion[1][0] + 2;
            tetri.postion[3][1] = tetri.postion[1][1];
        }
        break;
        case ROATE_DEGREES_90:
        case ROATE_DEGREES_270:
        {
            tetri.postion[0][0] = tetri.postion[1][0];
            tetri.postion[0][1] = tetri.postion[1][1] - 1;

            tetri.postion[2][0] = tetri.postion[1][0];
            tetri.postion[2][1] = tetri.postion[1][1] + 1;

            tetri.postion[3][0] = tetri.postion[1][0];
            tetri.postion[3][1] = tetri.postion[1][1] + 2;
        }
        break;
        default:
            break;
        }
    }
}
