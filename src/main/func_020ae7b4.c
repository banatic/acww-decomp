/* func_020ae7b4 @ 0x020ae7b4, 0x60 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_02062124(int);
extern unsigned int func_02062118(unsigned int);
extern unsigned int func_02063cd4(unsigned int, unsigned int);
extern void func_020b0164(int, int, int, int, int, int, int);

extern unsigned char data_021f4a80[];

void func_020ae7b4(int p0, int p1)
{
    unsigned int v1, v2, v3, v4;

    v1 = func_02062124(p0);
    v2 = func_02062118(v1);
    v3 = func_02063cd4((unsigned int) data_021f4a80, v1 + v2);
    v4 = func_02062124(v3);

    if (v3 < v4) {
        func_020b0164(p0, p1, 6, 0x1d, 1, 6, 1);
    } else {
        func_020b0164(p0, p1, 8, 0x1d, 1, 6, 1);
    }
}
