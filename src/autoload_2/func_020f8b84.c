/* func_020f8b84 @ 0x020f8b84, 0x38 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void func_020f7bc4(void *param1, int param2, void *param3);

void func_020f8b84(void *param1)
{
    func_020f7bc4(param1, 0x50f, (char *) param1 + 8);
    func_020f7bc4(param1, 0x510, (char *) param1 + 4);
    *(unsigned char *) ((char *) param1 + 0xd) = 1;
}
