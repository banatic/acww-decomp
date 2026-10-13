/* func_ov068_02269978 @ 0x02269978, 0xdc bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_02269978 {
    u8 pad_00[0x618];
    u8 unk_618;
    u8 pad_619[0x830 - 0x618 - 1];
    u32 unk_830;
    u8 pad_834[0x898 - 0x830 - 4];
    u8 unk_898;
} UnkStruct_02269978;

extern int func_02096190(int);
extern int func_ov068_0226d598(UnkStruct_02269978 *);
extern int func_02081d20(int, int);
extern int func_0208150c(u32);
extern int func_020036e8(int);
extern int func_0201c314(UnkStruct_02269978 *, int);
extern int func_ov068_0226cfd4(UnkStruct_02269978 *);
extern void func_ov003_02219874(int);
extern void func_020147b8(void *, int, int, int, int);
extern void func_ov068_02266c34(void *, UnkStruct_02269978 *, int, int, int, u32, int, u32, int);
extern u32 data_020c814c;
extern char data_021fbee8[];

int func_ov068_02269978(int unused, UnkStruct_02269978 *self)
{
    int r6;
    int r7;
    u32 r5;
    int temp;
    int t2;
    int idx;

    r6 = func_02096190(4);
    r7 = 0;
    r5 = self->unk_830;

    temp = func_ov068_0226d598(self);
    t2 = 0;
    if (temp != 0) {
        t2 = func_02081d20(temp, 0);
    }

    if (t2 >= 0) {
        idx = func_020036e8(func_0208150c(r5));
        if (idx == 0 || idx == 3) {
            r5 = 1;
        } else {
            r5 = 0;
        }
    } else {
        idx = func_020036e8(func_0208150c(r5));
        switch (idx) {
            case 0:
            case 3:
                r5 = 2;
                break;
            case 1:
            case 4:
                r5 = 3;
                break;
            case 2:
            default:
                r5 = 4;
                break;
        }
    }

    if (r6 != 0) {
        r7 = func_0201c314(self, r6);
    }

    func_ov003_02219874(func_ov068_0226cfd4(self));
    func_020147b8(&self->unk_618, r5, 0, r7, 0);
    func_ov068_02266c34(&self->unk_898, self, 1, 0, 0, (u32) data_021fbee8, 4, data_020c814c, 1);

    return 1;
}
