/* func_ov105_0229cf48 @ 0x0229cf48, 0x78 bytes, Thumb, module ov105
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov105_0229c340(void *obj, int arg);
extern int func_ov105_0229cff4(void *obj);
extern int func_ov105_0229cfe4(void *obj);
extern void func_ov002_0220a0b4(void *ptr, int a, int b);
extern void func_ov105_0229c320(void *obj, int arg);
extern void func_ov002_0220a05c(void *ptr, int a, int b, int c, int d);
extern unsigned char *func_ov002_02208098(void *obj, unsigned char value);

void func_ov105_0229cf48(void *obj)
{
    int a, b;
    unsigned char *src;

    if (func_ov105_0229c340(obj, 8) != 0) {
        a = func_ov105_0229cff4(obj);
        b = func_ov105_0229cfe4(obj);
        func_ov002_0220a0b4((char *) obj + 0x24a4, a, b);
        func_ov105_0229c320(obj, 8);
    } else {
        a = func_ov105_0229cff4(obj);
        b = func_ov105_0229cfe4(obj);
        func_ov002_0220a05c((char *) obj + 0x24a4, a, b, 3, 1);
        src = (unsigned char *) obj + 0x8d;
        ((unsigned char *) obj)[0x2bd] = *src;
        func_ov002_02208098(obj, 13);
    }
}
