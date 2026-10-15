/* func_020e9774 @ 0x020e9774, 0x30 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void func_020e9684(void *, int argument1);
extern void MTX_Concat43(void *, void *, void *);

void func_020e9774(void *param, int argument1)
{
    char local[0x30];
    func_020e9684(local, argument1);
    MTX_Concat43(local, param, param);
}
