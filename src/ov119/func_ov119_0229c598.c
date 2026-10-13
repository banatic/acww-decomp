/* func_ov119_0229c598 @ 0x0229c598, 0x5a bytes, Thumb, module ov119
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov119_0229c2a8(void *);
extern void func_ov119_0229c218(void *);
extern void func_ov119_0229c1a0(void *);
extern void func_ov119_0229bb0c(void *);
extern int func_ov002_02209770(void *);
extern int func_0206f52c(int);
extern int func_0206f50c(void);
extern int func_0206fc8c(int);
extern int func_ov119_0229a650(void *, int);
extern void func_ov119_0229a69c(void *, int);
extern void func_ov002_02208090(void *, int);
extern void func_ov119_0229c534(void *);

void func_ov119_0229c598(void *self)
{
    func_ov119_0229c2a8(self);
    func_ov119_0229c218(self);
    func_ov119_0229c1a0(self);
    func_ov119_0229bb0c(self);
    func_ov119_0229a69c(self, func_ov119_0229a650(self, (func_0206f52c(func_ov002_02209770((char *) self + 0xdc)) != 0)
                                                            ? func_0206fc8c(func_0206f50c())
                                                            : 0));
    func_ov002_02208090(self, 1);
    func_ov119_0229c534(self);
}
