/* func_ov002_02208fcc @ 0x02208fcc, 0x2c bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

extern void func_02003618(int, void *);
extern int func_02094fbc(void *);
extern void func_02094fd4(void *, int);
extern void func_020a8bb8(void *, void *);

int func_ov002_02208fcc(char *self, int a1)
{
    // DECLS
    char frame[0x24];
    // ENDDECLS
    func_02094fd4(frame, a1);
    func_02003618(a1, frame);
    func_020a8bb8(self, frame);
    return func_02094fbc(frame);
}
