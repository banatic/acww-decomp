/* func_020bf064 @ 0x020bf064, 0x154 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int FS_OpenFile(void *self, void *ptr, int size);
extern int FS_SeekFile(void *self, int val, int arg2);
extern int FS_ReadFile(void *self, void *dst, int size);
extern void MI_CpuCopy8(void *dst, void *src, int size);
extern int FS_CloseFile(void *self);

typedef struct {
    unsigned int unk_00;
    unsigned short unk_04;
    unsigned short unk_06;
    unsigned int unk_08;
    unsigned int pad_0C;
} Entry;

typedef struct {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
} Block;

extern Entry data_020d2bac[];
extern unsigned int data_020d22d8[];
extern Block data_020d26a0[];

int func_020bf064(void *self, int arg1)
{
    Entry *entry = &data_020d2bac[arg1];
    Block *block;
    int flag0, flag1, flag2;
    int i, j, local;
    int last;

    flag0 = FS_OpenFile(self, (void *) data_020d22d8[entry->unk_00], entry->unk_00 * 4);
    flag1 = 1;
    flag2 = 1;
    block = &data_020d26a0[entry->unk_08];

    if (entry->unk_04 != 0xffff) {
        char *p = (char *) self + 0x448;
        flag1 &= FS_SeekFile(self, (entry->unk_04 & ~0x1f) << 5, 0);
        i = 0;
        local = 0;
        for (; i < 4; i++) {
            if (block->unk_04 != 0) {
                int ret = FS_ReadFile(self, (char *) self + 0x48, 0x400);
                flag2 = flag2 & ((ret > 0) ? 1 : local);
                MI_CpuCopy8((char *) self + 0x48 + ((entry->unk_04 & 0x1f) << 5), p + (block->unk_00 << 5),
                            block->unk_04 << 5);
            }
            p += 0x180;
        }
    }

    if (entry->unk_06 != 0xffff) {
        char *p = (char *) self + 0xa48;
        flag1 &= FS_SeekFile(self, (entry->unk_06 & ~0x1f) << 5, 0);
        j = 4;
        for (; j < 8; j++) {
            if (block->unk_0C != 0) {
                int ret = FS_ReadFile(self, (char *) self + 0x48, 0x400);
                flag2 = flag2 & ((ret > 0) ? 1 : 0);
                MI_CpuCopy8((char *) self + 0x48 + ((entry->unk_06 & 0x1f) << 5), p + (block->unk_08 << 5),
                            block->unk_0C << 5);
            }
            p += 0x180;
        }
    }

    last = FS_CloseFile(self);
    if (flag0 && flag1 && flag2 && last) {
        return 1;
    } else {
        return 0;
    }
}