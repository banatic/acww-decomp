/* func_ov004_0220d290 @ 0x0220d290, 0x18 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov004_0220d280(unsigned char *object, unsigned char value, int pending);

#pragma opt_propagation off
void func_ov004_0220d290(unsigned char *self, int pending)
{
    unsigned char value = self[1];
    int next = value + 1;
    value = 1;
    if ((next & value) == 0) {
        value = 0;
    }
    func_ov004_0220d280(self, value, pending);
}
