/* func_ov121_0229af58 @ 0x0229af58, 0x24 bytes, Thumb, module ov121
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov090_022990b8(int);
extern const unsigned char data_ov121_0229c248[];

int func_ov121_0229af58(int a, unsigned int b)
{
    if (b >= 0x10 && b <= 0x17) {
        b -= 0x10;
        return func_ov090_022990b8(b);
    } else {
        return data_ov121_0229c248[b];
    }
}
