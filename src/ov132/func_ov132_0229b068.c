/* func_ov132_0229b068 @ 0x0229b068, 0x68 bytes, Thumb, module ov132
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_02208090(void *a, int b);
extern int func_020b9bbc(void *a, void *b, int c, int d, int e);
extern unsigned char *func_ov002_02208098(void *a, unsigned char value);
extern void func_0200467c(int cmd);

void func_ov132_0229b068(void *base)
{
    func_ov002_02208090(base, 2);
    *((unsigned char *) ((char *) base + 0x1506)) = 10;
    func_020b9bbc((char *) base + 0x39c, (char *) base + 0x500, 6, 0x800, 0);
    func_020b9bbc((char *) base + 0x3c0, (char *) base + 0xd00, 4, 0x800, 0);
    func_ov002_02208098(base, 6);
    func_0200467c(0x29);
}
