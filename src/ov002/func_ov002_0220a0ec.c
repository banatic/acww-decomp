/* func_ov002_0220a0ec @ 0x0220a0ec, 0x76 bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208e4bc(void *self);
extern void func_0208e508(void *self, int v);

void func_ov002_0220a0ec(void *self)
{
    switch (func_0208e4bc(self)) {
        case 0:
            break;
        case 1:
        case 2:
        case 3:
            func_0208e508(self, 1);
            break;
        case 7:
        case 8:
        case 9:
            func_0208e508(self, 7);
            break;
        case 13:
        case 14:
        case 15:
            func_0208e508(self, 0xd);
            break;
        case 16:
        case 17:
        case 18:
            func_0208e508(self, 0x10);
            break;
        default:
            func_0208e508(self, 9);
            break;
    }
}
