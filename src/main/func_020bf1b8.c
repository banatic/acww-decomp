/* func_020bf1b8 @ 0x020bf1b8, 0x68 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void FS_InitFile(void);
extern void MI_CpuFill8(void *dst, int val, unsigned int size);

void func_020bf1b8(void *self)
{
    FS_InitFile();
    MI_CpuFill8((char *) self + 0x48, 0, 0x400);
    MI_CpuFill8((char *) self + 0x448, 0, 0xc00);
    MI_CpuFill8((char *) self + 0x1048, 0, 0x1c0);
    MI_CpuFill8((char *) self + 0x1208, 0, 0x140);
    *(unsigned int *) ((char *) self + 0x1348) = 0x12345678;
}
