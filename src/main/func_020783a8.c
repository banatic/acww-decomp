/* func_020783a8 @ 0x020783a8, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02073d90(int);
extern int func_0207f294(int);
extern int func_0207cf74(int);
extern void func_020783e0(int, int);
extern int data_020ccf94;

void func_020783a8(int param1, int param2)
{
    if (func_02073d90(data_020ccf94) != 0) {
        param1 = func_0207f294(param1);
        if (func_0207cf74(param1) != 0) {
            func_020783e0(param1, param2);
        }
    }
}
