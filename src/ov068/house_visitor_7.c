/* house_visitor_7: 4 functions, module ov068
 * mwccarm 1.2/base -O4,s
 * func_ov068_022766e8 @ 0x022766e8, 0x3c bytes, Thumb
 * func_ov068_022766b0 @ 0x022766b0, 0x38 bytes, Thumb
 * func_ov068_022765b0 @ 0x022765b0, 0x100 bytes, Thumb
 * func_ov068_02276598 @ 0x02276598, 0x18 bytes, Thumb
 */

struct UnkStruct_022766e8 {
    void *unk_00;
    char pad_04[0x898];
    void *unk_89C;
};

typedef struct {
    int unk_00, w1;
} UnkStruct_022765b0;

extern unsigned int func_020edf70(unsigned int size);
extern void *func_0202e8e4(void *argument0);
extern void *func_0202decc(void *addr);
extern int data_ov068_02278140;
extern int data_ov068_022780b0;
extern int func_0202e364(void *p);
extern void func_0201c280(void *a, void *b);
extern void func_ov068_022761d0(void *a, void *b);
extern void *data_ov068_022788ec;
extern int func_0202e1fc(void *self);
extern UnkStruct_022765b0 data_ov068_02278064;
extern void func_ov068_022764b4(void *receiver);
extern void func_02013c0c(void *p);
extern unsigned char func_020b65b8(void);
extern int func_020b6674(int code);
extern int func_ov068_02275c78(void *self, int flag);
extern int func_ov068_0227629c(void *receiver);
extern void func_020b23d4(void);
extern int func_020644cc(int);
extern void func_0205ba64(void *buf);
extern int func_0205b91c(void *buf, void *p);
extern void func_0205ba60(void *buf);
extern int func_0201b790(void *argument0);

struct UnkStruct_022766e8 *func_ov068_022766e8(void)
{
    struct UnkStruct_022766e8 *p = (struct UnkStruct_022766e8 *) func_020edf70(0xa7c);
    if (p) {
        func_0202e8e4(p);
        p->unk_00 = &data_ov068_02278140;
        func_0202decc(&p->unk_89C);
        p->unk_89C = &data_ov068_022780b0;
    }
    return p;
}

int func_ov068_022766b0(void *self)
{
    if (func_0202e364(self) == 0) {
        return 0;
    }
    data_ov068_022788ec = self;
    func_0201c280(self, (char *) self + 0x89c);
    func_ov068_022761d0((char *) self + 0x89c, self);
    return 1;
}

int func_ov068_022765b0(void *self)
{
    char buf[0x18];
    int v0, v1;

    if (!func_0202e1fc(self)) {
        return 0;
    }

    *(UnkStruct_022765b0 *) ((char *) self + 0xa44) = data_ov068_02278064;

    func_ov068_022764b4(self);
    func_02013c0c((char *) self + 0x558);

    *(short *) ((char *) self + 0xa5e) = -1;
    *(char *) ((char *) self + 0xa5c) = 3;
    *(unsigned char *) ((char *) self + 0xa60) = 0xb0;

    if (func_020b6674(func_020b65b8()) != 0) {
        func_ov068_02275c78(self, 0);
    } else {
        if (func_ov068_0227629c((char *) self + 0x89c) != 0) {
            func_020b23d4();
            v0 = func_020644cc(0x14);
            *(short *) ((char *) self + 0xa5e) = (short) ((v0 + 0x28) * 0x3c);
            v1 = func_020644cc(4);
            *(char *) ((char *) self + 0xa5c) = (char) (v1 + 2);
            func_0205ba64(buf);
            v0 = func_0205b91c(buf, (char *) self + 0xa4c);
            *(int *) ((char *) self + 0xa54) = v0;
            func_ov068_02275c78(self, 6);
            func_0205ba60(buf);
        } else {
            v0 = func_020644cc(0x28);
            *(short *) ((char *) self + 0xa5e) = (short) ((v0 + 0x3c) * 0x3c);
            v1 = func_020644cc(4);
            *(char *) ((char *) self + 0xa5c) = (char) (v1 + 7);
            func_ov068_02275c78(self, 0);
        }
    }
    return 1;
}

int func_ov068_02276598(void *argument0)
{
    int result;

    if (func_0201b790(argument0) != 0) {
        result = 1;
    } else {
        result = 0;
    }

    return result;
}
