/* func_020783e0 @ 0x020783e0, 0x68 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *data_020ccf94;
extern int func_02073d90(void *);
extern void func_02078460(int *, void *, unsigned short *);
extern void func_02073820(void *);
extern void func_020737f0(void *, int *, int);
extern void func_02073770(void *, int, int);

void func_020783e0(void *a, unsigned short *b)
{
    if (func_02073d90(data_020ccf94) != 0) {
        int flag = (*b >= 0x11a8) && (*b <= 0x12a7);
        if (flag) {
            int local;
            func_02078460(&local, a, b);
            {
                void *obj = data_020ccf94;
                func_02073820(obj);
                func_020737f0(obj, &local, 3);
                func_02073770(obj, 0x3a, 4);
            }
        }
    }
}
