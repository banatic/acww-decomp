/* func_ov133_0229c0a4 @ 0x0229c0a4, 0x54 bytes, Thumb, module ov133
 * mwccarm 1.2/base -O4,s
 */

extern void func_02064af4(void *, void *, int);
extern void func_ov130_0229a678(int);
extern int func_ov133_0229ad78(void *, int);
extern void func_ov133_0229b2ac(void *);
extern void *data_ov133_0229c968;
extern void *data_ov133_0229c97c;

int func_ov133_0229c0a4(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov130_0229a678(0x4);
    func_02064af4(&data_ov133_0229c968, self + 0xb94, 0x800);
    func_02064af4(&data_ov133_0229c97c, self + 0x394, 0x800);
    func_ov133_0229b2ac(self);
    func_ov133_0229ad78(self, 0x2);
    return func_ov133_0229ad78(self, 0x4);
}
