/* func_ov137_0229cb48 @ 0x0229cb48, 0x48 bytes, Thumb, module ov137
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov134_02299a60(void *);
extern unsigned char *func_ov002_02208098(void *, unsigned char value);
extern void func_ov137_0229c628(void *);
extern int func_ov137_0229c794(void *);
extern int func_ov137_0229c750(void *);
extern void func_ov002_0220a0b4(void *, int, int);

void func_ov137_0229cb48(void *arg0)
{
    if (func_ov134_02299a60((char *) arg0 + 0x2c4)) {
        func_ov002_02208098(arg0, 5);
        func_ov137_0229c628(arg0);
    }
    {
        int r5 = func_ov137_0229c794(arg0);
        int r2 = func_ov137_0229c750(arg0);
        func_ov002_0220a0b4((char *) arg0 + 0x94, r5, r2);
    }
}
