/* func_ov147_0229a440 @ 0x0229a440, 0x28 bytes, Thumb, module ov147
 * mwccarm 1.2/base -O4,s
 */

extern int FS_OpenFile(void *file, const char *path);
extern int FS_ReadFile(int, int, int);
extern int FS_CloseFile(int);

void func_ov147_0229a440(int p0, int p1, int p2)
{
    FS_OpenFile((void *) p0, (const char *) p1);
    FS_ReadFile(p0, p2, 0x800);
    FS_CloseFile(p0);
}
