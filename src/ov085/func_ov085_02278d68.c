/* func_ov085_02278d68 @ 0x02278d68, 0x150 bytes, Thumb, module ov085
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_02278d68 {
    u8 pad_00[0x40];
    void *unk_40;
    u8 pad_44[0xb0 - 0x44];
    u8 *unk_B0;
    int unk_B4;
} UnkStruct_02278d68;

typedef struct Msg {
    const void *tag;
    u8 unk_04;
} Msg;

extern void *func_020984e8(void);
extern void *func_02099640(int);
extern int func_02099e9c(u16 *);
extern int func_0209f150(void *, int);
extern void func_0209f128(void *, int);
extern void *func_020867a0(void *);
extern void *func_0208675c(void *);
extern int func_02003704(void *);
extern void *func_02094fd4(int *);
extern void *func_02094fbc(int *);
extern int func_02003618(void *, int *);
extern void func_02068404(void *, int, int *);
extern int func_020644cc(int);
extern int func_0202ea80(int, int);

extern const int data_ov085_0227959c;
extern const int data_ov085_022795ac;
extern u8 data_021dc7a8[];
extern u8 data_021f3aa4[];

void func_ov085_02278d68(UnkStruct_02278d68 *obj, Msg *m)
{
    u16 hw;
    int blk1[8];
    int blk2[8];
    void *h;

    func_02099640((int) func_020984e8());
    m->tag = (const void *) &data_ov085_0227959c;

    if (obj->unk_B4 == -1) {
        hw = 0x37e0;
        obj->unk_B4 = func_02099e9c(&hw);
        if (obj->unk_B4 >= 0) {
            m->tag = (const void *) &data_ov085_022795ac;
            m->unk_04 = 0;
            return;
        }
    }

    if (obj->unk_B0[0x728] == 6) {
        if (func_0209f150(data_021dc7a8, 0x11) != 0) {
            h = func_020867a0(data_021f3aa4);
            if (func_02003704(h) != 0) {
                func_02094fd4(blk1);
                func_02003618(h, blk1);
                func_02068404(obj->unk_40, 1, blk1);
                func_02094fbc(blk1);
            }
            m->unk_04 = (u8) (func_020644cc(3) + 0x11);
        } else {
            m->unk_04 = 0xf;
            func_0209f128(data_021dc7a8, 0x11);
        }
    } else {
        h = func_0208675c(data_021f3aa4);
        if (func_02003704(h) != 0) {
            func_02094fd4(blk2);
            func_02003618(h, blk2);
            func_02068404(obj->unk_40, 0, blk2);
            m->unk_04 = (u8) (func_020644cc(4) + 0xb);
            func_02094fbc(blk2);
        } else {
            m->unk_04 = 4;
            if (func_0202ea80(0x1f, 1) == 0) {
                switch (obj->unk_B0[0x728]) {
                    case 0:
                        m->unk_04 = 0;
                        break;
                    case 1:
                    case 2:
                        m->unk_04 = 1;
                        break;
                    case 3:
                    case 4:
                        m->unk_04 = 2;
                        break;
                    case 5:
                        m->unk_04 = 3;
                        break;
                }
            }
        }
    }
}
