/* func_0206c49c @ 0x0206c49c, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#pragma opt_propagation off
extern void func_0206d420(void *self, void *part);
void func_0206c49c(char *self)
{
    char *base = *(char **) (self + 0x2c) + 0x18ac;
    func_0206d420(self, base + 0xb8);
}
