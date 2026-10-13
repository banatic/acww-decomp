/* func_02086d24 @ 0x02086d24, 0x18c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020951bc(void *);
extern int func_02003704(void *);
extern void func_0209f100(void *, int);
extern int func_0209f150(void *, int);
extern void func_02094fd4(void *);
extern void func_02095074(void *, void *);
extern void func_02003618(void *, void *);
extern void func_0203d7b0(int, int);
extern void func_0203d79c(int, int);
extern void func_0203d7c4(int, void *);
extern void func_020b5630(void *);
extern void func_020b4508(void *, int, int);
extern void func_020b45d0(void *, int, int, int, int, int);
extern void func_020b5618(void *);
extern int func_0204bcdc(unsigned short *);
extern int func_0204bc64(unsigned short *);
extern void func_02062f90(void *, unsigned short *);
extern void func_02062f4c(void *);
extern int func_020644cc(int);
extern void func_02077f14(int, int);
extern void func_02094fbc(void *);
extern char data_021dc7a8[];
extern int data_020e1fbc[];

typedef struct {
    char pad_00[0x1e];
    unsigned short unk_1E;
    char pad_20[0x1e];
    unsigned short unk_3E;
    int unk_40;
    unsigned char unk_44;
    unsigned char unk_45;
    unsigned char unk_46;
    unsigned char unk_47;
} UnkStruct_02086d24;

void func_02086d24(UnkStruct_02086d24 *self)
{
    unsigned short tmp;
    int bufA[0x8];
    int bufB[0x10];
    int bufC[0xa];
    int ok;
    int k;

    if (func_020951bc(self) == 0) {
        if (func_02003704(&self->unk_1E) == 0) {
            func_0209f100(data_021dc7a8, 0xf);
            return;
        }
    }
    if (self->unk_47 != 1 && self->unk_47 != 2 && self->unk_47 != 3) {
        return;
    }
    if (func_0209f150(data_021dc7a8, 0xf) == 0) {
        return;
    }

    func_02094fd4(bufA);
    if (func_020951bc(self) != 0) {
        func_02095074(self, bufA);
    } else {
        func_02003618(&self->unk_1E, bufA);
    }

    if ((unsigned char) (self->unk_47 + 0xff) <= 1) {
        func_0203d7b0(0, self->unk_45);
        func_0203d79c(1, self->unk_44);
        func_0203d7c4(4, bufA);
        if (self->unk_40 > 0) {
            func_020b5630(bufB);
            if (self->unk_47 == 1) {
                func_020b4508(bufB, self->unk_40, 1);
            } else {
                func_020b45d0(bufB, self->unk_40 >> 12, 3, 0, 0, 0);
            }
            func_0203d7c4(3, bufB);
            func_020b5618(bufB);
        }
        if (func_0204bcdc(&self->unk_3E) != 0) {
            tmp = 0xfff1;
            if (func_0204bc64(&self->unk_3E) == func_0204bc64(&tmp)) {
                ok = 1;
            } else {
                ok = 0;
            }
        } else {
            if (self->unk_3E == 0xfff1) {
                ok = 1;
            } else {
                ok = 0;
            }
        }
        if (ok == 0) {
            func_02062f90(bufC, &self->unk_3E);
            func_0203d7c4(2, bufC);
            func_02062f4c(bufC);
        }
    } else {
        func_0203d7c4(0, bufA);
    }

    if ((unsigned char) (self->unk_47 + 0xff) <= 1) {
        k = func_020644cc(3);
    } else {
        k = func_020644cc(2);
    }
    func_02077f14(k, data_020e1fbc[self->unk_47]);
    func_0209f100(data_021dc7a8, 0xf);
    func_02094fbc(bufA);
}
