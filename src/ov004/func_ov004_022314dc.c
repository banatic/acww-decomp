/* func_ov004_022314dc @ 0x022314dc, 0xb4 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern char data_ov004_022558e8, data_ov004_022558d8, data_ov004_022558e0;
extern void func_ov004_02231454(void *, void *, int);
extern int func_020b65c4(void);
extern void func_ov004_0223121c(void *, int);
extern void func_02068bbc(void *);
extern void func_02068bb0(void *);

void func_ov004_022314dc(char *self)
{
    char *p = *(char **) (self + 0x2d0);
    switch (*(unsigned char *) (self + 0x2ae)) {
        case 0x1b:
            func_ov004_02231454(self, &data_ov004_022558e8, -1);
            break;
        case 0xe:
        case 0x1f:
            if (func_020b65c4() == 6) {
                func_ov004_02231454(self, &data_ov004_022558d8, 3);
            } else {
                func_ov004_02231454(self, &data_ov004_022558e0, 2);
            }
            break;
        case 0xf:
            *(int *) (p + 0x14) = 1;
            func_ov004_0223121c(self, 0xd);
            break;
        case 0x20:
            func_02068bbc(p + 0x1a2c);
            break;
        case 0x2a:
        case 0x2b:
        case 0x2c:
            func_02068bb0(p + 0x1a2c);
            break;
    }
}
