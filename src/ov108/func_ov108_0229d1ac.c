/* func_ov108_0229d1ac @ 0x0229d1ac, 0x48 bytes, Thumb, module ov108
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov108_0229c864(void *, unsigned char);
extern int func_ov108_0229c2cc(void *, int);
extern int func_ov108_0229c9d8(void *);
extern int func_ov002_02209f70(void *);
extern int func_ov002_02208098(void *, int);

void func_ov108_0229d1ac(void *arg0)
{
    if (func_ov002_02209f70((char *) arg0 + 0x2498) == 0) {
        func_ov108_0229c864(arg0, *(unsigned char *) ((char *) arg0 + 0x2b2));
        func_ov108_0229c2cc(arg0, 0x40);
        func_ov002_02208098(arg0, 0x11);
        func_ov108_0229c9d8(arg0);
    } else {
        func_ov002_02208098(arg0, 6);
    }
}
