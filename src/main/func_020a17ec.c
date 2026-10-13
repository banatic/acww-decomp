/* func_020a17ec @ 0x020a17ec, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020a17ec {
    char pad_00[0x50];
    int unk_50;
    char pad_54[0xa1 - 0x54];
    unsigned char unk_A1;
};

extern struct UnkStruct_020a17ec *data_021f3c3c;

int func_020a17ec(void)
{
    if (data_021f3c3c != 0 && data_021f3c3c->unk_50 == 0x13 && data_021f3c3c->unk_A1 == 3) {
        return 1;
    } else {
        return 0;
    }
}
