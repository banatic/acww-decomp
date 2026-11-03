/* carried_letters_2: 4 functions, module ov103
 * mwccarm 1.2/base -O4,s
 * func_ov103_0229c774 @ 0x0229c774, 0x78 bytes, Thumb
 * func_ov103_0229c720 @ 0x0229c720, 0x54 bytes, Thumb
 * func_ov103_0229c6d4 @ 0x0229c6d4, 0x4c bytes, Thumb
 * func_ov103_0229c6a0 @ 0x0229c6a0, 0x34 bytes, Thumb
 */

struct UnkStruct_0229c6d4 {
    char pad_00[0x2274];
    char unk_2274;
    char pad_2275[0x63];
    char unk_22D8;
    char pad_22D9[0xad0];
    unsigned char unk_2DA9;
};

extern int func_ov103_0229c2f4(void *p, int a);
extern int func_ov103_0229c820(void *p);
extern int func_ov103_0229c810(void *p);
extern void func_ov103_0229c2d4(void *p, int a);
extern void func_ov002_0220a0b4(void *p, int a, int b);
extern void func_ov002_0220a05c(void *p, int a, int b, int c, int d);
extern unsigned char *func_ov002_02208098(void *p, unsigned char value);
extern int func_ov002_02208ae4(void *);
extern int func_ov002_02208ad8(void *, unsigned int);
extern int func_ov002_0220a08c(void *, int, int, int);
extern void func_ov002_0220a374(const char *p, int arg);

void func_ov103_0229c774(unsigned char *param)
{
    if (func_ov103_0229c2f4(param, 8) != 0) {
        int a;
        int b;
        a = func_ov103_0229c820(param);
        b = func_ov103_0229c810(param);
        func_ov002_0220a0b4((unsigned char *) param + 0x2274, a, b);
        func_ov103_0229c2d4(param, 8);
    } else {
        int a;
        int b;
        unsigned char *p;
        a = func_ov103_0229c820(param);
        b = func_ov103_0229c810(param);
        func_ov002_0220a05c((unsigned char *) param + 0x2274, a, b, 3, 1);
        p = param + 0x8d;
        param[0x2da7] = *p;
        func_ov002_02208098(param, 0xb);
    }
}

void func_ov103_0229c720(unsigned char *p)
{
    int a;
    unsigned char flag;
    int b;

    a = func_ov002_02208ae4(p + 0x22d8);
    flag = p[0x2da9];
    b = func_ov002_02208ad8(p + 0x22d8, flag);
    func_ov002_0220a08c(p + 0x2274, a, b, 2);
    p[0x2da7] = p[0x8d];
    func_ov002_02208098(p, 11);
}

void func_ov103_0229c6d4(struct UnkStruct_0229c6d4 *s)
{
    int a;
    s->unk_2DA9 = 0;
    a = func_ov002_02208ae4((void *) (&s->unk_22D8));
    func_ov002_0220a0b4((void *) (&s->unk_2274), a, func_ov002_02208ad8((void *) (&s->unk_22D8), s->unk_2DA9));
    func_ov002_0220a374(&s->unk_2274, 7);
}

void func_ov103_0229c6a0(char *param)
{
    int a = func_ov103_0229c820((void *) param);
    int b = func_ov103_0229c810((void *) param);
    func_ov002_0220a0b4(param + 0x2274, a, b);
    func_ov002_0220a374((const char *) (param + 0x2274), 1);
}
