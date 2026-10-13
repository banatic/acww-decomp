/* func_02074f28 @ 0x02074f28, 0x78 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_020ccf94;
extern int func_020738b4(int, int);
extern int func_020738bc(int, int);
extern int func_0207762c(int);
extern void MI_CpuCopy8(int, char *, int);

int func_02074f28(char *param0, int param1, int param2)
{
    if (param1 == 0) {
        int result = 0;
        int i = 0x45;
        int gValue = data_020ccf94;
        char ch;
        int tmp;
        int len;
        do {
            if (func_020738b4(gValue, i) != 0) {
                ch = (char) i;
                MI_CpuCopy8((int) &ch, param0, 1);
                param0++;
                result++;
                tmp = func_020738bc(gValue, i);
                len = func_0207762c(i);
                MI_CpuCopy8(tmp, param0, len);
                param0 += len;
                result += len;
            }
        } while (--i >= 0);
        *param0 = 0x46;
        return result + 1;
    } else {
        MI_CpuCopy8(param1, param0, param2);
        return param2;
    }
}
