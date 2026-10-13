/* func_020a8fe8 @ 0x020a8fe8, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020e9948(int, int);
extern int func_020a8f2c(int, int, int, int);
extern void NNS_FndAppendListObject(int *, int);
extern int data_021c8194;
extern int data_021c81bc;

int func_020a8fe8(int a, int b, int c)
{
    int r5 = 0;
    int r4;
    int ret = func_020e9948(data_021c8194, 0x84);
    r4 = r5;
    if (ret != 0) {
        if (ret != 0) {
            ret = func_020a8f2c(ret, a, b, c);
        }
        r4 = ret;
        r5 = 1;
    }
    if (r5 != 0) {
        NNS_FndAppendListObject(&data_021c81bc, r4);
    }
    return r4;
}
