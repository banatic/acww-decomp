/* func_ov048_02262c8c @ 0x02262c8c, 0x32 bytes, Thumb, module ov048
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int unk_00;
    int unk_04;
} UnkStruct_02262c8c;
extern UnkStruct_02262c8c *func_020682e0(int);
extern int func_020a1380(void);
extern void func_020b8dc0(void);
extern void func_02068320(UnkStruct_02262c8c *);

int func_ov048_02262c8c(void)
{
    UnkStruct_02262c8c *t = func_020682e0(0);
    if (t->unk_04 == 0) {
        if (func_020a1380() == 0) {
            func_020b8dc0();
            return 0;
        }
        func_02068320(t);
        return 1;
    }
    return 0;
}
