/* func_020f7438 @ 0x020f7438, 0x34 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern int func_020f7bc4(void *param1, int param2, void *param3);

void func_020f7438(void *param1)
{
    func_020f7bc4(param1, 0x501, (void *) ((char *) param1 + 4));
    func_020f7bc4(param1, 0x502, (void *) ((char *) param1 + 8));
}
