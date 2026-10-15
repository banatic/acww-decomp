/* func_ov004_0220fdec @ 0x0220fdec, 0x38 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov004_0220d4c0(void *argument0);
extern int func_ov004_0220d4c8(short *argument0);
extern int func_ov004_0223cd58(int *argument0, unsigned int argument1);
extern int func_ov004_0223ce84(void);

int func_ov004_0220fdec(char *self)
{
    // DECLS
    int v1;
    int v2;
    // ENDDECLS
    v1 = func_ov004_0220d4c8((short *) (self + 0x17c));
    if (v1 != 0x0) {
        v2 = func_ov004_0223ce84();
        return func_ov004_0223cd58((int *) (v2), (unsigned int) (func_ov004_0220d4c0(self + 0x17c)));
    }
    return 0x0;
}
