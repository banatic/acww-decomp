/* func_0202e1a0 @ 0x0202e1a0, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0201b744(void);
extern void func_02083068(void *);
extern void func_0202df00(void *);
extern void func_0201cd3c(void *);

int func_0202e1a0(void *r4)
{
    if (func_0201b744() == 0) {
        return 0;
    }
    func_02083068((void *) ((char *) r4 + 0x828));
    func_0202df00((void *) ((char *) r4 + 0x64c));
    func_0201cd3c((void *) ((char *) r4 + 0x83c));
    return 1;
}
