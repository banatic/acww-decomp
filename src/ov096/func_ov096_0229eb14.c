/* func_ov096_0229eb14 @ 0x0229eb14, 0x84 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov096_0229f830(void *obj, unsigned char b);
extern int func_ov096_0229f820(void *obj, unsigned char b);
extern int func_ov096_0229f150(void *obj, unsigned char b);
extern int func_ov096_0229f810(void *obj, unsigned char b);
extern int func_ov096_0229f800(void *obj, unsigned char b);
extern void func_ov002_02207cf0(void *ptr);
extern void func_ov002_02207cf8(void *ptr);

void func_ov096_0229eb14(void *obj)
{
    if (func_ov096_0229f830(obj, ((unsigned char *) obj)[0xb5]) != 0 ||
        func_ov096_0229f820(obj, ((unsigned char *) obj)[0xb5]) != 0) {
        if (func_ov096_0229f150(obj, ((unsigned char *) obj)[0xb5]) != 0) {
            func_ov002_02207cf0((char *) obj + 0x2418);
        } else {
            ((unsigned char *) obj)[0xb3] = ((unsigned char *) obj)[0xb5];
            func_ov002_02207cf8((char *) obj + 0x2418);
        }
    }
    if (func_ov096_0229f810(obj, ((unsigned char *) obj)[0xb5]) != 0 ||
        func_ov096_0229f800(obj, ((unsigned char *) obj)[0xb5]) != 0) {
        func_ov002_02207cf0((char *) obj + 0x2418);
    }
}
