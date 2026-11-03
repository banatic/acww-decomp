/* gatekeeper_states_3: 4 functions, module ov048
 * mwccarm 1.2/base -O4,s
 * func_ov048_02262adc @ 0x02262adc, 0x48 bytes, Thumb
 * func_ov048_02262aac @ 0x02262aac, 0x2e bytes, Thumb
 * func_ov048_02262a94 @ 0x02262a94, 0x16 bytes, Thumb
 * func_ov048_02262a84 @ 0x02262a84, 0x10 bytes, Thumb
 */

struct PtrStruct {
    int pad_00;
    int unk_04;
};

struct UnkStruct_02262adc {
    int a;
    int b;
    int c;
};

extern int func_020a6ed0(void);
extern struct PtrStruct *func_020682e0(int);
extern void func_02068320(struct PtrStruct *);
extern struct UnkStruct_02262adc data_ov048_022639a4;
extern int func_02095ab0(struct UnkStruct_02262adc *, int, int);
extern int func_020984fc(void *arg0);
extern int func_0209615c(int);
extern void func_02099a38(int);
extern int func_020b5e10(void);
extern int func_020b6098(int a, int b);

int func_ov048_02262adc(void)
{
    struct PtrStruct *p;
    struct UnkStruct_02262adc local;
    int unused;
    int v;

    v = func_020a6ed0();
    p = func_020682e0(0);

    if (p->unk_04 == 0) {
        func_02068320(p);
        local.a = data_ov048_022639a4.a;
        local.b = data_ov048_022639a4.b;
        local.c = data_ov048_022639a4.c;
        func_02095ab0(&local, 0x35c, v);
        return 1;
    } else {
        return 0;
    }
}

int func_ov048_02262aac(void)
{
    int r5 = func_020a6ed0();
    int r4 = func_020984fc((void *) r5);
    if (func_0209615c(r5) == 0) {
        func_02099a38(r4);
        return 1;
    }
    return 0;
}

int func_ov048_02262a94(void)
{
    func_020b6098(func_020b5e10(), 1);
    return 1;
}

int func_ov048_02262a84(unsigned char *base)
{
    base[0xe71] = 0;
    return 1;
}
