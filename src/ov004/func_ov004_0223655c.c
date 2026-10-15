/* func_ov004_0223655c @ 0x0223655c, 0x1a bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_02054cf4(void *, void *);

void func_ov004_0223655c(char *self)
{
    // DECLS
    // ENDDECLS
    if (*(int *) ((char *) *(int *) (self + 0x4) + 0x2c) != 0x0) {
        func_02054cf4((char *) *(int *) ((char *) *(int *) (self + 0x4) + 0x2c) + 0x64, self);
    }
}
