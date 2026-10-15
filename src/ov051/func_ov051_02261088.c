/* func_ov051_02261088 @ 0x02261088, 0x48 bytes, Thumb, module ov051
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int pad_00;
    int unk_04;
} UnkStruct_02261088;

extern UnkStruct_02261088 *func_020682e0(int);
extern int func_020644cc(int);
extern int func_ov068_02273030(void);
extern void func_0203ac18(void);
extern int func_02041d14(int, int);
extern void func_0200468c(void);
extern void func_ov051_0226122c(void *, int);

int func_ov051_02261088(void *param)
{
    if (func_020682e0(0)->unk_04 == 0) {
        if (func_020644cc(4) == 0) {
            func_ov068_02273030();
            func_0203ac18();
            ((char *) param)[0x71a] = 0xa;
        }
        func_02041d14(0, 0xf);
        func_0200468c();
        func_ov051_0226122c(param, 3);
    }
    return 1;
}
