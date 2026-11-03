/* block_021d27ac: 15 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02086198 @ 0x02086198, 0x42 bytes, Thumb
 * func_02086158 @ 0x02086158, 0x40 bytes, Thumb
 * func_02086130 @ 0x02086130, 0x28 bytes, Thumb
 * func_02086108 @ 0x02086108, 0x26 bytes, Thumb
 * func_020860f0 @ 0x020860f0, 0x18 bytes, Thumb
 * func_020860d4 @ 0x020860d4, 0x1a bytes, Thumb
 * func_020860d0 @ 0x020860d0, 0x4 bytes, Thumb
 * func_020860cc @ 0x020860cc, 0x4 bytes, Thumb
 * func_020860c8 @ 0x020860c8, 0x4 bytes, Thumb
 * func_020860c4 @ 0x020860c4, 0x4 bytes, Thumb
 * func_020860c0 @ 0x020860c0, 0x4 bytes, Thumb
 * func_020860bc @ 0x020860bc, 0x4 bytes, Thumb
 * func_020860b8 @ 0x020860b8, 0x4 bytes, Thumb
 * func_02086034 @ 0x02086034, 0x84 bytes, Thumb
 * func_0208602c @ 0x0208602c, 0x8 bytes, Thumb
 */

extern void func_02087a74(void *);
extern void func_020881a8(void *);
extern void func_02087f18(void *);
extern void func_02087e98(void *);
extern void func_02087e74(void *);
extern void func_02087ebc(void *);
extern void func_02087b88(void *);
extern void func_02087b84(char *);
extern void func_02087eb8(char *);
extern void func_02087e70(char *);
extern void func_02087e94(char *);
extern void func_02087f14(char *);
extern void func_020881a4(char *);
extern void func_02087a70(char *);
extern void func_02087f0c(void *);
extern void func_02087b78(void *);
extern void func_02087a64(void *);
extern void MI_CpuFill8(void *, int, int);
extern void *func_020984e8(void);
extern int func_02099870(void *);
extern int func_020951bc(void *);
extern int func_02099020(void *, int);
extern int func_0203cc38(void);
extern int func_0203cc1c(void);
extern void func_0209e474(void *);
extern void MI_CpuCopy8(void *, void *, unsigned int);
extern int func_0203fc78(int, void *, int);
extern int data_021d27ac;

void *func_02086198(void *self)
{
    func_02087a74((char *) self + 4);
    func_020881a8((char *) self + 0xc);
    func_02087f18((char *) self + 0x18);
    func_02087e98((char *) self + 0x20);
    func_02087e74((char *) self + 0x24);
    func_02087ebc((char *) self + 0x30);
    func_02087b88((char *) self + 0x31);
    return self;
}

char *func_02086158(char *p)
{
    func_02087b84(p + 0x31);
    func_02087eb8(p + 0x30);
    func_02087e70(p + 0x24);
    func_02087e94(p + 0x20);
    func_02087f14(p + 0x18);
    func_020881a4(p + 0xc);
    func_02087a70(p + 4);
    return p;
}

void func_02086130(void *arg0)
{
    void *r4 = arg0;
    func_02087f0c((char *) r4 + 0x18);
    MI_CpuFill8(r4, 0, 4);
    func_02087b78((char *) r4 + 0x31);
    func_02087a64((char *) r4 + 4);
}

int func_02086108(volatile unsigned int *p0, unsigned int p1)
{
    int idx = p1 >> 5;
    int bit = p1 & 0x1f;
    return (idx < 1) && (((1 << bit) & p0[idx]) != 0);
}

void func_020860f0(volatile unsigned int *p0, unsigned int p1)
{
    int idx = p1 >> 5;
    int bit = p1 & 0x1f;
    if (idx < 1) {
        p0[idx] = (1 << bit) | p0[idx];
    }
}

void func_020860d4(volatile unsigned int *p0, unsigned int p1)
{
    int idx = p1 >> 5;
    int bit = p1 & 0x1f;
    if (idx < 1) {
        p0[idx] = ~(1 << bit) & p0[idx];
    }
}

int func_020860d0(int p0)
{
    return ((int) (p0) + (24));
}

int func_020860cc(int p0)
{
    return ((int) (p0) + (32));
}

int func_020860c8(int p0)
{
    return ((int) (p0) + (48));
}

int func_020860c4(int p0)
{
    return ((int) (p0) + (12));
}

int func_020860c0(int p0)
{
    return ((int) (p0) + (36));
}

int func_020860bc(int p0)
{
    return ((int) (p0) + (49));
}

int func_020860b8(int p0)
{
    return ((int) (p0) + (4));
}

void func_02086034(void *arg)
{
    void *a;
    void *p;
    int zero[2];
    char buf[8];

    a = arg;
    p = func_020984e8();
    if (p == 0) {
        return;
    }
    if (func_020951bc((void *) func_02099870(p)) == 0) {
        return;
    }
    if (func_02099020(p, 1) != 0) {
        return;
    }
    if (func_02099020(p, 0x21) != 0 || func_0203cc38() == 0) {
        if (func_02099020(p, 0x22) != 0) {
            return;
        }
        if (func_0203cc1c() == 0) {
            return;
        }
    }
    zero[0] = 0;
    zero[1] = 0;
    func_0209e474(zero);
    MI_CpuCopy8(zero, buf, 8);
    if (func_0203fc78(8, buf, 0) != 0) {
        return;
    }
    func_020860f0((volatile unsigned int *) a, 8);
}

int func_0208602c(void)
{
    return (int) &data_021d27ac;
}
