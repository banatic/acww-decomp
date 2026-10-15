/* func_ov104_0229dfd4 @ 0x0229dfd4, 0x48 bytes, Thumb, module ov104
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov104_0229d448(int, unsigned char);
extern void func_ov104_0229c354(int, int);
extern void func_ov104_0229d5c0(int);
extern int func_ov002_02209f70(int);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);

void func_ov104_0229dfd4(int r0)
{
    int r4 = r0;
    if (func_ov002_02209f70(r4 + 0x24a0) == 0) {
        func_ov104_0229d448(r4, *(unsigned char *) (r4 + 0xba));
        func_ov104_0229c354(r4, 0x40);
        func_ov002_02208098((void *) (r4), 0x14);
        func_ov104_0229d5c0(r4);
    } else {
        func_ov002_02208098((void *) (r4), 7);
    }
}
