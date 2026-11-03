/* star_designer_6: 4 functions, module ov129
 * mwccarm 1.2/base -O4,s
 * func_ov129_0229da80 @ 0x0229da80, 0x60 bytes, Thumb
 * func_ov129_0229da60 @ 0x0229da60, 0x1e bytes, Thumb
 * func_ov129_0229da44 @ 0x0229da44, 0x1a bytes, Thumb
 * func_ov129_0229d9a4 @ 0x0229d9a4, 0xa0 bytes, Thumb
 */

extern void *func_ov002_02207f80(unsigned int size);
extern void *func_ov002_0220830c(void *ptr);
extern void *func_ov002_0220ba24(void *ptr);
extern void *func_ov002_0220b008(void *ptr);
extern void *func_ov002_02209ccc(void *ptr);
extern void *func_020b18ac(void *ptr);
extern int func_ov127_0229a0ec(void *ptr);
extern unsigned char data_ov129_0229dc38[];
extern void func_ov129_0229d2d0(void *);
extern unsigned char *func_ov002_022080a0(void *, unsigned char);
extern int func_020ee45c(void *arg);
extern void func_ov092_0229929c(void *argument0);
extern void func_ov129_0229d268(void *arg);
extern int func_0206fe54(void);
extern void func_ov002_02209eb8(void *);
extern int func_ov129_0229b7ec(void *, int);
extern void func_ov002_0220ad18(void *, unsigned int);
extern void func_ov127_02299dc0(void *, int);
extern void func_ov127_02299de8(void *, unsigned int, int);
extern int func_ov127_02299d64(void *, int);

void *func_ov129_0229da80(void)
{
    void *obj = func_ov002_02207f80(0x3160);
    if (obj) {
        func_ov002_0220830c(obj);
        *(void **) obj = (void *) data_ov129_0229dc38;
        func_ov002_0220ba24((char *) obj + 0xb8);
        func_ov002_0220b008((char *) obj + 0x1d4);
        func_ov002_02209ccc((char *) obj + 0x3a0);
        func_020b18ac((char *) obj + 0x404);
        func_ov127_0229a0ec((char *) obj + 0x734);
    }
    return obj;
}

int func_ov129_0229da60(void *arg0)
{
    void *r4 = arg0;
    func_ov129_0229d2d0(r4);
    ((unsigned char *) r4)[0x8c] = 0;
    func_ov002_022080a0(r4, 0);
    return 1;
}

int func_ov129_0229da44(void *arg)
{

    func_ov092_0229929c((void *) func_020ee45c(arg));
    func_ov129_0229d268(arg);
    return 1;
}

int func_ov129_0229d9a4(char *self)
{
    if (func_0206fe54()) {
        func_ov002_02209eb8(self + 0x3a0);
    }
    if (func_ov129_0229b7ec(self, 8)) {
        func_ov002_0220ad18(self + 0x1d4, *(unsigned int *) (self + 0xa0));
    }
    if (func_0206fe54()) {
        if (func_ov129_0229b7ec(self, 0x10)) {
            func_ov127_02299dc0(self + 0x734, 0);
        }
    }
    if (func_ov129_0229b7ec(self, 1)) {
        func_ov127_02299de8(self + 0x734, *(unsigned int *) (self + 0x9c), 5);
    }
    if (*(unsigned char *) (self + 0xb3) != 0xff) {
        if (func_ov129_0229b7ec(self, 0x80)) {
            func_ov127_02299d64(self + 0x734, *(unsigned char *) (self + 0xb3));
        }
    }
    return 1;
}
