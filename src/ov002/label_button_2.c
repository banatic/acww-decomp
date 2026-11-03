/* label_button_2: 2 functions, module ov002
 * mwccarm 1.2/base -O4,s
 * func_ov002_0220b550 @ 0x0220b550, 0x2c bytes, Thumb
 * func_ov002_0220b53c @ 0x0220b53c, 0x12 bytes, Thumb
 */

extern int func_0207094c(void *, int);
extern int func_02070be8(void *);
extern void *func_02070c08(void *);
extern void func_0208f218(void *, void *);
extern void func_ov002_0220b4fc(void *, int, int, int);

int func_ov002_0220b550(char *self, int a1)
{
    // DECLS
    char frame[0x6c];
    // ENDDECLS
    func_02070c08(frame);
    func_0207094c(frame, a1);
    func_0208f218(self, frame);
    return func_02070be8(frame);
}

void func_ov002_0220b53c(char *self, int a1)
{
    // DECLS
    // ENDDECLS
    func_ov002_0220b4fc(self, a1, 0x98, 0xac);
}
