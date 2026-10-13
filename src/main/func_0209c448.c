/* func_0209c448 @ 0x0209c448, 0x26 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0209c38c(int index);

void func_0209c448(unsigned char *array, int index, int delta)
{
    if (func_0209c38c(index)) {
        unsigned char *ptr = &array[index];
        int val = *ptr;
        val += delta;
        if (val >= 255) {
            val = 255;
        }
        *ptr = (unsigned char) val;
    }
}
