/* func_ov127_02299a00 @ 0x02299a00, 0x18 bytes, Thumb, module ov127
 * mwccarm 1.2/base -O4,s
 */

extern void func_020b0ffc(void *ptr, int argument1, int argument2);
extern void func_ov127_02299868(void *ptr, int value);

void func_ov127_02299a00(void *self, int argument1, int argument2)
{
    func_020b0ffc((char *) self + 0x24, argument1, argument2);
    func_ov127_02299868(self, 2);
}
