/* func_ov122_022a1d60 @ 0x022a1d60, 0x9e bytes, Thumb, module ov122
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov122_022a1808(void);
extern void func_ov122_022a1770(void *);
extern void func_ov095_0229c420(void *, int);
extern void func_ov095_0229bf7c(void *, int);
extern void func_ov002_02207f20(void *, int, int, int, int);
extern void func_02002708(int);
extern void func_ov002_02207e80(void *, int, int, int);
extern void func_ov122_022a1764(void *);
extern void func_ov122_022a1738(void *);
extern void func_ov122_0229efd8(void *, int);
extern int func_ov002_02207f60(void *);
extern void func_ov002_02208090(void *, int);

void func_ov122_022a1d60(void *self)
{
    func_ov122_022a1808();
    func_ov122_022a1770(self);
    func_ov095_0229c420((char *) self + 0xc0, 6);
    func_ov095_0229bf7c((char *) self + 0xc0, 6);
    func_ov002_02207f20(self, 0xb, 0, 0, 0x30);
    func_02002708(6);
    func_02002708(4);
    func_02002708(3);
    func_ov002_02207e80(self, 6, 0, 0);
    func_ov002_02207e80(self, 4, 0, ~0xf);
    func_ov002_02207e80(self, 3, 0, ~0xf);
    func_ov122_022a1764(self);
    func_ov122_022a1738(self);
    func_ov122_0229efd8(self, 1);
    *(int *) ((char *) self + 0x94) = func_ov002_02207f60(self);
    func_ov002_02208090(self, 1);
}
