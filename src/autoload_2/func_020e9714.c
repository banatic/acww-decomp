/* func_020e9714 @ 0x020e9714, 0x30 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void func_020e95fc(void *, int argument1);
extern void MTX_Concat43(void *, void *, void *);

void func_020e9714(void *param, int argument1)
{
    char local[0x30];
    func_020e95fc(local, argument1);
    MTX_Concat43(local, param, param);
}
