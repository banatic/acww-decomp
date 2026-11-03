/* scene_process_base: 9 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020a5428 @ 0x020a5428, 0x8 bytes, Thumb
 * func_020a5410 @ 0x020a5410, 0x18 bytes, Thumb
 * func_020a5408 @ 0x020a5408, 0x8 bytes, Thumb
 * func_020a53ec @ 0x020a53ec, 0x1c bytes, Thumb
 * func_020a53c4 @ 0x020a53c4, 0x28 bytes, Thumb
 * func_020a536c @ 0x020a536c, 0x58 bytes, Thumb
 * func_020a529c @ 0x020a529c, 0xd0 bytes, Thumb
 * func_020a5274 @ 0x020a5274, 0x28 bytes, Thumb
 * func_020a5254 @ 0x020a5254, 0x20 bytes, Thumb
 */

typedef struct {
    unsigned char pad_00[0x64];
    int unk_64;
} UnkStruct_020a529c;

extern void func_01ffd418(void *object);
extern int func_01ffd3e8(unsigned char *object);
extern void func_01ffd3e4(void *object);
extern unsigned short data_020e3c80;
extern unsigned char data_021f42ec;
extern unsigned char data_021f42e8;
extern unsigned char data_020e3c7c;
extern void *data_021dc740;
extern void func_02116a1c(int);
extern int func_0202f134(int, void *, int, int);
extern unsigned char data_021dc6c4;
extern unsigned char data_021c75b8;
extern unsigned char data_021c75b0;
extern UnkStruct_020a529c *data_020ccf94;
extern void func_0203ecfc(void);
extern void func_0203f4c4(void);
extern void func_020ee470(void *);
extern int func_02073dd4(UnkStruct_020a529c *, int);
extern int func_020a6ea0(void);
extern void func_020a6eb0(int);
extern void func_020ee62c(void *self);
extern void func_020edf54(void *self);
extern unsigned char data_020da13c[];
extern unsigned char data_020e3c94[];

void func_020a5428(void *object)
{
    func_01ffd418(object);
}

int func_020a5410(unsigned char *object)
{
    int result;
    if (func_01ffd3e8(object) != 0) {
        result = 1;
    } else {
        result = 0;
    }
    return result;
}

void func_020a5408(void *object, int status)
{
    func_01ffd3e4(object);
}

void func_020a53ec(int param0, int param1, int param2, int flags)
{
    data_020e3c80 = param0;
    data_021f42ec = param1;
    data_021f42e8 = param2;
}

void func_020a53c4(void)
{
    data_020e3c80 = 1;
    data_021f42ec = 3;
    data_021f42e8 = 3;
    data_020e3c7c = 0;
}

int func_020a536c(void)
{
    if (data_020e3c7c != 0 || data_020e3c80 == 0xd8) {
        return 0;
    }

    if (data_020e3c80 == 2) {
        func_02116a1c(1);
    }

    {
        int result = func_0202f134(data_020e3c80, data_021dc740, 0, 2);
        if (result != 0) {
            data_020e3c80 = 0xd8;
            data_020e3c7c = 1;
            return result;
        }
        return 0;
    }
}

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

void *func_020a5274(void *self)
{
    *(volatile unsigned int *) self = (unsigned int) data_020e3c94;
    *(volatile unsigned int *) self = (unsigned int) data_020da13c;
    func_020ee62c(self);
    func_020edf54(self);
    return self;
}

void *func_020a5254(void *r0)
{
    unsigned char *volatile *p = (unsigned char *volatile *) r0;
    *p = ((unsigned char *) data_020e3c94);
    *p = ((unsigned char *) data_020da13c);
    func_020ee62c(r0);
    return r0;
}
