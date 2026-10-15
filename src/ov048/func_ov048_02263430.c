/* func_ov048_02263430 @ 0x02263430, 0x8c bytes, Thumb, module ov048
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int a, b, c;
} UnkStruct_02263430;

extern int func_020984e8(void);
extern UnkStruct_02263430 *func_02095794(int);
extern int func_02014868(void *);
extern int func_02095ab0(void *, int, int);
extern int DWCi_GsMalloc(int);
extern int func_0203e020(void *);
extern UnkStruct_02263430 data_ov048_02263974;

int func_ov048_02263430(unsigned char *self)
{
    volatile UnkStruct_02263430 saved;
    UnkStruct_02263430 local2;
    UnkStruct_02263430 *ptr;

    func_020984e8();

    ptr = func_02095794(4);
    saved.a = ptr->a;
    saved.b = ptr->b;
    saved.c = ptr->c;

    switch (self[0xe71]) {
        case 0:
            if (func_02014868(self + 0x618) == 0) {
                self[0xe71] = 1;
            }
            break;
        case 1:
            local2.a = data_ov048_02263974.a;
            local2.b = data_ov048_02263974.b;
            local2.c = data_ov048_02263974.c;
            func_02095ab0(&local2, 0x266, 4);
            self[0xe71] = 3;
            break;
        case 3:
            if (DWCi_GsMalloc(4) == 0) {
                func_0203e020(self);
            }
            break;
        default:
            break;
    }

    return 1;
}
