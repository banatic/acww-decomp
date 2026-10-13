/* func_02070218 @ 0x02070218, 0x11c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct Pad {
    u16 unk_00;
    u16 unk_02;
} Pad;

extern u8 data_021dc6c4;
extern u8 data_021fbdd8;
extern u8 data_021fbddc;
extern u8 data_021f6c54;
extern u8 data_021f6c58;
extern u8 data_021cfc5c;
extern Pad data_021fbe40;

extern void func_020701a8(void);
extern void func_02070108(void);
extern void func_02070150(void);
extern void func_0206eec8(void);
extern int func_0203de78(void);
extern int func_020b65c4(void);
extern int func_0203ec98(void);
extern int func_02070094(void);
extern void func_0203e3c8(int);
extern void func_0206fe90(void);
extern void func_0206fe7c(void);
extern int func_02011ed4(void);

static __inline int chk(void)
{
    if (data_021fbdd8 != 0 && data_021fbddc != 0) {
        return 1;
    }
    return 0;
}

int func_02070218(void)
{
    int t;

    func_020701a8();
    func_02070108();
    func_02070150();
    func_0206eec8();
    if (func_0203de78()) {
        return 1;
    }
    if (func_020b65c4() == 6) {
        return 1;
    }
    if (data_021dc6c4 != 0) {
        return 1;
    }
    if (func_0203ec98()) {
        return 1;
    }
    if (func_02070094()) {
        t = chk();
        if (t && data_021f6c54 <= 0x10 && data_021f6c58 >= 0xe8) {
            func_0203e3c8(0);
            data_021cfc5c = 0;
            func_0206fe90();
            return 1;
        }
        if (data_021fbe40.unk_02 & 4) {
            func_0203e3c8(0);
            data_021cfc5c = 4;
            func_0206fe7c();
            return 1;
        }
        if (data_021fbe40.unk_02 & 0x800) {
            func_0203e3c8(0);
            data_021cfc5c = 0;
            func_0206fe7c();
            return 1;
        }
        if (func_02011ed4() != 2) {
            if (data_021fbe40.unk_02 & 0x400) {
                func_0203e3c8(0);
                data_021cfc5c = 5;
                func_0206fe7c();
                return 1;
            }
        }
    }
    return 1;
}
