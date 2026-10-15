/* func_020e9868 @ 0x020e9868, 0x30 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void func_020e96c8(void *dst, int argument1, int argument2, int argument3);
extern void MTX_Concat43(void *dst, void *src, void *src2);

void func_020e9868(void *arg, int argument1, int argument2, int argument3)
{
    char buf[0x30];
    func_020e96c8(buf, argument1, argument2, argument3);
    MTX_Concat43(buf, arg, arg);
}
