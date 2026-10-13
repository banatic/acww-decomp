/* func_ov146_02299b58 @ 0x02299b58, 0x28 bytes, Thumb, module ov146
 * mwccarm 1.2/base -O4,s
 */

extern void func_0208ea70(void *dest, int size, int value);

void func_ov146_02299b58(char *p)
{
    func_0208ea70(p + 0x1fb4, 0x62, *(int *) (p + 0x94) + (*(int *) (p + 0x98) - 0x28));
}
