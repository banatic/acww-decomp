/* func_02009624 @ 0x02009624, 0x88 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x704];
    int unk_704;
    char pad_708[0x7f0 - 0x704 - 4];
    int unk_7F0;
    char pad_7F4[0x7fc - 0x7f0 - 4];
    int unk_7FC;
} UnkStruct_02009624;

extern int func_0200f290(UnkStruct_02009624 *self, int a);
extern void func_020109fc(UnkStruct_02009624 *self, int a, int b, int c);
extern int func_02008258(UnkStruct_02009624 *self, int a);
extern int func_0200d4e8(UnkStruct_02009624 *self, int a, int b, int c);
extern int func_0203e3f8(void);
extern void func_0200f268(UnkStruct_02009624 *self, int a);
extern int func_0200c3b0(UnkStruct_02009624 *self, int a, int b, int c);

void func_02009624(UnkStruct_02009624 *self, int flag)
{
    if (flag) {
        if (func_0200f290(self, 0x18)) {
            if (self->unk_704) {
                func_020109fc(self, 0, 3, 0);
            }
            self->unk_7FC = func_02008258(self, self->unk_7F0);
            func_0200d4e8(self, 3, 1, -1);
            func_0203e3f8();
            func_0200f268(self, 5);
            func_0200f268(self, 0x18);
            func_0200f268(self, 3);
        } else {
            func_0200c3b0(self, 3, 5, -1);
            func_0200f268(self, 5);
        }
    }
}
