/* func_ov121_0229add4 @ 0x0229add4, 0x44 bytes, Thumb, module ov121
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021f6c58;
extern unsigned char data_021f6c54;

struct UnkStruct_0229add4 {
    unsigned char pad_00[0xa8];
    short x;
    short y;
};

extern int func_ov121_0229ae68(struct UnkStruct_0229add4 *s, int x, int y, int z);
extern int func_ov121_0229adac(struct UnkStruct_0229add4 *s, int x);

int func_ov121_0229add4(struct UnkStruct_0229add4 *s)
{
    int v1 = data_021f6c58;
    int v2 = data_021f6c54;
    int r;
    v1 += s->x;
    v2 += s->y;
    r = func_ov121_0229ae68(s, v1, v2, 15);
    if (func_ov121_0229adac(s, r) != 0) {
        r = 0x18;
    }
    return r;
}
