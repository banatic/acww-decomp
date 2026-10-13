/* func_ov068_0226d5f4 @ 0x0226d5f4, 0x70 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern void func_0202e118(void *dst, void *src);
extern void func_02012508(void *a, void *b, void *c, int d, int e);
extern void func_02012444(void *a, unsigned short b, int c);
extern void func_020121e0(void *a, int b);
extern unsigned short data_020c80f8;

void func_ov068_0226d5f4(void *param)
{
    unsigned short local[2];

    func_0202e118(&local[0], param);
    if (local[0] == 0xfff1) {
        return;
    }
    func_0202e118(&local[1], param);
    func_02012508((char *) param + 0x9b4, param, &local[1], 0, 0);
    func_02012444((char *) param + 0x9b4, data_020c80f8, 0);
    func_020121e0((char *) param + 0x9b4, 0x1000);
    *((unsigned char *) param + 0x9f0) = 1;
}
