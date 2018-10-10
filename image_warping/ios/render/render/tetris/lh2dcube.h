#pragma once
#include "tetri_type.h"

namespace lh_gl {
    class lh2dcube
    {
    public:
        lh2dcube();
        ~lh2dcube();
    public:
        void get_tetri(CUBETYPE type, TeTriUniti&);
        void get_roate(short degrees, TeTriUniti&);
    private:
        void get_line(TeTriUniti&);
        void get_t(TeTriUniti&);
        void get_l(TeTriUniti&);
        void get_z(TeTriUniti&);
        void get_side_l(TeTriUniti&);
        void get_side_z(TeTriUniti&);
        void get_block(TeTriUniti&);
        inline void get_roate_t(short degrees, TeTriUniti&);
        inline void get_roate_z(short degrees, TeTriUniti&);
        inline void get_roate_l(short degrees, TeTriUniti&);
        inline void get_roate_z_side(short degrees, TeTriUniti&);
        inline void get_roate_l_side(short degrees, TeTriUniti&);
        inline void get_roate_line(short degrees, TeTriUniti&);
    };
}

