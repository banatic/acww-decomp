/* func_02064828 @ 0x02064828, 0x2e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02064cd8(void *dst, void *src);
extern void func_02064658(void *dst, void *src, void *a3, void *a4);
extern int FS_CloseFile(void *ptr);

void func_02064828(void *r0, void *r1, void *r2, void *r3)
{
    char sp[0x4c];

    func_02064cd8(sp, r0);
    func_02064658(sp, r1, r2, r3);
    FS_CloseFile(sp);
}
