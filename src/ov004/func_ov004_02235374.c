/* func_ov004_02235374 @ 0x02235374, 0xf8 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_ov004_022593a4, data_ov004_02255c30;
extern unsigned char *data_ov004_022594d4[], *data_ov004_022593ac, *data_ov004_022593b4, *data_ov004_022593b8;
extern int func_020e9898(void *);
extern void func_0205502c(void *);
extern int func_02055454(void *);
extern void func_0209d090(void *);
extern void func_0209d200(void *, void *);
extern void func_02004280(void *);
void func_ov004_02235374(unsigned char *self, int index)
{
    if (index >= data_ov004_022593a4 && index < data_ov004_02255c30) {
        unsigned char **slot = &data_ov004_022594d4[index];
        int i;
        for (i = 0; i < 4; ++i) {
            if (*(void **) (*slot + 0x54 + i * 4)) {
                func_020e9898(*(void **) (*slot + 0x54 + i * 4));
                *(void **) (*slot + 0x54 + i * 4) = 0;
            }
        }
        *(int *) (*slot + 0x160) = 0;
        func_0205502c(*slot + 0x64);
        func_02055454(*slot + 0x64);
        func_0209d090(*slot + 0x168);
        func_0209d200(self + 0x7f8, *slot + 0x166);
        switch (*(int *) (*slot + 0x15c)) {
            case 11:
                if (data_ov004_022593ac) {
                    func_02004280(data_ov004_022593ac + 0x1fc);
                    data_ov004_022593ac = 0;
                }
                break;
            case 36:
                if (data_ov004_022593b4) {
                    data_ov004_022593b4 = 0;
                }
                break;
            case 35:
                if (data_ov004_022593b8) {
                    data_ov004_022593b8 = 0;
                }
                break;
        }
        *(int *) (*slot + 0x15c) = -1;
    }
}
