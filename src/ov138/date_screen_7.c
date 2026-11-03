/* date_screen_7: 4 functions, module ov138
 * mwccarm 1.2/base -O4,s
 * func_ov138_0229d3a0 @ 0x0229d3a0, 0x44 bytes, Thumb
 * func_ov138_0229d380 @ 0x0229d380, 0x1e bytes, Thumb
 * func_ov138_0229d364 @ 0x0229d364, 0x1a bytes, Thumb
 * func_ov138_0229d310 @ 0x0229d310, 0x54 bytes, Thumb
 */

struct UnkStruct_0229d380 {
    char pad_00[0x8c];
    unsigned char unk_8C;
};

extern void *func_ov002_02207f80(unsigned int);
extern void *func_ov002_0220830c(void *);
extern void *func_ov002_02209ccc(void *);
extern void *func_ov002_0220b008(void *);
extern void *func_ov134_0229bed4(void *);
extern char data_ov138_0229d4e0[];
extern void func_ov138_0229cff4(struct UnkStruct_0229d380 *p);
extern unsigned char *func_ov002_022080a0(void *object, unsigned char value);
extern int func_020ee45c(int);
void func_ov092_0229929c(int);
extern int func_0206fe54(void);
extern void func_ov002_02209eb8(void *);
extern int func_ov138_0229c574(void *, int);
extern int func_ov002_02207f60(void *);
extern void func_ov134_0229b220(void *, int, int);
extern void func_ov002_0220ad18(void *, int);
static void func_ov138_0229cfd4(int);

void *func_ov138_0229d3a0(void)
{
    void *p = func_ov002_02207f80(0x2b78);
    if (p) {
        func_ov002_0220830c(p);
        *(void **) p = data_ov138_0229d4e0;
        func_ov002_02209ccc((char *) p + 0x98);
        func_ov002_0220b008((char *) p + 0xfc);
        func_ov134_0229bed4((char *) p + 0x2c8);
    }
    return p;
}

int func_ov138_0229d380(struct UnkStruct_0229d380 *p, int a2)
{
    func_ov138_0229cff4(p);
    p->unk_8C = 0;
    func_ov002_022080a0((void *) (p), 0);
    return 1;
}

int func_ov138_0229d364(int arg0)
{
    int a = func_020ee45c(arg0);
    func_ov092_0229929c(a);
    func_ov138_0229cfd4(arg0);
    return 1;
}

int func_ov138_0229d310(char *param)
{
    if (func_0206fe54() != 0) {
        func_ov002_02209eb8(param + 0x98);
    }
    if (func_ov138_0229c574(param, 1) == 0) {
        return 0;
    }
    {
        int result1;
        int result2;
        result1 = func_ov002_02207f60(param);
        func_ov134_0229b220(param + 0x2c8, 0, result1);
        result2 = func_ov002_02207f60(param);
        func_ov002_0220ad18(param + 0xfc, result2);
    }
    return 1;
}
