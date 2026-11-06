/* song_pockets_2: 5 functions, module ov109
 * mwccarm 1.2/base -O4,s
 * func_ov109_0229c7b0 @ 0x0229c7b0, 0x78 bytes, Thumb
 * func_ov109_0229c75c @ 0x0229c75c, 0x54 bytes, Thumb
 * func_ov109_0229c6f8 @ 0x0229c6f8, 0x64 bytes, Thumb
 * func_ov109_0229c6ac @ 0x0229c6ac, 0x4c bytes, Thumb
 * func_ov109_0229c678 @ 0x0229c678, 0x34 bytes, Thumb
 */

typedef struct UnkStruct_0229c6ac {
    char pad_00[0x2274];
    int unk_2274;
    char pad_2278[0x22d8 - 0x2274 - 4];
    int unk_22D8;
    char pad_22DC[0x29d8 - 0x22d8 - 4];
    unsigned char unk_29D8;
} UnkStruct_0229c6ac;

extern int func_ov109_0229c2ac(void *p, int n);
extern void func_ov109_0229c28c(void *p, int n);
extern int func_ov109_0229c85c(void *p);
extern int func_ov109_0229c84c(void *p);
extern void func_ov002_0220a0b4(void *p, int a, int b);
extern void func_ov002_0220a05c(void *p, int a, int b, int c, int d);
extern unsigned char *func_ov002_02208098(void *p, unsigned char value);
extern int func_ov002_02208ae4(const unsigned char *p);
extern int func_ov002_02208ad8(const unsigned char *p, int b);
extern int func_ov002_0220a08c(const unsigned char *p, int a, int b, int c);
extern char func_ov002_022090e4(void *ptr, int arg1);
extern void func_0208e4c0(void *ptr, int val);
extern void func_ov002_0220a374(int *a, int b);

void func_ov109_0229c7b0(unsigned char *arg0)
{
    if (func_ov109_0229c2ac(arg0, 4)) {
        int a = func_ov109_0229c85c(arg0);
        int b = func_ov109_0229c84c(arg0);
        func_ov002_0220a0b4(arg0 + 0x2274, a, b);
        func_ov109_0229c28c(arg0, 4);
    } else {
        int a = func_ov109_0229c85c(arg0);
        int b = func_ov109_0229c84c(arg0);
        func_ov002_0220a05c(arg0 + 0x2274, a, b, 3, 1);
        arg0[0x29d6] = arg0[0x8d];
        func_ov002_02208098(arg0, 8);
    }
}

void func_ov109_0229c75c(unsigned char *self)
{
    int v1, v2;

    v1 = func_ov002_02208ae4(self + 0x22d8);
    v2 = func_ov002_02208ad8(self + 0x22d8, self[0x29d8]);
    func_ov002_0220a08c(self + 0x2274, v1, v2, 2);
    self[0x29d6] = self[0x8d];
    func_ov002_02208098((void *) self, 8);
}

int func_ov109_0229c6f8(unsigned char *p)
{
    p[0x29d7] = 1;
    p[0x29d8] = func_ov002_022090e4(p + 0x22d8, 1);
    func_ov002_0220a0b4(p + 0x2274, func_ov002_02208ae4((const unsigned char *) (p + 0x22d8)),
                        func_ov002_02208ad8((const unsigned char *) (p + 0x22d8), (unsigned char) p[0x29d8]));
    func_0208e4c0(p + 0x2274, 8);
    return (int) func_ov002_02208098(p, 0xc);
}

void func_ov109_0229c6ac(UnkStruct_0229c6ac *p)
{
    int ret1;
    int ret2;

    p->unk_29D8 = 0;
    ret1 = func_ov002_02208ae4((const unsigned char *) (&p->unk_22D8));
    ret2 = func_ov002_02208ad8((const unsigned char *) (&p->unk_22D8), p->unk_29D8);
    func_ov002_0220a0b4((void *) (&p->unk_2274), ret1, ret2);
    func_ov002_0220a374(&p->unk_2274, 7);
}

void func_ov109_0229c678(char *param)
{
    int a = func_ov109_0229c85c((void *) param);
    int b = func_ov109_0229c84c((void *) param);
    func_ov002_0220a0b4(param + 0x2274, a, b);
    func_ov002_0220a374((int *) (param + 0x2274), 1);
}
