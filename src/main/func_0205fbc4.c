/* func_0205fbc4 @ 0x0205fbc4, 0x78 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0205fbc4 {
    int unk_00;
    int unk_04;
};

void func_0205fbc4(struct UnkStruct_0205fbc4 *a, struct UnkStruct_0205fbc4 *b, int *out1, int *out2, unsigned char choice)
{
    int diff;
    switch (choice) {
        case 0:
            *out1 = 0xa3;
            break;
        case 1:
        case 3:
            diff = b->unk_04 - a->unk_04;
            if (diff < 0) {
                diff = -diff;
            }
            *out1 = (diff + 0x4000) / 100;
            break;
        case 2:
            diff = b->unk_04 - a->unk_04;
            if (diff < 0) {
                diff = -diff;
            }
            *out1 = (diff + 0x8000) / 100;
            break;
    }
    *out2 = *out1 * 10;
}
