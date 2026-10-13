/* func_020a1d94 @ 0x020a1d94, 0x74 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_020d1c20[];
extern int func_02050974(void *p);
extern void func_02050948(void *p);
extern void func_02050a84(void *p, int a, int b, int c);

struct UnkStruct_020a1d94 {
    unsigned char pad_00[0xa0];
    unsigned char unk_A0;
    char pad_A1[3];
    short unk_A4;
    char pad_A6[2];
    int unk_A8;
    char pad_AC[4];
    int unk_B0;
};

extern unsigned char data_021c8188[];

int func_020a1d94(struct UnkStruct_020a1d94 *s, int idx)
{
    int status;
    int shift;
    int table_val;

    status = func_02050974((void *) data_021c8188);
    table_val = data_020d1c20[idx];

    if (status == 1) {
        func_02050948((void *) data_021c8188);
        return 1;
    }

    if (status == 4) {
        shift = s->unk_A4 << 9;
        func_02050a84((void *) data_021c8188, shift + table_val, s->unk_B0 + shift, s->unk_A8);
    } else if (status != 3) {
        func_02050948((void *) data_021c8188);
        s->unk_A4 = -1;
        s->unk_A8 = 0;
        s->unk_A0 = 3;
    }

    return 3;
}
