/* func_ov119_0229aacc @ 0x0229aacc, 0x170 bytes, Thumb, module ov119
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0229aacc UnkStruct_0229aacc;
struct UnkStruct_0229aacc {
    unsigned char pad_00[0x64];
    int unk_64;
};

extern UnkStruct_0229aacc *data_020ccf94;

extern void func_020641c8(void *);
extern void func_020641b0(void *);
extern void func_02064210(int, void *);
extern void func_02094fd4(void *);
extern void func_02094fbc(void *);
extern int func_02095040(int);
extern void func_02095074(int, void *);
extern void *func_ov119_0229bb44(void *);
extern int func_02073d90(UnkStruct_0229aacc *);
extern void *func_020984fc(int);
extern int func_02099870(void *);
extern void func_020b496c(int, void *);
extern void func_0207094c(void *, int);
extern void func_020a8bb8(void *, void *);
extern void func_020a8c1c(void *);
extern void func_02070adc(void *, int, int, int, int, int, int);
extern void func_02070a04(void *, int, int);
extern void func_ov119_0229a8ec(void *, void *, int);
extern void func_0206fdd4(void *, int, int, int, int, int);

void func_ov119_0229aacc(unsigned char *self)
{
    int i;
    int n;
    int incA, incB;
    int j;
    UnkStruct_0229aacc *g;
    void *entry;
    int limit;
    void *objA, *objB;
    int tmp;
    int buf1[8];
    int buf2[8];

    incA = 0x1ce;
    incB = 0x14e;
    j = 0xc3;
    g = data_020ccf94;
    limit = g->unk_64;
    n = 0;
    func_020641c8(buf1);
    func_02094fd4(buf2);

    for (i = 0; i < 8; i++) {
        objA = func_ov119_0229bb44(self);
        objB = func_ov119_0229bb44(self);
        entry = 0;
        if (func_02073d90(g) != 0) {
            if (limit == n) {
                n++;
            }
            if (n < 4) {
                entry = func_020984fc(n);
                n++;
            }
        }
        if (entry != 0) {
            tmp = func_02099870(entry);
            func_02064210(func_02095040(tmp), buf1);
            func_020b496c(0, buf1);
            func_0207094c(objA, 0x66);
            func_02095074(tmp, buf2);
            func_020a8bb8(objB, buf2);
            func_ov119_0229a8ec(self, (unsigned short *) (self + 0xe0c) + j, 0x58);
            self[0xb2] |= 1 << i;
        } else {
            func_020a8c1c(objA);
            func_020a8c1c(objB);
            func_ov119_0229a8ec(self, (unsigned short *) (self + 0xe0c) + j, 0x10);
        }

        func_02070adc(objA, 4, incA, 0xa, 0xf, 0, 0);
        func_02070a04(objA, 0, 0);
        func_02070adc(objB, 4, incB, 8, 0xf, 0, 0);
        func_02070a04(objB, 0, 0);

        incA += 0x14;
        incB += 0x10;
        j += 0x40;
    }

    func_0206fdd4(self + 0xe0c, 5, 6, 0x17, 0x15, 5);
    func_02094fbc(buf2);
    func_020641b0(buf1);
}
