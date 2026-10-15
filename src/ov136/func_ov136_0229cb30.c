/* func_ov136_0229cb30 @ 0x0229cb30, 0x28 bytes, Thumb, module ov136
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02209f64(void *p);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern void func_ov136_0229d184(void *obj);

void func_ov136_0229cb30(void *obj)
{
    if (func_ov002_02209f64((char *) obj + 0x94) == 0) {
        func_ov002_02208098((void *) (obj), *((unsigned char *) obj + 0x2b76));
        func_ov136_0229d184(obj);
    }
}
