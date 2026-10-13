/* func_020648a0 @ 0x020648a0, 0x6c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x14];
    unsigned int unk_14;
    unsigned char pad_18[0x0C];
    unsigned int unk_24;
    unsigned int unk_28;
    unsigned int unk_2C;
} UnkStruct_020648a0;

extern void FS_SeekFile(UnkStruct_020648a0 *self, int a, int b);
extern int FS_ReadFile(UnkStruct_020648a0 *self, void *buf, int len);

int func_020648a0(UnkStruct_020648a0 *self)
{
    unsigned int diff = self->unk_28 - self->unk_24;
    if (diff >= 8) {
        unsigned int r6 = self->unk_2C - self->unk_24;
        unsigned int buf[2];
        FS_SeekFile(self, 0, 0);
        if (FS_ReadFile(self, buf, 8) == -1) {
            goto ret_neg1;
        }
        if (buf[0] == 0x37375a4c || buf[0] == 0x4c5a3737) {
            diff = buf[1] >> 8;
        }
        FS_SeekFile(self, r6, 0);
    }
    if (self->unk_14 != 0) {
        diff = -1;
    }
    return diff;
ret_neg1:
    return -1;
}
