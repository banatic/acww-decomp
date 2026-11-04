/* matrix_2: 2 functions, module autoload_2
 * mwccarm 1.2/base -O4,s
 * func_020e9868 @ 0x020e9868, 0x30 bytes, ARM
 * func_020e9838 @ 0x020e9838, 0x30 bytes, ARM
 */

extern void func_020e96c8(void *dst, int argument1, int argument2, int argument3);
extern void MTX_Concat43(void *dst, void *src, void *src2);
extern void MTX_Scale43_(void *dst, int x, int y, int z);

void func_020e9868(void *arg, int argument1, int argument2, int argument3)
{
    char buf[0x30];
    func_020e96c8(buf, argument1, argument2, argument3);
    MTX_Concat43(buf, arg, arg);
}

void func_020e9838(int arg0, int x, int y, int z)
{
    char local[0x30];
    MTX_Scale43_(local, x, y, z);
    MTX_Concat43(local, (void *) arg0, (void *) arg0);
}
