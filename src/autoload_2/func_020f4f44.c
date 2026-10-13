/* func_020f4f44 @ 0x020f4f44, 0x20 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void NNS_FndInitList(char *self, int flag);
extern int ENV_AppendResourceSet(char *res);

int func_020f4f44(char *self)
{
    NNS_FndInitList(self, 0);
    return ENV_AppendResourceSet(self + 0xC);
}
