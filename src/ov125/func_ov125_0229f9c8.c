/* func_ov125_0229f9c8 @ 0x0229f9c8, 0x64 bytes, Thumb, module ov125
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char func_ov002_022090e4(void *p, int arg1);
extern int func_ov002_02208ae4(void *p);
extern int func_ov002_02208ad8(void *p, unsigned char b);
extern void func_ov002_0220a0b4(void *p, int a, int b);
extern void func_0208e4c0(void *p, int n);
extern unsigned char *func_ov002_02208098(void *p, unsigned char value);

void func_ov125_0229f9c8(void *param)
{
    int v1, v2;
    ((unsigned char *) param)[0x87d] = 1;
    ((unsigned char *) param)[0x87e] = func_ov002_022090e4((char *) param + 0x180, 1);
    v1 = func_ov002_02208ae4((char *) param + 0x180);
    v2 = func_ov002_02208ad8((char *) param + 0x180, ((unsigned char *) param)[0x87e]);
    func_ov002_0220a0b4((char *) param + 0x644, v1, v2);
    func_0208e4c0((char *) param + 0x644, 8);
    func_ov002_02208098(param, 8);
}
