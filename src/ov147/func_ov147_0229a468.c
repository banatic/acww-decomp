/* func_ov147_0229a468 @ 0x0229a468, 0x24 bytes, Thumb, module ov147
 * mwccarm 1.2/base -O4,s
 */

extern int FS_OpenFile(void *file, const char *path);
extern int FS_ReadFile(void *a, void *b, int c);
extern int FS_CloseFile(void *a);

void func_ov147_0229a468(void *a0, void *a1, void *a2)
{
    FS_OpenFile((void *) a0, (const char *) a1);
    FS_ReadFile(a0, a2, 0x20);
    FS_CloseFile(a0);
}
