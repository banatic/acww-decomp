/* func_02018934 @ 0x02018934, 0x5c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020164cc(char *p);
extern void func_02019af0(void *self, int v);

struct UnkStruct_02018934 {
    unsigned char pad_00[0x190];          // 0x000
    unsigned int unk_190;                 // 0x190
    unsigned char pad_194[0x19c - 0x194]; // 0x194
    unsigned char unk_19C;                // 0x19c
};

void func_02018934(void *self, struct UnkStruct_02018934 *st)
{
    int result = 0;
    unsigned char idx;

    idx = st->unk_19C;

    switch (idx) {
        case 0:
        case 2:
            if (((st->unk_190 << 4) >> 16) == 0) {
                result = 1;
            }
            break;
        case 1:
        case 3:
            result = func_020164cc((char *) st + 0x334);
            break;
        default:
            break;
    }

    if (result != 0) {
        func_02019af0(self, 1);
    }
}
