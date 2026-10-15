/* func_020795f4 @ 0x020795f4, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b6660(void);
extern int func_02073d90(int);
extern int *func_02079350(void);
extern void func_02079640(void);
extern int data_020ccf94;

void func_020795f4(void)
{
    if (func_020b6660() == 0) {
        return;
    }
    if (func_02073d90(data_020ccf94) != 0) {
        return;
    }
    {
        int *p = func_02079350();
        if ((unsigned) p[0x5A] > 0x4b0u) {
            func_02079640();
        }
        p = func_02079350();
        p[0x5A]++;
    }
}
