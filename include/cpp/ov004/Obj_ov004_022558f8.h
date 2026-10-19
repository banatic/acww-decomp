#ifndef CPP_OV004_OBJ_OV004_022558F8_H
#define CPP_OV004_OBJ_OV004_022558F8_H

#include "cpp/main/Base_02066994.h"
#include "cpp/main/Member_020324c4.h"
#include "cpp/main/Member_020b7f60.h"
#include "cpp/main/Member_020b82d0.h"
#include "cpp/ov004/Obj_ov004_02254b28.h"

// vtable 0x022558f8, the Base_02066994 part at 0x290
struct Obj_ov004_022558f8 : public Obj_ov004_02254b28, public Base_02066994 {
    virtual ~Obj_ov004_022558f8();
    // slots overridden here, with the function the ROM vtable holds
    virtual void vfunc_00(); // func_ov004_022316f4
    virtual void vfunc_0c(); // func_ov004_02231674
    virtual void vfunc_18(); // func_ov004_022316a4
    virtual void vfunc_24(); // func_ov004_02231690
    virtual void vfunc_48(); // func_ov004_02231614
    virtual void vfunc_4c(); // func_ov004_022315ec
    virtual void vfunc_50(); // func_ov004_022315e4
    // Base_02066994 slots; primary slots 0x68..0x70
    virtual void vfunc_02066994_10(); // func_ov004_02231590
    virtual void vfunc_02066994_14(); // func_ov004_022314dc
    virtual void vfunc_02066994_18(); // func_ov004_02231258
    char pad_2d4[0x4];
    Member_020324c4 unk_2d8;
    char pad_2dc[0x98];
    Member_020b82d0 unk_374;
    char pad_378[0x2a4];
    Member_020b7f60 unk_61c;
};

#endif
