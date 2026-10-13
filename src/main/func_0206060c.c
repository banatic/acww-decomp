/* func_0206060c @ 0x0206060c, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02060504(char *p);
extern void func_020606d4(unsigned char *ctx, int val);
extern void func_02055454(void);
extern void func_020605d8(unsigned char *ctx, int val);
extern void func_0206052c(unsigned char *ctx, int val, int arg);
extern unsigned char data_021cad80[];

void func_0206060c(char *p)
{
    func_020606d4(data_021cad80, func_02060504(p));
    func_02055454();
    func_020605d8(data_021cad80, func_02060504(p));
    func_0206052c(data_021cad80, func_02060504(p), 0);
    *p = 9;
}
