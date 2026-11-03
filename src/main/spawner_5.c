/* spawner_5: 6 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02084b54 @ 0x02084b54, 0x1e bytes, Thumb
 * func_02084b14 @ 0x02084b14, 0x3e bytes, Thumb
 * func_02084af0 @ 0x02084af0, 0x22 bytes, Thumb
 * func_02084ad0 @ 0x02084ad0, 0x20 bytes, Thumb
 * func_02084a78 @ 0x02084a78, 0x58 bytes, Thumb
 * func_020849e8 @ 0x020849e8, 0x90 bytes, Thumb
 */

#include "types.h"

typedef struct {
    char unk_00[0x70];
    unsigned char unk_70;
    void *unk_74;
} UnkStruct_02084b54;

typedef struct {
    char pad_00[0x64];
    int unk_64;
} UnkStruct_02084a78;

typedef struct {
    char pad_00[8];
    int unk_08;
} UnkStruct_020849e8;

extern void func_0204f8ec(void *);
extern void func_02084d84(void *);
extern void func_0209e474(void *);
extern int func_02085d2c(void *, void *);
extern int func_020984e8(void);
extern int func_02099020(int arg1, int arg2);
extern int func_020b22b8(void);
extern int func_020b22dc(void);
extern UnkStruct_02084a78 *data_020ccf94;
extern int data_020d0644;
extern int func_020b65c4(void);
extern int func_0208602c(void);
extern int func_020860c8(int);
extern int func_02087ea0(unsigned char *);
extern int func_02073dd4(UnkStruct_02084a78 *, int);
extern int func_02084d5c(void *, void *, int);
extern char data_020e1d8c[];
extern u8 data_020e54a8;
extern void *data_021c80bc;
extern int func_0204f490(void *, int *, int *, int *, int *, u16 *, u16 *, int, int);
extern void func_0204f7ac(int a, int b, int c, int d, int e);

void func_02084b54(UnkStruct_02084b54 *self)
{
    if (self->unk_70) {
        func_0204f8ec(self->unk_74);
        func_02084d84(self);
    }
}

int func_02084b14(void *p, int n)
{
    int i;
    void *sp;
    int arr[2];
    int *q;

    arr[0] = 0;
    arr[1] = 0;
    sp = arr;
    func_0209e474(sp);
    i = 0;
    q = arr;
    while (i < n) {
        if (func_02085d2c(*(void **) p, q) != 0) {
            return i;
        }
        p = (char *) p + 8;
        i++;
    }
    return -1;
}

int func_02084af0(void)
{
    int result = func_020984e8();
    return result && func_02099020(result, 1);
}

int func_02084ad0(void)
{
    if (func_020b22b8() != 0 || func_020b22dc() != 0) {
        return 1;
    } else {
        return 0;
    }
}

int func_02084a78(void)
{
    if (func_020b65c4() != 0) {
        goto ret0;
    }
    if (func_02087ea0((unsigned char *) func_020860c8((int) func_0208602c())) == 0) {
        goto ret0;
    }
    if (func_02073dd4(data_020ccf94, data_020ccf94->unk_64) != 0) {
        goto ret0;
    }
    {
        unsigned short local = 0xd011;
        return func_02084d5c(&local, data_020e1d8c, data_020d0644);
    }
ret0:
    return 0;
}

int func_020849e8(void *unused, UnkStruct_020849e8 *self)
{
    unsigned int ok;
    void *g;
    u16 pair[2];
    int v4, v5, v6, v7;

    ok = (data_020e54a8 == 0) ? 1 : 0;
    if (ok != 0) {
        g = data_021c80bc;
        v4 = 0;
        v5 = 0;
        v6 = 0;
        v7 = 0;
        if (g != 0) {
            pair[0] = 0x5014;
            pair[1] = 0x501a;
            if (func_0204f490(g, &v4, &v5, &v6, &v7, &pair[0], &pair[1], 1, 0) != 0) {
                func_0204f7ac((int) self, v4, v5, v6, v7);
                self->unk_08 += 0x4000;
                return 1;
            }
        }
    }
    return 0;
}
