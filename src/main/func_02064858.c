/* func_02064858 @ 0x02064858, 0x22 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02064cf8(void *buffer, int arg1);
extern int FS_CloseFile(void *buffer);

int func_02064858(int arg0)
{
    char buffer[72];
    int result;
    result = func_02064cf8(buffer, arg0);
    if (result) {
        FS_CloseFile(buffer);
    }
    return result;
}
