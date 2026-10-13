/* func_ov050_02263258 @ 0x02263258, 0x13c bytes, Thumb, module ov050
 * mwccarm 1.2/base -O4,s
 */

extern int func_020984e8(void *a, void *b);
extern int func_02099640(int r0);
extern int func_0209ad9c(int r0, int r1);
extern void *func_0209b4d4(int r0);
extern void func_02099fe8(void *p);
extern int func_0209bc40(void *p);
extern unsigned int func_0209bba0(void *p);
extern int func_0209b414(int r0);
extern int func_ov050_02263394(void *a, void *b);
extern void func_02099f1c(void *dst, void *src);
extern void *func_02099710(int r0);
extern int func_0204bcdc(void *p);
extern void *func_0204bc64(void *p);
extern int func_02099e9c(void *p);
extern int func_0209a000(void *p, int r1);
extern void func_0209abd0(int r0);

struct UnkStruct_02263258 {
    unsigned char pad_00[4];
    unsigned char state;
};

extern void func_ov050_022634b4(void);

void func_ov050_02263258(void *a, struct UnkStruct_02263258 *b)
{
    int r7;
    int local0;
    int local1;
    void *r4;
    unsigned short buf[4];
    unsigned int local2;
    int temp;

    r7 = func_020984e8(a, b);
    local0 = func_02099640(r7);
    local1 = func_0209ad9c(local0, 0);
    r4 = func_0209b4d4(local1);
    func_02099fe8(r4);

    if (func_0209bc40(r4) == 0xb && func_0209bba0(r4) >= 1 && func_0209b414(local1) != 0) {
        if (func_ov050_02263394(a, b) == 0) {
            func_02099f1c(&local2, (void *) func_ov050_022634b4);
            if (((unsigned char *) &local2)[2] >= 7) {
                b->state = 8;
            } else {
                b->state = 9;
            }
        }
        return;
    }

    if (func_0209bc40(r4) == 0xb && func_0209bba0(r4) >= 1) {
        r4 = func_02099710(r7);
        if (func_0204bcdc(r4) != 0) {
            buf[3] = 0x11a8;
            r4 = func_0204bc64(r4);
            if (r4 == func_0204bc64(&buf[3])) {
                temp = 1;
            } else {
                temp = 0;
            }
        } else {
            if (*(unsigned short *) r4 == 0x11a8) {
                temp = 1;
            } else {
                temp = 0;
            }
        }
        if (temp != 0) {
            b->state = 7;
            return;
        }

        buf[0] = 0x11a8;
        if (func_02099e9c(buf) < 0) {
            temp = 1;
        } else {
            temp = 0;
        }
        if (temp != 0) {
            buf[1] = 0x11a8;
            if (func_0209a000(&buf[1], 0) != 0) {
                b->state = 4;
                return;
            } else {
                b->state = 2;
                return;
            }
        } else {
            b->state = 5;
            return;
        }
    } else {
        buf[2] = 0x11a8;
        if (func_0209a000(&buf[2], 0) != 0) {
            func_0209abd0(local0);
            b->state = 3;
            return;
        } else {
            b->state = 1;
            return;
        }
    }
}
