/* func_ov122_0229f394 @ 0x0229f394, 0x34 bytes, Thumb, module ov122
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0xa0];
    int unk_A0;
    char pad_A4[0xb3 - 0xa0 - 4];
    unsigned char unk_B3;
} UnkStruct_0229f394;

extern void func_ov122_0229f454(UnkStruct_0229f394 *p, int value);

void func_ov122_0229f394(UnkStruct_0229f394 *p)
{
    unsigned char b = p->unk_B3;
    int v = p->unk_A0;
    int diff = v - b;
    if (diff < 24) {
        func_ov122_0229f454(p, b - (24 - diff));
    } else if (diff > 48) {
        func_ov122_0229f454(p, b + (diff - 48));
    }
}
