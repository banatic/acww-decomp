/* func_ov068_0226d01c @ 0x0226d01c, 0x64 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */
typedef struct {
    char pad_00[0xa08];
    unsigned char unk_A08;
} UnkStruct_0226d01c;
extern void func_0209e474(unsigned char *p);
extern int func_0203dff0(void);
extern int func_ov068_0226d20c(UnkStruct_0226d01c *p);
extern int func_0201cddc(UnkStruct_0226d01c *p);
extern void func_ov068_0226d080(UnkStruct_0226d01c *p, unsigned char *l);
extern void func_ov068_0226d14c(UnkStruct_0226d01c *p, unsigned char *l);
void func_ov068_0226d01c(UnkStruct_0226d01c *param)
{
    union {
        unsigned char b[8];
        unsigned int w[2];
    } local;
    local.w[0] = 0;
    local.w[1] = 0;
    func_0209e474(local.b);
    if (param->unk_A08 != local.b[1]) {
        if (func_0203dff0() == 0) {
            if (func_ov068_0226d20c(param) != 0) {
                switch (func_0201cddc(param)) {
                    case 4:
                        func_ov068_0226d14c(param, local.b);
                        break;
                    case 3:
                        func_ov068_0226d080(param, local.b);
                        break;
                }
            }
        }
        param->unk_A08 = local.b[1];
    }
}
