/* func_020c0ad4 @ 0x020c0ad4, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x0c];
    int unk_0C;
    char pad_10[0x48];
    int unk_58;
    char pad_5C[0x04];
    int unk_60;
    int unk_64;
    int unk_68;
} UnkStruct_020c0ad4;

extern int func_020644cc(int);
extern void func_020bf568(UnkStruct_020c0ad4 *, int, int);

void func_020c0ad4(UnkStruct_020c0ad4 *s, int flags)
{
    int b;
    int one = 1;

    b = (func_020644cc(2) == 0) ? 1 : 0;
    func_020bf568(s, b, 1000);
    s->unk_0C = one;
    s->unk_58 = 2;
    s->unk_60 = 0;
    s->unk_64 = (flags & one) ? one : 0;
    s->unk_68 = 0;
}
