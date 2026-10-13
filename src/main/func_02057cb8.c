/* func_02057cb8 @ 0x02057cb8, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02057d34(int arg);
extern void func_0204fdbc(int);
extern void func_02059ac4(int);
extern int data_021c9350;

void func_02057cb8(int arg)
{
    int id;

    if (data_021c9350 != 0 && func_02057d34(arg) == 1) {
        id = *(int *) (data_021c9350 + 0xc4);
        if (id != -1) {
            func_0204fdbc(id);
        }
        func_02059ac4(data_021c9350);
    }
}
