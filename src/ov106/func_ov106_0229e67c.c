/* func_ov106_0229e67c @ 0x0229e67c, 0x48 bytes, Thumb, module ov106
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02207cc0(int object);
extern void func_ov106_0229c798(const unsigned char *, unsigned char, int);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);

void func_ov106_0229e67c(unsigned char *obj)
{
    if (func_ov002_02207cc0((int) (obj + 0x21b8)) == 0) {
        return;
    }
    if (obj[0xbf] != 0) {
        obj[0xbf]--;
    } else {
        func_ov106_0229c798(obj, obj[0xb5], 1);
        func_ov002_02208098((void *) (obj), 2);
    }
}
