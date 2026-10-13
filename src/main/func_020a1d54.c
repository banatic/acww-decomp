/* func_020a1d54 @ 0x020a1d54, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_020a1368(void);
extern void MI_CpuCopy8(unsigned int, unsigned int, unsigned int);
extern unsigned int data_020d1c08[];

typedef struct {
    char pad_00[0xa0];
    unsigned char unk_A0;
    char pad_A1[0x0f];
    unsigned int unk_B0;
} UnkStruct_020a1d54;

extern unsigned char data_021dc7a8[];

int func_020a1d54(UnkStruct_020a1d54 *self, int idx)
{
    unsigned int arr[3];
    arr[0] = (unsigned int) data_021dc7a8;
    arr[1] = (unsigned int) data_021dc7a8;
    arr[2] = func_020a1368();
    MI_CpuCopy8(self->unk_B0, arr[idx], data_020d1c08[idx]);
    self->unk_A0 = 6;
    return 3;
}
