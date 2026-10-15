/* func_ov003_0221b5c0 @ 0x0221b5c0, 0x28 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_020e9948(int, int);
extern void *memset(int, int, int);
extern int data_021c9b24;

int func_ov003_0221b5c0(int arg0)
{
    int ret = func_020e9948(data_021c9b24, arg0);
    memset(ret, 0, arg0);
    return ret;
}
