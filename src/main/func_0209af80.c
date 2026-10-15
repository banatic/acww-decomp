/* func_0209af80 @ 0x0209af80, 0xc4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0xc];
    unsigned char unk_0C;
} Func_0209af80_ObjA;

typedef struct {
    unsigned short h;
} Func_0209af80_ObjB;

extern int func_020984e8(void);
extern int func_02099870(int);
extern int func_02094ffc(int);
extern int func_0209bd44(Func_0209af80_ObjA *);
extern int func_0209bba0(Func_0209af80_ObjA *);
extern int func_0204bcdc(void *);
extern int func_0204bc64(void *);
extern unsigned short data_020d1a54[];

int func_0209af80(Func_0209af80_ObjA *a, Func_0209af80_ObjB *b)
{
    int v;
    int range;
    int ret;
    unsigned short t;
    unsigned short tmp;

    if (a->unk_0C >= 5) {
        goto fail;
    }

    v = func_020984e8();
    if (v == 0) {
        goto fail;
    }

    if (func_02094ffc(func_02099870(func_020984e8())) != 0) {
        goto fail;
    }

    if (((b->h & 0xF000) >> 12) != 0xD) {
        goto fail;
    }

    if (func_0209bd44(a) == 0) {
        goto fail;
    }

    if (func_0209bba0(a) != 0) {
        goto fail;
    }

    range = 0;
    if (b->h >= 0xD019 && b->h <= 0xD01C) {
        range = 1;
    }

    if (range != 0) {
        if (a->unk_0C != 0) {
            goto fail;
        }
        return 1;
    }

    t = data_020d1a54[a->unk_0C];

    if (func_0204bcdc(b) != 0) {
        tmp = t;
        ret = (func_0204bc64(b) == func_0204bc64(&tmp));
    } else {
        ret = (b->h == t);
    }

    if (ret == 0) {
        goto fail;
    }
    return 1;

fail:
    return 0;
}
