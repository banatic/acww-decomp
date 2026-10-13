/* func_ov101_0229cfa0 @ 0x0229cfa0, 0x34 bytes, Thumb, module ov101
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov101_0229c8bc(void *);
extern void func_ov101_0229ca58(void *);
extern void func_ov101_0229cb60(void *, unsigned char);
extern void func_ov002_02207fc0(void *);
extern void func_ov002_02208098(void *, int);

void func_ov101_0229cfa0(void *self)
{
    unsigned char *p = (unsigned char *) self;
    p[0xb1] = 0x10;
    func_ov101_0229c8bc(self);
    func_ov002_02207fc0(self);
    func_ov101_0229ca58(self);
    func_ov002_02208098(self, 6);
    func_ov101_0229cb60(self, p[0xb3]);
}
