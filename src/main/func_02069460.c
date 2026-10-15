/* func_02069460 @ 0x02069460, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#pragma opt_propagation off
extern void func_0206b97c(void *self, void *part);
void func_02069460(char *self)
{
    char *base = *(char **) (self + 0x24) + 0x14b8;
    func_0206b97c(self, base + 0x1cc);
}
