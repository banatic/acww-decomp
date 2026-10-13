/* func_ov009_02265024 @ 0x02265024, 0xac bytes, Thumb, module ov009
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_02265024 {
    virtual int v0();
    virtual int v1();
    virtual int v2();
    virtual int v3();
    virtual int v4();
    virtual int v5();
    virtual int v6();
    virtual int v7();
    virtual int v8();
    virtual int v9();
    virtual int v10();
    virtual int v11();
    virtual int v12();
    virtual int v13();
    virtual int v14();
    virtual int v15();
    virtual int v16();
    virtual int v17();
    virtual int v18();
    virtual int v19();
    virtual int v20();
    virtual int v21();
    virtual int v22();
    virtual int v23();
    virtual int v24();
    virtual int v25();
    virtual int v26();
    virtual int v27();
    virtual int v28();
    virtual int v29();
    virtual int v30();
    virtual int v31();
    virtual int v32();
    virtual int v33();
    virtual int v34();
    virtual int v35();
    virtual int v36();
    virtual int v37();
    virtual int v38();
    virtual int v39();
    virtual int v40();
    virtual int v41();
    virtual int v42();
    virtual int v43();
    virtual int fb0();
    char pad_04[0x235 - 4];
    u8 unk_235;
    char pad_236[0x294 - 0x236];
    int unk_294;
    char pad_298[0x2a0 - 0x298];
    int unk_2A0;
    int unk_2A4;
};

extern "C" int func_020033ec(void);
extern "C" u16 *func_ov009_02262fcc(UnkStruct_02265024 *self);
extern "C" int func_0204bcdc(u16 *p);
extern "C" int func_0204bc64(u16 *p);
extern "C" int func_0203adc4(int *a, int b, int c);
extern "C" void func_ov009_022632c8(UnkStruct_02265024 *self);

extern "C" int func_ov009_02265024(UnkStruct_02265024 *self)
{
    u16 *p;
    u16 tmp;
    int r;
    unsigned int ok;
    if (func_020033ec() == 0) {
        return 0;
    }
    if ((self->unk_235 & 1) == 0) {
        p = func_ov009_02262fcc(self);
        if (func_0204bcdc(p) != 0) {
            tmp = 0x500b;
            r = func_0204bc64(p);
            ok = (r == func_0204bc64(&tmp)) ? 1 : 0;
        } else {
            ok = (*p == 0x500b) ? 1 : 0;
        }
        if (ok != 0 || func_0203adc4(&self->unk_294, self->unk_2A0, self->unk_2A4) == 0) {
            if (self->fb0() != 0) {
                func_ov009_022632c8(self);
            }
            return 1;
        }
    }
    return 0;
}
