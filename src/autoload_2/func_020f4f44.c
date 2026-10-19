/* func_020f4f44 @ 0x020f4f44, 0x20 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void NNS_FndInitList(char *self, int flag);
extern void func_020eed48(char *res);

void func_020f4f44(char *self)
{
    NNS_FndInitList(self, 0);
    func_020eed48(self + 0xC);
}
