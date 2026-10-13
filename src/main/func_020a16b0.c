/* func_020a16b0 @ 0x020a16b0, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02050af8(void *base, unsigned int mask, char *flag, int param);
extern unsigned int data_021c8188;

int func_020a16b0(void)
{
    char flag = 0;
    if (func_02050af8(&data_021c8188, 0x0003fffc, &flag, 1) == 1) {
        return 1;
    } else {
        return 0;
    }
}
