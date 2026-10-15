/* func_ov085_02278ab8 @ 0x02278ab8, 0x15c bytes, Thumb, module ov085
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_02278ab8 {
    char pad_00[0x1e];
    u8 unk_1E;
    char pad_1F[0x40 - 0x1f];
    void *unk_40;
    char pad_44[0xb4 - 0x44];
    int unk_B4;
    char pad_B8[0xbc - 0xb8];
    int unk_BC[4];
} UnkStruct_02278ab8;

typedef struct Msg {
    u8 unk_00;
    u8 unk_01;
    u16 unk_02;
} Msg;

extern int func_020160b4(void *arg0);
extern int func_020ab504(int);
extern void func_0209a050(int);
extern int func_02015330(UnkStruct_02278ab8 *, u16 *, int, int, int);
extern void func_0206844c(void *, u8 *, const void *);
extern int func_020644cc(int);
extern void *func_02094fd4(int *);
extern void *func_02094fbc(int *);
extern void *func_0207cec0(void *, int);
extern void *func_0208150c(void *);
extern int func_02003704(void *);
extern int func_02003618(void *, int *);
extern void func_02068404(void *, int, int *);
extern void func_020867a4(void *, void *);
extern void func_02086760(void *, void *);
extern int data_021f3aa4;
extern int data_021e5a2c;
extern const int data_ov085_0227959c;
extern const int data_ov085_022795ac;

void func_ov085_02278ab8(UnkStruct_02278ab8 *this)
{
    Msg m;
    int blk[8];
    int ok = func_020ab504(func_020160b4((void *) this));
    const void *tag = (const void *) &data_ov085_0227959c;
    int code = 0xff;
    int v = this->unk_B4;

    if (v >= 0) {
        tag = (const void *) &data_ov085_022795ac;
        if (this->unk_1E == 0 && ok == 0) {
            if (v >= 0) {
                func_0209a050(v);
                m.unk_02 = 0x37e0;
                func_02015330(this, &m.unk_02, 0, 5, 0);
            }
            code = 2;
        }
        if (code != 0xff) {
            m.unk_00 = (u8) code;
            func_0206844c(this->unk_40, &m.unk_00, tag);
        }
        return;
    }

    {
        int st = this->unk_1E;
        switch (st) {
            case 4:
                if (ok == 0) {
                    code = (u8) (func_020644cc(2) + 7);
                } else {
                    code = (u8) (func_020644cc(2) + 5);
                }
                break;
            case 7:
            case 8:
            case 0x14:
            case 0x15: {
                if (this->unk_BC[ok] >= 0) {
                    void *pv = &data_021f3aa4;
                    void *h;
                    func_02094fd4(blk);
                    h = func_0207cec0(&data_021e5a2c, this->unk_BC[ok]);
                    if (func_02003704(func_0208150c(h)) != 0) {
                        func_02003618(func_0208150c(h), blk);
                        func_02068404(this->unk_40, 0, blk);
                    }
                    if (func_020644cc(2) == 0) {
                        func_020867a4(pv, func_0208150c(h));
                    }
                    func_02086760(pv, func_0208150c(h));
                    code = (u8) (func_020644cc(2) + 9);
                    func_02094fbc(blk);
                } else {
                    if (st != 0x14) {
                        code = 0x14;
                    } else {
                        code = 0x15;
                    }
                }
                break;
            }
        }
    }

    if (code != 0xff) {
        m.unk_01 = (u8) code;
        func_0206844c(this->unk_40, &m.unk_01, tag);
    }
}
