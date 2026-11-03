/* tune_editor_states_5: 3 functions, module ov143
 * mwccarm 1.2/base -O4,s
 * func_ov143_0229ae64 @ 0x0229ae64, 0x1e bytes, Thumb
 * func_ov143_0229ae48 @ 0x0229ae48, 0x1a bytes, Thumb
 * func_ov143_0229adc4 @ 0x0229adc4, 0x84 bytes, Thumb
 */

struct UnkStruct_0229ae64 {
    char pad_00[0x8c];
    char flag;
};

extern void func_ov143_0229a98c(struct UnkStruct_0229ae64 *this);
extern unsigned char *func_ov002_022080a0(struct UnkStruct_0229ae64 *this, unsigned char arg1);
extern int func_020ee45c(int);
extern void func_ov092_0229929c(int);
extern void func_ov143_0229a964(int);
extern int func_0206fe54(void);
extern void func_ov002_02209eb8(char *p);
extern int func_ov143_02299650(void *p, int a);
extern int func_ov002_02207f60(void *p);
extern void func_ov002_0220ad18(char *p, int a);
extern void func_02088df8(int a, void *b, int c, void *d, int e, int f, int g, int h, int i, int j, int k, int l);
extern void func_ov143_02299800(void *p, int a, void *b);
extern int data_ov143_0229afc0[];

int func_ov143_0229ae64(struct UnkStruct_0229ae64 *this)
{
    func_ov143_0229a98c(this);
    this->flag = 0;
    func_ov002_022080a0(this, 0);
    return 1;
}

int func_ov143_0229ae48(int arg)
{
    func_ov092_0229929c(func_020ee45c(arg));
    func_ov143_0229a964(arg);
    return 1;
}

int func_ov143_0229adc4(void *obj)
{
    int p;
    int base;
    if (func_0206fe54() != 0) {
        func_ov002_02209eb8((char *) obj + 0xac);
    }
    if (func_ov143_02299650(obj, 1) == 0) {
        return 0;
    }
    p = func_ov002_02207f60(obj);
    func_ov002_0220ad18((char *) obj + 0x110, p);
    base = *(int *) ((char *) obj + 0x94) + 0x60;
    func_02088df8(1, data_ov143_0229afc0, 0x80, (void *) base, -1, 2, 0x1000, 0x1000, 0, -1, 0, 0);
    func_ov143_02299800(obj, 0x80, (void *) base);
    return 1;
}
