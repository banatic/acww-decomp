/* func_ov046_022610fc @ 0x022610fc, 0x5c bytes, Thumb, module ov046
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b1558(void);
extern void *func_02073d90(void *);
extern short *func_0209d358(int, int);
extern void *data_020ccf94;

int func_ov046_022610fc(unsigned char *self)
{
    self[0xc5] = 16 - func_020b1558();
    self[0xc4] = 0;

    if (func_02073d90(data_020ccf94) != 0 || *func_0209d358(0, 0x4a) != 0) {
        if (func_020b1558() < 0x10) {
            return 0x27;
        }
        return 0x26;
    } else {
        if (func_020b1558() < 0x10) {
            return 0x28;
        }
        return 0x29;
    }
}
