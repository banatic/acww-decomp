/* func_0203f278 @ 0x0203f278, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0203f454(unsigned char, int);
extern void func_0203f490(int, int);
extern unsigned int OSiHeapInfo[];

void func_0203f278(unsigned char *ptr, int param)
{
    unsigned int combined;

    combined = ((unsigned int) ptr[4] << 24) |
               (((unsigned int) ptr[3] << 16) | ((unsigned int) ptr[1] | ((unsigned int) ptr[2] << 8)));
    if (func_0203f454((unsigned char) param, combined)) {
        OSiHeapInfo[param] = combined;
        func_0203f490(1, param);
    } else {
        func_0203f490(2, param);
    }
}
