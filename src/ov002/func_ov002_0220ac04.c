/* func_ov002_0220ac04 @ 0x0220ac04, 0x48 bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_ov002_0220b338(char *self, int value);
extern void func_ov002_0220b36c(void *, void *, int, int);
extern void *data_ov002_0220be08;
extern void *data_ov002_0220be38;

int func_ov002_0220ac04(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov002_0220b36c(self + 0x80, &data_ov002_0220be08, 0x6, 0x2);
    func_ov002_0220b338(self + 0x80, 0x21);
    func_ov002_0220b36c(self + 0x4, &data_ov002_0220be38, 0x6, 0x2);
    func_ov002_0220b338(self + 0x4, 0x65);
    *(u8 *) (self + 0x1c8) = 0x3;
    return 0x1c8;
}
