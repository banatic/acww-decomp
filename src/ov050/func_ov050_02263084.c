/* func_ov050_02263084 @ 0x02263084, 0x88 bytes, Thumb, module ov050
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020984e8(void);
extern void *func_02099640(void);
extern void func_0209ad9c(void *a, int b);
extern void func_0209b4d4(void);
extern void func_02099fe8(void);
extern int func_ov050_02263394(void *a, void *b);
extern int func_02099020(void *a, int b);
extern void *func_02099870(void *a);
extern int func_0207a5d0(void *a, void *b);
extern unsigned short *func_020992e4(void);

typedef struct {
    unsigned char pad_00[0xb4];
    void *ptr;
} FieldHolder;

extern unsigned char data_021e5a2c[];

void func_ov050_02263084(void *p0, void *p1)
{
    void *r6;

    r6 = func_020984e8();
    func_0209ad9c(func_02099640(), 0);
    func_0209b4d4();
    func_02099fe8();

    if (func_ov050_02263394(p0, p1) != 0) {
        return;
    }

    if (!(func_02099020(r6, 0xa) != 0 && func_0207a5d0((void *) data_021e5a2c, func_02099870(r6)) != 0)) {
        if (*((unsigned char *) (((FieldHolder *) p0)->ptr) + 0x73e) != 0) {
            ((unsigned char *) p1)[4] = 0x13;
        } else {
            ((unsigned char *) p1)[4] = 0x14;
        }
        return;
    }

    func_020984e8();
    if (*(unsigned short *) func_020992e4() == 0) {
        ((unsigned char *) p1)[4] = 0x15;
    } else {
        ((unsigned char *) p1)[4] = 0x16;
    }
}
