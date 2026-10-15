/* func_ov004_0223c820 @ 0x0223c820, 0x3a bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov004_0220ce5c();
extern int func_ov004_0223ca6c(char *argument0, int argument1);
extern int func_ov004_0223cadc(char *argument0, int argument1);
extern int func_ov004_0223cb18(void *argument0);

int func_ov004_0223c820(char *self)
{
    // DECLS
    int v1;
    int v2;
    // ENDDECLS
    v1 = func_ov004_0223cadc(self, 0x0);
    v2 = func_ov004_0223ca6c((char *) ((char *) (self)), (int) ((int) (0x0)));
    if (v1 != 0x0 && v2 != 0x0) {
        return func_ov004_0220ce5c(v2, func_ov004_0223cb18((void *) (v1)));
    }
    return 0x0;
}
