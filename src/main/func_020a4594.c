/* func_020a4594 @ 0x020a4594, 0x58 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020a4594 {
    int unk_00;
    int unk_04;
};

extern struct UnkStruct_020a4594 *func_020682e0(int);
extern void func_02068320(struct UnkStruct_020a4594 *);
extern int func_020b5e10(void);
extern int func_020b63f4(int, int, int *, int, int, int, int);
extern void func_020a4e94(int, int);
extern int data_020d1c14[3];

void func_020a4594(int param)
{
    struct UnkStruct_020a4594 *p;
    int local[3];

    p = func_020682e0(0);
    if (p->unk_04 != 0) {
        return;
    }
    func_02068320(p);
    local[0] = data_020d1c14[0];
    local[1] = data_020d1c14[1];
    local[2] = data_020d1c14[2];
    func_020b63f4(func_020b5e10(), 0xe, local, 0x00800000, 0, 3, 2);
    func_020a4e94(param, 0);
}
