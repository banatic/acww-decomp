/* unit_type_info_2: 10 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02031ba0 @ 0x02031ba0, 0x18 bytes, Thumb
 * func_02031b84 @ 0x02031b84, 0x1c bytes, Thumb
 * func_02031b5c @ 0x02031b5c, 0x28 bytes, Thumb
 * func_02031b38 @ 0x02031b38, 0x24 bytes, Thumb
 * func_02031b14 @ 0x02031b14, 0x24 bytes, Thumb
 * func_02031af0 @ 0x02031af0, 0x24 bytes, Thumb
 * func_02031acc @ 0x02031acc, 0x24 bytes, Thumb
 * func_02031aa0 @ 0x02031aa0, 0x2c bytes, Thumb
 * func_02031a74 @ 0x02031a74, 0x2c bytes, Thumb
 * func_02031a48 @ 0x02031a48, 0x2a bytes, Thumb
 */

typedef struct {
    short value;
    char pad_02[28];
} Entry_020c9082;

extern int func_01ffcb2c(int, int);
extern unsigned char data_020c9080[];
extern unsigned char data_020c9084[];
extern unsigned char data_020c9081[];
extern unsigned char data_020c9085[];
extern Entry_020c9082 data_020c9082[];
extern unsigned char data_020c9093[];

int func_02031ba0(int argument0, int argument1)
{
    if (func_01ffcb2c((int) argument0, (int) argument1) == 7) {
        return 1;
    } else {
        return 0;
    }
}

int func_02031b84(int result, int value)
{

    value = func_01ffcb2c(result, value);
    if (value == 3 || value == 0x1d) {
        result = 1;
    } else {
        result = 0;
    }
    return result;
}

int func_02031b5c(int argument0, int argument1)
{
    int x;
    x = func_01ffcb2c((int) argument0, (int) argument1);
    if (x == 8) {
        return 1;
    }
    if (x == 7 || (x >= 11 && x <= 18)) {
        return 2;
    }
    return 0;
}

unsigned char func_02031b38(int argument0, int argument1)
{
    int idx;

    idx = func_01ffcb2c((int) argument0, (int) argument1);
    if (idx < 124) {
        return data_020c9080[idx * 30];
    } else {
        return 0;
    }
}

int func_02031b14(int result, int index)
{

    index = func_01ffcb2c(result, index);
    if (index < 0x7c) {
        result = data_020c9084[index * 30];
    } else {
        result = 0;
    }
    return result;
}

int func_02031af0(int r0, int r1)
{

    r0 = func_01ffcb2c(r0, r1);
    if (r0 < 0x7c) {
        r1 = 0x1e;
        r0 = r0 * r1;
        return data_020c9081[r0];
    } else {
        return 0;
    }
}

unsigned char func_02031acc(int argument0, int argument1)
{
    int result;

    result = func_01ffcb2c((int) argument0, (int) argument1);
    if (result < 124) {
        return data_020c9085[result * 30];
    } else {
        return 2;
    }
}

int func_02031aa0(int param, int row)
{
    int idx;
    short s;
    int result;

    idx = func_01ffcb2c(param, row);
    if (idx < 0x7c) {
        s = data_020c9082[idx].value;
        if (s > 0) {
            result = 1;
        } else {
            result = s;
        }
    } else {
        result = -1;
    }
    return result;
}

int func_02031a74(int result, int value)
{

    value = func_01ffcb2c(result, value);
    if (value < 0x7c) {
        result = data_020c9093[value * 30];
    } else {
        result = 0;
    }

    if (result != 0) {
        return 1;
    } else {
        return 0;
    }
}

int func_02031a48(int a, int b)
{
    if (func_01ffcb2c(a, b) == 30 && func_01ffcb2c(a, b + 1) == 8) {
        return 1;
    }
    return 0;
}
