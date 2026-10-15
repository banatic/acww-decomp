/* func_ov123_0229c754 @ 0x0229c754, 0x1a0 bytes, Thumb, module ov123
 * mwccarm 1.2/base -O4,s
 */

extern int func_0206fe54(void);
extern int func_ov123_02299650(void *, int);
extern void func_ov123_0229a0cc(void *, int, int);
extern void func_ov002_02209eb8(void *);
extern void *func_ov002_02207f60(void *);
extern void func_ov002_0220ad18(void *, void *);
extern void func_ov123_02299f40(void *);
extern int func_020896b8(int, const void *, int, void *, int, int, int);
extern void func_02088df8(int, const void *, int, void *, int, int, int, int, int, int, int, int);

extern const unsigned char data_ov123_0229ce88[];
extern const unsigned char data_ov123_0229cf7c[];
extern const unsigned char data_ov123_0229cfcc[];
extern const unsigned char data_ov123_0229cea8[];
extern const unsigned char data_ov123_0229cf6c[];
extern const void *data_ov123_0229cf60[];

int func_ov123_0229c754(unsigned char *self)
{
    void *dst;

    if (func_0206fe54()) {
        if (self[0xac] == 2) {
            if (func_ov123_02299650(self, 0x100) == 0) {
                func_ov123_0229a0cc(self, self[0xaf], self[0xb0]);
            }
        } else {
            func_ov002_02209eb8(self + 0x1cc);
        }
    }

    if (func_ov123_02299650(self, 0x100) != 0) {
        func_ov123_02299f40(self);
    }
    func_ov002_0220ad18(self + 0x5030, func_ov002_02207f60(self));

    if (func_ov123_02299650(self, 1) != 0) {
        dst = (void *) (*(unsigned int *) (self + 0x98) + (*(unsigned int *) (self + 0x94) + 0x60));

        if (func_0206fe54()) {
            func_020896b8(1, data_ov123_0229ce88, 0x80, dst, -1, -1, 0);
            func_02088df8(1, data_ov123_0229cf7c, 0x80, dst, -1, -1, 0x1000, 0x1000, 0, -1, 0, 0);
        }

        func_02088df8(1, data_ov123_0229cfcc, self[0xa3] + 0x80, dst, -1, 2, 0x1000, 0x1000, 0, -1, 0, 0);

        if (self[0xa1] < 9) {
            func_02088df8(1, data_ov123_0229cea8, 0x80, dst, -1, 2, 0x1000, 0x1000, 0, -1, 0, 0);
        } else {
            func_02088df8(1, data_ov123_0229cf6c, 0x80, dst, -1, 2, 0x1000, 0x1000, 0, -1, 0, 0);
        }

        if (func_0206fe54()) {
            func_02088df8(1, data_ov123_0229cf60[self[0xac]], 0x80, dst, -1, -1, 0x1000, 0x1000, 0, -1, 0, 0);
        }
    }

    return 1;
}
