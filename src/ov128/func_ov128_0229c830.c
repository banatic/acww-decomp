/* func_ov128_0229c830 @ 0x0229c830, 0x60 bytes, Thumb, module ov128
 * mwccarm 1.2/base -O4,s
 */

extern void *func_ov002_02207f80(int size);
extern void func_ov002_0220830c(void);
extern void func_ov002_0220b3c4(void *p);
extern void func_ov002_02209ccc(void *p);
extern void func_020b18ac(void *p);
extern void func_ov127_0229a0ec(void *p);
extern void func_02070c08(void *p);
extern int data_ov128_0229cbc0;

void *func_ov128_0229c830(void)
{
    void *p = func_ov002_02207f80(0x2d74);
    if (p != 0) {
        func_ov002_0220830c();
        *(void **) p = &data_ov128_0229cbc0;
        func_ov002_0220b3c4((char *) p + 0x94);
        func_ov002_02209ccc((char *) p + 0x110);
        func_020b18ac((char *) p + 0x174);
        func_ov127_0229a0ec((char *) p + 0x4a4);
        func_02070c08((char *) p + 0x2cdc);
    }
    return p;
}
