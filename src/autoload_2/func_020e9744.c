/* func_020e9744 @ 0x020e9744, 0x30 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void func_020e9640(void *);
extern void MTX_Concat43(void *, int, int);

void func_020e9744(int param)
{
    char local[0x30];
    func_020e9640(local);
    MTX_Concat43(local, param, param);
}
