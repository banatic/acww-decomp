/* func_02064cf8 @ 0x02064cf8, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void FS_InitFile(int, int);
extern void FS_OpenFile(int, int);

void func_02064cf8(int a0, int a1)
{
    FS_InitFile(a0, a1);
    FS_OpenFile(a0, a1);
}
