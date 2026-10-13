/* func_0206c3fc @ 0x0206c3fc, 0x84 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a873c(void *a, void *b);
extern void func_020a9334(void *a, int b);
extern int func_02050bf8(unsigned char c);
extern int func_02050c04(unsigned char c);

void func_0206c3fc(unsigned char *p)
{
    unsigned char local;
    unsigned char *base;
    unsigned int x, val, rem;
    int result;

    func_020a873c(p + 0x34, &local);
    local--;

    base = *(unsigned char **) (p + 0x2c);
    val = *(unsigned int *) (base + 0x1a60);
    x = *(unsigned int *) (base + 0x1a5c);

    if (x != 0 && (rem = (int) (x - 0xAC00) % 28) != 0) {
        if (val == 1) {
            if (local == 6 && rem == 8) {
                result = func_02050bf8(local);
            } else {
                result = func_02050c04(local);
            }
        } else {
            result = func_02050c04(local);
        }
    } else {
        result = func_02050bf8(local);
    }

    func_020a9334(p, result);
}
