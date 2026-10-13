/* func_0204105c @ 0x0204105c, 0x90 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020410ec(void *, void *, int);
extern int func_020644cc(int);
extern const int data_020ca4ec[7];
extern const int data_020ca4d0[7];

int func_0204105c(void *a, void *b)
{
    int arrA[7];
    int arrB[7];
    int i, total, n, r, result;

    result = 0x63;
    for (i = 0; i < 7; i++) {
        arrA[i] = 0x63;
        arrB[i] = 0;
    }
    total = 0;
    n = 0;
    for (i = 0; i < 7; i++) {
        if (func_020410ec(a, b, data_020ca4ec[i]) == 0) {
            arrA[n] = data_020ca4ec[i];
            arrB[n] = data_020ca4d0[i];
            n++;
            total += data_020ca4d0[i];
        }
    }
    if (total > 0) {
        r = func_020644cc(total);
        for (i = 0; i < n; i++) {
            r = r - arrB[i];
            if (r < 0) {
                result = arrA[i];
                break;
            }
        }
    }
    return result;
}
