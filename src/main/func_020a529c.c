/* func_020a529c @ 0x020a529c, 0xd0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021dc6c4;
extern unsigned char data_021c75b8;
extern unsigned char data_021c75b0;
extern unsigned short data_020e3c80;

typedef struct {
    unsigned char pad_00[0x64];
    int unk_64;
} UnkStruct_020a529c;

extern UnkStruct_020a529c *data_020ccf94;

extern void func_020a53ec(int, int, int, int);
extern void func_0203ecfc(void);
extern void func_0203f4c4(void);
extern void func_020ee470(void *);
extern int func_02073dd4(UnkStruct_020a529c *, int);
extern int func_020a6ea0(void);
extern void func_020a6eb0(int);

void func_020a529c(void *self)
{
    if (data_021dc6c4 != 0) {
        unsigned int c1;
        unsigned int c2;
        unsigned char b1;

        b1 = data_021c75b8;
        c1 = (b1 == 2) ? 1 : 0;
        if (c1 != 0) {
            return;
        }
        c2 = (b1 == 0) ? 1 : 0;
        if (c2 == 0) {
            return;
        }
        func_020a53ec(0xd4, 0, 0, 0);
        func_020ee470(self);
        func_0203ecfc();
        func_0203f4c4();
    } else {
        unsigned int c1c;
        unsigned int c2c;
        unsigned char b1c;
        UnkStruct_020a529c *p;
        int ret;
        int v;

        if (data_020e3c80 == 0xd8) {
            return;
        }
        b1c = data_021c75b8;
        c1c = (b1c == 2) ? 1 : 0;
        if (c1c != 0) {
            return;
        }
        if (data_021c75b0 != 0) {
            return;
        }
        c2c = (b1c == 0) ? 1 : 0;
        if (c2c == 0) {
            return;
        }

        p = data_020ccf94;
        ret = func_02073dd4(p, p->unk_64);
        if (ret != 0) {
            v = func_020a6ea0();
            switch (v) {
                case 5:
                    func_020ee470(self);
                    func_020a6eb0(6);
                    break;
                case 0xc:
                    func_020ee470(self);
                    func_020a6eb0(0xd);
                    break;
                default:
                    break;
            }
        } else {
            func_020ee470(self);
        }
    }
}
