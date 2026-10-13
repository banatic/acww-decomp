/* func_02010e58 @ 0x02010e58, 0x5c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02010eb4(void *self, int param);
extern void func_02089b80(void *dst, void *src, int a, unsigned int b, int c, int d, int e, int f, unsigned char g, int h);

void func_02010e58(void *self, int param2, int param3)
{
    int r = func_02010eb4(self, param3);
    func_02089b80((char *) self + 0x174, self, param2, 0x0fd7, 0x2800, r | 4, 0x2fc, 0x15,
                  (unsigned char) (*(unsigned int *) ((char *) self + 0x800)), 0x1000);
}
