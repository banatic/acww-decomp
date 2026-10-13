/* func_ov128_0229bd38 @ 0x0229bd38, 0x30 bytes, Thumb, module ov128
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov128_0229b7ec(int a, int b);
extern unsigned char data_ov128_0229c8c4[];

int func_ov128_0229bd38(int a)
{
    int r4 = a;
    if (func_ov128_0229b7ec(r4, 2) != 0) {
        return *(int *) ((char *) r4 + 0x2d48);
    } else {
        return data_ov128_0229c8c4[*(unsigned char *) ((char *) r4 + 0x2d6c)];
    }
}
