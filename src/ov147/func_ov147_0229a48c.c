/* func_ov147_0229a48c @ 0x0229a48c, 0x28 bytes, Thumb, module ov147
 * mwccarm 1.2/base -O4,s
 */

extern void FS_OpenFile(int, int, int);
extern void FS_ReadFile(int, int, int);
extern void FS_CloseFile(int);

void func_ov147_0229a48c(int a, int b, int c)
{
    FS_OpenFile(a, b, c);
    FS_ReadFile(a, c, 0x9e0);
    FS_CloseFile(a);
}
