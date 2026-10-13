/* func_02096518 @ 0x02096518, 0x74 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x68];
    int unk_68;
} UnkStruct_02096518;

typedef struct {
    char pad_00[0x7f0];
    int unk_7F0;
} UnkStruct_02096518_2;

extern UnkStruct_02096518 *data_020ccf94;
extern int func_02073908(void *p, int x);
extern void *func_02096718(int x);
extern int func_020966c4(int x);
extern void MI_CpuCopy8(int, void *, int);

int func_02096518(int *param0, int param1, int param2)
{
    unsigned char local;
    if (param2 == 4) {
        param2 = data_020ccf94->unk_68;
    }
    if (func_02073908(data_020ccf94, param2) != 0) {
        void *ptr = func_02096718(4);
        if (ptr) {
            *param0 = ((UnkStruct_02096518_2 *) ptr)->unk_7F0;
            return 1;
        } else {
            return 0;
        }
    } else {
        int val = func_020966c4(param2);
        if (val == 0) {
            return 0;
        }
        MI_CpuCopy8(val + 1, &local, 1);
        if (local == 0) {
            return 0;
        }
        *param0 = local - 1;
        return 1;
    }
}
