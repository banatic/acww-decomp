/* func_0206f92c @ 0x0206f92c, 0x54 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020984e8(void);
extern int func_02098a18(int);
extern unsigned char *func_02097e14(void *p);
extern int func_02066830(int, void *);
extern void func_020664e0(int);
extern int func_02097e08(int);

extern int data_021cfd68;
extern unsigned char data_021cfc98[];

void func_0206f92c(void)
{
    int a;
    int b;
    unsigned char *p;

    a = func_020984e8();
    b = (int) func_02097e14((void *) func_02098a18(a));
    func_02066830(b, &data_021cfd68);
    func_020664e0(b);
    p = (unsigned char *) func_02097e08(func_02098a18(a));
    p[0] = 1;
    p[1] = 1;
    p[2] = 0;
    p[3] = 0;
    p[0] = data_021cfc98[3];
    p[1] = data_021cfc98[4];
    p[2] = data_021cfc98[5];
}
