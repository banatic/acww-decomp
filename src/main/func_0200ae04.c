/* func_0200ae04 @ 0x0200ae04, 0x78 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02056f94(void *);
extern void func_020109fc(void *, int, int, int);
extern int func_02008258(void *, int);
extern void func_0200f268(void *, int);
extern int func_0200fbe0(void *);
extern void func_0205eae0(void *, int, int, int);

typedef struct {
    char pad_00[0x2d0];
    char unk_2D0[0x2d0];
    char unk_5A0[0x164];
    int unk_704;
    char pad_708[0xe8];
    int unk_7F0;
    char pad_7F4[8];
    int unk_7FC;
} UnkStruct_0200ae04;

void func_0200ae04(UnkStruct_0200ae04 *self)
{
    if (func_02056f94(&self->unk_2D0) != 0) {
        if (self->unk_704 == 0x16 || self->unk_704 == 0x18) {
            func_020109fc(self, 0x6c, 3, 0);
        }
        self->unk_7FC = func_02008258(self, self->unk_7F0);
        func_0200f268(self, 0x12);
        func_0200f268(self, 0xd);
        if (func_0200fbe0(self) == 4) {
            func_0205eae0(&self->unk_5A0, 0, 9, 0);
        }
    }
}
