/* spawner_3: 9 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02084388 @ 0x02084388, 0x90 bytes, Thumb
 * func_0208437c @ 0x0208437c, 0xc bytes, Thumb
 * func_020842b8 @ 0x020842b8, 0xc4 bytes, Thumb
 * func_020842ac @ 0x020842ac, 0xc bytes, Thumb
 * func_02084260 @ 0x02084260, 0x4c bytes, Thumb
 * func_02084210 @ 0x02084210, 0x50 bytes, Thumb
 * func_02084188 @ 0x02084188, 0x88 bytes, Thumb
 * func_0208417c @ 0x0208417c, 0xc bytes, Thumb
 * func_02084160 @ 0x02084160, 0x1a bytes, Thumb
 */

#include "types.h"

typedef struct {
    u8 pad_00[0x64];
    int unk_64;
} UnkStruct_020842b8;

typedef struct {
    unsigned char pad_00[0x64];
    unsigned int unk_64;
} Object;

typedef struct {
    unsigned char pad_00[0x64];
    int unk_64;
} UnkStruct_02084188;

extern int func_0209fa30(void *p);
extern int func_02073dd4(void *obj, int field);
extern int func_020b65c4(void);
extern int func_02084af0(void);
extern int func_02084ad0(void);
extern int func_02085d2c(int a, int b);
extern int func_02084d5c(unsigned short *p, void *q, void *r);
extern void *data_020ccf94;
extern unsigned char data_020e54a8;
extern char data_020e1d8c;
extern void *data_020d0644;
extern char data_021f3b85[];
extern int func_020883cc(void);
extern int func_0208602c(void);
extern int func_020860c4(int);
extern int func_02087f30(void *);
extern int func_02073d90(UnkStruct_020842b8 *h);
extern void func_02087f40(int a, int *b);
extern void func_0204f794(int *a, int b, int c);
extern void func_02087f58(void *);
extern int func_02088394(void);

// Names are inferred, not original.
int func_02084388(int param0)
{
    int ret;
    void *obj;

    ret = func_0209fa30(data_021f3b85);
    obj = data_020ccf94;

    if (func_02073dd4(obj, *(int *) ((char *) obj + 0x64)) != 0) {
        goto fail;
    }

    if (param0 != 0) {
        unsigned int flag = (data_020e54a8 == 0) ? 1 : 0;
        if (flag == 0) {
            goto fail;
        }
        if (func_020b65c4() == 0x2c) {
            goto fail;
        }
    }

    if (ret != 0) {
        goto fail;
    }

    if (func_02084af0() != 0) {
        goto fail;
    }
    if (func_02084ad0() != 0) {
        goto fail;
    }

    if (func_02085d2c(0x3b, 0) == 0) {
        goto fail;
    }

    {
        unsigned short local = 0xd002;
        return func_02084d5c(&local, &data_020e1d8c, data_020d0644);
    }

fail:
    return 0;
}

int func_0208437c(void)
{
    return func_02084388(1);
}

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
            if ((*(u8 *) &data_020e54a8) == 0) {
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
        h = (*(UnkStruct_020842b8 **) &data_020ccf94);
        if (func_02073dd4((void *) h, h->unk_64) != 0) {
            goto L30e;
        }
        if (func_02085d2c(0x3d, 0) == 0) {
            goto act;
        }
    }
L30e:
    if (func_02087f30((void *) func_020860c4((int) func_0208602c())) != 0) {
        if (func_020b65c4() == 0xb) {
            if (func_02073d90((*(UnkStruct_020842b8 **) &data_020ccf94)) == 0) {
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
    return func_02084d5c((unsigned short *) (&v), (void *) (((int *) &data_020e1d8c)), data_020d0644);
ret0:
    return 0;
}

void func_020842ac(void)
{
    func_020842b8(1);
}

int func_02084260(int unused, int *p)
{
    int flag;

    flag = data_020e54a8 ? 0 : 1;
    if (flag != 0) {
        func_02087f40(func_020860c4((int) func_0208602c()), p);
        return 1;
    } else {
        func_0204f794(p, 6, 0x11);
        *p = *p + 0x1000;
        return 1;
    }
}

void func_02084210(void *receiver)
{
    unsigned int flag;

    if (func_02073dd4((void *) ((*(Object **) &data_020ccf94)), (*(Object **) &data_020ccf94)->unk_64) == 0) {
        return;
    }
    if (func_02084af0() != 0) {
        return;
    }
    if (func_020883cc() == 0) {
        return;
    }

    flag = (data_020e54a8 != 0) ? 0 : 1;
    if (flag > 0) {
        func_02087f58((void *) func_020860c4((int) func_0208602c()));
    }
}

int func_02084188(void *arg0)
{
    unsigned short local;
    unsigned int flag;

    if (func_02088394() == 0) {
        goto fail;
    }
    if (func_02084af0() != 0) {
        goto fail;
    }
    if (func_02084ad0() != 0) {
        goto fail;
    }

    if (arg0 != 0) {
        flag = (data_020e54a8 == 0) ? 1 : 0;
        if (flag == 0) {
            goto fail;
        }
        if (func_020b65c4() == 0x2c) {
            goto fail;
        }
    }

    if (func_02073dd4((*(UnkStruct_02084188 **) &data_020ccf94), (*(UnkStruct_02084188 **) &data_020ccf94)->unk_64) != 0) {
        goto fail;
    }
    if (func_02085d2c(0x3d, 0) != 0) {
        goto fail;
    }

    local = 0xd023;
    return func_02084d5c((unsigned short *) (&local), &data_020e1d8c, (void *) ((*(int *) &data_020d0644)));

fail:
    return 0;
}

void func_0208417c(void)
{
    func_02084188((void *) 1);
}

int func_02084160(int a, int b)
{
    int x;
    int y;
    x = func_0208602c();
    y = func_020860c4(x);
    func_02087f40(y, (int *) b);
    return 1;
}
