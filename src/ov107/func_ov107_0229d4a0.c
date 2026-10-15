/* func_ov107_0229d4a0 @ 0x0229d4a0, 0x34 bytes, Thumb, module ov107
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov107_0229cf08(void *);
extern void func_ov107_0229cf90(void *);
extern void func_ov107_0229d054(void *object, int index);
extern void func_ov002_02207fc0(void *);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);

void func_ov107_0229d4a0(void *self)
{
    unsigned char *p = (unsigned char *) self;
    p[0xb7] = 0x10;
    func_ov107_0229cf08(self);
    func_ov002_02207fc0(self);
    func_ov107_0229cf90(self);
    func_ov002_02208098((void *) (self), 5);
    func_ov107_0229d054(self, ((unsigned char *) self)[0xb8]);
}
