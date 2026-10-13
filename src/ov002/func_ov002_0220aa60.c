/* func_ov002_0220aa60 @ 0x0220aa60, 0x6c bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_ov002_0220b04c(char *p);
extern void func_ov002_0220b06c(char *p, void *a, int b, int c);
extern void func_0208aa68(char *p);
extern void func_ov002_0220b36c();
extern void func_ov002_0220b338();
extern void *data_ov002_0220bd38;
extern void *data_ov002_0220bd20;

int func_ov002_0220aa60(char *self, void *arg)
{
    func_ov002_0220b04c(self + 0xfc);
    func_ov002_0220b06c(self + 0xfc, arg, 0x80, 0x11);
    func_0208aa68(self + 0xfc);
    func_ov002_0220b36c(self + 0x4, &data_ov002_0220bd38, 0x4, 0x1);
    func_ov002_0220b338(self + 0x4, 0x4);
    func_ov002_0220b36c(self + 0x80, &data_ov002_0220bd20, 0x4, 0x1);
    func_ov002_0220b338(self + 0x80, 0x13);
    *(u8 *) (self + 0x1c8) = 0x8;
    return 0x1c8;
}
