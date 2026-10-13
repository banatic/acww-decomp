/* func_0204b7a0 @ 0x0204b7a0, 0x56 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0204b7f8(void *);
extern int func_0204ba94(void *);
extern int func_0204ba40(void *);
extern int func_0204b9ec(void *);
extern int func_0204b998(void *);

int func_0204b7a0(void *p)
{
    int r5 = -1;
    if (func_0204b7f8(p) != 0) {
        if (func_0204ba94(p) != 0) {
            r5 = 0;
        } else if (func_0204ba40(p) != 0) {
            r5 = 1;
        } else if (func_0204b9ec(p) != 0) {
            r5 = 2;
        } else if (func_0204b998(p) != 0) {
            r5 = 3;
        } else {
            r5 = 4;
        }
    }
    return r5;
}
