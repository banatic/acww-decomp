/* func_02066be0 @ 0x02066be0, 0x74 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern const short data_020def28[];
extern void func_02068d74(char *ptr, int val);
extern void func_020675c0(void *ptr);
extern void func_0206c124(char *ptr);

typedef struct {
    int unk_00;           // 0x00
    int unk_04;           // 0x04
    int unk_08;           // 0x08
    int unk_0C;           // 0x0C
    int unk_10;           // 0x10
    int unk_14;           // 0x14
    char pad_18[4];       // 0x18 - 0x1B
    char unk_1C;          // 0x1C
    char pad_1D[0x7F];    // 0x1D - 0x9B
    int unk_9C;           // 0x9C
    char pad_A0[0x5E4];   // 0xA0 - 0x683
    char unk_684;         // 0x684
    char pad_685[0x1813]; // 0x685 - 0x1E97
    char unk_1E98;        // 0x1E98
    char unk_1E99;        // 0x1E99
    char unk_1E9A;        // 0x1E9A
} UnkStruct_02066be0;

void func_02066be0(UnkStruct_02066be0 *self)
{
    int flag = 0;
    if (self->unk_0C > 0) {
        self->unk_0C--;
    } else {
        flag = 1;
    }
    self->unk_9C = data_020def28[self->unk_0C];
    func_02068d74(&self->unk_1C, self->unk_9C);
    if (flag) {
        func_020675c0(self);
        func_0206c124(&self->unk_684);
        if (self->unk_14 != 4) {
            self->unk_08 = 5;
        } else {
            self->unk_1E98 = 0;
            self->unk_1E9A = 0;
            self->unk_08 = 0;
        }
    }
}
