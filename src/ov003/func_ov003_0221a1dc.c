/* func_ov003_0221a1dc @ 0x0221a1dc, 0x4c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0208a020(void *arg);
extern int func_ov003_0221abf8(void *object, int flag);

void func_ov003_0221a1dc(void *s)
{
    *(unsigned int *) ((char *) s + 0x270) = *(unsigned int *) ((char *) s + 0x26c);
    if (*(unsigned char *) ((char *) s + 0x2e0) != 0) {
        void *ret;
        ret = func_0208a020((char *) s + 0x2a4);
        if (ret != 0) {
            if (*(int *) ((char *) ret + 0x98) > 0x666) {
                func_ov003_0221abf8(s, 1);
            }
        }
    }
}
