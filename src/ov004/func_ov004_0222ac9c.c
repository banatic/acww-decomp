/* func_ov004_0222ac9c @ 0x0222ac9c, 0x24 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_0200faa8(void *, int);
extern int func_0200fb58(void *, int, int);
extern void *data_ov004_02247774;

int func_ov004_0222ac9c(char *self)
{
    // DECLS
    // ENDDECLS
    func_0200faa8(self, 0x400);
    return func_0200fb58(self, *(int *) ((char *) &data_ov004_02247774), *(int *) ((char *) &data_ov004_02247774 + 0x8));
}
