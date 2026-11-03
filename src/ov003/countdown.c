/* countdown: 11 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_0221cb88 @ 0x0221cb88, 0x38 bytes, Thumb
 * func_ov003_0221cb60 @ 0x0221cb60, 0x28 bytes, Thumb
 * func_ov003_0221cb30 @ 0x0221cb30, 0x30 bytes, Thumb
 * func_ov003_0221cafc @ 0x0221cafc, 0x34 bytes, Thumb
 * func_ov003_0221cac4 @ 0x0221cac4, 0x38 bytes, Thumb
 * func_ov003_0221ca9c @ 0x0221ca9c, 0x28 bytes, Thumb
 * func_ov003_0221ca98 @ 0x0221ca98, 0x2 bytes, Thumb
 * func_ov003_0221c8fc @ 0x0221c8fc, 0x19c bytes, Thumb
 * func_ov003_0221c8ac @ 0x0221c8ac, 0x50 bytes, Thumb
 * func_ov003_0221c724 @ 0x0221c724, 0x188 bytes, Thumb
 * func_ov003_0221c720 @ 0x0221c720, 0x4 bytes, Thumb
 */

struct UnkStruct_0221cafc_2 {
    char pad_00;
};

struct UnkStruct_0221cafc {
    void *unk_00;
    char pad_04[0xe8];
    void *unk_EC;
    char pad_F0[0x1c8];
    struct UnkStruct_0221cafc_2 sub;
};

struct UnkStruct_0221cac4 {
    void *unk_00;
    char pad_04[0xec - 4];
    void *unk_EC;
    char pad_F0[0x2b8 - 0xec - 4];
    unsigned char unk_2B8[1];
};

typedef struct {
    unsigned char unk_00[0x198 - 0x0];
    int unk_198;
    unsigned char pad_19C[0x2b4 - 0x19c];
    unsigned char unk_2B4;
    unsigned char unk_2B5;
    unsigned char unk_2B6;
    unsigned char pad_2B7;
    unsigned char unk_2B8[0x2d8 - 0x2b8];
    unsigned char unk_2D8;
    unsigned char unk_2D9;
} UnkStruct_0221c8fc;

typedef struct {
    char pad_00[0x13c];
    int unk_13C;
    char pad_140[373];
    unsigned char unk_2B5;
    char pad_2B6[2];
    int unk_2B8;
} UnkStruct_0221c8ac;

typedef struct {
    unsigned char pad_00[0x2b4];
    unsigned char unk_2B4;
    unsigned char unk_2B5;
    unsigned char unk_2B6;
    unsigned char pad_2B7[0x21];
    unsigned char unk_2D8;
    unsigned char unk_2D9;
} UnkStruct_0221c724;

extern int func_ov009_02264cf8(void *this, int param2);
extern void func_02056478(void *ptr, int a, int b, int c, int d);
extern void func_02056ffc(void *);
extern void *func_ov009_0226552c(void *self);
extern void func_020565c8(void *sub);
extern unsigned char data_ov003_02238b10[];
extern unsigned char data_ov003_02238bd4[];
extern void *func_020565b0(void *p);
extern void *func_ov009_0226539c(void *p);
extern int func_020e9948(void *, int);
extern void *memset(int, int, int);
extern void *data_021c9b1c;
extern void func_0209e474(int *p);
extern void func_0203efb0(UnkStruct_0221c8fc *self, int idx);
extern int func_0205650c(void *p, int a, int b);
extern int func_02055e00(void *p);
extern void func_020563dc(void *p, int a);
extern unsigned char data_ov003_0223c8b0;
extern unsigned int data_ov003_0223c8b8;
extern unsigned int data_ov003_0223c8c0;
extern unsigned int data_ov003_0223c8bc;
extern void func_02056440(int *dst, void *src, int val, int flag, int param1, unsigned char param2);
extern int func_020b65c4(void);
extern void func_0200467c(int cmd);

void func_ov003_0221ca98(void *object);
void func_ov003_0221c724(UnkStruct_0221c724 *self);

int func_ov003_0221cb88(void *this)
{
    int ret;

    ret = func_ov009_02264cf8(this, 1);
    func_02056478((char *) this + 0x2b4, ret, 0, 0x1000, 0);
    *((char *) this + 0x2d5) = 1;
    return 1;
}

void func_ov003_0221cb60(void *self)
{
    func_02056ffc((char *) self + 0x2b4);
    *(int *) (*(int *) ((char *) self + 0x2cc)) = *(int *) ((char *) self + 0x2bc);
}

