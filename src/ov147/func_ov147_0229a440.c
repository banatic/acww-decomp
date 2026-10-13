/* func_ov147_0229a440 @ 0x0229a440, 0x28 bytes, Thumb, module ov147
 * mwccarm 1.2/base -O4,s
 */

extern void FS_OpenFile(int, int, int, int);
extern void FS_ReadFile(int, int, int);
extern void FS_CloseFile(int);

void func_ov147_0229a440(int p0, int p1, int p2, int p3)
{
    FS_OpenFile(p0, p1, p2, p3);
    FS_ReadFile(p0, p2, 0x800);
    FS_CloseFile(p0);
}
