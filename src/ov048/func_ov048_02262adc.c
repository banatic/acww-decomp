/* func_ov048_02262adc @ 0x02262adc, 0x48 bytes, Thumb, module ov048
 * mwccarm 1.2/base -O4,s
 */

extern int func_020a6ed0(void);
struct PtrStruct {
    int pad_00;
    int unk_04;
};
extern struct PtrStruct *func_020682e0(int);
extern void func_02068320(struct PtrStruct *);
struct UnkStruct_02262adc {
    int a;
    int b;
    int c;
};
extern struct UnkStruct_02262adc data_ov048_022639a4;
extern void func_02095ab0(struct UnkStruct_02262adc *, int, int);

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
