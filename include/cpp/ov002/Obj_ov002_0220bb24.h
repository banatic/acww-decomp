#ifndef CPP_OV002_OBJ_OV002_0220BB24_H
#define CPP_OV002_OBJ_OV002_0220BB24_H

#include "cpp/main/Obj_020da13c.h"

// Base of the small menu scenes. Each scene overlay derives one class from it and
// drives its states through pointer-to-member tables.

// vtable 0x0220bb24; the slot at 0x4c runs the scene's state table on `state`,
// some scenes run a second table on `subState`. Derived members start at 0x94.
class Obj_ov002_0220bb24 : public Obj_020da13c {
  public:
    virtual ~Obj_ov002_0220bb24();
    char pad_04[0x88];
    unsigned char state;    // 0x8c
    unsigned char subState; // 0x8d
    unsigned char unk_8E;
    unsigned char unk_8F;
    unsigned char unk_90;
    unsigned char unk_91;
    unsigned char unk_92;
    unsigned char unk_93;
};

#endif
