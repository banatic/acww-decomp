/* func_ov142_0229b4a8 @ 0x0229b4a8, 0x24 bytes, Thumb, module ov142
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208e484(void *);
extern void func_ov142_0229af00(void *);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);

void func_ov142_0229b4a8(void *arg0)
{
    if (func_0208e484((char *) arg0 + 0xe8)) {
        func_ov142_0229af00(arg0);
        func_ov002_02208098((void *) (arg0), *(unsigned char *) ((char *) arg0 + 0xba));
    }
}
