/* func_020693f0 @ 0x020693f0, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#pragma opt_propagation off
extern void func_0206b97c(void *self, void *part);
void func_020693f0(char *self)
{
    char *base = *(char **) (self + 0x24) + 0x14b8;
    func_0206b97c(self, base + 0x33c);
}
