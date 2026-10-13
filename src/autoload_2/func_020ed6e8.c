/* func_020ed6e8 @ 0x020ed6e8, 0x54 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021fbf68[];

void func_020ed6e8(unsigned char *cmd)
{
    switch (cmd[0]) {
        case 0:
            data_021fbf68[cmd[1]] = 1;
            break;
        case 1:
            data_021fbf68[cmd[1]] = 0;
            break;
        case 2:
            data_021fbf68[0] = 0xff;
            break;
    }
}
