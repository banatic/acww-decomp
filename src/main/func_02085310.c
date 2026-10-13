/* func_02085310 @ 0x02085310, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char flag;
    char pad_01[29];
} Entry;
extern Entry data_021d213c[];
extern char data_021d2128;
extern int func_0207762c(int);
extern void MI_CpuCopy8(void *dst, void *src, int value);

void func_02085310(void *param0, int param1)
{
    int index = param1 - 12;
    if ((unsigned) index < 8) {
        int ret;
        data_021d213c[index].flag = 1;
        ret = func_0207762c(param1);
        MI_CpuCopy8(&data_021d213c[index], param0, ret);
        data_021d2128 = 1;
    }
}
