/* func_0206e560 @ 0x0206e560, 0x8c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void GX_DispOn(void);
extern void func_020b03ac(void);
extern int data_020ccf94;
extern void func_020ecde8(void);
extern int func_020732c0(int);
extern void func_020732e4(int, int);
extern int func_020732d8(int);
extern void func_0206e670(int);
extern void func_0206e5f4(void);
extern void func_02038a00(int);
extern void func_020ee934(int);
extern void func_020389f0(void);
extern void func_0206e63c(int);
extern void func_0206e5ec(void);
extern void func_0206e6a0(void);
extern void func_0206e624(void);
extern void func_0206e5fc(int);

extern unsigned char data_021cfb6c[];

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
        func_0206e63c(v4);
        func_0206e5ec();
        *v7 = 1;
        func_0206e6a0();
        *v7 = 0;
        func_0206e624();
        func_0206e5fc(v4);
    }
}
