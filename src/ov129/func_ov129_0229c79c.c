/* func_ov129_0229c79c @ 0x0229c79c, 0x84 bytes, Thumb, module ov129
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov129_0229b7cc(void *p, int n);
extern void *func_ov002_0220a720(void *p, int n);
extern void func_ov002_02208090(void *p, int n);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern void func_ov129_0229bee4(void *p, int n);
extern void func_020b15b8(void *p, int *a, int *b);
extern void func_ov127_022999c0(void *p, int x, int y);
extern void func_0200467c(int cmd);

void func_ov129_0229c79c(unsigned char *self)
{
    int x, y;

    func_ov129_0229b7cc(self, 4);
    func_ov002_0220a720(self + 0x1d4, 6);
    func_ov002_02208090(self, 4);
    func_ov002_02208098((void *) (self), 10);
    func_ov129_0229b7cc(self, 16);
    func_ov129_0229bee4(self, 0);
    func_020b15b8(self + 0x2f78, &x, &y);
    x &= 0xfffc;
    y &= 0xfffc;
    func_ov127_022999c0(self + 0x734, x, y);
    func_0200467c(0x87f);
    func_ov129_0229b7cc(self, 0x80);
}
