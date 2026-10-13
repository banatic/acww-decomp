/* func_ov129_0229cc4c @ 0x0229cc4c, 0x50 bytes, Thumb, module ov129
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short data_021fbe40;
extern void func_ov002_02208098(void *, int);
extern void func_ov129_0229c2fc(void *);
extern void func_ov127_02299bbc(void *, unsigned char);
extern void func_ov127_02299c08(void *, unsigned char, int);

void func_ov129_0229cc4c(unsigned char *a)
{
    if (!(data_021fbe40 & 1)) {
        func_ov002_02208098(a, 4);
        func_ov129_0229c2fc(a);
        func_ov002_02208098(a, 6);
        func_ov127_02299bbc(a + 0x734, *(unsigned char *) (a + 0xad));
    } else {
        func_ov127_02299c08(a + 0x734, *(unsigned char *) (a + 0xad), 0);
    }
}
