/* func_020638d4 @ 0x020638d4, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020638b0(void *out, int flag, int *tmp, int value1, int value2, int byte_arg, int arg6, int arg7);
extern void func_02063cc8(int *tmp);

void func_020638d4(unsigned short *out, int *inp, int value1, int value2, unsigned char byte_arg, int arg6, int arg7)
{
    int tmp[2];
    *out = 0xfff1;
    tmp[0] = inp[0];
    tmp[1] = inp[1];
    func_020638b0(out, 1, tmp, value1, value2, byte_arg, arg6, arg7);
    func_02063cc8(tmp);
}
