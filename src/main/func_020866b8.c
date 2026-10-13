/* func_020866b8 @ 0x020866b8, 0x8c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x44];
    unsigned char b0;
    unsigned char b1;
    unsigned char b2;
} UnkStruct_020866b8;

extern void func_0209df64(unsigned char *);
extern void func_0208683c(UnkStruct_020866b8 *);
extern int func_02098844(unsigned int, int);
extern int func_02099a28(void);
extern int func_02099670(int);
extern void func_02088b38(int, int);
extern void func_02088b1c(int, int);
extern int data_021dc7bc;

void func_020866b8(UnkStruct_020866b8 *p, int mode)
{
    unsigned char arr[3];
    int i, val, zero;

    func_0209df64(arr);

    if (p->b2 == arr[2] && p->b1 == arr[1] && p->b0 == arr[0]) {
        return;
    }

    func_0208683c(p);

    zero = 0;

    for (i = 0; i < 4; i++) {
        val = func_02098844((unsigned int) &data_021dc7bc, i);
        if (val != 0 && func_02099a28() != 0) {
            switch (mode) {
                case 1:
                    func_02088b38(func_02099670(val), zero);
                    break;
                case 2:
                    func_02088b1c(func_02099670(val), zero);
                    break;
                default:
                    break;
            }
        }
    }
}
