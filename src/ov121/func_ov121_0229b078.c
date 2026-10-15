/* func_ov121_0229b078 @ 0x0229b078, 0x24 bytes, Thumb, module ov121
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_0220b8ac(void *ptr, int val);
extern unsigned char *func_ov121_0229afb8(void *obj);

int func_ov121_0229b078(void *obj)
{
    int result = func_ov002_0220b8ac((char *) obj + 0x40c, 1);
    if (result != 0) {
        result = (int) func_ov121_0229afb8(obj);
    }
    return result;
}
