/* func_ov142_0229abfc @ 0x0229abfc, 0x3c bytes, Thumb, module ov142
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov142_0229ae8c(void *argument0);
extern void func_020a8c1c(void *argument0);
extern void func_02070adc(int, int, int, int, int, int, int);
extern void func_02070a04(int, int, int);

void func_ov142_0229abfc(void *object)
{
    int x;
    x = func_ov142_0229ae8c(object);
    func_020a8c1c((void *) x);
    func_02070adc(x, 6, 0x15d, 8, 14, 4, 0);
    func_02070a04(x, 0, 0);
}
