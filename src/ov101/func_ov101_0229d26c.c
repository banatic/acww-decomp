/* func_ov101_0229d26c @ 0x0229d26c, 0x30 bytes, Thumb, module ov101
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov101_0229ceb4(void *p, unsigned char c);
extern int func_ov002_02209f9c(void *p);
extern unsigned char *func_ov002_02208098(void *p, unsigned char value);

void func_ov101_0229d26c(void *p)
{
    if (func_ov002_02209f9c((char *) p + 0x229c)) {
        func_ov101_0229ceb4(p, *(unsigned char *) ((char *) p + 0xb3));
        func_ov002_02208098(p, 0xe);
    }
}
