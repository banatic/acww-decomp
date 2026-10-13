#ifndef CPP_OV003_OBJ_OV003_02238B10_H
#define CPP_OV003_OBJ_OV003_02238B10_H

#include "cpp/main/Obj_020dd154.h"
#include "cpp/ov009/Obj_ov009_022658dc.h"

// Outdoor scene actor: primary vtable 0x02238b10, the Base_02066994 part at 0xec
// (vtable 0x02238bd4). Instances are never freed: its operator delete is empty.
class Obj_ov003_02238b10 : public Obj_ov009_022658dc {
  public:
    virtual ~Obj_ov003_02238b10();
    static void operator delete(void *p); // func_ov003_0221ca98

    int unk_2b4;
    Obj_020dd154 unk_2b8;
};

#endif
