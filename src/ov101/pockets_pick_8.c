/* pockets_pick_8: 3 functions, module ov101
 * mwccarm 1.2/base -O4,s
 * func_ov101_0229ded0 @ 0x0229ded0, 0xa0 bytes, Thumb
 * func_ov101_0229deb0 @ 0x0229deb0, 0x20 bytes, Thumb
 * func_ov101_0229de94 @ 0x0229de94, 0x1a bytes, Thumb
 */

extern void *func_ov002_02207f80(unsigned int);
extern void *func_ov002_0220830c(void *arg0);
extern void *func_020b9af4(void *);
extern void *func_ov094_0229b000(void *);
extern void func_ov094_0229bc3c(void *);
extern void *func_ov094_0229a2ec(void *);
extern void *func_ov002_02207e40(void *);
extern void func_ov002_02209e44(void *);
extern void *func_ov002_02209ccc(void *);
extern void *func_ov002_02209b14(void *);
extern void *func_ov002_0220ba24(void *);
extern void *func_ov002_0220b008(void *);
extern char data_ov101_0229e078;
extern void func_ov101_0229d97c(int);
extern void func_ov002_02208090(int, int);
extern unsigned char *func_ov002_022080a0(int, unsigned char value);
extern int __arm func_020ee45c(int);
extern void func_ov092_0229929c(int);
extern void func_ov101_0229d940(int);

void *func_ov101_0229ded0(void)
{
    void *self;
    char *p;
    char *end;

    self = func_ov002_02207f80(0x29dc);
    if (self != 0) {
        func_ov002_0220830c((void *) self);
        *(void **) self = (void *) &data_ov101_0229e078;

        p = (char *) self + 0xbc;
        end = (char *) self + 0xf4;
        do {
            func_020b9af4(p);
            p += 0x38;
        } while (p != end);

        func_ov094_0229b000(end);
        func_ov094_0229bc3c((char *) self + 0xb54);
        func_ov094_0229a2ec((char *) self + 0xb7c);
        func_ov002_02207e40((char *) self + 0x21b4);
        func_ov002_02209e44((char *) self + 0x2284);
        func_ov002_02209ccc((char *) self + 0x229c);
        func_ov002_02209b14((char *) self + 0x2300);
        func_ov002_0220ba24((char *) self + 0x26f4);
        func_ov002_0220b008((char *) self + 0x2810);
    }
    return self;
}

int func_ov101_0229deb0(int param0)
{
    func_ov101_0229d97c(param0);
    func_ov002_02208090(param0, 0);
    func_ov002_022080a0(param0, 0);
    return 1;
}

int func_ov101_0229de94(int arg0)
{
    func_ov092_0229929c(func_020ee45c(arg0));
    func_ov101_0229d940(arg0);
    return 1;
}
