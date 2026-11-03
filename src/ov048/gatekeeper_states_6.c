/* gatekeeper_states_6: 2 functions, module ov048
 * mwccarm 1.2/base -O4,s
 * func_ov048_02262e94 @ 0x02262e94, 0x54 bytes, Thumb
 * func_ov048_02262e68 @ 0x02262e68, 0x2c bytes, Thumb
 */

typedef struct {
    char pad_00[0x350];
    char unk_350[0xb1c];
    short unk_E6C;
    char pad_E6E[0x3];
    char unk_E71;
} UnkStruct_02262e68;

extern void func_020a13a0(void);
extern int func_020b5e10(void);
extern int func_020b6098(int, int);
extern void func_ov048_022635f4(void *, int);
extern unsigned char data_021c75b8;
extern void func_0201aff4(void *, int);

int func_ov048_02262e94(void *r0)
{
    char *ptr;
    ptr = (char *) r0;
    if ((*((unsigned int *) (ptr + 0x654))) == 8) {
        int cond = (data_021c75b8) ? (0) : (1);
        if (cond != 0) {
            func_020a13a0();
        } else {
            return 0;
        }
        func_ov048_022635f4(r0, 3);
    } else {
        func_020b6098(func_020b5e10(), 0);
        func_ov048_022635f4(r0, 3);
    }
    return 1;
}

int func_ov048_02262e68(UnkStruct_02262e68 *obj)
{
    obj->unk_E71 = 0;
    func_0201aff4(obj->unk_350, obj->unk_E6C);
    return 1;
}
