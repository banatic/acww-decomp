/* music_list_input_2: 2 functions, module ov144
 * mwccarm 1.2/base -O4,s
 * func_ov144_0229a0c8 @ 0x0229a0c8, 0x18 bytes, Thumb
 * func_ov144_0229a0a4 @ 0x0229a0a4, 0x24 bytes, Thumb
 */

extern void func_ov002_0220a1dc(void *);
extern unsigned char *func_ov002_02208098(void *, unsigned char value);
extern void func_ov002_0220a164(void *);

void func_ov144_0229a0c8(void *self)
{
    func_ov002_0220a1dc((char *) self + 0xc4);
    func_ov002_02208098(self, 7);
}

void func_ov144_0229a0a4(void *arg0)
{
    func_ov002_0220a164((char *) arg0 + 0xc4);
    *((unsigned char *) arg0 + 0xbe) = *((unsigned char *) arg0 + 0x8d);
    func_ov002_02208098(arg0, 8);
}
