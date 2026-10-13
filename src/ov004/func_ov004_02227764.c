/* func_ov004_02227764 @ 0x02227764, 0x30 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_020109fc();
extern int func_02073908();
extern void *data_020ccf94;

int func_ov004_02227764(char *self)
{
    // DECLS
    int v3;
    // ENDDECLS
    v3 = func_02073908(*(int *) ((char *) &data_020ccf94), *(int *) (self + 0x800));
    if (v3 == 0x0) {
        return func_020109fc(self, 0x0, 0x3, 0x3);
    }
    return v3;
}
