/* func_020e9838 @ 0x020e9838, 0x30 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void MTX_Scale43_(void *dst);
extern void MTX_Concat43(void *dst, int a, int b);

void func_020e9838(int arg0)
{
    char local[0x30];
    MTX_Scale43_(local);
    MTX_Concat43(local, arg0, arg0);
}
