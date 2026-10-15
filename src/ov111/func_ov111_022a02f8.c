/* func_ov111_022a02f8 @ 0x022a02f8, 0x168 bytes, Thumb, module ov111
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02208014(void *receiver);
extern void func_ov111_022a0204(void *);
extern int func_ov002_02208008(void *);
extern unsigned int func_ov111_0229f430(void *, int);
extern void func_ov095_0229b3ec(void *);
extern void func_ov111_0229f4c4(void *);
extern void func_ov111_0229f524(void *);
extern void func_ov111_0229fd08(void *);
extern void func_ov111_0229f10c(void *);
extern void RtcSendPxiCommand(int);
extern void func_ov095_0229a148(void *);
extern void func_ov111_0229efb8(void *, int);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern void func_ov111_0229f164(void *);
extern int func_ov002_02209f00(void *);
extern void func_ov095_0229a154(void *, int);
extern void func_ov002_0220a254(void *);
extern void func_ov095_0229a170(void *, int);
extern int func_ov111_0229f288(void *);
extern int func_ov111_0229f2ec(void *);
extern int func_ov111_0229f358(void *);
extern void func_ov111_0229efc8(void *, int);
extern int func_ov111_0229f24c(void *);
extern struct {
    unsigned short f0;
    unsigned short f2;
} data_021fbe40;
void func_ov111_022a02f8(void *self)
{
    unsigned char *ptr;
    ptr = (unsigned char *) self;
    if (func_ov002_02208014(self) != 0) {
        func_ov111_022a0204(self);
        return;
    }
    {
        int val = func_ov002_02208008(self);
        unsigned int action = func_ov111_0229f430(self, val);
        switch (action) {
            case 1:
                func_ov095_0229b3ec(((char *) self) + 0xac);
                func_ov111_0229f4c4(self);
                func_ov111_0229f524(self);
                func_ov111_0229fd08(self);
                func_ov111_0229f10c(self);
                RtcSendPxiCommand(0xb);
                break;

            case 4:
                func_ov095_0229a148(((char *) self) + 0xac);
                func_ov111_0229efb8(self, 2);
                func_ov002_02208098((void *) (self), 3);
                func_ov111_0229f164(self);
                break;

            case 2:
                func_ov095_0229a154(((char *) self) + 0xac, func_ov002_02209f00(ptr + 0x3d38));
                func_ov111_0229efb8(self, 2);
                func_ov002_02208098((void *) (self), 3);
                func_ov002_0220a254(((unsigned char *) self) + 0x3d38);
                func_ov111_0229f164(self);
                break;

            case 3:
                func_ov095_0229a170(((char *) self) + 0xac, func_ov002_02209f00(((char *) self) + 0x3d38));
                func_ov111_0229efb8(self, 2);
                func_ov002_02208098((void *) (self), 3);
                func_ov111_0229f164(self);
                break;

            default:

            case 0:
                if (func_ov111_0229f288(self) != 0) {
                    return;
                }
                if (func_ov111_0229f2ec(self) != 0) {
                    return;
                }
                {
                    unsigned char b = *((unsigned char *) (((char *) self) + 0x9e));
                    if (func_ov111_0229f358(self) != 0) {
                        if (b == (*((unsigned char *) (((char *) self) + 0x9e)))) {
                            return;
                        }
                        func_ov111_0229f10c(self);
                        return;
                    }
                    if ((data_021fbe40.f2 & 1) != 0) {
                        func_ov002_02208098((void *) (self), 0xa);
                        func_ov111_0229efc8(self, 1);
                        *((unsigned char *) (((char *) self) + 0x9f)) = *((unsigned char *) (((char *) self) + 0x9e));
                        *((unsigned char *) (((char *) self) + 0xa0)) = *((unsigned char *) (((char *) self) + 0x9e));
                        return;
                    } else if (func_ov111_0229f24c(self) != 0) {
                        return;
                    }
                }
                break;
        }
    }
}
