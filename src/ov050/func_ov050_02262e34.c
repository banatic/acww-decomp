/* func_ov050_02262e34 @ 0x02262e34, 0x5c bytes, Thumb, module ov050
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov050_02263394(void *p0, void *p1);
extern int func_020984e8(void);
extern int func_02099640(int a);
extern int func_0209ad9c(int a, int b);
extern int func_0209b4d4(void *object);
extern int func_0209bba0(int a);

typedef struct {
    unsigned char pad_00[0xb4];
    unsigned char *array;
} P0Struct;
typedef struct {
    unsigned char pad_00[4];
    unsigned char mode;
} P1Struct;

void func_ov050_02262e34(P0Struct *p0, P1Struct *p1)
{
    int r;
    if (func_ov050_02263394(p0, p1) != 0) {
        return;
    }
    r = func_020984e8();
    r = func_02099640(r);
    r = func_0209ad9c(r, 0);
    r = func_0209b4d4((void *) r);
    r = func_0209bba0(r);
    if (r == 1) {
        p1->mode = 0x33;
        return;
    }
    if (p0->array[0x73e] == 0) {
        p1->mode = 0x32;
        p0->array[0x73e] = 1;
        return;
    }
    p1->mode = 0x10;
}
