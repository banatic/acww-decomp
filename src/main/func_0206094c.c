/* func_0206094c @ 0x0206094c, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0205c3e4(int);
extern void func_02060754(int *ptr);
extern int func_020e9abc(int arg);
extern int data_021c9ac8;
extern int data_021cad80;

void func_0206094c(int argument0)
{
    func_0205c3e4((int) argument0);
    func_02060754(&data_021cad80);
    if (data_021c9ac8) {
        func_020e9abc(data_021c9ac8);
    }
}
