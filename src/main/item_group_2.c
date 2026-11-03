/* item_group_2: 13 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0204b3b4 @ 0x0204b3b4, 0x18 bytes, Thumb
 * func_0204b39c @ 0x0204b39c, 0x18 bytes, Thumb
 * func_0204b384 @ 0x0204b384, 0x18 bytes, Thumb
 * func_0204b368 @ 0x0204b368, 0x1c bytes, Thumb
 * func_0204b350 @ 0x0204b350, 0x18 bytes, Thumb
 * func_0204b328 @ 0x0204b328, 0x28 bytes, Thumb
 * func_0204b320 @ 0x0204b320, 0x8 bytes, Thumb
 * func_0204b2f8 @ 0x0204b2f8, 0x28 bytes, Thumb
 * func_0204b2f0 @ 0x0204b2f0, 0x8 bytes, Thumb
 * func_0204b2c8 @ 0x0204b2c8, 0x28 bytes, Thumb
 * func_0204b2c0 @ 0x0204b2c0, 0x8 bytes, Thumb
 * func_0204b298 @ 0x0204b298, 0x28 bytes, Thumb
 * func_0204b290 @ 0x0204b290, 0x8 bytes, Thumb
 */

typedef struct {
    unsigned short unk_00;
} UnkStruct_0204b2f8;

unsigned short func_0204b3b4(unsigned int x)
{
    if (x < 0x38) {
        return (unsigned short) (x + 0x12b0);
    } else {
        return 0x12b0;
    }
}

unsigned short func_0204b39c(unsigned int a)
{
    if (a < 0x40) {
        return (unsigned short) (a + 0x13c8);
    }
    return 0x13c8;
}

unsigned short func_0204b384(unsigned short x)
{
    if (x < 0x44) {
        return (unsigned short) (x + 0x1144);
    }
    return 0x1144;
}

unsigned short func_0204b368(unsigned short param)
{
    if (param < 0x100) {
        return (unsigned short) (param + 0x11a8);
    }
    return 0x11a8;
}

unsigned short func_0204b350(unsigned int x)
{
    if (x < 0x40) {
        return x + 0x1431;
    } else {
        return 0x1431;
    }
}

int func_0204b328(unsigned short *p)
{
    unsigned short value;
    int flag;

    flag = 0;
    value = *p;
    if (value >= 0x13c8u && value <= 0x1407u) {
        flag = 1;
    }
    if (flag) {
        return 1;
    } else {
        return 0;
    }
}

void func_0204b320(unsigned short *argument0)
{
    func_0204b328((unsigned short *) argument0);
}

int func_0204b2f8(UnkStruct_0204b2f8 *s)
{
    int r;
    unsigned short v;

    r = 0;
    v = s->unk_00;

    if (v >= 0x1144 && v <= 0x1187) {
        r = 1;
    }

    if (r) {
        return 1;
    } else {
        return 0;
    }
}

void func_0204b2f0(void *argument0)
{
    func_0204b2f8((UnkStruct_0204b2f8 *) ((void *) argument0));
}

int func_0204b2c8(unsigned short *ptr)
{
    int flag;
    flag = 0;
    if (*ptr >= 0x11a8 && *ptr <= 0x12a7) {
        flag = 1;
    }
    if (flag) {
        return 1;
    } else {
        return 0;
    }
}

void func_0204b2c0(unsigned short *argument0)
{
    func_0204b2c8((unsigned short *) argument0);
}

unsigned short func_0204b298(void *param0)
{
    unsigned short r1;
    unsigned short r2;
    unsigned short r0;

    r2 = 0;
    r1 = *(unsigned short *) param0;
    r0 = 0x1431;
    if (r1 < r0) {
        goto label_0204b2aa;
    }
    r0 = 0x1470;
    if (r1 > r0) {
        goto label_0204b2aa;
    }
    r2 = 1;
label_0204b2aa:
    if (r2 == 0) {
        goto label_0204b2b2;
    }
    return 1;
label_0204b2b2:
    return 0;
}

void func_0204b290(void *argument0)
{
    func_0204b298((void *) argument0);
}
