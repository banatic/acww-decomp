/* func_ov095_0229c1c4 @ 0x0229c1c4, 0x44 bytes, Thumb, module ov095
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov095_0229c22c(void *obj, int a, int b, int c);

void func_ov095_0229c1c4(void *obj, int id, int b)
{
    switch (id) {
        case 0x107:
            ((unsigned char *) obj)[0x16] = 4;
            break;
        case 0x108:
            ((unsigned char *) obj)[0x16] = 1;
            break;
        case 0x109:
            ((unsigned char *) obj)[0x16] = 2;
            break;
    }
    func_ov095_0229c22c(obj, 9, b, 1);
}
