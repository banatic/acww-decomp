/* func_02060cbc @ 0x02060cbc, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x15a0];
    unsigned int : 3;
    unsigned int value : 3;
} UnkStruct_02060cbc;

extern int func_02060e78(UnkStruct_02060cbc *);
extern int func_02060d3c(UnkStruct_02060cbc *);
extern int func_0209f150(void *, int);

extern unsigned char data_021dc7a8[];

int func_02060cbc(UnkStruct_02060cbc *arg)
{
    int ret;
    ret = func_02060e78(arg);
    if (arg->value != ret) {
        goto ret_zero;
    }
    if (func_02060d3c(arg) != 0) {
        goto ret_zero;
    }
    return func_0209f150((void *) data_021dc7a8, 13);
ret_zero:
    return 0;
}
