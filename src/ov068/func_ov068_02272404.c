/* func_ov068_02272404 @ 0x02272404, 0xa0 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02272404 {
    unsigned int unk_00;
    unsigned int unk_04;
    unsigned int unk_08;
};

extern int func_ov003_02220174(unsigned int);
extern int func_ov009_0226321c(int, struct UnkStruct_02272404 *, short *);
extern unsigned int func_020b5e10(void);
extern int func_020b6098(unsigned int, int);
extern unsigned int func_020b65c4(void);
extern unsigned int func_020b5ea0(unsigned int, unsigned int, struct UnkStruct_02272404 *, unsigned int, int, unsigned int,
                                  unsigned int);
extern void func_0203e328(void);

void func_ov068_02272404(char *self)
{
    short val;
    struct UnkStruct_02272404 s;
    int status;
    unsigned int a, b;
    int temp;

    if (*(unsigned short *) ((char *) self + 0x2d8) != 0) {
        (*(unsigned short *) ((char *) self + 0x2d8))--;
    }
    if (*(unsigned short *) ((char *) self + 0x2d8) != 0) {
        return;
    }

    status = func_ov003_02220174(0x5000);
    if (status == 0) {
        return;
    }

    if (func_ov009_0226321c(status, &s, &val) == 0) {
        return;
    }

    func_020b6098(func_020b5e10(), 9);

    s.unk_08 += 0x1000;

    a = func_020b5e10();
    b = func_020b65c4();
    temp = (short) (val + 0x8000);

    ((void) (func_020b5ea0(a, b, &s, 0x0f000000, temp, *(unsigned int *) ((char *) self + 0x2b8),
                           *(unsigned int *) ((char *) self + 0x2bc))),
     func_0203e328());
}
