/* func_ov004_0222c5c8 @ 0x0222c5c8, 0x38 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_02064328(void *, void *, int);
extern int func_ov004_0222c600(void *, void *, void *);
extern void *data_ov004_02254bd4;
extern void *data_ov004_02254be4;

int func_ov004_0222c5c8(char *self, int a1)
{
    // DECLS
    char frame[0x54];
    // ENDDECLS
    func_02064328(frame, &data_ov004_02254bd4, a1);
    func_02064328(frame + 0x28, &data_ov004_02254be4, a1);
    return func_ov004_0222c600(self, frame, frame + 0x28);
}
