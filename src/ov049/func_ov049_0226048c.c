/* func_ov049_0226048c @ 0x0226048c, 0x74 bytes, Thumb, module ov049
 * mwccarm 1.2/base -O4,s
 */

extern int func_02073d90(void *);
extern void *data_020ccf94;
extern short *func_0209d358(int, int);
extern int *func_02095794(int);
extern int func_02030818(int *);
extern void func_ov049_0226208c(char *, int);
extern void func_0203e0a8(char *, int);
extern void func_ov049_02262a94(char *, int);

int func_ov049_0226048c(char *param)
{
    int local[3];
    if (func_02073d90(data_020ccf94) != 0 || *(short *) func_0209d358(0, 0x4a) != 0) {
        return 0;
    }
    {
        int *p = func_02095794(4);
        local[0] = p[0];
        local[1] = p[1];
        local[2] = p[2];
    }
    if (func_02030818(local) != 0) {
        func_ov049_0226208c(param + 0x658, 3);
        func_0203e0a8(param, 0);
        func_ov049_02262a94(param, 0xf);
        return 1;
    }
    return 0;
}
