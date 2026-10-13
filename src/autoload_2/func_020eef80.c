/* func_020eef80 @ 0x020eef80, 0x54 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

func_020eef80(unsigned char *arg0)
{
    unsigned int local_0;
    unsigned int local_4;

    if (arg0 == 0) {
        OS_Terminate();
    }
    local_4 = MIi_ReadWordStreamFromMemory(arg0);
    if (local_4 == 0) {
        return;
    }
    do {
        func_020ef284(local_4);
        local_4 = func_020efc2c(arg0, local_4);
    } while (local_4 != 0);
}
