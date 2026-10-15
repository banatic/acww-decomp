/* func_ov131_0229b07c @ 0x0229b07c, 0x54 bytes, Thumb, module ov131
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_0220a620(char *p, int n);
extern int func_ov002_0220a720(char *p, int n);
extern void func_ov002_02208090(char *p, int n);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern void func_0206fc4c(int n);
extern int func_ov130_02299ddc(char *p);
extern void func_0206f830(int argument0);
extern void func_ov131_0229ad5c(char *p);

int func_ov131_0229b07c(char *ptr)
{
    if (func_ov002_0220a620(ptr + 0xf8, 6) != 0) {
        return 0;
    }

    func_ov002_0220a720(ptr + 0xf8, 6);
    func_ov002_02208090(ptr, 2);
    func_ov002_02208098((void *) (ptr), 7);
    func_0206fc4c(1);

    func_0206f830(func_ov130_02299ddc(ptr + 0x2c4));
    func_ov131_0229ad5c(ptr);

    return 1;
}
