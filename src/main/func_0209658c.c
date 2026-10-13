/* func_0209658c @ 0x0209658c, 0x88 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02073908(void *ptr, int val);
extern void *func_02096718(int val);
extern int func_020966c4(int val);
extern int func_02096518(int *a, int b, int c);
extern int func_020966e0(int val);
extern int func_020778f8(void);

struct GStruct_020ccf94 {
    char pad_00[0x68];
    int unk_68;
};
extern struct GStruct_020ccf94 *data_020ccf94;

int func_0209658c(short *out, int p1, int p2)
{
    int r4 = p2;

    if (r4 == 4) {
        r4 = data_020ccf94->unk_68;
    }

    if (func_02073908(data_020ccf94, r4) != 0) {
        void *p = func_02096718(4);
        if (p != 0) {
            *out = (short) (*(short *) ((char *) p + 0x8e));
            return 1;
        } else {
            return 0;
        }
    } else {
        int local;
        if (func_020966c4(r4) == 0) {
            return 0;
        }
        if (func_02096518(&local, p1, r4) == 0) {
            return 0;
        }
        if (local >= 0x93) {
            return 0;
        }
        if (func_020966e0(r4) == 0) {
            return 0;
        }
        *out = (short) func_020778f8();
        return 1;
    }
}
