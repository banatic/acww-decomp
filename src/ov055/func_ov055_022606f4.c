/* func_ov055_022606f4 @ 0x022606f4, 0x78 bytes, Thumb, module ov055
 * mwccarm 1.2/base -O4,s
 */

extern void func_02073090(void);
extern int func_020ead48(void);
extern int func_020ead58(void);
extern void func_020ead7c(void);
extern void RtcSendPxiCommand(int);
extern void func_02074958(void);
extern void func_0206844c(void *, unsigned char *, void *);
extern void func_02068434(void *);
extern void func_ov055_02260870(void *, int);
extern void *data_ov055_02260e60;

typedef struct {
    unsigned char pad_00[0x40];
    void *unk_40;
} UnkStruct_022606f4;

void func_ov055_022606f4(UnkStruct_022606f4 *self)
{
    void *field40;
    unsigned char b;

    field40 = self->unk_40;

    if ((((*(volatile unsigned short *) 0x027fffa8) & 0x8000) >> 15) != 0) {
        return;
    }

    if (((void) (func_02073090()), func_020ead48()) != 0) {
        RtcSendPxiCommand(0x69);
        func_02074958();

        b = 0x3c;
        func_0206844c(self->unk_40, &b, data_ov055_02260e60);
    } else {
        if (((void) (func_02073090()), func_020ead58()) != 1) {
            ((void) (func_02073090()), func_020ead7c());
            return;
        }
    }

    func_02068434(field40);
    func_ov055_02260870(self, 0);
}
