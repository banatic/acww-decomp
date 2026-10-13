/* func_ov003_02232c70 @ 0x02232c70, 0xc0 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    char pad_00[0x64];
    int unk_64;
} UnkStruct_02232c70;
extern UnkStruct_02232c70 *data_020ccf94;

extern int func_ov003_022353e0(void *self, int *p);
extern int func_ov003_02232598(void *self, int a);
extern void func_ov003_02230f60(void *self);
extern void func_ov003_02233e4c(void *self, int *v);
extern void func_020550e4(void *p, int a);
extern int func_0200322c(int *p, int *v);
extern int func_02073dd4(void *a, int b);
extern int func_020a7278(void);
extern void func_ov003_02235834(void *self, int a, int b);

void func_ov003_02232c70(char *self)
{
    int v[4];
    short n;
    int *p;

    n = *(short *) (self + 0x232);
    p = (int *) (self + 0x204);
    if (func_ov003_022353e0(self, p) != 0) {
        n = 1;
    }
    if (n <= 0) {
        if (func_ov003_02232598(self, 1) != 0) {
            func_ov003_02230f60(self);
        }
    } else {
        func_ov003_02233e4c(self, v);
        if (v[0] != 0) {
            *(short *) (self + 0x232) = n - 1;
            if (*(u8 *) (self + 0x254) < *(u8 *) (self + 0x255)) {
                *(u8 *) (self + 0x251) = 4;
                func_020550e4(self + 0x50, 1);
                *(short *) (self + 0x23a) = func_0200322c(p, v) + 0x8000;
                if (func_02073dd4(data_020ccf94, data_020ccf94->unk_64) != 0 && func_020a7278() != 0) {
                    func_ov003_02235834(self, *(short *) (self + 0x23a), 0xc000);
                }
            }
        }
    }
}
