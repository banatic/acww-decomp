/* func_ov048_02262d4c @ 0x02262d4c, 0x64 bytes, Thumb, module ov048
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020a13d0(void);
extern unsigned char data_021c75b8;
extern int func_02095ed0(int, void *);
extern void func_02095eec(int, int);
extern void func_02095ab0(unsigned int *, unsigned int, void *);
extern unsigned int data_ov048_02263998[3];

int func_ov048_02262d4c(void)
{
    unsigned int local[3];
    void *h;
    unsigned int ok;
    h = func_020a13d0();
    ok = (data_021c75b8 == 2) ? 1 : 0;
    if (ok > 0) {
        if (func_02095ed0(1, h) != 0) {
            func_02095eec(1, 4);
            local[0] = data_ov048_02263998[0];
            local[1] = data_ov048_02263998[1];
            local[2] = data_ov048_02263998[2];
            func_02095ab0(local, 0x35c, h);
            return 1;
        }
    }
    return 0;
}
