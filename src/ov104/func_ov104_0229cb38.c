/* func_ov104_0229cb38 @ 0x0229cb38, 0x38 bytes, Thumb, module ov104
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov104_0229d8f8(void *obj, unsigned char idx);
extern void func_02066830(void *dest, int value);

void func_ov104_0229cb38(void *base)
{
    unsigned char j;
    int i;

    i = 0;
    j = 11;

    do {
        int val = func_ov104_0229d8f8(base, j);
        func_02066830((char *) base + 0x37b4 + (i << 8), val);
        i++;
        j++;
    } while (j <= 20);
}
