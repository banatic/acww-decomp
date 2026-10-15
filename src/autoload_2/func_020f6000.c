/* func_020f6000 @ 0x020f6000, 0x9c bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

struct UnkStruct_020f6000 {
    char pad_00[0x3c];
    char unk_3C;
};

struct UnkStruct_020f6000_2 {
    char pad_00[0x30];
    struct UnkStruct_020f6000 *ptr;
};

struct Unknown_s {
    char pad_00[6];
    signed char unk_06;
    char unk_07;
    char pad_08;
    signed char unk_09;
    char unk_0A;
};

extern struct UnkStruct_020f6000_2 data_021fd1bc;
extern unsigned char *data_021fd268;
extern int func_020eed18(struct Unknown_s *self, int arg);

int func_020f6000(struct Unknown_s *self)
{
    if (self->unk_06 >= 15) {
        func_020eed18(self, 0);
        data_021fd1bc.ptr->unk_3C = 0;
        self->unk_0A = 0;
        self->unk_06 = -1;
        self->unk_07 = 0;
        return 1;
    }

    {
        int idx = self->unk_06 + 1;
        unsigned char b = data_021fd268[idx];

        if (b != 14) {
            if (b == 15) {
                if (self->unk_09 != 1) {
                    func_020eed18(self, 0);
                }
            } else {
                func_020eed18(self, 0);
            }
        }
    }

    return 0;
}
