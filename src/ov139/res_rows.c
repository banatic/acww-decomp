/* res_rows: 11 functions, module ov139
 * mwccarm 1.2/base -O4,s
 * func_ov139_022997f0 @ 0x022997f0, 0x96 bytes, Thumb
 * func_ov139_022997c0 @ 0x022997c0, 0x2e bytes, Thumb
 * func_ov139_02299798 @ 0x02299798, 0x28 bytes, Thumb
 * func_ov139_02299770 @ 0x02299770, 0x28 bytes, Thumb
 * func_ov139_02299744 @ 0x02299744, 0x2c bytes, Thumb
 * func_ov139_0229964c @ 0x0229964c, 0xf8 bytes, Thumb
 * func_ov139_022995e4 @ 0x022995e4, 0x68 bytes, Thumb
 * func_ov139_022995d8 @ 0x022995d8, 0xc bytes, Thumb
 * func_ov139_022995c0 @ 0x022995c0, 0x18 bytes, Thumb
 * func_ov139_022995b0 @ 0x022995b0, 0x10 bytes, Thumb
 * func_ov139_022995a0 @ 0x022995a0, 0x10 bytes, Thumb
 */

extern int func_0207094c(int, int);
extern void func_02070adc(int, int, int, int, int, int, int);
extern void func_02070a04(int, int, int);
extern void func_02070b84(void *);
extern unsigned int data_ov139_02299e84;
extern unsigned int data_ov139_02299e80;
extern char data_ov139_02299ea0;
extern char data_ov139_02299e88;
extern char data_ov139_02299ebc;
extern char data_ov139_02299e94;
extern void *func_02064170(void *p);
extern void *func_020641c8(void *p);
extern void __register_global_object(void *a, void *destructor, void *c);
extern void func_020a8c1c(void *p);
extern void func_020a8874(void *p, int a, int b);
extern int func_020a8a70(void *p1, void *p2, int a, int b);
extern void *func_020b496c(int a, void *p);
extern void *func_02064158(void *arg0);
extern void *func_020641b0(void *arg0);
extern void func_020708e4(int, int, int);
extern unsigned int data_ov139_02299c60[];

unsigned char *func_ov139_02299744(unsigned char *p);
void func_ov139_0229964c(void *arg0, int arg1, int arg2, int arg3);
void func_ov139_022995e4(int a0, int a1, int a2, int a3);

void func_ov139_022997f0(int param)
{
    int a;
    a = (int) func_ov139_02299744((unsigned char *) param);
    func_0207094c(a, 0x65);
    func_02070adc(a, 8, 0x93, 6, 15, 0, 0);
    func_02070a04(a, 1, 0);
    a = (int) func_ov139_02299744((unsigned char *) param);
    func_0207094c(a, 0xc2);
    func_02070adc(a, 8, 0x8d, 6, 15, 0, 0);
    func_02070a04(a, 1, 0);
    a = (int) func_ov139_02299744((unsigned char *) param);
    func_0207094c(a, 0xc1);
    func_02070adc(a, 8, 0x99, 6, 15, 0, 0);
    func_02070a04(a, 1, 0);
}

void func_ov139_022997c0(int a, int b, void *c)
{
    unsigned char x = (unsigned char) (14 - b);
    func_ov139_0229964c((void *) a, b, (int) c, (int) x);
    func_ov139_022995e4(a, b, (int) ((char *) c + 12), (int) x);
}

void func_ov139_02299798(int param0, int param1)
{
    unsigned char v = (unsigned char) (14 - param1);
    func_ov139_0229964c((void *) param0, param1, 0, (int) v);
    func_ov139_022995e4(param0, param1, 0, (int) v);
}

void func_ov139_02299770(char *arg0)
{
    int i;
    char *base;

    i = 0;
    arg0[0x9a3] = 0;
    base = arg0 + 0xcc;
    do {
        func_02070b84(base + i * 0x6c);
        i++;
    } while (i < 0x14);
}

unsigned char *func_ov139_02299744(unsigned char *p)
{
    unsigned char b = p[0x9a3];
    if (b >= 0x14) {
        return p + 0x8d0;
    } else {
        p[0x9a3] = b + 1;
        return p + 0xcc + 0x6c * (p[0x9a3] - 1);
    }
}

#define DisposeGlobal_func_02064158 ((void *) &func_02064158)

#define DisposeGlobal_func_020641b0 ((void *) &func_020641b0)

void func_ov139_0229964c(void *arg0, int arg1, int arg2, int arg3)
{
    int a1 = arg1;
    int a2 = arg2;
    int a3 = arg3;
    void *r4;
    int offset, a, b;

    r4 = (void *) func_ov139_02299744((unsigned char *) arg0);

    if ((data_ov139_02299e84 & 1) == 0) {
        func_02064170(&data_ov139_02299ea0);
        __register_global_object(&data_ov139_02299ea0, DisposeGlobal_func_02064158, &data_ov139_02299e88);
        data_ov139_02299e84 |= 1;
    }

    if ((data_ov139_02299e80 & 1) == 0) {
        func_020641c8(&data_ov139_02299ebc);
        __register_global_object(&data_ov139_02299ebc, DisposeGlobal_func_020641b0, &data_ov139_02299e94);
        data_ov139_02299e80 |= 1;
    }

    if (a2 == 0) {
        func_020a8c1c(r4);
    } else {
        func_020a8874(&data_ov139_02299ea0, a2, 6);
        func_020a8a70(&data_ov139_02299ebc, &data_ov139_02299ea0, 0, 0);
        func_020b496c(0, &data_ov139_02299ebc);
        func_0207094c((int) r4, 0x66);
    }

    offset = a1 * 20 + 0x11e;
    a = 0xf;
    b = 0xe;
    if (a3 != 0xff) {
        a = a3;
        b = 0xf;
    }

    func_02070adc((int) r4, (int) (*(unsigned char *) ((char *) arg0 + 0x9a2)), offset, 0x0a, a, b, 0);
    func_02070a04((int) r4, 1, 0);
}

#undef DisposeGlobal_func_02064158
#undef DisposeGlobal_func_020641b0

void func_ov139_022995e4(int a0, int a1, int a2, int a3)
{
    int local0;
    int a, b;
    int r2;

    local0 = (int) func_ov139_02299744((unsigned char *) a0);

    if (a2 == 0) {
        func_020a8c1c((void *) local0);
    } else {
        func_020708e4(local0, a2, 6);
    }

    r2 = a1 * 16 + 0x1d2;

    a = 0xF;
    b = 0xE;
    if (a3 != 0xFF) {
        a = a3;
        b = 0xF;
    }

    func_02070adc(local0, *(unsigned char *) ((char *) a0 + 0x9a2), r2, 8, a, b, 0);
    func_02070a04(local0, 1, 0);
}

unsigned int func_ov139_022995d8(unsigned int param1, unsigned int param2)
{
    return data_ov139_02299c60[param2];
}

int func_ov139_022995c0(const unsigned short *p, unsigned short mask)
{
    return (p[0x4d0] & mask) != 0;
}

unsigned short *func_ov139_022995b0(unsigned short *r0, unsigned short r1)
{
    unsigned short *p;
    unsigned short v;

    p = (unsigned short *) ((char *) r0 + 0x9a0);
    v = *p;
    v |= r1;
    *p = v;
    return p;
}

void func_ov139_022995a0(unsigned short *param0, unsigned short param1)
{
    unsigned short *ptr;
    unsigned short val;

    ptr = (unsigned short *) ((char *) param0 + 0x9a0);
    val = *ptr;
    val &= ~param1;
    *ptr = val;
}
