/* func_ov004_022304bc @ 0x022304bc, 0x1c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov004_022308dc(int);
extern void *data_ov004_02258870;

int func_ov004_022304bc(char *self)
{
    // DECLS
    // ENDDECLS
    if (*(int *) ((char *) &data_ov004_02258870) != 0x0) {
        return func_ov004_022308dc(*(int *) ((char *) &data_ov004_02258870));
    }
    return *(int *) ((char *) &data_ov004_02258870);
}
