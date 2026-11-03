/* event_announce: 5 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0204141c @ 0x0204141c, 0x54 bytes, Thumb
 * func_020413f8 @ 0x020413f8, 0x24 bytes, Thumb
 * func_020413f4 @ 0x020413f4, 0x2 bytes, Thumb
 * func_0204130c @ 0x0204130c, 0xe8 bytes, Thumb
 * func_020412a0 @ 0x020412a0, 0x6a bytes, Thumb
 */

struct UnkStruct_0204141c {
    int unk_00;
    int unk_04;
};

extern struct UnkStruct_0204141c *func_020682e0(int);
extern void func_02068320(struct UnkStruct_0204141c *);
extern int func_020b5e10(void);
extern int func_020b6098(int, int);
extern void func_02035c1c(int, int, unsigned char);
extern int data_021c526c;
extern int data_021c758c;
extern unsigned char data_021c75a0[];
extern int func_020415a8(void);
extern struct {
    unsigned char pad[0x64];
    unsigned int field_0x64;
} *data_020ccf94;
int func_02073d90(void *p);
int func_020b65c4(void);
int func_0208602c(void);
int func_020860c8(int);
int func_02087ea0(unsigned char *);
int func_02073dd4(void *obj, unsigned int member);
void func_0209e474(int *buf);

void func_0204141c(void *receiver)
{
    struct UnkStruct_0204141c *p = func_020682e0(0);
    if (p->unk_04 != 0) {
        return;
    }
    func_02068320(p);
    func_020b6098(func_020b5e10(), 0x14);
    func_02035c1c(data_021c526c + 0x2d0, data_021c758c, data_021c75a0[4]);
    data_021c758c = 0;
    data_021c75a0[0] = 0;
    data_021c75a0[2] = 0;
}

void func_020413f8(int param)
{
    int cond;
    if (param == 3) {
        cond = func_020415a8();
    } else {
        cond = 1;
    }
    if (cond) {
        (*(unsigned char *) data_021c75a0) = (unsigned char) param;
    }
}

void func_020413f4(void *object) {}

void func_0204130c(int a, int b, int c)
{
    int r4;
    int r6;
    int buf[2];

    if (func_02073d90(data_020ccf94) != 0) {
        return;
    }
    if (func_020b65c4() != 0) {
        goto label_1348;
    }
    if (func_02087ea0((unsigned char *) func_020860c8((int) func_0208602c())) == 0) {
        goto label_1348;
    }
    if (func_02073dd4(data_020ccf94, data_020ccf94->field_0x64) == 0) {
        return;
    }

label_1348:
    if (data_021c75a0[2] != 0) {
        return;
    }

    r4 = -1;

    if (a >= 9 && a <= 18) {
        r4 = a - 9;
        if (c == 0) {
            data_021c758c = 1;
        } else {
            data_021c758c = 2;
        }
        r6 = 2;
        goto common;
    } else if (a == 68) {
        if (data_021c75a0[0] == 0) {
            r4 = 14;
            data_021c758c = 0;
            r6 = 2;
            goto common;
        } else {
            goto common;
        }
    } else if (a >= 0) {
        goto common;
    } else {
        switch (data_021c75a0[0]) {
            case 0:
                buf[0] = 0;
                buf[1] = 0;
                r4 = 15;
                data_021c758c = 0;
                data_021c75a0[3] = 1;
                func_0209e474(buf);
                if (((unsigned char *) buf)[1] != 0) {
                    goto set_r6_3;
                }
                r6 = 1;
                goto common;
            set_r6_3:
                r6 = 3;
                break;
            case 2:
                data_021c75a0[3] = 1;
                // fall through
        }
    }

common:
    if (r4 < 0) {
        return;
    }
    func_020413f8(r6);
    data_021c75a0[4] = (unsigned char) r4;
    data_021c75a0[1] = (unsigned char) c;
    *(unsigned int *) (data_021c75a0 + 8) = b;
}

int func_020412a0(void)
{
    int key = func_020b65c4();
    switch (key) {
        case 6:
        case 12:
        case 13:
        case 14:
        case 44:
        case 45:
        case 46:
        case 47:
        case 48:
        case 50:
            return 1;
        default:
            return 0;
    }
}
