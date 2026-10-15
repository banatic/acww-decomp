/* func_0204cafc @ 0x0204cafc, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x58];
    void *array[1];
} UnkStruct_0204cafc;

extern int func_020984d4(void);
extern void func_0209df64(void *);
extern int func_0209dcdc(void *, void *);

int func_0204cafc(UnkStruct_0204cafc *param)
{
    int ret = 0;
    int idx;
    struct {
        int a, b;
    } obj;

    idx = func_020984d4();
    func_0209df64(&obj);
    if (func_0209dcdc(&obj, &param->array[idx]) != 0) {
        ret = 1;
    }
    return ret;
}
