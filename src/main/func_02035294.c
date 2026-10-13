/* func_02035294 @ 0x02035294, 0xb0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char *data_021c526c;
extern void func_02035a30(void *);
extern void func_02035d8c(void *);
extern void func_02035fc0(void *);
extern void func_020367ec(void *);
extern void func_02036920(void *);
extern void func_0203741c(void *);
extern void func_02036490(void *);
extern void func_020374ac(void *);

void func_02035294(void)
{
    unsigned char *p;
    unsigned char *end;

    func_02035a30(data_021c526c + 0x2e4);
    func_02035d8c(data_021c526c + 0x2d0);
    func_02035fc0(data_021c526c + 0x2b4);
    func_020367ec(data_021c526c + 0x2a0);
    func_02036920(data_021c526c + 0x264);
    func_0203741c(data_021c526c + 0x24c);
    func_02036490(data_021c526c + 0x1c4);

    p = data_021c526c;
    end = data_021c526c + 0x1c0;
    while (p < end) {
        func_020374ac(p);
        p += 0x1c;
    }

    *(unsigned int *) (data_021c526c + 0x1c0) = 0;
    *(unsigned char *) (data_021c526c + 0x2f4) = 0;
}
