/* func_0206c3b8 @ 0x0206c3b8, 0x42 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0206c3b8 {
    char pad_00[0x34];
    char unk_34[0x14];
    int unk_48;
};

extern int func_02068114(void);
extern void func_020a8328(char *, int *, int *, int *);
extern void func_020a93e8(struct UnkStruct_0206c3b8 *, int);
extern void func_020a9334(struct UnkStruct_0206c3b8 *, int);

void func_0206c3b8(struct UnkStruct_0206c3b8 *self)
{
    int a, b, c;
    int ret = ((int) (func_020a8328(self->unk_34, &a, &b, &c), self->unk_34));
    if (func_02068114() == 0) {
        func_020a93e8(self, a << 1);
        func_020a9334(self, c);
        self->unk_48 = c + ((b - c) ^ 1);
    }
}
