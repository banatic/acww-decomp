/* scene_exit: 11 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020b5e88 @ 0x020b5e88, 0x6 bytes, Thumb
 * func_020b5e84 @ 0x020b5e84, 0x4 bytes, Thumb
 * func_020b5e70 @ 0x020b5e70, 0x12 bytes, Thumb
 * func_020b5e44 @ 0x020b5e44, 0x2c bytes, Thumb
 * func_020b5e40 @ 0x020b5e40, 0x4 bytes, Thumb
 * func_020b5e38 @ 0x020b5e38, 0x6 bytes, Thumb
 * func_020b5e34 @ 0x020b5e34, 0x4 bytes, Thumb
 * func_020b5e24 @ 0x020b5e24, 0xe bytes, Thumb
 * func_020b5e20 @ 0x020b5e20, 0x4 bytes, Thumb
 * func_020b5e1c @ 0x020b5e1c, 0x4 bytes, Thumb
 * func_020b5e18 @ 0x020b5e18, 0x4 bytes, Thumb
 */

typedef struct {
    unsigned char unk_00;
} UnkStruct_020b5e88;

extern int func_020b5e10(void);
extern unsigned short data_020e3c80;
extern void func_020a53ec(int, int, int, int);
extern void func_0209d074(int);

void func_020b5e88(UnkStruct_020b5e88 *p)
{
    p->unk_00 = 63;
}

int func_020b5e84(unsigned char *p0)
{
    return p0[0];
}

int func_020b5e70(void)
{
    return func_020b5e84((unsigned char *) func_020b5e10());
}

void func_020b5e44(int arg0, int arg1)
{
    int local_0;
    int local_1;

    local_0 = arg0;
    local_1 = arg1;
    if (data_020e3c80 != 5) {
        func_020a53ec(5, local_0, 3, 1);
        func_0209d074(local_1);
    }
}

int func_020b5e40(int p0)
{
    return ((int) (p0) + (4));
}

int func_020b5e38(short *p)
{
    return p[1];
}

int func_020b5e34(int *p0)
{
    return p0[4];
}

int func_020b5e24(const unsigned char *p)
{
    if (p[1] != 0) {
        return 1;
    }
    return 0;
}

int func_020b5e20(unsigned char *p0)
{
    return p0[20];
}

void func_020b5e1c(unsigned char *p0, int p1)
{
    p0[20] = p1;
}

int func_020b5e18(unsigned char *p0)
{
    return p0[21];
}
