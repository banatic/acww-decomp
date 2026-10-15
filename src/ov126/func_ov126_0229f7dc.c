/* func_ov126_0229f7dc @ 0x0229f7dc, 0x60 bytes, Thumb, module ov126
 * mwccarm 1.2/base -O1,s
 */

extern void func_020a8874(void *, void *, unsigned char);
extern int func_020a8a70(void *, void *, int, int);
extern int func_020b4424(void *);
extern int func_020a87e0(void *, void *);
extern int func_0205182c(void *, void *, unsigned char);

void func_ov126_0229f7dc(void *self)
{
    char *p1;
    unsigned char b;

    p1 = (char *) self + 0x4248;
    b = *(unsigned char *) ((char *) self + 0xa6);

    func_020a8874((char *) self + 0x40cc, p1, b);
    func_020a8a70((char *) self + 0x4060, (char *) self + 0x40cc, 0, 0);
    if (func_020b4424((char *) self + 0x4060)) {
        func_020a87e0((char *) self + 0x40cc, (char *) self + 0x4060);
        func_0205182c((char *) self + 0x40cc, p1, b);
    }
}
