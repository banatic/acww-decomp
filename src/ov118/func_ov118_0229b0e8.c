/* func_ov118_0229b0e8 @ 0x0229b0e8, 0x38 bytes, Thumb, module ov118
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021f6c58;
extern unsigned char data_021f6c54;
extern int func_ov118_0229b088(int a, unsigned char b, unsigned char c);
extern void func_ov118_0229afd4(int a, unsigned char b);

int func_ov118_0229b0e8(int param)
{
    int ret = func_ov118_0229b088(param, data_021f6c58, data_021f6c54);
    if (ret == 14) {
        return 0;
    } else {
        func_ov118_0229afd4(param, (unsigned char) (ret + 1));
        return 1;
    }
}
