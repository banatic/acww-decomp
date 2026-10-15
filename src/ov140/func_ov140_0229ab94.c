/* func_ov140_0229ab94 @ 0x0229ab94, 0x38 bytes, Thumb, module ov140
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov139_022999f8(void *);
extern void func_ov139_022999c4(void *);
extern int func_02064af4(const void *, void *, unsigned int);
extern void func_ov140_0229a41c(void *);
extern const unsigned char data_ov140_0229b5b4[];

void func_ov140_0229ab94(void *self)
{
    func_ov139_022999f8((char *) self + 0x8e8);
    func_ov139_022999c4((char *) self + 0x8e8);
    func_02064af4(data_ov140_0229b5b4, (char *) self + 0xac, 0x800);
    func_ov140_0229a41c(self);
}
