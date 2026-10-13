/* func_020787d4 @ 0x020787d4, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_020ccf94;
extern int func_02073d90(int);
extern int func_0207f294(int);
extern int func_0207cf74(int);
extern int func_0207880c(int, int, int);

int func_020787d4(int a, int b, int c)
{
    if (func_02073d90(data_020ccf94) != 0) {
        a = func_0207f294(a);
        if (func_0207cf74(a) != 0) {
            return func_0207880c(a, b, c);
        }
    }
}
