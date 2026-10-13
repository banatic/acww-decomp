/* func_ov004_02213b70 @ 0x02213b70, 0x18 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

void func_ov004_02213b70(char *self, int a1, char *a2)
{
    // DECLS
    // ENDDECLS
    if (a1 == *(int *) (self + 0x844)) {
        *(void **) ((char *) *(int *) (a2 + 0xb8)) = 0x0;
    }
}
