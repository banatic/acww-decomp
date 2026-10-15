/* func_020509a8 @ 0x020509a8, 0x68 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020509a8 {
    unsigned int unk_00;
    int unk_04;
};

extern int OS_GetLockID(void);
extern void func_0211ec44(unsigned short);
extern int CARDi_RequestStreamCommand(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int,
                                      unsigned int, unsigned int, unsigned int);
extern int func_02050974(struct UnkStruct_020509a8 *);
extern void func_02050948(struct UnkStruct_020509a8 *);

int func_020509a8(struct UnkStruct_020509a8 *p, unsigned b, unsigned c, unsigned d)
{
    int ret = 1;
    if (d + c > p->unk_00) {
        goto end;
    }
    p->unk_04 = OS_GetLockID();
    if (p->unk_04 == -3) {
        goto end;
    }
    func_0211ec44((unsigned short) p->unk_04);
    CARDi_RequestStreamCommand(d, b, c, 0, 0, ret, 6, ret, 0);
    if (func_02050974(p) == 3) {
        ret = 3;
    } else {
        func_02050948(p);
    }
end:
    return ret;
}
