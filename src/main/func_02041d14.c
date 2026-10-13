/* func_02041d14 @ 0x02041d14, 0xb0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    u8 unk_00;
    u8 unk_01;
    u8 pad[2];
    u32 unk_04;
    u32 unk_08;
} UnkStruct_02041d14;
typedef void (*Fn)(void);
typedef struct {
    Fn fn;
    char pad[12];
} UnkStruct_02041d14_2;

extern UnkStruct_02041d14 data_021c75b8;
extern u8 data_021c75b0;
extern UnkStruct_02041d14_2 data_020ca518[];
extern UnkStruct_02041d14_2 data_020ca514[];
extern char *data_021c526c;

extern int FX_Div(int a, int b);
extern void func_02035e90(void *p);
extern void func_0208f97c(int a);
extern void func_0200468c(void);

int func_02041d14(int a, int b)
{
    unsigned int ok;
    Fn fn;
    int old;

    old = data_021c75b8.unk_01;
    if (data_021c75b8.unk_00 == 2) {
        ok = 1;
    } else {
        ok = 0;
    }
    if (ok == 0 && data_021c75b0 == 0) {
        return 0;
    }
    data_021c75b8.unk_00 = 3;
    data_021c75b0 = 0;
    fn = data_020ca518[old].fn;
    if (fn != 0) {
        fn();
    }
    data_021c75b8.unk_01 = (u8) a;
    data_021c75b8.unk_04 = 0;
    fn = data_020ca514[a].fn;
    if (fn != 0) {
        fn();
        func_02035e90(data_021c526c + 0x2d0);
        func_0208f97c(a);
        if (a == 2) {
            func_0200468c();
        }
    }
    if (b == 0 || a == 3) {
        data_021c75b8.unk_08 = 0x1000;
    } else {
        data_021c75b8.unk_08 = FX_Div(0x1000, b << 12);
    }
    return 1;
}
