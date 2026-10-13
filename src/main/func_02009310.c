/* func_02009310 @ 0x02009310, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02009484(void *src, unsigned char *out0, unsigned char *out1, unsigned char *out2);
extern void func_020094a0(void *obj, unsigned char a, unsigned char b, unsigned char c, int d, int e);

void func_02009310(unsigned char *obj, int arg1)
{
    unsigned char temp[3];

    func_02009484(obj + 0x8f0, &temp[0], &temp[1], &temp[2]);
    func_020094a0(obj, temp[0], temp[1], temp[2], 6, arg1);
}
