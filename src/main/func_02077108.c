/* func_02077108 @ 0x02077108, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int data_021fbe94;
extern unsigned int data_020ccf94;

extern unsigned int func_020e9958(unsigned int, unsigned int);
extern void func_020736bc(unsigned int, unsigned int, unsigned int);
extern void func_02070760(unsigned int, unsigned int);
extern void func_020e993c(unsigned int, unsigned int);

void func_02077108(int length, int sequence, unsigned char category, unsigned int player)
{
    unsigned int w = data_021fbe94;
    unsigned int v = func_020e9958(w, length);
    func_020736bc(data_020ccf94, v, length);
    func_02070760(v, player);
    func_020e993c(w, v);
}
