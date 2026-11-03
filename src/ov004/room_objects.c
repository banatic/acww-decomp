/* room_objects: 7 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_0223b3c0 @ 0x0223b3c0, 0x38 bytes, Thumb
 * func_ov004_0223b39c @ 0x0223b39c, 0x22 bytes, Thumb
 * func_ov004_0223b364 @ 0x0223b364, 0x38 bytes, Thumb
 * func_ov004_0223b340 @ 0x0223b340, 0x22 bytes, Thumb
 * func_ov004_0223b33c @ 0x0223b33c, 0x4 bytes, Thumb
 * func_ov004_0223b338 @ 0x0223b338, 0x4 bytes, Thumb
 * func_ov004_0223b334 @ 0x0223b334, 0x4 bytes, Thumb
 */

extern int func_ov004_02213f8c(void *);
extern int func_ov004_02212564(void *);
extern int func_ov004_0223cc10(int, void *, int, int);
extern int func_ov004_0223cd50(void);
extern int func_ov004_02213f78(void *self);
extern int func_ov004_02212550(void *self);

int func_ov004_0223b3c0(char *self)
{
    if (self != 0) {
        switch (*(int *) (self + 0x780)) {
            case 0x1b:
                if (self != 0) {
                    return func_ov004_02213f8c(self);
                }
                break;
            case 0x27:
                if (self != 0) {
                    return func_ov004_02212564(self);
                }
                break;
        }
    }
    return 0;
}

int func_ov004_0223b39c(char *self, int a1)
{
    // DECLS
    // ENDDECLS
    return func_ov004_0223b3c0((char *) (func_ov004_0223cc10(func_ov004_0223cd50(), self, a1, 0x0)));
}

int func_ov004_0223b364(unsigned char *self)
{
    if (self != 0) {
        switch (*(int *) (self + 0x780)) {
            case 0x1b:
                if (self != 0) {
                    return func_ov004_02213f78(self);
                }
                break;
            case 0x27:
                if (self != 0) {
                    return func_ov004_02212550(self);
                }
                break;
        }
    }
    return 0;
}

int func_ov004_0223b340(char *self, int a1)
{
    // DECLS
    // ENDDECLS
    return func_ov004_0223b364((unsigned char *) (func_ov004_0223cc10(func_ov004_0223cd50(), self, a1, 0x0)));
}

int func_ov004_0223b33c(void *position, short angle)
{
    return 1;
}

int func_ov004_0223b338(void *position, short angle)
{
    return 1;
}

int func_ov004_0223b334(void *position, short angle)
{
    return 1;
}
