/* func_ov139_0229964c @ 0x0229964c, 0xf8 bytes, Thumb, module ov139
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int data_ov139_02299e84;
extern unsigned int data_ov139_02299e80;
extern char data_ov139_02299ea0;
extern char data_ov139_02299e88;
extern char data_ov139_02299ebc;
extern char data_ov139_02299e94;

extern void *func_ov139_02299744(void *p);
extern void *func_02064170(void *p);
extern void *func_020641c8(void *p);
extern void __register_global_object(void *a, void *destructor, void *c);
extern void func_020a8c1c(void *p);
extern void func_020a8874(void *p, int a, int b);
extern int func_020a8a70(void *p1, void *p2, int a, int b);
extern void *func_020b496c(int a, void *p);
extern int func_0207094c(void *p, int a);
extern void func_02070adc(void *p, unsigned int b, int c, int d, int e, int f, int g);
extern void func_02070a04(void *p, int a, int b);

extern void *func_02064158(void *arg0);
extern void *func_020641b0(void *arg0);

#define DisposeGlobal_func_02064158 ((void *) &func_02064158)

#define DisposeGlobal_func_020641b0 ((void *) &func_020641b0)

void func_ov139_0229964c(void *arg0, int arg1, int arg2, int arg3)
{
    int a1 = arg1;
    int a2 = arg2;
    int a3 = arg3;
    void *r4;
    int offset, a, b;

    r4 = func_ov139_02299744(arg0);

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
        func_0207094c(r4, 0x66);
    }

    offset = a1 * 20 + 0x11e;
    a = 0xf;
    b = 0xe;
    if (a3 != 0xff) {
        a = a3;
        b = 0xf;
    }

    func_02070adc(r4, *(unsigned char *) ((char *) arg0 + 0x9a2), offset, 0x0a, a, b, 0);
    func_02070a04(r4, 1, 0);
}

#undef DisposeGlobal_func_02064158
#undef DisposeGlobal_func_020641b0
