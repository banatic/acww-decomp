/* func_ov068_022765b0 @ 0x022765b0, 0x100 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int unk_00, w1;
} UnkStruct_022765b0;

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
