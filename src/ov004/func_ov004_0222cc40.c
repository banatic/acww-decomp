/* func_ov004_0222cc40 @ 0x0222cc40, 0x20 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov004_0222c598(void *);
extern int func_ov004_0222c8f4(void *);
extern void *data_ov004_02258224;

int func_ov004_0222cc40(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov004_0222c8f4(self);
    func_ov004_0222c598(self);
    *(void **) ((char *) &data_ov004_02258224) = 0x0;
    return 0x1;
}
