/* func_020b3b38 @ 0x020b3b38, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *data_021f4b2c;

int func_020b3b38(void *arg)
{
    if (data_021f4b2c == 0) {
        data_021f4b2c = arg;
        return 1;
    }
    return 0;
}
