/* func_ov004_0223b540 @ 0x0223b540, 0x34 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_020961a8();
extern int func_ov004_0223b574();

int func_ov004_0223b540(char *self, int a1, int a2)
{
    // DECLS
    int v1;
    // ENDDECLS
    v1 = func_020961a8(0x4, a1, a2);
    if (v1 != 0x0) {
        return func_ov004_0223b574(self, a1, (char *) v1 + 0x5c, *(short *) ((char *) v1 + 0x8e), a2);
    }
    return 0x0;
}
