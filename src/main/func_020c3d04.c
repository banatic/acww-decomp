/* func_020c3d04 @ 0x020c3d04, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02014868(void *ptr);
extern int func_0203e020(void *ptr);
extern void func_020c3dac(void *ptr, int arg);

int func_020c3d04(void *ptr)
{
    if (func_02014868((char *) ptr + 0x618) == 0) {
        func_0203e020(ptr);
        func_020c3dac(ptr, 2);
    }
    return 1;
}
