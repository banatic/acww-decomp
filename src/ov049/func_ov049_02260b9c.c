/* func_ov049_02260b9c @ 0x02260b9c, 0xc4 bytes, Thumb, module ov049
 * mwccarm 1.2/base -O4,s
 */

extern void *data_ov049_02263298;

struct UnkStruct_02260b9c {
    unsigned char op;
    unsigned short key;
    unsigned short val;
};

extern int func_0206fc6c(void);
extern int func_020984e8(void);
extern int func_02099640(int argument0);
extern int func_0209a850(int argument0);
extern int func_0202e9fc(void);
extern int func_0206fc8c(void);
extern int func_0209a034(int);
extern void func_0209a050(int);
extern int func_0204bcdc(unsigned short *);
extern int func_0204bc64(unsigned short *);
extern int func_02015330(void *, unsigned short *, int, int, int);
extern void *func_0209b0f0(void *record);
extern void func_0209bb90(void *, int);
extern void func_0206844c(void *, struct UnkStruct_02260b9c *, void *);

struct UnkStruct_02260b9c_2 {
    unsigned char pad_00[0x40];
    void *unk_40;
};

void func_ov049_02260b9c(struct UnkStruct_02260b9c_2 *ctx)
{
    unsigned int status;
    int something;
    int r5;
    unsigned int eq;
    struct UnkStruct_02260b9c local;
    void *r6 = ctx->unk_40;
    void *r7 = data_ov049_02263298;
    status = 0x30;
    if (func_0206fc6c() == 0) {
        goto end;
    }

    something = func_0209a850((int) func_02099640(func_020984e8()));

    if (func_0202e9fc() == 0) {
        goto end;
    }

    r5 = func_0206fc8c();
    local.key = func_0209a034(r5);

    if (r5 >= 0) {
        func_0209a050(r5);
    }

    if (func_0204bcdc(&local.key)) {
        local.val = 0xfff1;
        eq = (func_0204bc64(&local.key) == func_0204bc64(&local.val));
    } else {
        eq = (local.key == 0xfff1);
    }

    if (eq != 0) {
        goto end;
    }

    func_02015330(ctx, &local.key, 2, 5, 0);
    status = 0x2f;
    {
        void *retainedAddress;
        retainedAddress = func_0209b0f0((void *) something);
        func_0209bb90(retainedAddress, 1);
    }

end:
    local.op = (unsigned char) status;
    func_0206844c(r6, &local, r7);
}
