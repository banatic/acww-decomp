/* func_ov004_0220e504 @ 0x0220e504, 0x30 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov004_0220cfd0(unsigned char *argument0);
extern int func_ov004_0220cfd4(void *argument0, int argument1);

int func_ov004_0220e504(char *self, int a1, char *a2)
{
    // DECLS
    int v1;
    int v2;
    // ENDDECLS
    v1 = func_ov004_0220cfd4((void *) ((void *) (self + 0x764)), (int) ((int) (a1)));
    if (v1 != 0x0) {
        v2 = func_ov004_0220cfd0((unsigned char *) (self + 0x764));
        *(int *) ((char *) *(int *) (a2 + 0xb8)) = v2;
        return v2;
    }
    return v1;
}
