/* func_ov002_0220b764 @ 0x0220b764, 0x54 bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

extern int func_0207094c(void *, int);
extern int func_02070be8(void *);
extern void *func_02070c08(void *);
extern void func_0208aa48(void *, void *);
extern void func_0208aa60(void *, int, int);
extern void func_0208aa98(void *);
extern void func_ov002_02207cec(void *, int);
extern void func_ov002_02207cf8(void *);
extern void func_ov002_02207d00(void *);
extern void func_ov002_0220b6b8(void *receiver);

int func_ov002_0220b764(char *self)
{
    // DECLS
    char frame[0x70];
    // ENDDECLS
    func_02070c08(frame);
    func_0207094c(frame, 0x64);
    func_0208aa48(self, frame);
    func_0208aa60(self, 0x0, 0x40);
    func_ov002_02207cf8(self);
    func_0208aa98(self);
    func_ov002_02207cec(self, 0x0);
    func_ov002_0220b6b8(self);
    func_ov002_02207d00(self);
    return func_02070be8(frame);
}
