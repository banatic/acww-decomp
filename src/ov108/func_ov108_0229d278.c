/* func_ov108_0229d278 @ 0x0229d278, 0x30 bytes, Thumb, module ov108
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02209f9c(void *p);
extern void func_ov108_0229ce68(void *p, unsigned char b);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);

void func_ov108_0229d278(void *this)
{
    if (func_ov002_02209f9c((char *) this + 0x2498)) {
        func_ov108_0229ce68(this, *(unsigned char *) ((char *) this + 0x2B0));
        func_ov002_02208098((void *) (this), 0xE);
    }
}
