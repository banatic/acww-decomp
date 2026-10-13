/* func_ov137_0229c92c @ 0x0229c92c, 0x4c bytes, Thumb, module ov137
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_0220a720(void *ptr, int n);
extern void func_ov002_02208090(void *ptr, int n);
extern void func_ov002_02208098(void *ptr, int n);
extern void *func_020984e8(void);
extern void func_ov134_0229bbdc(void *dst, void *src);
extern void func_020992d0(void *ptr, int a, int b);

void func_ov137_0229c92c(char *self)
{
    unsigned int local[3];
    void *r;
    func_ov002_0220a720(self + 0xf8, 6);
    func_ov002_02208090(self, 2);
    func_ov002_02208098(self, 0xb);
    r = func_020984e8();
    local[0] = 0;
    local[1] = 0;
    func_ov134_0229bbdc(self + 0x2c4, local);
    func_020992d0(r, ((unsigned char *) local)[4], ((unsigned char *) local)[3]);
}
