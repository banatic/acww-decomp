/* func_ov002_0220a690 @ 0x0220a690, 0x26 bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

extern void func_0208aa90(void *);
extern void func_ov002_0220b150(void *);

void func_ov002_0220a690(char *self)
{
    // DECLS
    int i;
    // ENDDECLS
    func_0208aa90(self + 0xfc);
    for (i = 0; i < 0x2; i++) {
        func_ov002_0220b150(self + 0x4 + (0x7c * i));
    }
}
