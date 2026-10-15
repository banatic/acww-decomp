/* func_ov004_022346a0 @ 0x022346a0, 0x6c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_022346a0 {
    int a;
    ~UnkStruct_022346a0() {}
};

extern "C" {
extern u8 data_ov004_022593a4;
extern u8 data_ov004_02255c30;
extern char *data_ov004_022594d4[];
extern void *data_021fbe94;
extern void func_ov004_02235374(void *, int);
extern void func_020e993c(void *, void *);
extern int func_0209d138(void *);
extern void func_02004644(int, int);
}
extern "C" int func_ov004_022346a0(char *self)
{
    UnkStruct_022346a0 t;
    int i = data_ov004_022593a4;
    while (i < (int) data_ov004_02255c30) {
        char **e = &data_ov004_022594d4[i];
        if (*e != 0) {
            func_ov004_02235374(self, i);
            func_020e993c(data_021fbe94, *e);
            *e = 0;
        }
        i++;
    }
    func_0209d138(self + 0x7f8);
    func_02004644(0x4da, 1);
    return 1;
}
