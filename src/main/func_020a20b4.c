/* func_020a20b4 @ 0x020a20b4, 0x6c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0xa0];
    unsigned char unk_A0;
    unsigned char pad_A1;
    unsigned char unk_A2;
    unsigned char pad_A3;
    short unk_A4;
    unsigned short pad_A6;
    unsigned int unk_A8;
    unsigned int pad_AC;
    unsigned int unk_B0;
} UnkStruct_020a20b4;

extern unsigned int func_020a1368(void);
extern void MI_CpuFill8(unsigned int, int, unsigned int);
extern void MI_CpuCopy8(unsigned int, unsigned int, unsigned int);
extern unsigned int data_020d1bf0[];
extern unsigned int data_020d1c08[];

extern unsigned char data_021dc7a8[];

int func_020a20b4(UnkStruct_020a20b4 *self, int idx)
{
    unsigned int arr[3];

    arr[0] = (unsigned int) data_021dc7a8;
    arr[1] = (unsigned int) data_021dc7a8;
    arr[2] = func_020a1368();
    MI_CpuFill8(self->unk_B0, 0, data_020d1bf0[idx]);
    MI_CpuCopy8(arr[idx], self->unk_B0, data_020d1c08[idx]);
    self->unk_A2 = 0;
    self->unk_A4 = -1;
    self->unk_A8 = 0;
    self->unk_A0 = 1;
    return 3;
}
