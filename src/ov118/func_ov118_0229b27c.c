/* func_ov118_0229b27c @ 0x0229b27c, 0x94 bytes, Thumb, module ov118
 * mwccarm 1.2/base -O4,s
 */

extern void func_020896b8(int, void *, int, int, int, int, int);

typedef struct {
    unsigned short unk_00;
    unsigned short unk_02;
    unsigned short unk_04;
} data_ov118_0229cb40_t;

extern data_ov118_0229cb40_t data_ov118_0229cb40;

void func_ov118_0229b27c(int unused, int b, int c, int d, int e, int f)
{
    unsigned short mask;

    data_ov118_0229cb40.unk_04 = (data_ov118_0229cb40.unk_04 & 0xfffffc00) | ((unsigned short) ((d << 1) + 0xc0) & 0x3ff);

    if (e) {
        unsigned short old = data_ov118_0229cb40.unk_02;
        mask = (unsigned short) (((unsigned int) old << 18) >> 27 | 8);
        data_ov118_0229cb40.unk_02 = (old & 0xffffc1ff) | ((mask & 0x1f) << 9);
    }

    func_020896b8(1, (void *) &data_ov118_0229cb40, b, c, f, 1, 0);

    if (e) {
        data_ov118_0229cb40.unk_02 =
            (data_ov118_0229cb40.unk_02 & 0xffffc1ff) | (((unsigned short) (mask & 0x17) & 0x1f) << 9);
    }
}
