/* func_02077108 @ 0x02077108, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int data_021fbe94;
extern unsigned int data_020ccf94;

extern unsigned int func_020e9958(unsigned int, unsigned int);
extern void func_020736bc(unsigned int, unsigned int, unsigned int);
extern void func_02070760(unsigned int, unsigned int);
extern unsigned int func_020e993c(unsigned int, unsigned int);

unsigned int func_02077108(unsigned int a1, unsigned int a2, unsigned int a3, unsigned int a4)
{
    unsigned int w = data_021fbe94;
    unsigned int v = func_020e9958(w, a1);
    func_020736bc(data_020ccf94, v, a1);
    func_02070760(v, a4);
    return func_020e993c(w, v);
}
