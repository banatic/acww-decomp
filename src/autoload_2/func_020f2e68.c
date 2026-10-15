/* func_020f2e68 @ 0x020f2e68, 0x48 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

extern void func_020f97dc(void *, int enabled);
extern void func_020f95f0(void *, int);

void func_020f2e68(char *obj, int unused, unsigned int v)
{
    if (v >= 99 && v <= 171) {
        func_020f97dc(obj + 8, unused);
        func_020f95f0(obj + 8, 1);
    } else {
        func_020f95f0(obj + 8, 0);
    }
}
