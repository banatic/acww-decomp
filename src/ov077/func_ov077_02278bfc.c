/* func_ov077_02278bfc @ 0x02278bfc, 0x54 bytes, Thumb, module ov077
 * mwccarm 1.2/base -O4,s
 */

extern int func_020984e8(void);
extern int func_02099670(int);
extern int func_02088b7c(unsigned char *);
extern int func_020644cc(int);
extern unsigned char data_ov077_02279600[];
extern int data_ov077_02279700;

struct UnkStruct_02278bfc {
    int unk_00;
    unsigned char unk_04;
};

void func_ov077_02278bfc(int a, struct UnkStruct_02278bfc *out)
{
    int var;

    var = func_02088b7c((unsigned char *) func_02099670((int) func_020984e8())) - 1;
    if (var < 0) {
        var = 0;
    } else if (var > 5) {
        var = 5;
    }
    if (var == 5) {
        var = func_020644cc(4) + 1;
    }
    if (var < 0) {
        var = 0;
    } else if (var > 4) {
        var = 4;
    }
    out->unk_04 = data_ov077_02279600[var];
    out->unk_00 = data_ov077_02279700;
}
