/* func_02047898 @ 0x02047898, 0x74 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0209fa30(const void *);
extern void func_0209e474(void *);
extern void MI_CpuCopy8(void *, const void *, int);
extern int func_0203fc78(unsigned char, void *, int);
extern void func_020b2f28(void);
extern void func_020b2f08(void);
extern void func_020b2ee8(void);
extern unsigned char data_020db764[];
void func_02047898(int a, int b, int c)
{
    char buf[20];
    int i;
    if (func_0209fa30((void *) (b + 0x173dd))) {
        return;
    }
    ((int *) buf)[0] = 0;
    ((int *) buf)[1] = 0;
    func_0209e474(buf);
    for (i = 0; i < 3; i++) {
        MI_CpuCopy8(buf, buf + 8, 8);
        switch (func_0203fc78(data_020db764[i], buf + 8, c)) {
            case 2:
            case 3:
                switch (i) {
                    case 0:
                        func_020b2f28();
                        break;
                    case 1:
                        func_020b2f08();
                        break;
                    case 2:
                        func_020b2ee8();
                        break;
                }
                break;
        }
    }
}
