/* func_ov054_02261a00 @ 0x02261a00, 0x94 bytes, Thumb, module ov054
 * mwccarm 1.2/base -O4,s
 */

struct PType {
    char pad_00[0x40];
    void *unk_40;
    char pad_44[0x6c];
    int *unk_B0;
};
struct DataElem {
    int a;
    int b;
    int c;
};
struct LocalInfo {
    unsigned char flag;
    char pad_01[3];
    int data[2];
};
extern struct DataElem data_ov054_02262fac[];
extern int func_0206fc6c(void);
extern void func_0206f80c(void *);
extern void func_02015fb0(void *, int, int, int, int, int);
extern void func_02015ed0(void *, int, int);
extern void func_02015ea0(void *, int, int);
extern void func_0206f910(void);
extern void func_ov054_02261cc4(void *, int);
extern void func_0206844c(void *, void *, int);
void func_ov054_02261a00(struct PType *p)
{
    void *saved;
    unsigned char val;
    unsigned char flag;
    unsigned char b7;
    unsigned char b8;
    int local_c;
    struct LocalInfo info;
    saved = p->unk_40;
    local_c = data_ov054_02262fac[p->unk_B0[0x202]].a;
    if (func_0206fc6c() != 0) {
        flag = 12;
        info.data[0] = 0;
        info.data[1] = 0;
        func_0206f80c(info.data);
        val = ((unsigned char *) (&info.data[1]))[0];
        b7 = ((unsigned char *) (&info.data[0]))[3];
        b8 = val;
        func_02015fb0(p, ((unsigned char *) (&info.data[1]))[1] + 0x7d0, 1, 4, 0, 0);
        func_02015ed0(p, b8, 2);
        func_02015ea0(p, b7, 3);
    } else {
        flag = 14;
        func_0206f910();
    }
    func_ov054_02261cc4(p, 0);
    info.flag = flag;
    func_0206844c(saved, &info, local_c);
}
