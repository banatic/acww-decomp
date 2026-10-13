/* func_02078864 @ 0x02078864, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02073d90(int);
extern int func_0207f294(int);
extern int func_0207cf74(int);
extern int func_0207889c(int, int, int);
extern int data_020ccf94;

int func_02078864(int a, int b, int c)
{
    if (func_02073d90(data_020ccf94) != 0) {
        int t = func_0207f294(a);
        if (func_0207cf74(t) != 0) {
            return func_0207889c(t, b, c);
        }
    }
}
