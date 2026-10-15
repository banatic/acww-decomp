/* func_ov129_0229da80 @ 0x0229da80, 0x60 bytes, Thumb, module ov129
 * mwccarm 1.2/base -O4,s
 */

extern void *func_ov002_02207f80(unsigned int size);
extern void *func_ov002_0220830c(void *ptr);
extern void *func_ov002_0220ba24(void *ptr);
extern void *func_ov002_0220b008(void *ptr);
extern void *func_ov002_02209ccc(void *ptr);
extern void *func_020b18ac(void *ptr);
extern int func_ov127_0229a0ec(void *ptr);
extern unsigned char data_ov129_0229dc38[];

void *func_ov129_0229da80(void)
{
    void *obj = func_ov002_02207f80(0x3160);
    if (obj) {
        func_ov002_0220830c(obj);
        *(void **) obj = (void *) data_ov129_0229dc38;
        func_ov002_0220ba24((char *) obj + 0xb8);
        func_ov002_0220b008((char *) obj + 0x1d4);
        func_ov002_02209ccc((char *) obj + 0x3a0);
        func_020b18ac((char *) obj + 0x404);
        func_ov127_0229a0ec((char *) obj + 0x734);
    }
    return obj;
}
