/* func_ov003_022207e0 @ 0x022207e0, 0x68 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_020b1e54(void);
extern void func_ov003_02220138(void);
extern void func_020b2980(void);
extern void func_020b3b38(int);
extern void func_ov003_022203fc(int);
extern void func_ov003_0221fe34(int);
extern void func_ov003_0221ffec(int);
extern void func_ov003_0221fec0(int);
extern void func_ov003_02220798(int);
extern void func_ov003_02220794(int);
extern void func_ov003_02220520(int);
extern void func_0202f134(int, int, int, int);
extern int data_ov003_0223ce58;
extern int data_ov003_0223cea0;
extern int data_ov003_0223ce80;
extern int data_021f42f4;

int func_ov003_022207e0(int r0)
{
    int r4 = r0;
    func_020b1e54();
    func_ov003_02220138();
    func_020b2980();
    func_020b3b38(r4);
    func_ov003_022203fc(r4);
    func_ov003_0221fe34((int) &data_ov003_0223ce58);
    func_ov003_0221ffec((int) &data_ov003_0223cea0);
    func_ov003_0221fec0((int) &data_ov003_0223ce80);
    func_ov003_02220798(r4);
    func_ov003_02220794(r4);
    func_ov003_02220520(r4);
    func_0202f134(0xf, data_021f42f4, 0, 0);
    return 1;
}
