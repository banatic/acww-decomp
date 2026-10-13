/* func_ov137_0229cab8 @ 0x0229cab8, 0x68 bytes, Thumb, module ov137
 * mwccarm 1.2/base -O4,s
 */

void func_ov137_0229cab8(void *this)
{
    if (func_0208e484((unsigned char *) this + 0x94) != 0) {
        if (func_ov137_0229c574(this, 2) != 0) {
            if (func_ov134_02299b70((unsigned char *) this + 0x2c4) != 0) {
                func_ov002_02208098(this, 6);
            } else {
                func_ov134_022997b0((unsigned char *) this + 0x2c4);
                func_ov137_0229c8d4(this);
            }
        } else {
            unsigned char b = *((unsigned char *) this + 0x2b77);
            if (b == 2) {
                func_ov137_0229c92c(this);
            } else {
                func_ov137_0229c900(this, b + 1);
            }
        }
    }
}
