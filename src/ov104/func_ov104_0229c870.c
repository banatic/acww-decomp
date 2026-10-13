/* func_ov104_0229c870 @ 0x0229c870, 0xd4 bytes, Thumb, module ov104
 * mwccarm 1.2/base -O4,s
 */

extern int func_02097890(const char *, int);
extern int func_02065ec0(const char *);
extern int func_02065e9c(const char *);
extern int func_020979ac(const char *);
extern int func_ov104_0229c7dc(void *, const char *);
extern void func_02066650(const char *);

typedef struct {
    char pad_00[0xb2];
    unsigned short flags;
} UnkStruct_0229c870;

unsigned short func_ov104_0229c870(UnkStruct_0229c870 *self, const char *ptr, int flag)
{
    unsigned short result;
    int i;

    if (func_02097890(ptr, 10) == 0) {
        return 0;
    }

    result = 0;
    i = 0;

loop_body:
    if (func_02065ec0(ptr) == 0) {
        goto next_iter;
    }
    if (func_02065ec0(ptr) == 1) {
        goto case_one;
    }

    if (flag != 0) {
        self->flags |= (1 << i);
    } else {
        func_02066650(ptr);
    }
    goto next_iter;

case_one:
    if (func_02065e9c(ptr) != 0) {
        goto next_iter;
    }
    if (func_020979ac(ptr) == 0) {
        goto result_108;
    }
    if (func_ov104_0229c7dc(self, ptr) == 0) {
        goto result_110;
    }

    if (flag != 0) {
        self->flags |= (1 << i);
    } else {
        func_02066650(ptr);
    }
    result |= 0x300;
    goto next_iter;

result_110:
    result |= 0x110;
    goto next_iter;

result_108:
    result |= 0x108;
    goto next_iter;

next_iter:
    ptr += 0x100;
    i++;
    if (i < 10) {
        goto loop_body;
    }

    return result;
}