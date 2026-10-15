/* func_020a03e0 @ 0x020a03e0, 0x208 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_020a03e0 UnkStruct_020a03e0;
struct UnkStruct_020a03e0 {
    char pad_00[0xb8];
    void *unk_B8;
    char pad_BC[0xef - (0xb8 + 4)];
    unsigned char unk_EF;
    char pad_F0[0x10e - (0xef + 1)];
    struct {
        unsigned char lo : 4;
        unsigned char hi : 4;
    } unk_10E;
};

extern int func_02073fdc(int a);
extern void func_02074078(void);
extern int func_020a238c(void *self);
extern int func_020a19c0(int unused, int idx);
extern int func_020a2120(void *p, int idx);
extern void func_020a2468(int p0);
extern void func_020a24ac(void);
extern void func_020a0b94(void);
extern void func_02088368(void);
extern void func_0209fb54(void *p);
extern void func_0209fb4c(void *p);
extern int func_02075aa4(int a, int b);
extern void func_020a1224(void *base);
extern void MI_CpuCopy8(const void *src, void *dest, unsigned int size);

extern unsigned char data_021dc7a8[];
extern unsigned char data_021f3ba0[];

int func_020a03e0(UnkStruct_020a03e0 *p, unsigned char *q, int a, int b, unsigned char c, unsigned char d, unsigned char e,
                  int f)
{
    int r;
    unsigned char v;
    int lf = f;

    if (*q == a) {
        if (func_02073fdc(lf) != 0) {
            func_02074078();
            return 0x20;
        }
        r = func_020a238c(p);
        if (r == 1) {
            *q = (unsigned char) b;
            goto out;
        }
        if (r == 3) {
            goto out;
        }
        MI_CpuCopy8((void *) data_021dc7a8, p->unk_B8, 0x173fc);
        *q = (unsigned char) (a + 1);
        goto out;
    }
    if (*q == a + 1) {
        if (func_02073fdc(lf) != 0) {
            func_02074078();
            return 0x20;
        }
        r = func_020a19c0((int) p, p->unk_10E.lo);
        if (r == 1) {
            *q = (unsigned char) b;
            goto out;
        }
        if (r != 0) {
            goto out;
        }
        if (d) {
            func_020a2468((int) p);
        }
        asm { add r0, p, #0 }
        func_020a24ac();
        if (d) {
            asm { add r0, p, #0 }
            func_020a0b94();
            func_02088368();
        }
        func_0209fb54((void *) data_021f3ba0);
        *q = (unsigned char) (a + 2);
        goto out;
    }
    if (*q == a + 2) {
        if (func_02073fdc(lf) != 0) {
            func_02074078();
            return 0x20;
        }
        r = func_020a2120(p, p->unk_10E.hi);
        if (r == 1) {
            *q = (unsigned char) b;
            goto out;
        }
        if (r != 0) {
            goto out;
        }
        *q = (unsigned char) (a + 3);
        goto out;
    }
    if (*q == a + 3) {
        if (func_02073fdc(lf) != 0) {
            func_02074078();
            return 0x20;
        }
        if (func_02075aa4(1, 1) == 0) {
            goto out;
        }
        *q = (unsigned char) (a + 4);
        goto out;
    }
    if (*q == a + 4) {
        if (func_02073fdc(lf) != 0) {
            func_02074078();
            return 0x20;
        }
        v = p->unk_EF;
        if (v == 1) {
            func_020a1224(p);
            func_0209fb4c((void *) data_021f3ba0);
            *q = (unsigned char) (a + 5);
            goto out;
        }
        if (v == 2) {
            *q = (unsigned char) c;
            goto out;
        }
        goto out;
    }
    if (*q == a + 5) {
        if (func_02073fdc(lf) != 0) {
            func_02074078();
            return 0x20;
        }
        r = func_020a2120(p, p->unk_10E.hi);
        if (r == 1) {
            *q = (unsigned char) b;
            goto out;
        }
        if (r != 0) {
            goto out;
        }
        if (e) {
            MI_CpuCopy8(p->unk_B8, (void *) data_021dc7a8, 0x173fc);
        }
        *q = (unsigned char) (a + 6);
        goto out;
    }
    if (*q == a + 6) {
        if (func_02073fdc(lf) != 0) {
            func_02074078();
            return 0x20;
        }
        if (func_02075aa4(1, 1) == 0) {
            goto out;
        }
        *q = (unsigned char) (a + 7);
        goto out;
    }
    if (*q == a + 7) {
        if (func_02073fdc(lf) != 0) {
            func_02074078();
            return 0x20;
        }
        v = p->unk_EF;
        if (v == 1) {
            *q = (unsigned char) (a + 8);
            goto out;
        }
        if (v == 2) {
            *q = (unsigned char) c;
            goto out;
        }
        goto out;
    }
out:
    return 0x20;
}
