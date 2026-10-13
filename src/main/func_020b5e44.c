/* func_020b5e44 @ 0x020b5e44, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short data_020e3c80;
extern void func_020a53ec(int, int, int, int);
extern void func_0209d074(int);

void func_020b5e44(int arg0, int arg1)
{
    int local_0;
    int local_1;

    local_0 = arg0;
    local_1 = arg1;
    if (data_020e3c80 != 5) {
        func_020a53ec(5, local_0, 3, 1);
        func_0209d074(local_1);
    }
}
