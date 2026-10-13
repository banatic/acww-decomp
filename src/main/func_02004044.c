/* func_02004044 @ 0x02004044, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_021c67a4;
extern int data_021c67b8[3];
extern void func_020f61e4(int, int *);

void func_02004044(int arg0, int *arg1)
{
    if (arg1) {
        if (data_021c67a4) {
            int diff[3];
            diff[0] = arg1[0] - data_021c67b8[0];
            diff[1] = arg1[1] - data_021c67b8[1];
            diff[2] = arg1[2] - data_021c67b8[2];
            func_020f61e4(arg0, diff);
        }
    } else {
        func_020f61e4(arg0, arg1);
    }
}
