/* func_ov144_0229aa08 @ 0x0229aa08, 0x26 bytes, Thumb, module ov144
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02209f64(void *ptr);
extern void func_ov002_02208098(void *ptr, unsigned char byte);
extern void func_ov144_0229b02c(void *ptr);

void func_ov144_0229aa08(unsigned char *ptr)
{
    unsigned char *p = ptr;

    if (func_ov002_02209f64(ptr + 0xc4) == 0) {
        p += 0xbe;
        func_ov002_02208098(ptr, *p);
        func_ov144_0229b02c(ptr);
    }
}
