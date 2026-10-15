/* func_02064cf8 @ 0x02064cf8, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void FS_InitFile(void *file);
extern int FS_OpenFile(void *file, const char *path);

int func_02064cf8(void *file, const char *path)
{
    FS_InitFile(file);
    return FS_OpenFile(file, path);
}
