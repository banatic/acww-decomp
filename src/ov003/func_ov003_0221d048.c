/* func_ov003_0221d048 @ 0x0221d048, 0x1c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov003_0221cffc(void *, unsigned char, void *);

typedef struct {
    char pad_00[1];
    unsigned char unk_01;
} UnkStruct_0221d048;
typedef struct {
    char pad_00[0x2c];
    void *unk_2C;
} UnkStruct_0221d048_2;
typedef struct {
    UnkStruct_0221d048 *unk_00;
    UnkStruct_0221d048_2 *unk_04;
} UnkStruct_0221d048_3;

void func_ov003_0221d048(UnkStruct_0221d048_3 *s)
{
    void *t = s->unk_04->unk_2C;
    if (t != 0) {
        func_ov003_0221cffc(t, s->unk_00->unk_01, s);
    }
}
