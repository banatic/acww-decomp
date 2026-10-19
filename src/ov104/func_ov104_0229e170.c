/* func_ov104_0229e170 @ 0x0229e170, 0x64 bytes, Thumb, module ov104
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208e484(const void *ptr);
extern void func_0200467c(int command);
extern void func_ov002_02209114(void *ptr, unsigned char idx, int flag);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);

void func_ov104_0229e170(void *p)
{
    if (func_0208e484((char *) p + 0x24a0) != 0) {
        int flag;
        *(unsigned char *) ((char *) p + 0xbc) =
            *(unsigned char *) ((char *) p + (*(unsigned char *) ((char *) p + 0xbd)) + 0x28f1);
        flag = 1;
        if (*(unsigned char *) ((char *) p + 0xbc) == 2) {
            flag = 0;
            func_0200467c(0x24);
        }
        func_ov002_02209114((char *) p + 0x2504, *(unsigned char *) ((char *) p + 0xbd), flag);
        func_ov002_02208098((void *) (p), 0x17);
    }
}
