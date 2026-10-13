/* func_020c3244 @ 0x020c3244, 0x36 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020984e8(void *);
extern int func_02099688(int);
extern int func_020882ec(int);
extern void func_02015e70(void *, int, int);

void func_020c3244(void *param)
{
    int r4;
    r4 = func_02099688(func_020984e8(param));
    func_02015e70(param, func_020882ec(r4), 0);
    func_02015e70(param, func_020882ec(r4), 1);
}
