/* main_loop: 10 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0206e6c0 @ 0x0206e6c0, 0x2 bytes, Thumb
 * func_0206e6b0 @ 0x0206e6b0, 0x10 bytes, Thumb
 * func_0206e6a0 @ 0x0206e6a0, 0x10 bytes, Thumb
 * func_0206e670 @ 0x0206e670, 0x2e bytes, Thumb
 * func_0206e63c @ 0x0206e63c, 0x34 bytes, Thumb
 * func_0206e624 @ 0x0206e624, 0x16 bytes, Thumb
 * func_0206e5fc @ 0x0206e5fc, 0x28 bytes, Thumb
 * func_0206e5f4 @ 0x0206e5f4, 0x8 bytes, Thumb
 * func_0206e5ec @ 0x0206e5ec, 0x8 bytes, Thumb
 * func_0206e560 @ 0x0206e560, 0x8c bytes, Thumb
 */

extern void OS_SleepThread(void *arg);
extern char data_021cfb90;
extern int data_021cfb98;
extern void func_020b0340(void);
extern void func_02054094(void);
extern void func_02074904(int);
extern void func_020b9280(void);
extern void func_020e9548(void);
extern void func_0209d36c(void);
extern void func_0209dfa4(int);
extern void func_020a6c04(void);
extern void func_02074330(void *);
extern void func_02054070(void);
extern int data_021fbdd0;
extern void func_0205401c(void);
extern void func_020389e0(void);
extern void func_020b983c(void);
extern void func_02050e68(void);
extern void func_02011eec(void);
extern void func_020ba340(void);
extern void func_0205c080(void);
extern void func_02004b30(int);
extern void func_0203de74(void);
extern void func_0203de70(void);
extern void GX_DispOn(void);
extern void func_020b03ac(void);
extern int data_020ccf94;
extern void func_020ecde8(void);
extern int func_020732c0(int);
extern void func_020732e4(int, int);
extern int func_020732d8(int);
extern void func_02038a00(int);
extern void func_020ee934(int);
extern void func_020389f0(void);
extern unsigned char data_021cfb6c[];

void func_0206e6c0(void) {}

void func_0206e6b0(void)
{
    OS_SleepThread(&data_021cfb90);
}

void func_0206e6a0(void)
{
    OS_SleepThread(&data_021cfb98);
}

void func_0206e670(int arg0)
{
    int r4 = arg0;
    func_020b0340();
    func_02054094();
    if (r4 != 0) {
        func_02074904(r4);
    }
    func_020b9280();
    func_020e9548();
    func_0209d36c();
    func_0209dfa4(r4);
}

void func_0206e63c(void *arg)
{
    if (arg == 0) {
        func_020a6c04();
    }
    func_02074330(arg);
    func_02054070();
    data_021fbdd0++;
    *(volatile unsigned int *) 0x04000540 = 3;
}

void func_0206e624(void)
{
    func_0205401c();
    func_020389e0();
    func_020b983c();
}

void func_0206e5fc(int arg0)
{
    int r4;
    int result;

    r4 = arg0;
    func_02050e68();
    func_02011eec();
    func_020ba340();
    func_0205c080();
    if (r4 == 0) {
        result = 0;
    } else {
        result = 1;
    }
    func_02004b30(result);
}

void func_0206e5f4(void)
{
    func_0203de74();
}

void func_0206e5ec(void)
{
    func_0203de70();
}

void func_0206e560(void)
{
    int v4;
    int v6;
    unsigned short *v7;

    GX_DispOn();
    *((unsigned int *) 0x04001000) |= 0x00010000;
    func_020b03ac();
    v6 = data_020ccf94;
    v7 = (unsigned short *) data_021cfb6c;

    while (1) {
        int v5;

        func_020ecde8();
        func_020732e4(v6, func_020732c0(v6));
        v4 = func_020732d8(v6);
        func_0206e670(v4);
        func_0206e5f4();
        if (v4 != 0) {
            v5 = 1;
        } else {
            v5 = 0;
        }
        func_02038a00(v5);
        func_020ee934(v5);
        func_020389f0();
        func_0206e63c((void *) v4);
        func_0206e5ec();
        *v7 = 1;
        func_0206e6a0();
        *v7 = 0;
        func_0206e624();
        func_0206e5fc(v4);
    }
}
