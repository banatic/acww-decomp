/* func_ov128_0229bd08 @ 0x0229bd08, 0x30 bytes, Thumb, module ov128
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov128_0229b7ec(int param1, int param2);
extern unsigned char data_ov128_0229c8c0[];

int func_ov128_0229bd08(int param1)
{
    int r4;
    unsigned char r1;
    unsigned char r0;

    r4 = param1;
    if (func_ov128_0229b7ec(r4, 2) != 0) {
        return *(int *) ((char *) r4 + 0x2d4c);
    }
    r1 = *(unsigned char *) ((char *) r4 + 0x2d6c);
    r0 = data_ov128_0229c8c0[r1];
    return r0;
}
