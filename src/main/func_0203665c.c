/* func_0203665c @ 0x0203665c, 0x2e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02035624(int);
extern void func_02035638(int);

void func_0203665c(unsigned char *r0)
{
    unsigned char *r4 = r0;
    if (r4[0xc] != 0) {
        func_02035624(0x10);
        r4[0xc] = 0;
    }
    if (r4[0xd] != 0) {
        func_02035638(0x51);
        r4[0xd] = 0;
    }
    r4[0xe] = 0;
}
