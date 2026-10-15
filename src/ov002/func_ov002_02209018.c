/* func_ov002_02209018 @ 0x02209018, 0x2c bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

extern int func_02094fbc(void *);
extern void *func_02094fd4(void *);
extern void *func_02095074(int, void *);
extern void *func_020a8bb8(void *, void *);

int func_ov002_02209018(char *self, int a1)
{
    // DECLS
    char frame[0x24];
    // ENDDECLS
    func_02094fd4(frame);
    func_02095074(a1, frame);
    func_020a8bb8(self, frame);
    return func_02094fbc(frame);
}
