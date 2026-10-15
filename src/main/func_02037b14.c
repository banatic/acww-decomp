/* func_02037b14 @ 0x02037b14, 0xb0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_02037bc4(int);

unsigned int func_02037b14(int index)
{
    unsigned int value = func_02037bc4(index);
    if (value & 0x7f000) {
        unsigned char count = 0;
        if (value & 0x1000) {
            count++;
        }
        if (value & 0x2000) {
            count++;
        }
        if (value & 0x4000) {
            count++;
        }
        if (value & 0x8000) {
            count++;
        }
        if (value & 0x10000) {
            count++;
        }
        if (value & 0x20000) {
            count++;
        }
        if (value & 0x40000) {
            count++;
        }
        return count;
    }
    return 0;
}
