/* func_0207e978 @ 0x0207e978, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0207e978 {
    unsigned short first;
    unsigned short pad_02;
    unsigned int other;
};

extern struct UnkStruct_0207e978 *func_020996f8(void);
extern int func_0204bcdc(struct UnkStruct_0207e978 *);
extern int func_0204bc64(struct UnkStruct_0207e978 *);

int func_0207e978(void)
{
    struct UnkStruct_0207e978 *p;

    p = func_020996f8();
    if (func_0204bcdc(p) != 0) {
        struct UnkStruct_0207e978 local;
        local.first = 0x13e6;
        if (func_0204bc64(p) != func_0204bc64(&local)) {
            return 0;
        } else {
            return 1;
        }
    } else {
        if (p->first == 0x13e6) {
            return 1;
        } else {
            return 0;
        }
    }
}
