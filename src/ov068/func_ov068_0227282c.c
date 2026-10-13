/* func_ov068_0227282c @ 0x0227282c, 0x48 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov009_02262ed4(void *, int);
extern int func_02056f94(void *);
extern void func_ov068_02272a7c(void *, int);
extern void func_ov068_02272c64(void *);
extern void func_02055124(void *);

void func_ov068_0227282c(void *p)
{
    func_ov009_02262ed4((void *) ((char *) p + 0x238), 0x888);
    if (func_02056f94((void *) ((char *) p + 0x1d8)) != 0) {
        func_ov068_02272a7c(p, 3);
    }
    func_ov068_02272c64(p);
    func_02055124((void *) ((char *) p + 0x13c));
}
