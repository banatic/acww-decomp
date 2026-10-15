/* func_ov119_0229be8c @ 0x0229be8c, 0x54 bytes, Thumb, module ov119
 * mwccarm 1.2/base -O4,s
 */

extern int func_0206f56c(void);
extern void func_ov119_0229a4e4(int);
extern int func_0208e484(int);
extern void func_ov002_02209114(int, int, int);
extern int func_ov119_0229a5cc(int, int);
extern unsigned char *func_ov002_02208098(int, unsigned char value);

void func_ov119_0229be8c(int r0)
{
    int r4 = r0;
    if (func_0206f56c()) {
        func_ov119_0229a4e4(r4);
        return;
    }
    if (func_0208e484(r4 + 0xda8)) {
        func_ov002_02209114(r4 + 0xdc, *(unsigned char *) (r4 + 0xae), 1);
        *(unsigned char *) (r4 + 0xad) = func_ov119_0229a5cc(r4, *(unsigned char *) (r4 + 0xae));
        func_ov002_02208098(r4, 0xb);
    }
}
