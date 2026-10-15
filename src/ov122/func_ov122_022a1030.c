/* func_ov122_022a1030 @ 0x022a1030, 0xe0 bytes, Thumb, module ov122
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov122_0229f958(void *);
extern void func_ov095_0229b3ec(void *);
extern void func_ov122_0229f89c(void *);
extern void *func_ov122_0229f634(void *);
extern int func_ov095_0229b3a0(void *, void *, unsigned char);
extern void func_ov122_0229f388(void *receiver);
extern void RtcSendPxiCommand(int);
extern void func_ov122_022a15b8(void *, int, int);
extern void func_ov122_0229f9a8(void *);

int func_ov122_022a1030(void *self, int param)
{
    if (func_ov122_0229f958(self) != 0) {
        func_ov095_0229b3ec((char *) self + 0xc0);
        func_ov122_0229f89c(self);
    } else {
        if (*(unsigned char *) ((char *) self + 0xac) != 0) {
            void *ret = func_ov122_0229f634(self);
            if (func_ov095_0229b3a0((char *) self + 0xc0, ret, *(unsigned char *) ((char *) self + 0xac)) == 0) {
                *(unsigned char *) ((char *) self + 0xad) = *(unsigned char *) ((char *) self + 0xac);
                *(unsigned char *) ((char *) self + 0xae) = (unsigned char) (*(unsigned char *) ((char *) self + 0xac) - 1);
                func_ov122_0229f89c(self);
            }
        } else {
            unsigned char *ret = func_ov122_0229f634(self);
            unsigned char b = *(unsigned char *) ((char *) self + 0xaa);
            if (b == 0) {
                unsigned char *ptr = *(unsigned char **) ((char *) self + 0xbc);
                if (*(unsigned char *) ((char *) ptr + 0xf8) == 0) {
                    goto ret0;
                }
            }
            if (b == 1) {
                unsigned char *ptr = *(unsigned char **) ((char *) self + 0xbc);
                if (*(unsigned char *) ((char *) ptr + 0xf8) == 0xa) {
                    goto ret0;
                }
            }
            if (*(unsigned short *) ret != 0) {
                goto set_fields;
            }
        ret0:
            if (param != 0) {
                func_ov122_0229f388((void *) self);
            }
            return 0;
        set_fields:
            *(unsigned char *) ((char *) self + 0xad) = 0;
            *(unsigned char *) ((char *) self + 0xae) = 1;
            func_ov122_0229f89c(self);
        }
    }

    RtcSendPxiCommand(0x35);
    func_ov122_022a15b8(self, 0, 1);
    func_ov122_0229f9a8(self);
    return 1;
}
