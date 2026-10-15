/* func_020ade0c @ 0x020ade0c, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020afb24(void *p);
extern void func_020ade44(int a, unsigned short b);

extern unsigned char data_021f395c[];

void func_020ade0c(int arg0, int arg1)
{
    unsigned short r4;
    r4 = (unsigned short) (arg1 / 100);
    if (func_020afb24((void *) data_021f395c)) {
        r4 = (unsigned short) (r4 * 5);
    }
    func_020ade44(arg0, r4);
}
