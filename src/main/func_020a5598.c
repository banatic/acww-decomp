/* func_020a5598 @ 0x020a5598, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02041a9c(void);
extern void func_02074904(int);
extern void func_020a6c08(void);
extern void func_02046600(void);
extern void func_0203de64(void);
extern void func_0202f144(int, int);

extern unsigned char data_021f42f0;

void func_020a5598(int r0, int r1)
{
    int r5 = r0;
    int r4 = r1;
    if (r4 == 2) {
        data_021f42f0 = 0;
        if (*(unsigned short *) (r5 + 0xc) != 6) {
            func_02041a9c();
        }
        func_02074904(0);
        func_020a6c08();
        func_02046600();
        func_0203de64();
    }
    func_0202f144(r5, r4);
}
