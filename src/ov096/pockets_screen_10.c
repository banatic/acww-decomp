/* pockets_screen_10: 5 functions, module ov096
 * mwccarm 1.2/base -O4,s
 * func_ov096_0229ee80 @ 0x0229ee80, 0x1a bytes, Thumb
 * func_ov096_0229ee50 @ 0x0229ee50, 0x30 bytes, Thumb
 * func_ov096_0229ee38 @ 0x0229ee38, 0x16 bytes, Thumb
 * func_ov096_0229ee10 @ 0x0229ee10, 0x28 bytes, Thumb
 * func_ov096_0229edec @ 0x0229edec, 0x24 bytes, Thumb
 */

struct UnkStruct_0229ee80 {
    char pad_00[0xac];
    unsigned short unk_AC;
    char pad_AE[2];
    unsigned char unk_B0;
};

extern int func_ov096_0229ef30(struct UnkStruct_0229ee80 *s, int x, unsigned short a, unsigned char b);
extern int func_ov096_0229e4f8(void *argument0);
extern int func_ov096_0229e6b0(int a);
extern int func_ov096_0229e170(int, int);
extern void func_ov094_0229ab5c(void *);
extern void func_ov094_0229b98c(void *);

int func_ov096_0229ee80(struct UnkStruct_0229ee80 *s, int x)
{
    return func_ov096_0229ef30(s, x, s->unk_AC, s->unk_B0);
}

int func_ov096_0229ee50(int r0, int r1)
{
    if (r1 == 0) {
        return 1;
    }
    if (r1 == 2) {
        return 0;
    }
    if (r1 == 1) {
        if (func_ov096_0229e4f8((void *) r0) == 1) {
            return 0;
        }
        return 1;
    }
    return 0;
}

int func_ov096_0229ee38(int a, int b)
{
    if (b == 1) {
        return func_ov096_0229e6b0(a);
    }
    return 0;
}

int func_ov096_0229ee10(int param1, int param2)
{
    int result;
    int ret;

    if (param2 == 2) {
        result = 0;
    } else if (param2 == 0) {
        result = 1;
    } else if (param2 == 1) {
        ret = func_ov096_0229e170(param1, 0);
        result = ret;
    } else {
        result = 0;
    }
    return result;
}

void func_ov096_0229edec(void *arg0)
{
    func_ov094_0229ab5c((char *) arg0 + 0x358);
    func_ov094_0229b98c((char *) arg0 + 0xdb8);
}
