/* func_ov004_0221d4c0 @ 0x0221d4c0, 0x28 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov004_0221cff8(char *self);
extern void *data_ov004_02257a18;

int func_ov004_0221d4c0(void)
{
    // DECLS
    // ENDDECLS
    if (*(int *) ((char *) &data_ov004_02257a18) != 0x0) {
        return func_ov004_0221cff8((char *) *(int *) ((char *) &data_ov004_02257a18) + 0x8a0);
    }
    return 0x0;
}
