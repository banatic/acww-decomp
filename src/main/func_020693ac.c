/* func_020693ac @ 0x020693ac, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#pragma opt_propagation off
extern void func_0206b97c(void *self, void *part);
void func_020693ac(char *self)
{
    char *base = *(char **) (self + 0x24) + 0x18ac;
    func_0206b97c(self, base + 0x5c);
}
