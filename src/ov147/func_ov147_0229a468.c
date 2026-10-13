/* func_ov147_0229a468 @ 0x0229a468, 0x24 bytes, Thumb, module ov147
 * mwccarm 1.2/base -O4,s
 */

extern void FS_OpenFile(void *a, void *b, void *c, void *d);
extern void FS_ReadFile(void *a, void *b, int c);
extern void FS_CloseFile(void *a);

void func_ov147_0229a468(void *a0, void *a1, void *a2, void *a3)
{
    FS_OpenFile(a0, a1, a2, a3);
    FS_ReadFile(a0, a2, 0x20);
    FS_CloseFile(a0);
}
