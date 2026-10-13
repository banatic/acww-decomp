/* func_ov110_0229ce44 @ 0x0229ce44, 0x64 bytes, Thumb, module ov110
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov110_0229d5e4(void *, unsigned char);
extern int func_ov110_0229d5d4(void *, unsigned char);
extern int func_ov110_0229d0fc(void *, unsigned char);
extern void func_ov002_02207cf0(void *);
extern void func_ov002_02207cf8(void *);

typedef struct {
    char pad_00;
} UnkStruct_0229ce44_2;

typedef struct {
    unsigned char pad_00[0xf3];
    unsigned char unk_F3;
    unsigned char pad_F4;
    unsigned char unk_F5;
    unsigned char pad_F6[0x2102];
    UnkStruct_0229ce44_2 unk_21F8;
} UnkStruct_0229ce44;

void func_ov110_0229ce44(UnkStruct_0229ce44 *s)
{
    if (func_ov110_0229d5e4(s, s->unk_F5) != 0 || func_ov110_0229d5d4(s, s->unk_F5) != 0) {
        if (func_ov110_0229d0fc(s, s->unk_F5) != 0) {
            func_ov002_02207cf0(&s->unk_21F8);
        } else {
            s->unk_F3 = s->unk_F5;
            func_ov002_02207cf8(&s->unk_21F8);
        }
    } else {
        func_ov002_02207cf0(&s->unk_21F8);
    }
}
