/* func_ov054_022614b4 @ 0x022614b4, 0x80 bytes, Thumb, module ov054
 * mwccarm 1.2/base -O4,s
 */

typedef struct Inner_808 {
    unsigned char pad_808[0x808];
    unsigned int id;
} Inner_808;

typedef struct TabEntry12 {
    unsigned int a;
    unsigned char pad_12[8];
} TabEntry12;

typedef struct ArgType {
    unsigned char pad_00[0x40];
    unsigned int unk_40;
    unsigned char pad_44[0x6c];
    void *unk_B0;
    unsigned char pad_B4[0x14];
    unsigned char unk_C8;
} ArgType;

extern int func_020e8840(void *);
extern void func_0206844c(unsigned int, unsigned char *, unsigned int);
extern void func_02068358(unsigned int);
extern void func_02068434(unsigned int);
extern void func_ov054_02261cc4(ArgType *, int);
extern void func_ov054_02261f44(ArgType *);
extern void func_02073044(int);
extern int func_020ec920(void);
extern TabEntry12 data_ov054_02262fac[];

void func_ov054_022614b4(ArgType *arg)
{
    unsigned int field_40;
    int res;
    field_40 = arg->unk_40;
    res = func_020e8840((char *) arg + 0xc8);
    if (res == 0) {
        unsigned char local;
        func_ov054_02261f44(arg);
        local = 0x37;
        func_0206844c(field_40, &local, data_ov054_02262fac[((Inner_808 *) arg->unk_B0)->id].a);
        func_02068358(field_40);
        func_02068434(field_40);
        func_ov054_02261cc4(arg, 0);
    } else {
        func_02073044(res);
        if (func_020ec920()) {
            func_02068358(field_40);
            func_02068434(field_40);
            func_ov054_02261cc4(arg, 0);
        }
    }
}
