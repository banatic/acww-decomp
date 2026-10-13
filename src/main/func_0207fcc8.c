/* func_0207fcc8 @ 0x0207fcc8, 0x54 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0204bcdc(void *);
extern int func_02080834(void *, void *);

int func_0207fcc8(void *p1, void *p2)
{
    int r6 = 0;
    int r4 = 0;
    int r1;
    unsigned short r0;
    int r2;

    if (func_0204bcdc(p2) != 0) {
        r1 = 0;
        r0 = *(unsigned short *) p2;
        if (r0 >= 0x450c && r0 <= 0x45db) {
            r1 = 1;
        }
        if (r1 == 0) {
            r4 = 1;
        }
    }
    if (r4 != 0) {
        if (func_02080834(p1, p2) > 0) {
            r6 = 1;
        }
    }
    return r6;
}
