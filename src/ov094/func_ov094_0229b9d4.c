/* func_ov094_0229b9d4 @ 0x0229b9d4, 0x130 bytes, Thumb, module ov094
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char data[0x20];
} TypeC;
typedef struct {
    unsigned char data[0x30];
} TypeB;
typedef struct {
    unsigned char data[0x6C];
} TypeA;

extern int func_02065ec0(int);
extern void func_02070c08(void *);
extern void func_02094fd4(void *);
extern void func_0208aecc(void *);
extern int func_02065f44(int);
extern void func_02065f38(int, void *);
extern void func_020b496c(int, void *);
extern void func_0207094c(void *, int);
extern void func_02051a78(void *, void *);
extern int func_02065f20(int);
extern void func_02065f2c(int, void *);
extern void func_02070be8(void *);
extern void func_0208aa48(int, void *);
extern void func_0208aeb8(void *);
extern void func_02094fbc(void *);
extern const unsigned short data_ov094_0229bdec[];

void func_ov094_0229b9d4(int p0, int p1, int p2)
{
    TypeC local_B;
    TypeB local_C;
    TypeB local_D;
    TypeA local_A;
    int r4, x, y;

    r4 = func_02065ec0(p2);
    func_02070c08(&local_A);
    func_02094fd4(&local_B);
    func_0208aecc(&local_C);
    func_0208aecc(&local_D);

    x = func_02065f44(p2);
    if (x == 0x11) {
        func_02065f38(p2, &local_B);
        func_020b496c(1, &local_B);
        func_0207094c(&local_A, 0x4b);
    } else if (x == 0) {
        func_02065f38(p2, &local_B);
        func_020b496c(1, &local_B);
        if (r4 == 4) {
            func_0207094c(&local_A, 0x4b);
        } else {
            func_0207094c(&local_A, 0x3d);
        }
    } else {
        func_0207094c(&local_A, data_ov094_0229bdec[x]);
    }

    func_02051a78(&local_D, &local_A);

    y = func_02065f20(p2);
    if (y != 0) {
        TypeA local_E;
        func_02070c08(&local_E);
        func_0207094c(&local_E, 0x43);
        func_020b496c(0, &local_E);
        func_02070be8(&local_E);
    } else {
        func_02065f2c(p2, &local_B);
        func_020b496c(0, &local_B);
    }

    func_0207094c(&local_A, 0x3c);
    func_02051a78(&local_C, &local_A);

    switch (r4) {
        case 1:
        case 4:
        case 7:
        case 8:
            func_0208aa48(p1, &local_C);
            break;
        default:
            func_0208aa48(p1, &local_D);
            break;
    }

    func_0208aeb8(&local_D);
    func_0208aeb8(&local_C);
    func_02094fbc(&local_B);
    func_02070be8(&local_A);
}
