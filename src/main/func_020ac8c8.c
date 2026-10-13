/* func_020ac8c8 @ 0x020ac8c8, 0x26 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern __arm void FS_InitFile(void *buffer);
extern int func_020ac8f0(void *param, void *buffer);

int func_020ac8c8(void *param)
{
    unsigned char buffer[0x4c];
    int result = 0;

    FS_InitFile(buffer);
    if (func_020ac8f0(param, buffer) != 0) {
        result = 1;
    }
    return result;
}
