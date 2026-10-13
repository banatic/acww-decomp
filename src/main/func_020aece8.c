/* func_020aece8 @ 0x020aece8, 0x50 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_020aefbc(unsigned short *p);
extern void func_020b00fc(unsigned short *p0, unsigned int *p1, int p2, int p3, unsigned int p4, int p5, int p6);
extern unsigned short data_020d1e5c[];

void func_020aece8(unsigned short *param0, unsigned int *param1)
{
    unsigned int start;
    unsigned int i;
    unsigned short *p;

    start = *param1;
    func_020b00fc(param0 + 2, param1, 0, 12, func_020aefbc(param0), 37, 0);

    for (i = start; i < start + func_020aefbc(param0); i++) {
        p = param0 + i;
        p[2] = data_020d1e5c[p[2]];
    }
}
