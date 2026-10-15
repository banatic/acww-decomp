/* func_020f3e84 @ 0x020f3e84, 0x30 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern int func_020eec48(void);
extern void func_020eec60(int argument0);
extern int func_020f4338(int a, int b);

int func_020f3e84(int a, int b)
{
    int tmp;
    tmp = a;

    func_020eec60(func_020eec48());
    return func_020f4338(tmp, b);
}
