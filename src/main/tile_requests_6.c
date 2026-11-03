/* tile_requests_6: 4 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02044878 @ 0x02044878, 0x24 bytes, Thumb
 * func_02044858 @ 0x02044858, 0x20 bytes, Thumb
 * func_0204482c @ 0x0204482c, 0x2c bytes, Thumb
 * func_02044808 @ 0x02044808, 0x24 bytes, Thumb
 */

struct UnkStruct_02044878 {
    char pad_00[0x68];
    int unk_68;
};

extern struct UnkStruct_02044878 *data_020ccf94;
extern int func_02073d90(int);
extern int func_02073918(int a, int b);
extern int func_020984fc(void *);
extern int func_02099728(unsigned int);

int func_02044878(int param)
{
    struct UnkStruct_02044878 *s;

    s = data_020ccf94;
    if (func_02073d90((int) s) != 0) {
        return param;
    } else {
        return s->unk_68;
    }
}

int func_02044858(int arg0)
{
    int r4;
    int result;

    r4 = arg0;
    result = func_02073d90(*(unsigned int *) ((unsigned int *) &data_020ccf94));
    if (result == 0) {
        r4 = 0;
    }
    return r4;
}

int func_0204482c(int param)
{
    int a = (*(int *) &data_020ccf94);
    if (func_02073d90(a) == 0) {
        return 1;
    } else {
        return func_02073918(a, param);
    }
}

int func_02044808(void *argument0)
{
    int r4;
    int r0;

    r4 = 0x0000fff1;
    r0 = func_020984fc((void *) argument0);
    if (r0 != 0) {
        r0 = func_02099728(r0);
        if (r0 != 0) {
            r4 = *(unsigned short *) r0;
        }
    }
    return r4;
}
