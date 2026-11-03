/* rmo_object_slots_2: 2 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_0222c600 @ 0x0222c600, 0x2c bytes, Thumb
 * func_ov004_0222c5c8 @ 0x0222c5c8, 0x38 bytes, Thumb
 */

extern int func_ov004_0222c66c(int, int, void *, void *, void *);
extern int func_02064328(void *, void *, int);
extern void *data_ov004_02254bd4;
extern void *data_ov004_02254be4;

int func_ov004_0222c600(char *self, int a1, int a2)
{
    // DECLS
    // ENDDECLS
    return func_ov004_0222c66c(a1, a2, self + 0xec, self + 0x1a4, self + 0x248);
}

int func_ov004_0222c5c8(char *self, int a1)
{
    // DECLS
    char frame[0x54];
    // ENDDECLS
    func_02064328(frame, &data_ov004_02254bd4, a1);
    func_02064328(frame + 0x28, &data_ov004_02254be4, a1);
    return func_ov004_0222c600((char *) self, (int) frame, (int) (frame + 0x28));
}
