/* func_ov143_02299bd0 @ 0x02299bd0, 0x44 bytes, Thumb, module ov143
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov143_02299650(void *obj, int);
extern int func_020b9bbc(void *a, void *b, int c, int d, int e);
extern void func_ov143_02299630(void *obj, int);

void func_ov143_02299bd0(void *obj)
{
    if (func_ov143_02299650(obj, 4)) {
        if (func_020b9bbc((char *) obj + 0x119c, (char *) obj + 0x099c, 4, 0x800, 0)) {
            func_ov143_02299630(obj, 4);
        }
    }
}
