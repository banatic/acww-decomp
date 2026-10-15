/* func_02073de4 @ 0x02073de4, 0x4a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02073dd4(void *, int);
extern unsigned int func_020ec2d4(void);
extern unsigned int func_02073044(void);
extern int func_020ebf70(void);

typedef struct {
    char pad_00[0x64];
    int unk_64;
} UnkStruct_02073de4;

int func_02073de4(void *ptr)
{
    UnkStruct_02073de4 *self = (UnkStruct_02073de4 *) ptr;
    int r4 = self->unk_64;
    if (func_02073dd4(ptr, r4) == 0) {
        goto ret1;
    }
    if (r4 == 0) {
        if (func_020ec2d4() <= 1) {
            goto ret1;
        }
        func_02073044();
        if (func_020ebf70() != 0) {
            return 1;
        } else {
            return 0;
        }
    } else {
        func_02073044();
        if (func_020ebf70() != 0) {
            return 1;
        } else {
            return 0;
        }
    }
ret1:
    return 1;
}
