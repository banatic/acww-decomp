/* func_020aa4f4 @ 0x020aa4f4, 0xda bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0209d368(int, int);
extern void func_020ac39c(char *, int, int);
extern void func_020ab304(char *);
extern void func_020aa4c0(char *);

typedef struct {
    unsigned char pad_00[0xb4];
    int unk_B4;
    int unk_B8;
    int unk_BC;
} UnkStruct_020aa4f4;

void func_020aa4f4(UnkStruct_020aa4f4 *self)
{
    int flag;

    if (self->unk_BC > func_0209d368(100, 3) + 2) {
        self->unk_B4 += func_0209d368(100, 6) - 6;
        self->unk_B8 += func_0209d368(100, 7) + 6;
    } else {
        self->unk_B4 += func_0209d368(100, 8) + 1;
        self->unk_B8 += func_0209d368(100, 9) - 1;
    }

    self->unk_BC -= 1;
    flag = (self->unk_BC <= 0);

    if (flag) {
        self->unk_B4 = 0;
        self->unk_B8 = 0;
    }

    func_020ac39c((char *) self + 0xc, self->unk_B4, self->unk_B8);

    if (flag) {
        func_020ab304((char *) self + 0x84);
        func_020aa4c0((char *) self);
    }
}
