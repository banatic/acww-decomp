/* func_020e9838 @ 0x020e9838, 0x30 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void MTX_Scale43_(void *dst, int x, int y, int z);
extern void MTX_Concat43(void *dst, int a, int b);

void func_020e9838(int arg0, int x, int y, int z)
{
    char local[0x30];
    MTX_Scale43_(local, x, y, z);
    MTX_Concat43(local, arg0, arg0);
}
