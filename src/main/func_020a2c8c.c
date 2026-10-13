/* func_020a2c8c @ 0x020a2c8c, 0xbc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020a11c4(void *);
extern void *func_020682e0(int);
extern void func_02068358(void *);
extern void func_02068434(void *);
extern void func_0206844c(void *, void *, const void *);
extern void func_020a4e94(void *, int);
extern int func_020ec2d4(int);
extern int func_020e8840(void *);
extern void func_02074308(void);
extern int func_0209ffb0(void *);
extern void func_020a0174(void);
extern const char data_020e3c54;

struct Self020a2c8c {
    unsigned char pad_00[0xd0];
    unsigned short unk_D0;
};

void func_020a2c8c(struct Self020a2c8c *self)
{
    char buf[2];
    int v;

    v = func_020a11c4(self);
    if (v > 0 && v < 4) {
        void *p;

        p = func_020682e0(0);
        func_02068358(p);
        func_02068434(p);
        buf[0] = 0x26;
        func_0206844c(p, buf, &data_020e3c54);
        func_020a4e94(self, 0);
    } else {
        int flag = 0;
        int w;

        w = func_020ec2d4(v);
        if (w == 2) {
            self->unk_D0 = 0;
        } else {
            if (func_020ec2d4(w) == 1) {
                if (func_020e8840(&self->unk_D0) == 0) {
                    flag = 1;
                } else {
                    func_02074308();
                }
            } else {
                flag = 1;
            }
            if (flag) {
                void *p;

                if (func_0209ffb0(self)) {
                    func_020a0174();
                }
                p = func_020682e0(0);
                buf[1] = 0x25;
                func_0206844c(p, &buf[1], &data_020e3c54);
                func_02068358(p);
                func_02068434(p);
                func_020a4e94(self, 0xc);
            }
        }
    }
}
