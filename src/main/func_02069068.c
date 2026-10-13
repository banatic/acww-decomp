/* func_02069068 @ 0x02069068, 0x70 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int FS_OpenFile(const void *src, const void *data);
extern void *func_020e98d4(int size);
extern int FS_ReadFile(const void *src, void *dst, int size);
extern int FS_CloseFile(const void *src);

extern unsigned char data_020df100[];
extern unsigned char data_020df11c[];

int func_02069068(void **out, const void *src, int flag)
{
    const void *addr;
    int result1;
    int flag3;
    int result4;

    if (flag) {
        addr = (const void *) data_020df100;
    } else {
        addr = (const void *) data_020df11c;
    }

    result1 = FS_OpenFile(src, addr);
    *out = func_020e98d4(0x800);

    if (*out != 0) {
        if (FS_ReadFile(src, *out, 0x800) == -1) {
            flag3 = 0;
        } else {
            flag3 = 1;
        }
    } else {
        flag3 = 0;
    }

    result4 = FS_CloseFile(src);

    if (result1 != 0 && flag3 != 0 && result4 != 0 && *out != 0) {
        return 1;
    } else {
        return 0;
    }
}
