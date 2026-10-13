/* func_02068388 @ 0x02068388, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a9dc8(void *a, void *b);
extern void func_020a9d24(void *a);

void func_02068388(unsigned char *obj, int cond)
{
    if (cond) {
        obj[0x18] = 1;
    } else {
        func_020a9dc8(obj + 0xb4, obj + 0x31c);
        func_020a9d24(obj + 0xb4);
    }
}
