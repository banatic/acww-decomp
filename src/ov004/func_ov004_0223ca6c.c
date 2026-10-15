/* func_ov004_0223ca6c @ 0x0223ca6c, 0x2e bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov004_0223cadc(char *argument0, int argument1);
extern int func_ov004_0223cb5c(void *argument0);
extern int func_ov004_0223cd58(int *argument0, unsigned int argument1);
extern int func_ov004_0223ce84(void);

int func_ov004_0223ca6c(char *self, int index)
{
    // DECLS
    int v1;
    int v2;
    // ENDDECLS
    v1 = func_ov004_0223cadc((char *) (self), (int) (index));
    if (v1 != 0x0) {
        v2 = func_ov004_0223ce84();
        return func_ov004_0223cd58((int *) (v2), (unsigned int) (func_ov004_0223cb5c((void *) (v1))));
    }
    return 0x0;
}
