/* func_ov068_0226bc1c @ 0x0226bc1c, 0x2e0 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    char pad_00[0x20];
    int unk_20;
    char pad1[0xdc - 0x24];
    short unk_DC;
    short unk_DE;
} UnkStruct_0226bc1c;

typedef struct {
    char pad_00[0x5c];
    char unk_5C[0x8e - 0x5c];
    short unk_8E;
    char pad1[0x98 - 0x90];
    int unk_98;
    char pad_9C[0x350 - 0x9c];
    char unk_350[0x3aa - 0x350];
    char unk_3AA[0x3b0 - 0x3aa];
    char unk_3B0[0x564 - 0x3b0];
    char unk_564[0x898 - 0x564];
    int unk_898;
    int unk_89C;
    char pad_8A0[0x8ac - 0x8a0];
    u16 unk_8AC;
} UnkStruct_0226bc1c_2;

extern u16 data_020c80f8;
extern char data_021cb5a0[];
extern int data_021fbee8[];

extern int func_ov068_0226ca74(UnkStruct_0226bc1c *a, UnkStruct_0226bc1c_2 *b);
extern void func_ov068_0226cce8(UnkStruct_0226bc1c *a, UnkStruct_0226bc1c_2 *b, int n);
extern int func_ov068_0226befc(UnkStruct_0226bc1c *a, UnkStruct_0226bc1c_2 *b);
extern int func_02019de8(char *w);
extern int func_0201ac28(char *p, UnkStruct_0226bc1c_2 *b);
extern void func_ov068_02266c70(int *p, UnkStruct_0226bc1c_2 *b);
extern int func_02019e00(char *w);
extern int func_0201b354(char *p);
extern void func_02019c6c(char *w, int a, int b);
extern unsigned int func_020e92e8(char *p);
extern int func_ov068_0226c6ac(UnkStruct_0226bc1c *a, int *v, UnkStruct_0226bc1c_2 *b);
extern int func_ov068_0226c754(UnkStruct_0226bc1c *a, char *p, int n);
extern int func_ov068_0226c7bc(UnkStruct_0226bc1c *a, int *v, char *p);
extern short func_0200322c(char *p, int *v);
extern int func_0201c3dc(int d);
extern int func_020644cc(int n);
extern unsigned char func_ov068_0226cf8c(UnkStruct_0226bc1c_2 *b);
extern int func_02019d0c(char *w, int a, int b, int c, int d, short e, short f, int g, int h, u16 i, u16 j);
extern int func_ov068_0226c7dc(UnkStruct_0226bc1c *a, UnkStruct_0226bc1c_2 *b);
extern int *func_0201afd0(char *p);

int func_ov068_0226bc1c(UnkStruct_0226bc1c *a, UnkStruct_0226bc1c_2 *b)
{
    char *w;
    char *p;
    int *q;
    int vec[3];
    int v2[3];
    int t;
    int v;
    short ang;
    int k;

    w = b->unk_564;
    if (func_ov068_0226ca74(a, b) == 0) {
        goto fail0;
    }
    if (func_ov068_0226befc(a, b) != 0) {
        goto done;
    }
    if (func_02019de8(w) != 0) {
        if (a->unk_DC > 0) {
            if (b->unk_898 == 0) {
                t = b->unk_89C;
                if (t != 0) {
                    if (t == 1) {
                        goto chk;
                    }
                    goto reset;
                }
            chk: {
                v = b->unk_8AC;
                if (v >= 0xf) {
                    if (v == 0) {
                        goto join;
                    }
                    if (func_0201ac28(b->unk_3B0, b) != 0) {
                        goto join;
                    }
                }
            }
            }
        reset:
            a->unk_DC = 0;
            a->unk_DE = 0x4b0;
            func_ov068_02266c70(&b->unk_898, b);
        }
    join:
        if (func_02019e00(w) == 0) {
            if (a->unk_DC != 0) {
                goto done;
            }
        }
        a->unk_DC = 0;
        if (func_0201b354(b->unk_3AA) == 2) {
            func_02019c6c(w, 1, data_020c80f8);
            goto done;
        }
        if ((func_020e92e8(data_021cb5a0) & 7) != 0) {
            goto fail7;
        }
        p = b->unk_5C;
        vec[0] = data_021fbee8[0];
        vec[1] = data_021fbee8[1];
        vec[2] = data_021fbee8[2];
        if (func_ov068_0226c6ac(a, vec, b) == 0) {
            goto fail1;
        }
        if (func_ov068_0226c754(a, p, 0xc000) != 0) {
            if (func_ov068_0226c7bc(a, vec, p) != 0) {
                goto fail1;
            }
        }
        ang = func_0200322c(p, vec);
        if (func_0201c3dc((short) (ang - b->unk_8E)) != 0) {
            k = 1;
            if (func_020644cc(4) == 0) {
                if (func_ov068_0226cf8c(b) == 0) {
                    k = 2;
                }
            }
            func_02019d0c(w, k, 1, vec[0], vec[2], 0, 0, 0, 0, data_020c80f8, 0);
            a->unk_20 = 0x100;
            goto done;
        }
        func_02019d0c(w, 4, 1, vec[0], vec[2], 0, ang, 0, 0, data_020c80f8, 0);
        a->unk_20 = 0x128;
        goto done;
    fail1:
        func_02019c6c(w, 1, data_020c80f8);
        goto done;
    fail7:
        func_02019c6c(w, 1, data_020c80f8);
        goto done;
    }
    goto other;
other:
    if (b->unk_98 == 0) {
        goto done;
    }
    if (func_02019e00(b->unk_564) != 1 && func_02019e00(b->unk_564) != 2 && func_02019e00(b->unk_564) != 4) {
        goto done;
    }
    if (a->unk_20 == 0) {
        func_02019c6c(w, 1, data_020c80f8);
        goto done;
    }
    if (a->unk_DE == 0) {
        if (b->unk_898 == 0) {
            if ((unsigned) ((char *) 0 + b->unk_89C) <= 1) {
                if ((int) b->unk_8AC > 0xf) {
                    func_02019c6c(w, 1, data_020c80f8);
                    a->unk_DC = (short) (func_020644cc(0xc8) + 0xa0);
                    a->unk_DE = 0x4b0;
                    goto done;
                }
            }
        }
    }
    if (func_ov068_0226c754(a, b->unk_5C, 0x8000) != 0) {
        if (func_ov068_0226c7dc(a, b) != 0) {
            func_02019c6c(w, 1, data_020c80f8);
            goto done;
        }
    }
    q = func_0201afd0(b->unk_350);
    v2[0] = q[0];
    v2[1] = q[1];
    v2[2] = q[2];
    if (func_0201c3dc((short) (func_0200322c(b->unk_5C, v2) - b->unk_8E)) == 0) {
        func_02019c6c(w, 1, data_020c80f8);
    }
    goto done;
fail0:
    func_ov068_0226cce8(a, b, 1);
done:
    return 0;
}
