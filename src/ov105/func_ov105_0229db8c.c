/* func_ov105_0229db8c @ 0x0229db8c, 0x34 bytes, Thumb, module ov105
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208e484(unsigned char *arg);
extern void func_ov105_0229c5fc(unsigned char *arg);
extern void func_ov105_0229c62c(unsigned char *arg);

void func_ov105_0229db8c(unsigned char *this)
{
    if (func_0208e484(this + 0x24a4) != 0) {
        if (this[0x2c2] != 0) {
            func_ov105_0229c5fc(this);
        } else {
            func_ov105_0229c62c(this);
        }
    }
}
