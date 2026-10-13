/* func_ov133_0229bc40 @ 0x0229bc40, 0x24 bytes, Thumb, module ov133
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_0220b8ac(char *ptr, int size);
extern void func_ov133_0229bbb4(char *ptr);

void func_ov133_0229bc40(char *arg)
{
    if (func_ov002_0220b8ac(arg + 0x1394, 1)) {
        func_ov133_0229bbb4(arg);
    }
}
