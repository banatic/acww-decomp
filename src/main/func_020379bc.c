/* func_020379bc @ 0x020379bc, 0x84 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b65c4(void);
extern void func_0204e938(void *);
extern void func_02037a40(unsigned char *);
extern void func_0205cacc(unsigned int, int);
extern void func_02037928(unsigned char *);
extern void func_02037858(unsigned char *);
extern unsigned char data_020c9fd4[];

extern unsigned char data_021e9aac[];

int func_020379bc(unsigned char *p, int param1)
{
    unsigned int idx;
    unsigned char val;

    idx = func_020b65c4();
    if (idx == 0x2c) {
        func_0204e938((void *) data_021e9aac);
    }

    func_02037a40(p);

    p[0x618] = (unsigned char) param1;

    idx = func_020b65c4();

    val = (unsigned char) (idx < 0x33u ? data_020c9fd4[idx] : 0xac);

    *(volatile unsigned int *) (p + 0x61c) = val << 10;
    func_0205cacc(*(volatile unsigned int *) (p + 0x61c), 0);

    if (param1 != 0 || idx == 0xb || idx == 0x2f || (unsigned char) (idx + 0xf4) <= 2) {
        func_02037928(p);
    }
    if (param1 != 0) {
        func_02037858(p);
    }

    return 1;
}
