/* func_ov123_0229b598 @ 0x0229b598, 0x34 bytes, Thumb, module ov123
 * mwccarm 1.2/base -O4,s
 */

extern void func_0200467c(int cmd);
extern void func_ov123_02299640(void *self, int arg);
extern void func_ov123_0229b56c(void *self, int a, int b);

void func_ov123_0229b598(void *self)
{
    func_0200467c(0x2a);
    func_ov123_02299640(self, 8);
    if (*(unsigned char *) ((char *) self + 0xac) == 2) {
        *(unsigned char *) ((char *) self + 0xac) = 0;
    }
    func_ov123_0229b56c(self, 6, 8);
}
