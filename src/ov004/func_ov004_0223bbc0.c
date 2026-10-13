/* func_ov004_0223bbc0 @ 0x0223bbc0, 0x3a bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_020961a8();
extern int func_ov004_0223bbfc();

int func_ov004_0223bbc0(char *self, int a1, int a2, int a3)
{
    // DECLS
    int v1;
    // ENDDECLS
    v1 = func_020961a8(0x4, a1, a2, a3);
    if (v1 != 0x0) {
        return func_ov004_0223bbfc(self, a1, (char *) v1 + 0x5c, *(short *) ((char *) v1 + 0x8e), a2, a3);
    }
    return -0x1;
}
