/* func_ov123_02299684 @ 0x02299684, 0x58 bytes, Thumb, module ov123
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov123_02299650(void *p, int x);
extern void func_ov123_02299930(void *p);
extern void func_ov123_02299640(void *p, int x);
extern void func_02001a7c(void);
extern void func_02001a1c(int x);
extern void func_ov002_0220a6b8(void *p);
extern void func_02001d60(int a, int b);
extern void func_02001b7c(int a);
extern void func_02001c58(int a, int b, int c, int d);

void func_ov123_02299684(void *self)
{
    if (func_ov123_02299650(self, 0x20) != 0) {
        func_ov123_02299930(self);
        func_ov123_02299640(self, 0x00020000);
    }
    func_02001a7c();
    func_02001a1c(~5);
    func_ov002_0220a6b8((char *) self + 0x5030);
    func_02001d60(0x1f, 0);
    func_02001b7c(2);
    func_02001c58(0x40, 0x18, 0xc0, 0x98);
}
