/* func_0205e708 @ 0x0205e708, 0x134 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0205e848(int);
extern int func_0205e860(int);
extern int func_0205e86c(int);
extern int func_0205e854(int);
extern int func_0205e83c(int);
extern int func_020624d4(unsigned short *);
extern int func_0204be38(unsigned short *);
extern int func_0204bff4(unsigned short *);

void func_0205e708(int arg1, int value, unsigned short *data, int *out_value, int *out_result)
{
    int result = 0x9e;
    int flag = 0;
    unsigned short v = *data;
    int idx;

    if (v >= 0x13a8 && v <= 0x13c7) {
        flag = 1;
    }

    if (flag) {
        idx = (v >= 0x13a8 && v <= 0x13c7) ? v - 0x13a8 : -1;
        if (idx >= 0 && (unsigned) idx < 0x20) {
            value = func_0205e848(idx);
        } else {
            value = func_0205e848(0);
        }
    } else {
        if (((v >= 0x13c8 && v <= 0x1407) || (v >= 0x1429 && v <= 0x1430)) && func_020624d4(data) == 0) {
            value = func_0205e860(value);
        } else {
            value = func_0205e86c(value);
        }
    }

    flag = 0;
    v = *data;
    if (v >= 0x1429 && v <= 0x1430) {
        flag = 1;
    }

    if (flag) {
        result = (arg1 == 0) ? 0x80 : 0x81;
    } else {
        if (v >= 0x13c8 && v <= 0x1407) {
            idx = (v >= 0x13c8 && v <= 0x1407) ? v - 0x13c8 : -1;
            if (idx >= 0 && (unsigned) idx < 0x48) {
                result = func_0205e854(idx);
            }
        } else if (v >= 0x1408 && v <= 0x1428) {
            if (func_0204be38(data) != 0) {
                int res = func_0204bff4(data);
                if (res >= 0 && (unsigned) res < 0x16) {
                    result = func_0205e83c(res);
                    if (result == 0x9c) {
                        result = 0x9d;
                    }
                }
            }
        }
    }

    *out_value = value;
    *out_result = result;
}
