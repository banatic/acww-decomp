/* func_020e9868 @ 0x020e9868, 0x30 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void func_020e96c8(void *dst);
extern void MTX_Concat43(void *dst, void *src, void *src2);

void func_020e9868(void *arg)
{
    char buf[0x30];
    func_020e96c8(buf);
    MTX_Concat43(buf, arg, arg);
}
