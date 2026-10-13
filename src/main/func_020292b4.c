/* func_020292b4 @ 0x020292b4, 0x444 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_020292b4 UnkStruct_020292b4;
struct UnkStruct_020292b4 {
    char pad_00[0x40];
    int unk_40;
    char pad_44[0xbc];
    void *unk_100;
    char pad_104[0x20];
    u16 unk_124;
    char pad_126[0x3e];
    int unk_164;
};

typedef struct {
    u8 zb[0x24];
} UnkStruct_020292b4_2;
typedef struct {
    u8 unk_00;
    u8 unk_01;
    u16 q[9];
    int w0;
    int w1;
} Buf;
typedef struct {
    int a, b;
} Pair8;

extern u8 data_020e54a8;
extern const int data_020c8928;
extern const int data_020c8924;
extern const Pair8 data_020d8e40;
extern const Pair8 data_020d8dc0;

extern void func_0207f1c8(void *);
extern int func_0209b5e8(void);
extern int func_0209b91c(int);
extern void func_0202d9d0(UnkStruct_020292b4 *, int);
extern int func_0202d9c4(UnkStruct_020292b4 *);
extern int func_0209bc40(int);
extern int func_0201cddc(void *);
extern int func_0209b908(int);
extern int func_020951bc(int);
extern int func_0209b914(int);
extern u16 *func_0209bb70(int);
extern void func_0209e474(int *);
extern void func_0202e118(u16 *, void *);
extern int func_0202cef4(u16 *, int, int, int);
extern int func_0202c9e8(u16 *, int, int, int, int);
extern void func_020266d8(u16 *, UnkStruct_020292b4 *, int);
extern void func_02026584(u16 *, UnkStruct_020292b4 *, int);
extern void func_0201cfb4(UnkStruct_020292b4 *, UnkStruct_020292b4_2 *);
extern void func_0201cf74(UnkStruct_020292b4 *, UnkStruct_020292b4_2 *, int, const int *, const void *);
extern void func_0201cec8(UnkStruct_020292b4 *, UnkStruct_020292b4_2 *);
extern void func_0202da74(UnkStruct_020292b4 *, Pair8);
extern void func_02068388(int, int);
extern int func_02029ef8(UnkStruct_020292b4 *, void *, int, int);
extern void func_0202a1ac(void);
extern void func_0202a15c(void);
extern int func_020296f8(UnkStruct_020292b4 *);
extern int func_02029a98(UnkStruct_020292b4 *);
extern int func_02029ca4(UnkStruct_020292b4 *);
extern int func_0207dd10(void *);
extern void func_02080864(void *, int);
extern int func_020822b0(void);
extern void func_02015dd4(UnkStruct_020292b4 *, int, u8 *, const void *, u8 *);

extern unsigned char data_020d9fa0[];
extern unsigned char data_021c1d6c[];
extern unsigned char data_021c1e14[];
extern unsigned char data_021c2c8c[];

int func_020292b4(UnkStruct_020292b4 *p, void *arg)
{
    Buf b;
    UnkStruct_020292b4_2 z;
    int ok;
    int changed;
    int key;
    int r6;
    unsigned int ok2;
    u16 hv, lv;

    ok = 0;
    func_0207f1c8(arg);
    p->unk_164 = func_0209b5e8();
    func_0202d9d0(p, func_0209b91c(p->unk_164));
    key = func_0209bc40(func_0202d9c4(p));
    if (func_0201cddc(p->unk_100) != 0xb) {
        goto end2;
    }
    if (func_020951bc(func_0209b908(p->unk_164)) != 0) {
        goto sw;
    }
    r6 = func_0209b914(p->unk_164);
    b.q[0] = *func_0209bb70(func_0202d9c4(p));
    changed = ok;
    b.w0 = changed;
    b.w1 = changed;
    func_0209e474(&b.w0);
    switch (func_0209bc40(func_0202d9c4(p))) {
        case 0:
            if ((unsigned int) (data_020e54a8 == 0) + (unsigned int) ok) {
                func_0202e118(&b.q[1], p->unk_100);
                ok2 = 0;
                hv = *(volatile u16 *) &b.q[1];
                lv = *(volatile u16 *) &b.q[1];
                if (lv >= 0x1376 && hv <= 0x1376) {
                    ok2 = 1;
                }
                if (ok2 == 0) {
                    goto end;
                }
            }
            if (r6 == 2) {
                changed = 1;
                goto end;
            }
            ok2 = 0;
            hv = *(volatile u16 *) &b.q[0];
            lv = *(volatile u16 *) &b.q[0];
            if (lv >= 0x12b0 && hv <= 0x12e7) {
                ok2 = 1;
            }
            if (ok2 != 0 && func_0202cef4(&b.q[0], 0, 0x17, ((u8 *) &b)[0x18]) != 0) {
                p->unk_124 = b.q[0];
            } else {
                func_020266d8(&b.q[2], p, r6);
                p->unk_124 = b.q[2];
            }
            ok2 = 0;
            if (p->unk_124 >= 0x12b0 && p->unk_124 <= 0x12e7) {
                ok2 = 1;
            }
            if (ok2 == 0) {
                goto end;
            }
            changed = 1;
            break;
        case 1:
            if ((unsigned int) (data_020e54a8 == 0) + (unsigned int) ok) {
                func_0202e118(&b.q[3], p->unk_100);
                ok2 = 0;
                hv = *(volatile u16 *) &b.q[3];
                lv = *(volatile u16 *) &b.q[3];
                if (lv >= 0x1374 && hv <= 0x1374) {
                    ok2 = 1;
                }
                if (ok2 == 0) {
                    goto end;
                }
            }
            if (r6 == 2) {
                changed = 1;
                goto end;
            }
            ok2 = 0;
            hv = *(volatile u16 *) &b.q[0];
            lv = *(volatile u16 *) &b.q[0];
            if (lv >= 0x12e8 && hv <= 0x131f) {
                ok2 = 1;
            }
            if (ok2 != 0 && func_0202c9e8(&b.q[0], 0, 0x17, ((u8 *) &b)[0x18], ((u8 *) &b)[0x17]) != 0) {
                p->unk_124 = b.q[0];
            } else {
                func_02026584(&b.q[4], p, r6);
                p->unk_124 = b.q[4];
            }
            ok2 = 0;
            if (p->unk_124 >= 0x12e8 && p->unk_124 <= 0x131f) {
                ok2 = 1;
            }
            if (ok2 == 0) {
                goto end;
            }
            changed = 1;
            break;
        case 2:
            if ((unsigned int) (data_020e54a8 == 0) + (unsigned int) ok) {
                func_0202e118(&b.q[5], p->unk_100);
                ok2 = 0;
                hv = *(volatile u16 *) &b.q[5];
                lv = *(volatile u16 *) &b.q[5];
                if (lv >= 0x1369 && hv <= 0x1369) {
                    ok2 = 1;
                }
                if (ok2 == 0) {
                    goto end;
                }
            }
            hv = *(volatile u16 *) &b.q[0];
            lv = *(volatile u16 *) &b.q[0];
            if (lv != 0xfff1) {
                p->unk_124 = hv;
            }
            changed = 1;
            break;
        default:
            if ((unsigned int) (data_020e54a8 == 0) + (unsigned int) ok) {
                func_0202e118(&b.q[6], p->unk_100);
                if (b.q[6] != 0xfff1) {
                    func_0202e118(&b.q[7], p->unk_100);
                    ok2 = 0;
                    hv = *(volatile u16 *) &b.q[7];
                    lv = *(volatile u16 *) &b.q[7];
                    if (lv >= 0x1380 && hv <= 0x139f) {
                        ok2 = 1;
                    }
                    if (ok2 == 0) {
                        goto end;
                    }
                }
            }
            hv = *(volatile u16 *) &b.q[0];
            lv = *(volatile u16 *) &b.q[0];
            if (lv != 0xfff1) {
                p->unk_124 = hv;
            }
            changed = 1;
            break;
    }
end:
    if (changed == 0) {
        goto end2;
    }
    {
        func_0201cfb4(p, &z);
        func_0201cf74(p, &z, 0, &data_020c8928, (const void *) data_021c2c8c);
        func_0201cf74(p, &z, 1, &data_020c8924, (const void *) data_021c1d6c);
        z.zb[0x20] = 2;
        z.zb[0x21] = (u8) (z.zb[0x20] - 1);
        func_0201cec8(p, &z);
        func_0202da74(p, data_020d8e40);
        func_02068388(p->unk_40, 1);
        ok = 1;
    }
    goto end2;
sw:
    switch (key) {
        case 0:
            ok = func_02029ef8(p, (void *) func_0202a1ac, 0x28, 0x19);
            break;
        case 1:
            ok = func_02029ef8(p, (void *) func_0202a15c, 0x29, 0x18);
            break;
        case 2:
            ok = func_020296f8(p);
            break;
        case 3:
            ok = func_02029a98(p);
            break;
        case 4:
            ok = func_02029ca4(p);
            if (ok == 1) {
                void *h = *(void **) ((char *) p->unk_100 + 0x830);
                func_02080864(h, func_0207dd10(h));
                b.unk_00 = (u8) func_020822b0();
                b.unk_01 = 0;
                func_02015dd4(p, 0, &b.unk_00, (const void *) data_020d9fa0, &b.unk_01);
            }
            break;
    }

end2:
    if (ok == 0) {
        func_0201cfb4(p, &z);
        func_0201cf74(p, &z, 0, &data_020c8928, (const void *) data_021c1e14);
        func_0201cf74(p, &z, 1, &data_020c8924, (const void *) data_021c1d6c);
        z.zb[0x20] = 2;
        z.zb[0x21] = (u8) (z.zb[0x20] - 1);
        func_0201cec8(p, &z);
        func_0202da74(p, data_020d8dc0);
        func_02068388(p->unk_40, 1);
        ok = 1;
    }
    return ok;
}
