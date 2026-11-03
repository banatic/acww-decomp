/* room_object_light_3: 3 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_0220ede0 @ 0x0220ede0, 0x94 bytes, Thumb
 * func_ov004_0220ed40 @ 0x0220ed40, 0xa0 bytes, Thumb
 * func_ov004_0220ecec @ 0x0220ecec, 0x54 bytes, Thumb
 */

extern int func_ov004_0220e5c0(void *self);
extern int func_ov004_0220ee74(void);
extern int func_ov004_0220d2b8(void *p);
extern int func_ov004_0220d220(void *p, int a, void *b, int c);
extern int func_ov004_0223c264(void *fn);
extern int func_ov004_0221134c(void *arg0);
extern void func_ov004_02211414(int k);
extern unsigned char func_020b65c4(void);
extern void func_02052038(int x, int k);
extern void func_02064db8(int a, int b, int c);
extern int data_ov004_02250010;
extern int func_ov004_0220d208(void *p, int a, int b, int c);
extern void func_02064da0(unsigned int index, unsigned int value);
extern void func_ov004_0220d150(void *p);
extern int func_ov004_0220cdf8(void *self);

void func_ov004_0220ede0(char *self)
{
    int a;
    int k;

    if (func_ov004_0220e5c0(self) != 0) {
        a = *(int *) (self + 0x594);
        (void) func_ov004_0220d220(self + 0x748, a, &data_ov004_02250010, func_ov004_0220d2b8(self + 0x740));
        if (func_ov004_0220ee74() != 0) {
            k = func_ov004_0223c264((void *) func_ov004_0221134c);
            if (func_ov004_0220d2b8(self + 0x740) != 0 && k == 1) {
                if (*(int *) (self + 0x76c) != 0) {
                    func_02052038(((void) (func_ov004_02211414(*(int *) (self + 0x794))), func_020b65c4()), 1);
                } else {
                    func_02064db8(0, 1, 0);
                }
            }
        }
    }
}

void func_ov004_0220ed40(void *self)
{
    int k;

    if (func_ov004_0220e5c0(self) != 0 && func_ov004_0220ee74() != 0 &&
        func_ov004_0220d208((char *) self + 0x748, func_ov004_0220d2b8((char *) self + 0x740), 1,
                            *(int *) ((char *) self + 0x794) == 1) != 0) {
        k = func_ov004_0223c264((void *) func_ov004_0221134c);
        if (func_ov004_0220d2b8((char *) self + 0x740) != 0) {
            if (k == 1) {
                func_ov004_02211414(*(int *) ((char *) self + 0x794));
                func_02052038(func_020b65c4(), 1);
            }
        } else if (k == 0) {
            func_02064da0(0, 8);
            func_02052038(func_020b65c4(), 0);
        }
    }
    func_ov004_0220d150((char *) self + 0x748);
}

void func_ov004_0220ecec(char *self)
{
    if (func_ov004_0220e5c0((void *) self) && func_ov004_0220ee74() && func_ov004_0220d2b8(self + 0x740) &&
        func_ov004_0223c264((void *) func_ov004_0221134c) == 1) {
        func_02064da0(0, 1);
        if (func_ov004_0220cdf8(self)) {
            func_02052038((int) func_020b65c4(), 0);
        }
    }
}
