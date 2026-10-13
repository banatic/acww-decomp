/* func_020716f4 @ 0x020716f4, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02073d90(int);
extern int func_020984fc(int);
extern int func_020996b8(void);
extern int func_02072bd0(int, int);
extern int data_020ccf94;

int func_020716f4(int arg0, int arg1)
{
    if (func_02073d90(data_020ccf94) && func_020984fc(arg0)) {
        return func_02072bd0(func_020996b8(), arg1);
    }
    return 0;
}
