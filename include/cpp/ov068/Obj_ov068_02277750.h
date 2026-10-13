#ifndef CPP_OV068_OBJ_OV068_02277750_H
#define CPP_OV068_OBJ_OV068_02277750_H

#include "cpp/ov009/Obj_ov009_022658dc.h"

// Arrival-sequence actor: primary vtable 0x02277750. Seventeen states share
// one index at 0x2b4: an update handler and an entry check for each.
class Obj_ov068_02277750 : public Obj_ov009_022658dc {
  public:
    virtual ~Obj_ov068_02277750();
    // Base_02066994 slots; 0x6c is also appended after that vtable
    virtual void vfunc_02066994_14(); // func_ov068_02272d5c
    virtual void vfunc_02066994_6c(); // func_ov068_02272d60

    // update handlers (table data_ov068_02278774)
    void func_ov068_022728fc();
    void func_ov068_022728a8();
    void func_ov068_0227282c();
    void func_ov068_0227276c();
    void func_ov068_022726c8();
    void func_ov068_022726a0();
    void func_ov068_02272550();
    void func_ov068_02272530();
    void func_ov068_022724b4();
    void func_ov068_02272404();
    void func_ov068_022723e0();
    void func_ov068_02272338();
    void func_ov068_0227227c();
    void func_ov068_02272208();
    void func_ov068_022721a0();
    void func_ov068_02272114();
    void func_ov068_022720b4();
    void func_ov068_02272934();

    // entry checks; a passing check moves state_2b4
    int func_ov068_02272900();
    int func_ov068_022728c4();
    int func_ov068_02272874();
    int func_ov068_022727d0();
    int func_ov068_022726d4();
    int func_ov068_022726c4();
    int func_ov068_02272654();
    int func_ov068_0227254c();
    int func_ov068_022724fc();
    int func_ov068_022724a4();
    int func_ov068_022723ec();
    int func_ov068_022723b4();
    int func_ov068_02272304();
    int func_ov068_02272238();
    int func_ov068_022721e4();
    int func_ov068_0227215c();
    int func_ov068_02272104();
    int func_ov068_02272a7c(int state);

    int state_2b4;
    char pad_2b8[0x2dd - 0x2b8];
    unsigned char unk_2dd;
};

#endif
