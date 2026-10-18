/* func_0201584c @ 0x0201584c, 0x110 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_0201584c;
typedef int (UnkStruct_0201584c::*PMF)(void);

struct UnkStruct_0201584c {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void v18();
    virtual void v19();
    virtual void v20();
    virtual void v21();
    virtual void v22();
    virtual void v23();
    virtual void v24();
    virtual void v25();
    virtual void v26();
    virtual void v27();
    virtual void v28();
    virtual void v29();
    virtual void v30();
    virtual void v31();
    virtual void v32();
    virtual void doit(int);
    u8 pad_04[0x64 - 4];
    int unk_64;
    u8 pad_68[0xad - 0x68];
    u8 unk_AD;
};

extern PMF data_020d881c;
extern PMF data_020d8844;
extern PMF data_020d86cc;
extern PMF data_020d88c4;
extern PMF data_020d8904;
extern PMF data_020d8934;
extern PMF data_020d893c;
extern PMF data_020d8954;
extern PMF data_020d896c;
extern PMF data_020d8974;
extern PMF data_020d8984;
extern PMF data_020d8994;

extern int data_021c1524;
extern PMF data_021c1814[12];

extern "C" void func_0201584c(UnkStruct_0201584c *obj)
{
    if (!(data_021c1524 & 1)) {
        data_021c1814[0] = data_020d881c;
        data_021c1814[1] = data_020d8844;
        data_021c1814[2] = data_020d86cc;
        data_021c1814[3] = data_020d88c4;
        data_021c1814[4] = data_020d8904;
        data_021c1814[5] = data_020d8934;
        data_021c1814[6] = data_020d893c;
        data_021c1814[7] = data_020d8954;
        data_021c1814[8] = data_020d896c;
        data_021c1814[9] = data_020d8974;
        data_021c1814[10] = data_020d8984;
        data_021c1814[11] = data_020d8994;
        data_021c1524 |= 1;
    }
    int idx;

    idx = obj->unk_64;
    if (idx < 12) {
        if ((obj->*data_021c1814[idx])()) {
            idx = obj->unk_64;
            obj->unk_AD = 0;
            obj->unk_64 = 0xc;
            obj->doit(idx);
        }
    }
}
