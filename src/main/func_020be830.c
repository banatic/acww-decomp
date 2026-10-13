/* func_020be830 @ 0x020be830, 0x78 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[8];
    int counter;
} UnkStruct_020be830;

extern void func_020be6ac(UnkStruct_020be830 *s, int a, int b);
extern void func_ov003_02219774(void);
extern void func_0203aeac(void);
extern void *func_02098844(void *base, int index);
extern int func_02099a28(void *obj);
extern void *func_0209967c(void *obj);
extern void func_02088768(void *obj, int arg);
extern void func_020871b8(char *addr);
extern void func_0204130c(int a, int b, int c);
extern void func_020be758(UnkStruct_020be830 *s);
extern char data_021dc7bc[];
extern char data_021ebcd2[];

void func_020be830(UnkStruct_020be830 *s)
{
    int i;
    void *r;

    func_020be6ac(s, 0x190, 0x190);
    s->counter -= 1;
    if (s->counter > 0) {
        return;
    }

    func_ov003_02219774();
    func_0203aeac();

    for (i = 0; i < 4; i++) {
        r = func_02098844(data_021dc7bc, i);
        if (r && func_02099a28(r)) {
            func_02088768(func_0209967c(r), 0x14);
        }
    }

    func_020871b8(data_021ebcd2);
    func_0204130c(0x44, 0x63, 0);
    func_020be758(s);
}
