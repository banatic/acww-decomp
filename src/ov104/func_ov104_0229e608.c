/* func_ov104_0229e608 @ 0x0229e608, 0x34 bytes, Thumb, module ov104
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02208054(void *p, int flag);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern int func_ov002_0220b498(void *object);
extern void func_ov104_0229cbe8(void *p);

void func_ov104_0229e608(void *param)
{
    if (func_ov002_02208054(param, 1)) {
        func_ov002_02208098((void *) (param), 9);
    } else {
        if (func_ov002_0220b498((void *) ((char *) param + 0x2d3c))) {
            func_ov104_0229cbe8(param);
        }
    }
}
