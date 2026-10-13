/* func_ov004_0222f234 @ 0x0222f234, 0x14 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov004_0222f17c();

int func_ov004_0222f234(char *self, int a1, char *a2)
{
    // DECLS
    int v1;
    // ENDDECLS
    v1 = func_ov004_0222f17c(self, a1, a2);
    *(int *) ((char *) *(int *) (a2 + 0xb8)) = v1;
    return v1;
}
