/* block_021d27ac_parts: 18 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02087f18 @ 0x02087f18, 0x8 bytes, Thumb
 * func_02087f14 @ 0x02087f14, 0x2 bytes, Thumb
 * func_02087f0c @ 0x02087f0c, 0x8 bytes, Thumb
 * func_02087f08 @ 0x02087f08, 0x2 bytes, Thumb
 * func_02087ef0 @ 0x02087ef0, 0x18 bytes, Thumb
 * func_02087ec0 @ 0x02087ec0, 0x30 bytes, Thumb
 * func_02087ebc @ 0x02087ebc, 0x2 bytes, Thumb
 * func_02087eb8 @ 0x02087eb8, 0x2 bytes, Thumb
 * func_02087eb0 @ 0x02087eb0, 0x6 bytes, Thumb
 * func_02087ea0 @ 0x02087ea0, 0xe bytes, Thumb
 * func_02087e9c @ 0x02087e9c, 0x4 bytes, Thumb
 * func_02087e98 @ 0x02087e98, 0x2 bytes, Thumb
 * func_02087e94 @ 0x02087e94, 0x2 bytes, Thumb
 * func_02087e8c @ 0x02087e8c, 0x6 bytes, Thumb
 * func_02087e88 @ 0x02087e88, 0x4 bytes, Thumb
 * func_02087e84 @ 0x02087e84, 0x4 bytes, Thumb
 * func_02087e80 @ 0x02087e80, 0x4 bytes, Thumb
 * func_02087e78 @ 0x02087e78, 0x6 bytes, Thumb
 */

typedef struct {
    unsigned char unk_00;
} UnkStruct_02087eb0;

typedef struct {
    unsigned char pad_00[2];
    unsigned char unk_02;
} UnkStruct_02087e8c;

extern void func_0209e474(unsigned char *);
extern int func_0209e3ac(void *, void *, int);

void func_02087f18(int *p0)
{
    p0[0] = 0;
    p0[1] = 0;
}

void func_02087f14(void *object) {}

void func_02087f0c(int *p0)
{
    p0[0] = 0;
    p0[1] = 0;
}

void *func_02087f08(void *record)
{
    return record;
}

void func_02087ef0(unsigned char *r4)
{
    func_0209e474(r4);
    r4[2] = 0x17;
    r4[1] = 0;
    r4[0] = 0;
}

int func_02087ec0(void *param)
{
    int result;
    int local[2];
    int i;

    local[0] = 0;
    local[1] = 0;
    func_0209e474((unsigned char *) local);
    result = func_0209e3ac(param, local, 0x3f);
    i = 0;
    if (result == -1) {
        i = 1;
    }
    return i;
}

void func_02087ebc(void *object) {}

void func_02087eb8(void *object) {}

void func_02087eb0(UnkStruct_02087eb0 *p)
{
    p->unk_00 = 0;
}

int func_02087ea0(unsigned char *p)
{
    if (*p != 0) {
        return 1;
    } else {
        return 0;
    }
}

void func_02087e9c(unsigned char *p0, int p1)
{
    p0[0] = p1;
}

void func_02087e98(void *object) {}

void func_02087e94(void *object) {}

void func_02087e8c(UnkStruct_02087e8c *p)
{
    p->unk_02 = 0;
}

void func_02087e88(unsigned char *p0, int p1)
{
    p0[2] = p1;
}

int func_02087e84(unsigned char *p0)
{
    return p0[2];
}

void func_02087e80(unsigned short *p0, int p1)
{
    p0[0] = p1;
}

int func_02087e78(short *p)
{
    return p[0];
}
