/* func_020842b8 @ 0x020842b8, 0xc4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    u8 pad_00[0x64];
    int unk_64;
} UnkStruct_020842b8;

extern u8 data_020e54a8;
extern UnkStruct_020842b8 *data_020ccf94;
extern int data_020e1d8c;
extern void *data_020d0644;
extern int func_02084af0(void);
extern int func_02084ad0(void);
extern int func_020883cc(void);
extern int func_020b65c4(void);
extern int func_02073dd4(UnkStruct_020842b8 *h, int a);
extern int func_02085d2c(int a, int b);
extern int func_0208602c(void);
extern int func_020860c4(int);
extern int func_02087f30(void *);
extern int func_02073d90(UnkStruct_020842b8 *h);
extern int func_02084d5c(u16 *p, int *a, void *b);

int func_020842b8(int p)
{
    u16 v;
    unsigned int q;
    UnkStruct_020842b8 *h;

    if (func_02084af0() != 0) {
        goto ret0;
    }
    if (func_02084ad0() != 0) {
        goto ret0;
    }
    if (func_020883cc() != 0) {
        if (p != 0) {
            if (data_020e54a8 == 0) {
                q = 1;
            } else {
                q = 0;
            }
            if (q == 0) {
                goto L30e;
            }
            if (func_020b65c4() == 0x2c) {
                goto L30e;
            }
        }
        h = data_020ccf94;
        if (func_02073dd4(h, h->unk_64) != 0) {
            goto L30e;
        }
        if (func_02085d2c(0x3d, 0) == 0) {
            goto act;
        }
    }
L30e:
    if (func_02087f30((void *) func_020860c4((int) func_0208602c())) != 0) {
        if (func_020b65c4() == 0xb) {
            if (func_02073d90(data_020ccf94) == 0) {
                goto act;
            }
        }
    }
    if (func_02087f30((void *) func_020860c4((int) func_0208602c())) == 0) {
        goto ret0;
    }
    if (func_020b65c4() != 0xc) {
        goto ret0;
    }
act:
    v = 0xd022;
    return func_02084d5c(&v, &data_020e1d8c, data_020d0644);
ret0:
    return 0;
}
