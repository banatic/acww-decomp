/* func_ov003_0220e828 @ 0x0220e828, 0x38 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov003_0220e8e0(char *addr, unsigned char *a, unsigned char *b);
extern int func_ov003_0220e8f4(char *base, int *data, int count, char *other);

void func_ov003_0220e828(char *p, char *q)
{
    unsigned char bytes[2];
    int data[2];
    func_ov003_0220e8e0(p + 0x8f0, &bytes[0], &bytes[1]);
    data[0] = bytes[0];
    data[1] = bytes[1];
    func_ov003_0220e8f4(p, data, 6, q);
}
