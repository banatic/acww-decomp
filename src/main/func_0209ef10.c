/* func_0209ef10 @ 0x0209ef10, 0x6c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02098068(int);
extern void func_0203a678(int);
extern void func_02071028(int, int);
extern void func_0207172c(int);
extern void func_020ae310(int);
extern int func_020a1368(void);
extern void func_02097f38(int);

void func_0209ef10(int a, int b)
{
    int ret;

    func_02098068(a + 0x13144 + 0xa04 * b);
    func_0203a678(a + 0x16800 + 0xb4 * b);
    func_02071028(a + 0x17150, b);
    func_0207172c(b);
    ret = (((int) (func_020ae310((unsigned char) b), (unsigned char) b)), func_020a1368());
    if (ret != 0) {
        func_02097f38(ret + 0x3200 * b);
    }
}
