/* func_ov048_022610f8 @ 0x022610f8, 0x28 bytes, Thumb, module ov048
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov048_02260474(unsigned int);
extern void func_020a1900(void);
extern void func_ov048_022616b8(void *, int);
extern void func_020c189c(void);

void func_ov048_022610f8(void *this)
{
    if (func_ov048_02260474(*(unsigned int *) ((char *) this + 0xb8)) != 0) {
        func_020a1900();
        func_ov048_022616b8(this, 0x16);
    } else {
        func_020c189c();
    }
}
