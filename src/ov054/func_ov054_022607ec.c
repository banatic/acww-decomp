/* func_ov054_022607ec @ 0x022607ec, 0x50 bytes, Thumb, module ov054
 * mwccarm 1.2/base -O1,s
 */

extern int func_02060d3c(void *);
extern void func_02015fb0(void *, int, int, int, int, int);
extern void func_0206844c(void *, char *, int, int);

extern char data_021ebcd4;

struct DataEntry {
    int a;
    int b;
    int c;
};
extern struct DataEntry data_ov054_02262fac[];

struct UnkStruct_022607ec {
    unsigned char pad_00[0x808];
    int idx;
};

struct UnkStruct_022607ec_2 {
    unsigned char pad_00[0x40];
    void *unk_40;
    unsigned char pad_44[0xb0 - 0x44];
    struct UnkStruct_022607ec *unk_B0;
};

void func_ov054_022607ec(struct UnkStruct_022607ec_2 *self)
{
    func_02015fb0(self, func_02060d3c(&data_021ebcd4), 4, 10, 0, 0);
    {
        char byte = 18;
        func_0206844c(self->unk_40, &byte, data_ov054_02262fac[self->unk_B0->idx].a, self->unk_B0->idx * 12);
    }
}
