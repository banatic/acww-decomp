/* func_ov004_0223cb30 @ 0x0223cb30, 0x22 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_020ea990();
extern int func_ov004_0223cb54();
extern int func_ov004_0223cb58();

int func_ov004_0223cb30(char *self)
{
    // DECLS
    int v1;
    // ENDDECLS
    v1 = func_ov004_0223cb54(self);
    return func_020ea990(v1, func_ov004_0223cb58(self));
}
