/* func_ov003_0220d9b8 @ 0x0220d9b8, 0xf4 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_02010f5c(void *self);
extern int func_0203f7d0(void *a, void *b);
extern void func_020110c4(unsigned short *dest, void *self);
extern int func_0200f328(void *self, int code);
extern void func_0200fa6c(unsigned int *dest, void *self);
extern unsigned int func_020912d4(unsigned int kind, void *src, void *dst, unsigned int flag);
extern void func_02091278(unsigned int kind, void *src, void *dst, unsigned int flag);
extern unsigned char data_ov003_02260540;
extern unsigned int data_ov003_02260558[3];

typedef struct UnkStruct_0220d9b8 UnkStruct_0220d9b8;
struct UnkStruct_0220d9b8 {
    char pad_00[0x8e];
    unsigned char unk_8E;
    char pad_8F[0x62c - 0x8f];
    unsigned int unk_62C;
    unsigned int unk_630;
    unsigned int unk_634;
    char pad_638[0x7d4 - 0x638];
    unsigned int unk_7D4;
    unsigned char unk_7D8;
};

void func_ov003_0220d9b8(UnkStruct_0220d9b8 *self)
{
    unsigned short v1;
    unsigned short v2;
    unsigned int buf[3];
    unsigned int out[3];
    unsigned int *pf;
    unsigned char *pb;
    unsigned int t0, t1, t2;
    unsigned int f;

    func_02010f5c(self);
    pf = &self->unk_7D4;
    pb = (unsigned char *) pf + 4;

    t2 = self->unk_634;
    t1 = self->unk_630;
    t0 = self->unk_62C;
    buf[0] = t0;
    buf[1] = t1;
    buf[2] = t2;

    func_0203f7d0(buf, buf);

    f = self->unk_7D4;
    if (f == -1) {
        *pb = *pb + 1;
        if ((int) *pb <= 9) {
            return;
        }
        if (*pb == 10) {
            func_020110c4(&v1, self);
            if (v1 == 0x137f) {
                func_0200f328(self, 0x85a);
            } else {
                func_0200f328(self, 0x859);
            }
            func_0200fa6c(out, self);
            data_ov003_02260540 = 1;
            data_ov003_02260558[0] = out[0];
            data_ov003_02260558[1] = out[1];
            data_ov003_02260558[2] = out[2];
        }
        func_020110c4(&v2, self);
        if (v2 == 0x137f) {
            *pf = func_020912d4(0x35, buf, &self->unk_8E, 0);
        } else {
            *pf = func_020912d4(0x36, buf, &self->unk_8E, 0);
        }
        return;
    } else {
        func_02091278(f, buf, &self->unk_8E, 0);
    }
}
