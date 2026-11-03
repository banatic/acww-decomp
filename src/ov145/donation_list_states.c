/* donation_list_states: 6 functions, module ov145
 * mwccarm 1.2/base -O4,s
 * func_ov145_0229a3fc @ 0x0229a3fc, 0x32 bytes, Thumb
 * func_ov145_0229a3d8 @ 0x0229a3d8, 0x24 bytes, Thumb
 * func_ov145_0229a370 @ 0x0229a370, 0x68 bytes, Thumb
 * func_ov145_0229a358 @ 0x0229a358, 0x16 bytes, Thumb
 * func_ov145_0229a330 @ 0x0229a330, 0x28 bytes, Thumb
 * func_ov145_0229a310 @ 0x0229a310, 0x20 bytes, Thumb
 */

typedef struct {
    unsigned char pad_00[0xC1];
    unsigned char c1;
    unsigned char c2;
} UnkStruct_0229a330;

extern int func_0208e484(void *);
extern int func_ov145_022998f0(void *, unsigned char);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern void func_ov145_02299e08(void *);
extern void func_ov145_02299e44(void *);
extern int func_0208e4bc(void *);
extern void func_ov145_02299ed0(void *);
extern int func_ov002_0220a700(void *);
extern int func_ov002_0220a6e0(void *);
extern int func_ov002_0220a768(void *, int);
extern int func_ov002_0220a72c(void *, int);
extern void func_ov002_0220a0b4(void *, int, int);
extern unsigned char *func_ov002_022080a0(void *object, unsigned char value);
extern void func_ov145_02299f7c(void *p);
extern void func_ov002_02207fc0(void *p);
extern int func_0206fe60(void);

void func_ov145_0229a3fc(void *self)
{
    if (func_0208e484((char *) self + 0xc8) == 0) {
        return;
    }
    if (func_ov145_022998f0(self, *(unsigned char *) ((char *) self + 0xc2)) != 0) {
        return;
    }
    func_ov002_02208098((void *) (self), 3);
    func_ov145_02299e08(self);
}

void func_ov145_0229a3d8(void *p)
{
    if (func_0208e484((char *) p + 0xc8) != 0) {
        func_ov145_02299e44(p);
        func_ov002_02208098((void *) (p), *(unsigned char *) ((char *) p + 0xc3));
    }
}

void func_ov145_0229a370(void *self)
{
    int r4, r6;
    int r2;
    void *p;

    if (func_ov002_0220a700((char *) self + 0x174) != 0) {
        if (func_0208e4bc((char *) self + 0xc8) != 0) {
            r4 = func_ov002_0220a6e0((char *) self + 0x174);
            r6 = func_ov002_0220a768((char *) self + 0x174, -1);
            r2 = func_ov002_0220a72c((char *) self + 0x174, -1);
            p = (char *) self + 0xc8;
            func_ov002_0220a0b4(p, r4 + r6, r4 + r2);
        }
    } else {
        func_ov145_02299ed0(self);
        func_ov002_022080a0((void *) (self), 1);
    }
}

void func_ov145_0229a358(void *p)
{
    func_ov145_02299ed0(p);
    func_ov002_02208098((void *) (p), 0);
}

void func_ov145_0229a330(UnkStruct_0229a330 *p)
{
    p->c2 = p->c1;
    func_ov145_02299f7c(p);
    func_ov002_02207fc0(p);
    func_ov002_02208098((void *) (p), 3);
}

void func_ov145_0229a310(int param)
{
    if (func_0206fe60() != 0) {
        func_ov145_0229a358((void *) param);
    } else {
        func_ov145_0229a330((UnkStruct_0229a330 *) param);
    }
}
