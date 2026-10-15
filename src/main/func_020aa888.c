/* func_020aa888 @ 0x020aa888, 0x138 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_020aa888 {
    void *unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
    int unk_10;
    u8 pad_14[0x30 - 0x14];
    u8 unk_30;
} UnkStruct_020aa888;

extern int func_020abd98(void *p);
extern int func_020a7e50(void);
extern int func_020a8028(int *a, int *b);
extern int func_020abcfc(void *p);
extern int func_020abd14(void *p);
extern int func_020a7e44(void);
extern int func_020a7ebc(void);
extern int func_020a7e94(void);
extern void RtcSendPxiCommand(int command);

void func_020aa888(UnkStruct_020aa888 *self)
{
    int down;
    int speed;
    int upper;
    int crossed;
    int lower;
    int i;
    int up;
    int old;
    int ascending;
    int diff;
    int boundary;
    int pos;
    int x;
    int bottom;
    int top;
    int cur;
    int y;

    if (self->unk_30 != 0 && func_020abd98(self->unk_00) != 0) {
        if (func_020a7e50() != 0) {
            if (func_020a8028(&x, &y) != 0) {
                top = func_020abcfc(self->unk_00);
                bottom = func_020abd14(self->unk_00);
                pos = y - self->unk_10;
                if (pos < bottom) {
                    pos = bottom;
                } else if (pos > top) {
                    pos = top;
                }
                self->unk_08 = ((pos - top) << 12) / (bottom - top);
            }
            self->unk_04 = 0;
        } else if (func_020a7e44() != 0) {
            up = func_020a7ebc();
            down = func_020a7e94();
            if (up == 0 && down == 0) {
                self->unk_04 = 0x28;
            } else {
                self->unk_04 += 0x51;
                speed = self->unk_04;
                if (speed < 0) {
                    speed = 0;
                } else if (speed > 0x199) {
                    speed = 0x199;
                }
                self->unk_04 = speed;
            }
            if (up != 0) {
                self->unk_08 += self->unk_04;
            }
            if (down != 0) {
                self->unk_08 -= self->unk_04;
            }
            pos = self->unk_08;
            if (pos < 0) {
                pos = 0;
            } else if (pos > 0x1000) {
                pos = 0x1000;
            }
            self->unk_08 = pos;
        }
    }
    old = self->unk_0C;
    cur = self->unk_08;
    diff = cur - old;
    if (diff < 0) {
        diff = -diff;
    }
    if (diff >= 0x51) {
        ascending = cur > old ? 1 : 0;
        upper = ascending ? cur : old;
        lower = ascending ? old : cur;
        crossed = 0;
        for (i = 0; i < 10; i++) {
            boundary = i * 0x199;
            if (boundary >= lower && boundary < upper) {
                crossed = 1;
                break;
            }
        }
        if (upper == 0x1000) {
            crossed = 1;
        }
        if (crossed != 0) {
            RtcSendPxiCommand(0x19);
        }
    }
    self->unk_0C = self->unk_08;
}
