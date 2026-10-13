/* func_ov134_0229bcf0 @ 0x0229bcf0, 0x3c bytes, Thumb, module ov134
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov134_0229b6b4(void);
extern void func_0200277c(unsigned char);
extern void func_020b9ccc(void *);

void func_ov134_0229bcf0(void *self)
{
    func_ov134_0229b6b4();
    func_0200277c(*(unsigned char *) ((char *) self + 0xa4));
    func_020b9ccc((char *) self + 0x804);
    func_020b9ccc((char *) self + 0x828);
    func_020b9ccc((char *) self + 0x84c);
}
