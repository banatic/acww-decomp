/* face_anim_timer: 6 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0206463c @ 0x0206463c, 0x2 bytes, Thumb
 * func_02064638 @ 0x02064638, 0x2 bytes, Thumb
 * func_0206461c @ 0x0206461c, 0x1c bytes, Thumb
 * func_020645e0 @ 0x020645e0, 0x3c bytes, Thumb
 * func_020645d4 @ 0x020645d4, 0xa bytes, Thumb
 * func_020645bc @ 0x020645bc, 0x18 bytes, Thumb
 */

typedef struct {
    unsigned char unk_00;
    unsigned char unk_01;
} UnkStruct_020645d4;

extern unsigned int func_020e92e8(void *arg);
extern char data_021cb5a0;
extern int func_020e92d0(char *addr, int arg);

void func_0206463c(void *object) {}

void func_02064638(void *object) {}

void func_0206461c(unsigned char *arg0)
{
    arg0[1] = (unsigned char) ((func_020e92e8(&data_021cb5a0) >> 31) + 1);
}

int func_020645e0(unsigned char *p)
{
    if (p[0] != 0) {
        goto handle0;
    }
    if (p[1] != 0) {
        goto handle1;
    }
    func_0206461c(p);
    p[0] = (unsigned char) (func_020e92d0(&data_021cb5a0, 0x5a) + 0x1e);
    goto common_exit;
handle1:
    p[1]--;
    return 1;
handle0:
    p[0]--;
common_exit:
    return 0;
}

void func_020645d4(UnkStruct_020645d4 *p)
{
    p->unk_01 = 0;
    p->unk_00 = p->unk_01;
}

void func_020645bc(unsigned char *arg)
{
    arg[0] = 0;
    if (arg[1] == 0) {
        func_0206461c(arg);
    }
}
