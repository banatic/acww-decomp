/* func_ov100_0229d8d0 @ 0x0229d8d0, 0x3c bytes, Thumb, module ov100
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov100_0229ccb8(void *);
extern void func_ov100_0229cecc(void *);
extern void func_ov100_0229d068(void *, unsigned char);
extern void func_ov002_02207fc0(void *);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);

void func_ov100_0229d8d0(void *self)
{
    ((unsigned char *) self)[0x291f] = 0x20;
    func_ov100_0229ccb8(self);
    func_ov002_02207fc0(self);
    func_ov100_0229cecc(self);
    func_ov002_02208098((void *) (self), 4);
    func_ov100_0229d068(self, ((unsigned char *) self)[0x2921]);
}
