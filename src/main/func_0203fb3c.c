/* func_0203fb3c @ 0x0203fb3c, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0203fe58(int);
extern int func_02073d90(void *);
extern void *data_020ccf94;
extern int data_021c74b4;

int func_0203fb3c(void)
{
    if (func_02073d90(data_020ccf94) == 0) {
        if (data_021c74b4) {
            func_0203fe58(0);
        }
        data_021c74b4 = 0;
    } else {
        func_0203fe58(0);
        data_021c74b4 = 1;
    }
    return 1;
}
