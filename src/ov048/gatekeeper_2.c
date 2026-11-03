/* gatekeeper_2: 6 functions, module ov048
 * mwccarm 1.2/base -O4,s
 * func_ov048_0226384c @ 0x0226384c, 0x118 bytes, Thumb
 * func_ov048_022637d4 @ 0x022637d4, 0x78 bytes, Thumb
 * func_ov048_022636c8 @ 0x022636c8, 0x10c bytes, Thumb
 * func_ov048_0226369c @ 0x0226369c, 0x2c bytes, Thumb
 * func_ov048_02263690 @ 0x02263690, 0xc bytes, Thumb
 * func_ov048_02263684 @ 0x02263684, 0xc bytes, Thumb
 */

typedef struct {
    char pad_00[0x8e];
    short unk_8E;
    char pad_90[4];
    short unk_94;
    char pad_96[0x4e8 - 0x96];
    unsigned int unk_4E8;
    char pad_4EC[0x658 - 0x4ec];
    char unk_658;
    char pad_659[0xe6c - 0x659];
    short unk_E6C;
} UnkStruct_022636c8;

extern void *func_020edf70(unsigned int);
extern void *func_0203f130(void *arg0);
extern void *func_0205467c(void *);
extern void func_0201b394(void *);
extern void *func_0201a430(void *);
extern int func_020169a8(void *);
extern int func_0201b324(void *);
extern void func_0201af14(void *);
extern void func_0201b370(void *);
extern void func_0201adec(void *);
extern void *func_0201a7ec(void *);
extern void func_0201a794(void *);
extern void *func_02032c64(void *);
extern void *func_02089c88(void *);
extern void *func_020f55cc(void *);
extern void func_02013c2c(void *);
extern void *func_02019eb0(void *);
extern void func_0201489c(void *);
extern void *func_02082f60(void *);
extern void *func_ov048_02262738(void *);
extern char data_020d8c64;
extern char data_020da088;
extern char data_ov048_02264298;
extern int func_0202edc8(void *ptr);
extern void func_0201c280(void *a, void *b);
extern void func_ov048_02262680(void *a, void *b);
extern void func_0201c3f4(void *a, int b);
extern void func_0201b388(void *a, int b);
extern void func_0201b38c(void *a, int b);
extern int func_020b65c4(void);
extern int func_0202ec58(void *arg0);
extern int func_02073d90(int);
extern int func_0201c0e0(void *);
extern void func_ov048_022635f4(void *, int);
extern int func_0208602c(void);
extern int func_020860cc(int);
extern int func_02087e84(int);
extern int func_02087e78(int);
extern void func_02087e8c(int);
extern void func_0203e334(void);
extern void func_ov048_02262678(void *, int);
extern int data_020ccf94;
extern int func_0202ec14(void *parameter0);
extern void func_0203e328(void);
extern int data_ov048_02263d24;
extern unsigned int data_ov048_02263d28;

void *func_ov048_0226384c(void)
{
    char *obj;
    obj = func_020edf70(0x0e74);
    if (obj == 0) {
        goto done;
    }
    func_0203f130((void *) obj);
    *(void **) obj = (void *) &data_020d8c64;
    *(unsigned short *) (obj + 0xea) = 0xfff1;
    func_0205467c(obj + 0xec);
    func_0201b394(obj + 0x2a0);
    func_0201a430(obj + 0x2ac);
    func_020169a8(obj + 0x334);
    func_0201b324(obj + 0x350);
    func_0201af14(obj + 0x3a8);
    func_0201b370(obj + 0x3aa);
    func_0201adec(obj + 0x3b0);
    func_0201a7ec(obj + 0x418);
    func_0201a794(obj + 0x420);
    func_02032c64(obj + 0x49c);
    func_02089c88(obj + 0x4cc);
    func_020f55cc(obj + 0x514);
    func_02013c2c(obj + 0x558);
    func_02019eb0(obj + 0x564);
    func_0201489c(obj + 0x618);
    *(void **) obj = (void *) &data_020da088;
    func_02082f60(obj + 0x640);
    *(void **) obj = (void *) &data_ov048_02264298;
    func_ov048_02262738(obj + 0x658);
done:
    return obj;
}

int func_ov048_022637d4(void *arg)
{
    if (func_0202edc8(arg) == 0) {
        return 0;
    }

    func_0201c280(arg, (char *) arg + 0x658);
    func_ov048_02262680((char *) arg + 0x658, arg);
    func_0201c3f4(arg, 0x100);
    func_0201b388((char *) arg + 0x2a0, 0xd9);
    func_0201b38c((char *) arg + 0x2a0, 0xd8);

    if (func_020b65c4() != 0xb) {
        *((char *) arg + 0x563) = 1;
    }

    if (func_020b65c4() == 0xc) {
        *((char *) arg + 0x510) = 0;
    }

    return 1;
}

int func_ov048_022636c8(UnkStruct_022636c8 *self)
{
    if (func_0202ec58((void *) self) == 0) {
        return 0;
    }
    self->unk_E6C = self->unk_8E;
    self->unk_4E8 |= 2;
    if (func_02073d90(data_020ccf94) != 0 && func_020b65c4() == 0xb) {
        if (func_0201c0e0(self) != 0) {
            func_ov048_022635f4(self, 1);
        } else {
            func_ov048_022635f4(self, 0xf);
        }
        return 1;
    } else {
        int r4;
        r4 = func_020860cc((int) func_0208602c());
        if (func_02087e84(r4) == 1 || func_02087e84(r4) == 2) {
            if (func_02087e84(r4) == 1) {
                func_ov048_02262678(&self->unk_658, 6);
            } else {
                func_ov048_02262678(&self->unk_658, 7);
            }
            func_ov048_022635f4(self, 0);
            self->unk_8E = (short) func_02087e78(r4);
            self->unk_94 = (short) func_02087e78(r4);
            func_02087e8c(r4);
        } else {
            if (func_020b65c4() == 0xd) {
                func_0203e334();
                func_ov048_022635f4(self, 9);
            } else if (func_020b65c4() == 0xe) {
                func_0203e334();
                func_ov048_022635f4(self, 0xb);
            } else {
                func_ov048_022635f4(self, 1);
            }
        }
        return 1;
    }
}

int func_ov048_0226369c(void *arg0)
{
    if (func_0202ec14((void *) arg0) == 0) {
        return 0;
    }
    if (func_020b65c4() == 0xd || func_020b65c4() == 0xe) {
        func_0203e328();
    }
    return 1;
}

int func_ov048_02263690(void)
{
    return data_ov048_02263d24;
}

unsigned int func_ov048_02263684(void)
{
    return data_ov048_02263d28;
}
