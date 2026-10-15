/* func_020414e0 @ 0x020414e0, 0xc8 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0203e370(void);
extern int func_0203e37c(void);
extern int func_0203e364(void);
extern int func_0206e980(void);
extern int func_0204e414(void);
extern int func_0204df68(int, void *);
extern int func_0204e188(int, void *, int, int);
extern int func_020b5e10(void);
extern int func_020b5ee4(int, int);
extern int func_020b63f4(int, int, void *, int, int, int, int);
extern void func_02035c64(int, int, int);

struct UnkStruct_020414e0 {
    unsigned char unk_00;
    unsigned char _p1;
    unsigned char unk_02;
    unsigned char _p3;
    unsigned char unk_04;
    unsigned char _p5[3];
    int unk_08;
};

extern struct UnkStruct_020414e0 data_021c75a0;
extern int data_020db6e4;
extern int data_020db6e0;
extern int data_021c526c;
extern int data_021c758c;
extern int data_021c7590;

void func_020414e0(void *receiver)
{
    unsigned int local[4];
    int r0;

    if (func_0203e370() == 0) {
        if (func_0203e37c() == 0) {
            data_021c75a0.unk_00 = 0;
            data_021c75a0.unk_02 = 0;
        }
        return;
    }

    r0 = data_021c75a0.unk_08;
    data_020db6e4 = r0;
    data_020db6e0 = r0;

    if (func_0203e364() == 0) {
        return;
    }
    if (func_0206e980() != 0) {
        return;
    }

    r0 = func_0204e414();
    if (r0 == 0) {
        return;
    }

    if (data_021c75a0.unk_04 == 0xe) {
        r0 = func_0204df68(r0, local);
    } else {
        r0 = func_0204e188(r0, local, 0, 0);
    }
    if (r0 == 0) {
        return;
    }

    r0 = func_020b5e10();
    func_020b5ee4(r0, 0);
    r0 = func_020b5e10();
    func_020b63f4(r0, 0x31, local, 0x400000, 0, 2, 2);
    func_02035c64(data_021c526c + 0x2d0, data_021c758c, data_021c75a0.unk_04);
    data_021c75a0.unk_00 = 4;
    data_021c7590 = 1;
}
