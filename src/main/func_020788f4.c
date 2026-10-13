/* func_020788f4 @ 0x020788f4, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_020ccf94;
extern int func_02073d90(int);
extern int func_0207f294(int);
extern int func_0207cf74(int);
extern void func_0207892c(int, int);

void func_020788f4(int arg0, int arg1)
{
    int temp;
    if (func_02073d90(data_020ccf94)) {
        temp = func_0207f294(arg0);
        if (func_0207cf74(temp)) {
            func_0207892c(temp, arg1);
        }
    }
}
