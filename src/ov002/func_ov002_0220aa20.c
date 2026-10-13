/* func_ov002_0220aa20 @ 0x0220aa20, 0x40 bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_0220b338(void *, int);
extern void func_ov002_0220b36c(void *, void *, int, int);
extern void *data_ov002_0220be08;
extern void *data_ov002_0220be38;

int func_ov002_0220aa20(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov002_0220b36c(self + 0x4, &data_ov002_0220be08, 0x6, 0x2);
    func_ov002_0220b338(self + 0x4, 0x4);
    func_ov002_0220b36c(self + 0x80, &data_ov002_0220be38, 0x6, 0x2);
    return func_ov002_0220b338(self + 0x80, 0x13);
}
