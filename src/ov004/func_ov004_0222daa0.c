/* func_ov004_0222daa0 @ 0x0222daa0, 0x1c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov004_0222d32c(void *, unsigned char, void *);

typedef struct {
    char pad_00[1];
    unsigned char unk_01;
} UnkStruct_0222daa0;
typedef struct {
    char pad_00[0x2c];
    void *unk_2C;
} UnkStruct_0222daa0_2;
typedef struct {
    UnkStruct_0222daa0 *unk_00;
    UnkStruct_0222daa0_2 *unk_04;
} UnkStruct_0222daa0_3;

void func_ov004_0222daa0(UnkStruct_0222daa0_3 *s)
{
    void *t = s->unk_04->unk_2C;
    if (t != 0) {
        func_ov004_0222d32c(t, s->unk_00->unk_01, s);
    }
}
