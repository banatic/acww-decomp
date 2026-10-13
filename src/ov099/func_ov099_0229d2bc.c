/* func_ov099_0229d2bc @ 0x0229d2bc, 0x48 bytes, Thumb, module ov099
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02209f70(void *p);
extern void func_ov099_0229c80c(void *p, unsigned char b);
extern void func_ov099_0229c29c(void *p, int n);
extern void func_ov002_02208098(void *p, int n);
extern void func_ov099_0229c9d0(void *p);

void func_ov099_0229d2bc(unsigned char *obj)
{
    if (func_ov002_02209f70(obj + 0x2274) == 0) {
        func_ov099_0229c80c(obj, obj[0x2909]);
        func_ov099_0229c29c(obj, 0x40);
        func_ov002_02208098(obj, 0xf);
        func_ov099_0229c9d0(obj);
    } else {
        func_ov002_02208098(obj, 4);
    }
}
