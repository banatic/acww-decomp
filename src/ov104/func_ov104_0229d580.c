/* func_ov104_0229d580 @ 0x0229d580, 0x40 bytes, Thumb, module ov104
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov104_0229c364(void *ptr, unsigned int size);
extern void func_ov094_0229b5e8(void *a, unsigned int b, unsigned int c, void *d);

void func_ov104_0229d580(char *p)
{
    unsigned char flag;

    if (func_ov104_0229c364(p, 0x40) != 0) {
        return;
    }
    flag = *(unsigned char *) (p + 0xb4);
    if (flag == 0) {
        return;
    }
    if (flag != 1) {
        return;
    }
    func_ov094_0229b5e8(p + 0xd58, *(unsigned int *) (p + 0xa8), *(unsigned int *) (p + 0xac), p + 0xc0);
}
