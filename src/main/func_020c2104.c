/* func_020c2104 @ 0x020c2104, 0x1c0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Vec3;

typedef struct UnkStruct_020c2104 UnkStruct_020c2104;
struct UnkStruct_020c2104 {
    char pad_00[0x5c];
    Vec3 unk_5C;
    char pad_68[0x350 - 0x68];
    int unk_350;
    char pad_354[0x3a8 - 0x354];
    int unk_3A8;
    char pad_3AC[0x510 - 0x3ac];
    unsigned char unk_510;
    char pad_511[0x564 - 0x511];
    int unk_564;
    char pad_568[0x712 - 0x568];
    unsigned short unk_712;
    char pad_714[0x718 - 0x714];
    Vec3 unk_718;
};

extern void *func_020984e8(void);
extern int func_020b65c4(void);
extern void *func_0204e414(void);
extern int func_0204e08c(void *a, Vec3 *b, int c, int d);
extern void func_0204f7e0(Vec3 *a, Vec3 *b);
extern void func_0204f794(Vec3 *a, int b, int c);
extern void *func_02095794(int a);
extern int func_0201c378(UnkStruct_020c2104 *p, int a);
extern unsigned int func_02099688(void *a);
extern int func_0208829c(void *);
extern int func_02019e00(void *a);
extern void func_020c26b4(UnkStruct_020c2104 *p, int a);
extern int func_0201ae40(void *a);
extern int func_020ea990(void *a, void *b);
extern int func_020e8840(void *a);
extern int func_02019d0c(void *a, int b, int c, int d, int e, int f, int g, int h, int i, int j, int k);
extern void func_0201b044(void *a, void *b);
extern unsigned short data_020c80f8;

int func_020c2104(UnkStruct_020c2104 *p)
{
    Vec3 v1, v2, v3, v4;
    void *a;
    void *c;
    int b, d, e;

    a = func_020984e8();
    if (a == 0) {
        return 1;
    }
    if (p->unk_510 == 0 && func_020b65c4() == 0) {
        func_0204e08c(func_0204e414(), &v1, 0, 0);
        func_0204f7e0(&v2, &p->unk_5C);
        if (v2.z > v1.z) {
            p->unk_510 = 1;
        }
    }
    if (p->unk_510 == 0 && func_020b65c4() == 0xb) {
        func_0204f7e0(&v4, &p->unk_5C);
        func_0204f794(&v3, 6, 0xf);
        if (v4.z < v3.z) {
            p->unk_510 = 1;
        }
    }
    c = func_02095794(4);
    if (c == 0) {
        return 1;
    }
    b = func_0201c378(p, 4);
    if (func_020b65c4() != 0) {
        if (func_020b65c4() != 0xc) {
            goto lab;
        }
        if (func_0208829c((void *) func_02099688(a)) != 0) {
            goto lab;
        }
    }
    if (func_02019e00(&p->unk_564) != 2) {
        goto lab;
    }
    if (b > 0x6000) {
        func_020c26b4(p, 6);
        return 1;
    }
    d = func_0201ae40(&p->unk_3A8);
    e = func_020ea990(&p->unk_718, &p->unk_5C);
    p->unk_718.x = p->unk_5C.x;
    p->unk_718.y = p->unk_5C.y;
    p->unk_718.z = p->unk_5C.z;
    if (e <= 0x29 || d != 0) {
        if (func_020e8840(&p->unk_712) != 0) {
            goto lab;
        }
        func_020c26b4(p, 1);
        return 1;
    } else {
        p->unk_712 = 0x28;
    }
lab:
    if (b > 0x2800) {
        if (func_02019e00(&p->unk_564) != 2) {
            func_02019d0c(&p->unk_564, 2, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
        }
        func_0201b044(&p->unk_350, c);
    } else {
        if (func_02019e00(&p->unk_564) != 0) {
            func_02019d0c(&p->unk_564, 0, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
        }
    }
    return 1;
}
