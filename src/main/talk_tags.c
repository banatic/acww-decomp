/* talk_tags: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020692f8 @ 0x020692f8, 0x84 bytes, Thumb
 * func_020692c8 @ 0x020692c8, 0x30 bytes, Thumb
 * func_02069270 @ 0x02069270, 0x56 bytes, Thumb
 */

typedef struct {
    char pad_00[0x24];
    void *unk_24;
    char pad_28[0x10];
    char unk_38;
} UnkStruct_020692f8;

struct UnkStruct_020692c8 {
    char unk_00[0x24];        // 0x00
    void *unk_24;             // 0x24
    void *unk_28;             // 0x28
    char unk_2C[0x38 - 0x2C]; // 0x2C
    char unk_38[0x5c - 0x38]; // 0x38
    unsigned int value_5c;    // 0x5c
};

extern void func_020a873c(void *a, void *b);
extern int func_02050bf8(unsigned char c);
extern int func_02050c04(unsigned char c);
extern void func_020a9334(void *self, int value);
extern unsigned int func_020a8308(void *);
extern void func_0206c224(void *, void *);
extern void func_0206c1a8(void *, unsigned int);
extern void func_020a8328(char *p, int *a, int *b, int *c);
extern int func_02068114(void);
extern void func_0206bf78(char *p, int b, int a, int flag);
extern void func_0206bf3c(char *p, int c, int d, int flag);
extern void func_020a93e8(char *p, int shifted);

void func_020692f8(UnkStruct_020692f8 *self)
{
    unsigned char local;
    char *base;
    int first;
    int second;
    int rem;
    int result;

    func_020a873c((char *) self + 0x38, &local);
    local--;
    base = (char *) self->unk_24;
    first = *(int *) (base + 0x1a60);
    second = *(int *) (base + 0x1a5c);
    if (second == 0) {
        goto simple;
    }
    rem = (second - 0xac00) % 0x1c;
    if (rem == 0) {
        goto simple;
    }
    if (first != 1) {
        goto f2b;
    }
    if (local != 6) {
        goto f2a;
    }
    if (rem != 8) {
        goto f2a;
    }
    result = func_02050bf8(local);
    goto done;
f2a:
    result = func_02050c04(local);
    goto done;
f2b:
    result = func_02050c04(local);
    goto done;
simple:
    result = func_02050bf8(local);
    goto done;
done:
    func_020a9334(self, result);
}

void func_020692c8(struct UnkStruct_020692c8 *r4)
{
    r4->value_5c = func_020a8308(&r4->unk_38);
    func_0206c224(r4->unk_28, &r4->unk_38);
    func_0206c1a8(r4->unk_28, r4->value_5c);
    *((unsigned int *) ((char *) r4->unk_24 + 0x1a54)) = r4->value_5c;
}

void func_02069270(char *p)
{
    int a, b, c;
    int flag;

    func_020a8328(p + 0x38, &a, &b, &c);
    flag = func_02068114();
    func_0206bf78(p + 0x60, b, a, flag);
    func_0206bf3c(p + 0x9c, c, c + ((b - c) ^ 1), !flag);
    func_020a93e8(p, a << 1);
}
