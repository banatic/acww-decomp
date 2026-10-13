/* func_ov142_02299f5c @ 0x02299f5c, 0x30 bytes, Thumb, module ov142
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02209eec(void *ptr);

void func_ov142_02299f5c(char *obj)
{
    int result;
    int mask;
    result = func_ov002_02209eec(obj + 0xe8);
    mask = result & 0xf;
    if (mask == 0) {
        result--;
    }
    if (result < 0x18) {
        result = 0x18;
    }
    if (result >= 0xa8) {
        result = 0xa7;
    }
    result -= 0x18;
    result >>= 4;
    obj[0xc0] = result;
}
