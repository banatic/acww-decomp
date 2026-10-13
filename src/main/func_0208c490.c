/* func_0208c490 @ 0x0208c490, 0xdc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0208c490 {
    char pad_00[0xc8];
    int c8;
    int cc;
};

extern void func_0208c3ec(struct UnkStruct_0208c490 *self);

struct Flags {
    char pad_00[2];
    unsigned short flags;
};
extern struct Flags data_021fbe40;

int func_0208c490(struct UnkStruct_0208c490 *self)
{
    int old_c8 = self->c8;
    int old_cc = self->cc;
    unsigned short flags = data_021fbe40.flags;

    if (flags & 0x10) {
        self->c8 += 1;
    } else if (flags & 0x20) {
        self->c8 -= 1;
    } else if (flags & 0x40) {
        self->cc -= 1;
    } else if (flags & 0x80) {
        self->cc += 1;
    }

    {
        int c8 = self->c8;
        if (c8 < -1) {
            c8 = -1;
        } else if (c8 > 1) {
            c8 = 1;
        }
        self->c8 = c8;
    }

    {
        int cc = self->cc;
        if (cc < -1) {
            cc = -1;
        } else if (cc > 1) {
            cc = 1;
        }
        self->cc = cc;
    }

    func_0208c3ec(self);

    if (old_c8 != self->c8 || old_cc != self->cc) {
        return 1;
    }
    return 0;
}
