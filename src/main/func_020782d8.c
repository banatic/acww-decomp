/* func_020782d8 @ 0x020782d8, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_020ccf94;
extern int func_02073d90(int);
extern int func_0207f294(int);
extern int func_0207cf74(int);
extern void func_02078310(int, int);

void func_020782d8(int param0, int param1)
{
    int x;
    if (func_02073d90(data_020ccf94)) {
        x = func_0207f294(param0);
        if (func_0207cf74(x)) {
            func_02078310(x, param1);
        }
    }
}
