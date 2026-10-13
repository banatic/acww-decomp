/* func_ov004_0222c62c @ 0x0222c62c, 0x40 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_02064328();
extern int func_ov004_0222c66c(void *, void *, int, int, int);
extern void *data_ov004_02254bd4;
extern void *data_ov004_02254be4;

int func_ov004_0222c62c(char *self, int a1, int a2, int a3)
{
    // DECLS
    char frame[0x50];
    // ENDDECLS
    func_02064328(frame, &data_ov004_02254bd4, self, a3);
    func_02064328(frame + 0x28, &data_ov004_02254be4, self);
    return func_ov004_0222c66c(frame, frame + 0x28, a1, a2, a3);
}
