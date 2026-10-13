/* func_ov144_0229a9d4 @ 0x0229a9d4, 0x32 bytes, Thumb, module ov144
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208e484(void *p);
extern int func_ov144_02299ac4(void *p, int c);
extern void func_ov002_02208098(void *p, int n);
extern void func_ov144_0229a0a4(void *p);

void func_ov144_0229a9d4(void *p)
{
    if (func_0208e484((char *) p + 0xc4)) {
        if (func_ov144_02299ac4(p, *(unsigned char *) ((char *) p + 0xc1)) == 0) {
            func_ov002_02208098(p, 3);
            func_ov144_0229a0a4(p);
        }
    }
}
