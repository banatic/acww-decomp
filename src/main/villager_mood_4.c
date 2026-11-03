/* villager_mood_4: 6 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0201cdcc @ 0x0201cdcc, 0x10 bytes, Thumb
 * func_0201cdbc @ 0x0201cdbc, 0x10 bytes, Thumb
 * func_0201cd7c @ 0x0201cd7c, 0x40 bytes, Thumb
 * func_0201cd5c @ 0x0201cd5c, 0x20 bytes, Thumb
 * func_0201cd3c @ 0x0201cd3c, 0x1e bytes, Thumb
 * func_0201cd2c @ 0x0201cd2c, 0x10 bytes, Thumb
 */

typedef struct {
    int a;
    int b;
} Pair;

struct UnkStruct_0201cd7c {
    char pad_00[0x40];
    char unk_40;
    int unk_44;
    char unk_48;
    Pair pair;
    char pad_54[4];
    char unk_58;
    char unk_59;
    char unk_5A;
};

extern void func_020f5958(int);
extern void func_020f5948(void *arg);
extern Pair __ptmf_null;
extern void func_0201ccc0(struct UnkStruct_0201cd7c *p);
extern void func_0200451c(void *param1);
extern int func_020044a0(void *ptr);

int func_0201cd2c(unsigned char *p);

int func_0201cdcc(int arg)
{
    func_020f5958(arg);
    return arg;
}

void *func_0201cdbc(void *arg)
{
    func_020f5948(arg);
    return arg;
}

void func_0201cd7c(struct UnkStruct_0201cd7c *p)
{
    p->unk_59 = 0;
    p->unk_40 = 5;
    p->unk_44 = 5;
    p->unk_48 = 0;
    p->pair = __ptmf_null;
    func_0201ccc0(p);
    p->unk_58 = 0;
    p->unk_5A = 0;
}

void func_0201cd5c(void *param1)
{
    void *r4;
    unsigned char *r0;
    unsigned char *r4b;

    r4 = param1;
    func_0201cd7c((struct UnkStruct_0201cd7c *) r4);
    func_0200451c(r4);
    r0 = (unsigned char *) r4 + 0x5a;
    *r0 = 1;
    r4b = (unsigned char *) r4 + 0x59;
    *r4b = 1;
}

int func_0201cd3c(void *ptr)
{
    if (func_0201cd2c((unsigned char *) ptr) != 0) {
        func_020044a0(ptr);
    }
    ((char *) ptr)[0x59] = 0;
    return 0;
}

int func_0201cd2c(unsigned char *p)
{
    return p[0x59] != 0;
}
