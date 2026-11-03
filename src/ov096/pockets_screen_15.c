/* pockets_screen_15: 7 functions, module ov096
 * mwccarm 1.2/base -O4,s
 * func_ov096_0229fbf0 @ 0x0229fbf0, 0x1c bytes, Thumb
 * func_ov096_0229fbbc @ 0x0229fbbc, 0x34 bytes, Thumb
 * func_ov096_0229fb9c @ 0x0229fb9c, 0x20 bytes, Thumb
 * func_ov096_0229fb84 @ 0x0229fb84, 0x16 bytes, Thumb
 * func_ov096_0229fb6c @ 0x0229fb6c, 0x16 bytes, Thumb
 * func_ov096_0229fb4c @ 0x0229fb4c, 0x20 bytes, Thumb
 * func_ov096_0229faf8 @ 0x0229faf8, 0x54 bytes, Thumb
 */

typedef struct {
    char pad_00[0xb2];
    unsigned char unk_B2;
    char pad_B3[0x2899];
    char unk_294C[1];
} UnkStruct_0229faf8;

extern void func_ov096_0229ddd8(void *);
extern void func_ov096_0229edec(void *);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern int func_0206fe60(void);
extern void func_ov096_0229de50(int arg);
extern void func_ov096_0229c2dc(void *, int);
extern void func_ov096_0229c2ec(void *, int);
extern int func_ov096_0229f830(void *, unsigned char);
extern void func_ov096_0229cf84(void *, unsigned char);
extern void func_ov002_02208d30(void *, int);
extern int func_ov002_02208d18(void *);

void func_ov096_0229fbf0(void *p)
{
    func_ov096_0229ddd8(p);
    func_ov096_0229edec(p);
    func_ov002_02208098((void *) (p), 0);
}

void func_ov096_0229fbbc(void *param)
{
    extern void func_ov096_0229dea4(void *);
    extern void func_ov096_0229eb14(void *);
    extern void func_ov096_0229ed74(void *, unsigned char);
    extern void func_ov002_02207fc0(void *);
    extern unsigned char *func_ov002_02208098(void *object, unsigned char value);

    unsigned char *p = (unsigned char *) param;
    p[0xb3] = 0x26;
    func_ov096_0229dea4(param);
    func_ov002_02207fc0(param);
    func_ov096_0229eb14(param);
    func_ov002_02208098((void *) (param), 0xa);
    func_ov096_0229ed74(param, p[0xb5]);
}

void func_ov096_0229fb9c(int r0)
{
    int r4 = r0;
    if (func_0206fe60() != 0) {
        func_ov096_0229fbf0((void *) r4);
    } else {
        func_ov096_0229fbbc((void *) r4);
    }
}

int func_ov096_0229fb84(int a)
{
    func_ov096_0229ddd8((void *) a);
    return (int) func_ov002_02208098((void *) (a), 8);
}

int func_ov096_0229fb6c(int arg)
{
    func_ov096_0229de50(arg);
    return (int) func_ov002_02208098((void *) (arg), 0x19);
}

void func_ov096_0229fb4c(int param)
{
    if (func_0206fe60()) {
        func_ov096_0229fb84(param);
    } else {
        func_ov096_0229fb6c(param);
    }
}

void func_ov096_0229faf8(UnkStruct_0229faf8 *param)
{
    func_ov096_0229c2dc(param, 0x00010000);
    if (func_ov096_0229f830(param, param->unk_B2) != 0) {
        func_ov002_02208d30(&param->unk_294C, 0x22);
        func_ov096_0229cf84(param, param->unk_B2);
        if (func_ov002_02208d18(&param->unk_294C) == 0) {
            func_ov096_0229c2ec(param, 0x00010000);
        }
    }
}
