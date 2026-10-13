/* func_020031d4 @ 0x020031d4, 0x58 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_020031d4 {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
    int unk_10;
    int unk_14;
    int unk_18;
    int unk_1C;
    int unk_20;
    int unk_24;
    int unk_28;
    int unk_2C;
} UnkStruct_020031d4;

typedef struct Src {
    char pad_00[0x8c];
    short cond;
    short e;
    char pad_90[0x34];
    int a;
    int b;
    int c;
    short d;
} Src;

extern void func_020e96c8(UnkStruct_020031d4 *p, int a, int b, int c);
extern void func_020e9774(UnkStruct_020031d4 *p, int v);
extern void func_020e9744(UnkStruct_020031d4 *p, int v);

void func_020031d4(Src *s, UnkStruct_020031d4 *out)
{
    UnkStruct_020031d4 local;
    func_020e96c8(&local, s->a, s->b, s->c);
    func_020e9774(&local, s->d);
    func_020e9744(&local, s->e);
    if (s->cond) {
        func_020e9774(&local, s->cond);
    }
    *out = local;
}
