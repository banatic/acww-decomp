/* func_ov102_0229cc60 @ 0x0229cc60, 0x30 bytes, Thumb, module ov102
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov102_0229d2a4(void *s, int param2, unsigned short f1, unsigned char f2);

typedef struct {
    char pad_00[0x259c];
    unsigned short unk_259C;
    unsigned char unk_259E;
    unsigned char flag;
} UnkStruct_0229cc60;

void func_ov102_0229cc60(UnkStruct_0229cc60 *s, int param2)
{
    if (s->flag == 1) {
        func_ov102_0229d2a4(s, param2, s->unk_259C, s->unk_259E);
    }
    s->flag = 0;
}
