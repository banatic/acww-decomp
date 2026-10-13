/* func_02037f74 @ 0x02037f74, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void FS_InitFile(void *);
extern int FS_OpenFile(void *, const void *);
extern void FS_ReadFile(void *, const void *, int);
extern void FS_CloseFile(void *);

extern unsigned char data_020da4c4[];
extern unsigned char data_021c5914[];

void func_02037f74(void)
{
    char buffer[0x4c];
    int result;

    FS_InitFile(buffer);
    result = FS_OpenFile(buffer, (const void *) data_020da4c4);
    if (result == 1) {
        FS_ReadFile(buffer, (const void *) data_021c5914, 0x20);
        FS_CloseFile(buffer);
    }
}
