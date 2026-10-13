/* func_ov134_0229aaa8 @ 0x0229aaa8, 0x30 bytes, Thumb, module ov134
 * mwccarm 1.2/base -O4,s
 */

extern void *data_ov134_0229bfd4[];
extern void *data_ov134_0229bfec[];
extern void *data_ov134_0229bf74[];

typedef struct {
    char pad_00[0xa0];
    unsigned char sel;
} FileInfo;

void *func_ov134_0229aaa8(FileInfo *self, int idx)
{
    unsigned char sel = self->sel;
    if (sel == 2) {
        return data_ov134_0229bfd4[idx];
    }
    if (sel == 1) {
        return data_ov134_0229bfec[idx];
    }
    return data_ov134_0229bf74[idx];
}
