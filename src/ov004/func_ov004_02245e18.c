/* func_ov004_02245e18 @ 0x02245e18, 0xc0 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_0203e334(void);
extern char data_021dc7a8[];
extern void *func_02098844(void *, int);
extern int func_02099a28(void *);
extern void func_0208e2ac(void *, int);
extern int func_020b4980(void *, void *, int);
extern int func_0209f150(void *, unsigned int);
extern int func_0208ffac(void);
extern void func_ov004_02245cf4(void *, int);
extern void func_0209e474(void *);

int func_ov004_02245e18(char *self)
{
    unsigned char i;
    unsigned char flag;
    char *g;
    void *entry;
    func_0203e334();
    g = data_021dc7a8;
    for (i = 0; i < 4; ++i) {
        entry = func_02098844(g + 0x14, i);
        if (entry && func_02099a28(entry)) {
            self[0x31c] = i;
            break;
        }
    }
    for (i = 0; i < 5; ++i) {
        func_0208e2ac(self + 0x9c + i * 0x80, i);
    }
    flag = 0x81;
    func_020b4980(self + 0x338, &flag, 0);
    if (!func_0209f150(g, 0)) {
        func_ov004_02245cf4(self, 0);
    } else if (func_0208ffac()) {
        func_ov004_02245cf4(self, 2);
    } else {
        func_ov004_02245cf4(self, 1);
    }
    self[0x31d] = 0;
    func_0209e474(self + 0x328);
    return 1;
}
