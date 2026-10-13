/* func_0203fc78 @ 0x0203fc78, 0x3a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02040a48(int);
extern void MI_CpuCopy8(void *src, void *dst, int size);
extern int func_0203fcb4(int, void *, int);

int func_0203fc78(int arg0, void *arg1, int arg2)
{
    int ret = 0;
    if (func_02040a48(arg0) == 0) {
        char buf[8];
        MI_CpuCopy8(arg1, buf, 8);
        ret = func_0203fcb4(arg0, buf, arg2);
        if (ret == 1) {
            ret = 0;
        }
    }
    return ret;
}
