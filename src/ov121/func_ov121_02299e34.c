/* func_ov121_02299e34 @ 0x02299e34, 0x20 bytes, Thumb, module ov121
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_ov121_0229c210[];
extern void func_ov002_0220a2b4(void *p);

void func_ov121_02299e34(unsigned char *p, int idx)
{
    p[0xb1] = data_ov121_0229c210[idx];
    func_ov002_0220a2b4(p + 0x3a8);
}
