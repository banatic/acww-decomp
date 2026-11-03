/* order_catalog_cursor_3: 2 functions, module ov142
 * mwccarm 1.2/base -O4,s
 * func_ov142_0229aee8 @ 0x0229aee8, 0x18 bytes, Thumb
 * func_ov142_0229aec4 @ 0x0229aec4, 0x24 bytes, Thumb
 */

extern void func_ov002_0220a1dc(void *);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern void func_ov002_0220a164(void *p);

void func_ov142_0229aee8(void *self)
{
    func_ov002_0220a1dc((char *) self + 0xe8);
    func_ov002_02208098((void *) (self), 9);
}

void func_ov142_0229aec4(unsigned char *self)
{
    func_ov002_0220a164(self + 0xe8);
    self[0xba] = self[0x8d];
    func_ov002_02208098((void *) (self), 0xa);
}
