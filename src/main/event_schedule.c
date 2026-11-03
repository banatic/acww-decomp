/* event_schedule: 9 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02040a10 @ 0x02040a10, 0x36 bytes, Thumb
 * func_020409e8 @ 0x020409e8, 0x28 bytes, Thumb
 * func_020409c8 @ 0x020409c8, 0x20 bytes, Thumb
 * func_02040980 @ 0x02040980, 0x48 bytes, Thumb
 * func_0204093c @ 0x0204093c, 0x44 bytes, Thumb
 * func_020408e8 @ 0x020408e8, 0x54 bytes, Thumb
 * func_020408d4 @ 0x020408d4, 0x12 bytes, Thumb
 * func_020408b8 @ 0x020408b8, 0x1c bytes, Thumb
 * func_020408a8 @ 0x020408a8, 0x10 bytes, Thumb
 */

typedef struct {
    unsigned short unk_00;
    unsigned char unk_02;
    unsigned char unk_03;
    unsigned char unk_04;
    unsigned char unk_05;
} UnkStruct_020408d4;

extern unsigned char func_0209ded0(void);
extern unsigned short data_021c7580;
extern unsigned char data_021f39c0[];
extern int data_021dc7a8[];
extern void func_0209e474(void *ptr);
extern int func_02040bcc(void *tbl, int a);
extern int func_020984d4(void);

void func_020409e8(void *context);
void *func_02040980(void *context);

void func_02040a10(unsigned char *param)
{
    unsigned char val;
    unsigned char *p;
    unsigned char b2;
    unsigned char b13;

    val = func_0209ded0();
    p = func_02040980(param);
    if (p != 0) {
        b2 = p[2];
        b13 = param[0x13];
        if (val != b13 || b2 != param[0x12]) {
            param[0x12] = b2;
            param[0x13] = val;
        }
        func_020409e8(param);
    }
}

void func_020409e8(void *context)
{
    unsigned char *p;
    data_021c7580 = 0xff;
    p = func_02040980(data_021f39c0);
    if (p != 0) {
        data_021c7580 = p[5];
    }
}

void *func_020409c8(void *base, int n)
{
    void *ret = 0;
    if (n >= 0 && n <= 6 && n != 0 && n != 6) {
        ret = ((char *) base + 20) + (6 * (n - 1));
    }
    return ret;
}

void *func_02040980(void *context)
{
    char *base = (char *) data_021dc7a8;
    void *result = 0;
    int status = (int) func_0209ded0();

    if (status != 0) {
        struct {
            int a;
            int b;
        } local;
        local.a = 0;
        local.b = 0;

        func_0209e474(&local);
        if (((unsigned char *) &local)[2] < 6) {
            status--;
        }
        result = func_020409c8(base + 0x17218, status);
    }

    return result;
}

void func_0204093c(int a)
{
    void *table;
    int idx;
    unsigned char *p;

    table = ((char *) data_021f39c0);
    idx = func_02040bcc(table, a);
    p = func_020409c8(table, idx);
    if (p != 0) {
        if (a == 0x44) {
            p[5] = 0xff;
        } else {
            int shift = func_020984d4();
            p[5] = (unsigned char) ((p[5] & ~(1 << shift)) | (1 << shift));
        }
    }
}

int func_020408e8(int param, unsigned char flag)
{
    if (param == 0x45) {
        return 0;
    }
    {
        char *base;
        int result;
        unsigned char *p;
        int shift;

        base = ((char *) data_021dc7a8);
        result = 0;
        if (param == 0x60) {
            param = 0x40;
        }
        p = func_020409c8(base + 0x17218, flag);
        if (p != 0) {
            if (param != p[2]) {
                result = 1;
            } else {
                shift = func_020984d4();
                flag = (unsigned char) ((p[5] >> shift) & 1);
                if (flag != 0) {
                    result = 1;
                }
            }
        }
        return result;
    }
}

void func_020408d4(UnkStruct_020408d4 *arg)
{
    arg->unk_00 = 1;
    arg->unk_02 = 99;
    arg->unk_03 = 0;
    arg->unk_04 = 0;
    arg->unk_05 = 0;
}

void func_020408b8(unsigned char *dest, unsigned char value, unsigned char *src)
{
    func_020408d4((UnkStruct_020408d4 *) dest);
    dest[1] = src[4];
    dest[0] = src[3];
    dest[2] = value;
}

void func_020408a8(unsigned char *r0)
{
    unsigned char r1;
    r1 = r0[2];
    if (r1 == 0x45) {
        return;
    }
    r1 = 0xff;
    r0[5] = r1;
    r1 = 2;
    r0[3] = r1;
}
