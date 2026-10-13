/* func_ov122_022a1a58 @ 0x022a1a58, 0x2c bytes, Thumb, module ov122
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_022097b8(void *);
extern void func_ov122_0229f0dc(void *, int);
extern void func_ov002_022080a0(void *, int);

void func_ov122_022a1a58(void *self)
{
    *((unsigned char *) self + 0xb7) = 0;
    func_ov002_022097b8((char *) self + 0x42b0);
    func_ov122_0229f0dc(self, 1);
    func_ov002_022080a0(self, 2);
}
