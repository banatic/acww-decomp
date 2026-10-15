/* func_0207f590 @ 0x0207f590, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0204bcdc(void *item);
extern int func_02053bc0(int item);

extern unsigned short data_020cd42c[];

void func_0207f590(unsigned short *r5, int r1, int r2)
{
    unsigned short *p = r5;
    int r4 = r2;
    int r0;

    *p = 0xfff1;
    r0 = func_0204bcdc((void *) r4);
    if (r0 != 0) {
        r0 = func_02053bc0(r4);
        if (r0 < 3) {
            *p = data_020cd42c[r0];
        }
    }
}
