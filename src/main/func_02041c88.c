/* func_02041c88 @ 0x02041c88, 0x8c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    u8 unk_00;
    u8 unk_01;
    u8 pad[2];
    u32 unk_04;
    u32 unk_08;
} UnkStruct_02041c88;
typedef void (*Fn)(void);
typedef struct {
    Fn fn;
    char pad[12];
} UnkStruct_02041c88_2;

extern UnkStruct_02041c88 data_021c75b8;
extern UnkStruct_02041c88_2 data_020ca514[];
extern char *data_021c526c;

extern void func_02041b74(void);
extern int FX_Div(int a, int b);
extern void func_02035dcc(void *p);
extern void func_0208f95c(int a);

int func_02041c88(int a, int b, int c)
{
    unsigned int ok;
    Fn fn;

    if (data_021c75b8.unk_00 == 0) {
        ok = 1;
    } else {
        ok = 0;
    }
    if (ok == 0) {
        return 0;
    }
    func_02041b74();
    data_021c75b8.unk_00 = 1;
    data_021c75b8.unk_01 = (u8) a;
    data_021c75b8.unk_04 = 0x1000;
    fn = data_020ca514[a].fn;
    if (fn != 0) {
        fn();
    }
    if (b == 0 || a == 3) {
        data_021c75b8.unk_08 = 0xfffff000;
    } else {
        data_021c75b8.unk_08 = FX_Div(0xfffff000, b << 12);
    }
    if (c == 0) {
        func_02035dcc(data_021c526c + 0x2d0);
        func_0208f95c(a);
    }
    return 1;
}
