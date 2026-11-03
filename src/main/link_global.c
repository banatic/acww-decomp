/* link_global: 14 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020a6ff0 @ 0x020a6ff0, 0x74 bytes, Thumb
 * func_020a6f88 @ 0x020a6f88, 0x68 bytes, Thumb
 * func_020a6f74 @ 0x020a6f74, 0x14 bytes, Thumb
 * func_020a6f64 @ 0x020a6f64, 0x10 bytes, Thumb
 * func_020a6f54 @ 0x020a6f54, 0x10 bytes, Thumb
 * func_020a6f44 @ 0x020a6f44, 0x10 bytes, Thumb
 * func_020a6f34 @ 0x020a6f34, 0x10 bytes, Thumb
 * func_020a6f20 @ 0x020a6f20, 0x14 bytes, Thumb
 * func_020a6f10 @ 0x020a6f10, 0x10 bytes, Thumb
 * func_020a6f00 @ 0x020a6f00, 0x10 bytes, Thumb
 * func_020a6ef0 @ 0x020a6ef0, 0x10 bytes, Thumb
 * func_020a6ee0 @ 0x020a6ee0, 0x10 bytes, Thumb
 * func_020a6ed0 @ 0x020a6ed0, 0x10 bytes, Thumb
 * func_020a6ec0 @ 0x020a6ec0, 0x10 bytes, Thumb
 */

typedef struct UnkStruct_020a6f88 {
    char pad_00[0x64];
    struct UnkStruct_020a6f88 *unk_64;
} UnkStruct_020a6f88;

extern unsigned char data_021f4320[12];
extern void func_020a7738(const unsigned char *src, unsigned char *b0, unsigned char *b1, unsigned char *b2);
extern UnkStruct_020a6f88 *data_020ccf94;
extern int func_02073918(UnkStruct_020a6f88 *obj, int arg);
extern int func_020b5e70(void);
extern void func_020a7408(UnkStruct_020a6f88 *obj, int arg);
extern void func_020a7948(void *p);
extern void func_020a7940(void *p, int arg);
extern void func_02073820(UnkStruct_020a6f88 *obj);
extern void func_020737f0(UnkStruct_020a6f88 *obj, void *p, int arg);
extern void func_02073770(UnkStruct_020a6f88 *obj, int arg1, int arg2);
extern void func_020a7944(void *p);
extern void func_020a617c(void *arg0, int arg1, int arg2);
extern int func_020a6170(void *, int);
extern void func_020a5c20(void *dst, const void *src);
extern unsigned short func_020a5c18(void *ptr);
extern void func_020a5bf8(void *param1, void *param2);
extern void func_020a5bc4(void *a, void *b, void *c);
extern void func_020a5be0(void *dst, const void *src);
extern int func_020a5bd8(void *);
extern void func_020a5728(void *dst, const void *src);
extern unsigned long func_020a5720(void *ptr);
extern unsigned long func_020a5c28(void *ptr);
extern void func_020a5c30(void *ptr, int arg);

int func_020a6ff0(int key)
{
    int idx_zero = 4;
    int idx_nonzero = 4;
    unsigned int i;
    unsigned char *p = data_021f4320;
    unsigned char b[3];

    for (i = 0; i < 4; i++) {
        func_020a7738(p, &b[0], &b[1], &b[2]);
        if (b[0] == key && b[1] != 0) {
            if (b[2] != 0) {
                idx_zero = (int) i;
            } else {
                idx_nonzero = (int) i;
            }
        }
        p += 3;
    }

    if (idx_zero == 4 && idx_nonzero == 4) {
        return 4;
    }
    if (idx_zero != 4 && idx_nonzero != 4) {
        return idx_nonzero;
    }
    if (idx_zero != 4) {
        return idx_zero;
    }
    return idx_nonzero;
}

void func_020a6f88(void)
{
    UnkStruct_020a6f88 *obj;
    int local[2];

    obj = data_020ccf94;
    if (func_02073918(obj, 0)) {
        obj = obj->unk_64;
        func_020a7408(obj, func_020b5e70());
    } else {
        func_020a7948(&local);
        func_020a7940(&local, func_020b5e70());
        obj = data_020ccf94;
        func_02073820(obj);
        func_020737f0(obj, &local, 1);
        func_02073770(obj, 8, 0);
        func_020a7944(&local);
    }
}

void func_020a6f74(int arg0, int arg1)
{
    func_020a617c((void *) data_021f4320, arg0, arg1);
}

int func_020a6f64(int arg)
{
    return func_020a6170((void *) data_021f4320, arg);
}

void func_020a6f54(void *src)
{
    func_020a5c20((void *) data_021f4320, src);
}

unsigned short func_020a6f44(void)
{
    return func_020a5c18(((unsigned char *) data_021f4320));
}

void func_020a6f34(void *param1)
{
    func_020a5bf8((void *) data_021f4320, param1);
}

void func_020a6f20(void *a, void *b)
{
    ((void (*)(void *, void *, void *)) &func_020a5bc4)(((char *) data_021f4320), a, b);
}

void func_020a6f10(void *arg0)
{
    func_020a5be0((void *) data_021f4320, arg0);
}

int func_020a6f00(void)
{
    return func_020a5bd8((void *) data_021f4320);
}

void func_020a6ef0(void *src)
{
    func_020a5728((void *) data_021f4320, src);
}

unsigned long func_020a6ee0(void)
{
    return func_020a5720(((char *) data_021f4320));
}

unsigned long func_020a6ed0(void)
{
    return func_020a5c28((void *) data_021f4320);
}

void func_020a6ec0(int arg)
{
    func_020a5c30((void *) data_021f4320, arg);
}
