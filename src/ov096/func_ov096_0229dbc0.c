/* func_ov096_0229dbc0 @ 0x0229dbc0, 0x28 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_0220a374(void *ptr, int size);
extern void func_ov002_02208098(void *ptr, int value);

void func_ov096_0229dbc0(void *self)
{
    func_ov002_0220a374((char *) self + 0x2500, 4);
    func_ov002_02208098(self, 0x12);
    *((char *) self + 0xb9) = 0x26;
}
