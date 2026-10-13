/* func_ov003_0221c724 @ 0x0221c724, 0x188 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x2b4];
    unsigned char unk_2B4;
    unsigned char unk_2B5;
    unsigned char unk_2B6;
    unsigned char pad_2B7[0x21];
    unsigned char unk_2D8;
    unsigned char unk_2D9;
} UnkStruct_0221c724;

extern void func_0209e474(int *p);
extern int func_020b65c4(void);
extern void RtcSendPxiCommand(int cmd);

extern unsigned int data_ov003_0223c8b8; // hours
extern unsigned int data_ov003_0223c8c0; // minutes
extern unsigned int data_ov003_0223c8bc; // seconds

void func_ov003_0221c724(UnkStruct_0221c724 *self)
{
    int local[3];
    int st;

    if (self->unk_2D8 == 0) {
        goto end;
    }

    local[0] = 0;
    local[1] = 0;
    func_0209e474(local);
    if (((unsigned char *) local)[4] == 1) {
        goto stop;
    }

    switch (self->unk_2B4) {
        case 0:
            self->unk_2B5 = (unsigned char) ((data_ov003_0223c8b8 / 10) & 1);
            break;
        case 1:
            self->unk_2B5 = (unsigned char) (data_ov003_0223c8b8 % 10);
            break;
        case 2:
            self->unk_2B5 = (unsigned char) (data_ov003_0223c8c0 / 10);
            break;
        case 3:
            self->unk_2B5 = (unsigned char) (data_ov003_0223c8c0 % 10);
            break;
        case 4:
            self->unk_2B5 = (unsigned char) (data_ov003_0223c8bc / 10);
            break;
        case 5:
            self->unk_2B5 = (unsigned char) (data_ov003_0223c8bc % 10);
            break;
    }

    st = -1;
    if (data_ov003_0223c8b8 != 0) {
        goto end;
    }
    if (func_020b65c4() == 0x2c) {
        goto end;
    }

    if (data_ov003_0223c8c0 == 1 && data_ov003_0223c8bc == 0) {
        st = 3;
    } else if (data_ov003_0223c8c0 == 0 && data_ov003_0223c8bc != 0) {
        if (data_ov003_0223c8bc <= 10) {
            st = 2;
        } else {
            st = 3;
        }
    }

    if (self->unk_2B6 == self->unk_2B5) {
        goto end;
    }
    if (st != -1 && self->unk_2B4 == 5) {
        switch (st) {
            case 1:
                if (self->unk_2D9 == 0) {
                    RtcSendPxiCommand(0x61);
                }
                break;
            case 2:
                if (self->unk_2D9 == 0) {
                    RtcSendPxiCommand(0x60);
                }
                break;
            case 3:
                if (self->unk_2D9 == 0) {
                    RtcSendPxiCommand(0x62);
                }
                break;
        }
        self->unk_2D9 = 0;
        goto end;
    }
    self->unk_2D9 = 0;
    goto end;

stop:
    self->unk_2D8 = 0;
end:
    self->unk_2B6 = self->unk_2B5;
}
