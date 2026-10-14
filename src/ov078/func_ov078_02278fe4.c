/* func_ov078_02278fe4 @ 0x02278fe4, 0x2c bytes, Thumb, module ov078
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_ov078_02279a9c[];
extern void func_0202eb20(void *);
extern void func_020051b0(void);
extern void __cxa_vec_cleanup(void *, int, int, void (*)(void));

typedef struct {
    unsigned char *unk_00;
    unsigned char pad_04[0xb4];
    unsigned char sub[1];
} UnkStruct_02278fe4;

UnkStruct_02278fe4 *func_ov078_02278fe4(UnkStruct_02278fe4 *p)
{
    int n = 2;
    p->unk_00 = data_ov078_02279a9c;
    __cxa_vec_cleanup(p->sub, n, n, func_020051b0);
    func_0202eb20(p);
    return p;
}
