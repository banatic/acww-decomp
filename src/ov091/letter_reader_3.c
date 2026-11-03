/* letter_reader_3: 3 functions, module ov091
 * mwccarm 1.2/base -O4,s
 * func_ov091_02299494 @ 0x02299494, 0x48 bytes, Thumb
 * func_ov091_02299470 @ 0x02299470, 0x24 bytes, Thumb
 * func_ov091_0229945c @ 0x0229945c, 0x14 bytes, Thumb
 */

extern void *func_ov002_02207f80(unsigned int size);
extern void *func_ov002_0220830c(void *p);
extern void *func_0206e388(void *p);
extern void *func_ov002_0220b428(void *p);
extern void *func_ov002_02209c78(void *p);
extern int data_ov091_02299530;
extern void func_ov091_02299064(int arg);
extern void func_ov002_02208090(int arg, int n);
extern unsigned char *func_ov002_022080a0(int arg, unsigned char value);
extern void func_020041fc(void);
extern void func_ov091_02299058(char *object);
extern void func_020041ec(void);

void *func_ov091_02299494(void)
{
    void *p;
    p = func_ov002_02207f80(0x498);
    if (p == 0) {
        goto end;
    }
    func_ov002_0220830c(p);
    *(int *) p = (int) &data_ov091_02299530;
    func_0206e388((char *) p + 0x94);
    func_ov002_0220b428((char *) p + 0x3bc);
    func_ov002_02209c78((char *) p + 0x434);
end:
    return p;
}

int func_ov091_02299470(int arg)
{
    func_ov091_02299064(arg);
    func_ov002_02208090(arg, 0);
    func_ov002_022080a0(arg, 1);
    func_020041fc();
    return 1;
}

int func_ov091_0229945c(char *object)
{
    func_ov091_02299058(object);
    func_020041ec();
    return 1;
}
