/* func_020ecde8 @ 0x020ecde8, 0x6c bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

extern unsigned char data_021fbef8;
extern unsigned short data_021fbefc;
extern void DWC_ProcessInet(void);
extern void func_ov065_02278000(void);
extern int func_ov065_0227f700(void);
extern void func_020ed03c(void);
extern void func_020ecf24(void);

void func_020ecde8(void)
{
    unsigned char c;
    unsigned short s;

    c = data_021fbef8;
    c = (unsigned char) (c + 0xfd);
    if (c > 1) {
        return;
    }

    s = data_021fbefc;
    if (s == 1) {
        DWC_ProcessInet();
        return;
    }

    func_ov065_02278000();
    func_ov065_0227f700();
    func_020ed03c();
    func_020ecf24();
}
