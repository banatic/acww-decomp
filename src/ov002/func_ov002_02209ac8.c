/* func_ov002_02209ac8 @ 0x02209ac8, 0x4c bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

extern void func_02138c48(void *, int, int, void *);
extern void func_ov002_022087bc(void *);
extern void func_ov002_0220b0f4(void *);
extern void func_ov002_0220b464(void *);
extern void func_ov002_02209bf0();
extern void *data_ov002_0220bb98;

void *func_ov002_02209ac8(char *self)
{
    // DECLS
    // ENDDECLS
    *(void **) (self) = &data_ov002_0220bb98;
    func_ov002_022087bc(self + 0x3b0);
    func_ov002_0220b0f4(self + 0x2e4);
    func_ov002_0220b464(self + 0x26c);
    func_02138c48(self + 0x28, 0x5, 0x74, (void *) func_ov002_02209bf0);
    return self;
}
