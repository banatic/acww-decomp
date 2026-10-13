/* func_ov147_02298f20 @ 0x02298f20, 0x34 bytes, Thumb, module ov147
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short data_ov147_0229b2ac[];
extern void func_ov147_02298f54(int, int, int);

void func_ov147_02298f20(int a, int b, int c, int d)
{
    int mask = data_ov147_0229b2ac[c + (d << 5)] & 0x3ff;
    if (mask != 0x10 && mask >= 0x140) {
        func_ov147_02298f54(a, b, mask - 0x140);
    }
}