void *func_ov003_0221cb30(void *self)
{
    func_ov009_0226552c(self);
    *(void **) self = (void *) data_ov003_02238b10;
    *(void **) ((char *) self + 0xEC) = (void *) data_ov003_02238bd4;
    func_020565c8((char *) self + 0x2B8);
    return self;
}

struct UnkStruct_0221cafc *func_ov003_0221cafc(struct UnkStruct_0221cafc *self)
{
    self->unk_00 = (void *) ((int *) data_ov003_02238b10);
    self->unk_EC = (void *) ((int *) data_ov003_02238bd4);
    func_020565b0(&self->sub);
    func_ov009_0226539c(self);
    return self;
}

void *func_ov003_0221cac4(struct UnkStruct_0221cac4 *self)
{
    self->unk_00 = ((unsigned char *) data_ov003_02238b10);
    self->unk_EC = ((unsigned char *) data_ov003_02238bd4);
    func_020565b0(self->unk_2B8);
    func_ov009_0226539c(self);
    func_ov003_0221ca98(self);
    return self;
}

int func_ov003_0221ca9c(int a)
{
    int res;

    res = func_020e9948(data_021c9b1c, a);
    memset(res, 0, a);
    return res;
}

void func_ov003_0221ca98(void *object) {}

int func_ov003_0221c8fc(UnkStruct_0221c8fc *self)
{
    int local[3];

    self->unk_2B4 = data_ov003_0223c8b0;
    self->unk_2B5 = 0;
    func_0203efb0(self, self->unk_2B4);

    if (func_0205650c(self->unk_2B8, self->unk_198, (*(int *) &data_021c9b1c)) != 0) {
        func_02056478(self->unk_2B8, func_ov009_02264cf8((void *) self, 0), 1, 0x1000, 0);
        func_020563dc(self->unk_2B8, func_02055e00(self->unk_00 + 0x13c));
    }

    self->unk_2D8 = 1;
    self->unk_2B6 = 0xff;

    local[0] = 0;
    local[1] = 0;
    func_0209e474(local);
    if (((unsigned char *) local)[4] == 1) {
        goto end;
    }

    switch (self->unk_2B4) {
        case 0:
            self->unk_2B6 = (unsigned char) ((data_ov003_0223c8b8 / 10) & 1);
            self->unk_2B5 = self->unk_2B6;
            self->unk_2D9 = 0;
            break;
        case 1:
            self->unk_2B6 = (unsigned char) (data_ov003_0223c8b8 % 10);
            self->unk_2B5 = self->unk_2B6;
            self->unk_2D9 = 0;
            break;
        case 2:
            self->unk_2B6 = (unsigned char) (data_ov003_0223c8c0 / 10);
            self->unk_2B5 = self->unk_2B6;
            self->unk_2D9 = 0;
            break;
        case 3:
            self->unk_2B6 = (unsigned char) (data_ov003_0223c8c0 % 10);
            self->unk_2B5 = self->unk_2B6;
            self->unk_2D9 = 0;
            break;
        case 4:
            self->unk_2B6 = (unsigned char) (data_ov003_0223c8bc / 10);
            self->unk_2B5 = self->unk_2B6;
            self->unk_2D9 = 1;
            break;
        case 5:
            self->unk_2B6 = (unsigned char) (data_ov003_0223c8bc % 10);
            self->unk_2B5 = self->unk_2B6;
            self->unk_2D9 = 1;
            break;
    }

end:
    func_ov003_0221c724((UnkStruct_0221c724 *) self);
    return 1;
}

int func_ov003_0221c8ac(UnkStruct_0221c8ac *param)
{
    void *ptr;
    int val;
    func_ov003_0221c724((UnkStruct_0221c724 *) param);
    ptr = (void *) func_02055e00((void *) (&param->unk_13C));
    val = func_ov009_02264cf8(param, 0);
    func_02056440(&param->unk_2B8, ptr, val, 1, 0x1000, param->unk_2B5);
    return 1;
}

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
                    func_0200467c(0x61);
                }
                break;
            case 2:
                if (self->unk_2D9 == 0) {
                    func_0200467c(0x60);
                }
                break;
            case 3:
                if (self->unk_2D9 == 0) {
                    func_0200467c(0x62);
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

int func_ov003_0221c720(void)
{
    return 0;
}
