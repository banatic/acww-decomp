/* activity_jobs: 8 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020a43e0 @ 0x020a43e0, 0x2 bytes, Thumb
 * func_020a43a0 @ 0x020a43a0, 0x40 bytes, Thumb
 * func_020a439c @ 0x020a439c, 0x2 bytes, Thumb
 * func_020a4370 @ 0x020a4370, 0x2c bytes, Thumb
 * func_020a4368 @ 0x020a4368, 0x8 bytes, Thumb
 * func_020a42d4 @ 0x020a42d4, 0x94 bytes, Thumb
 * func_020a42b8 @ 0x020a42b8, 0x1a bytes, Thumb
 * func_020a4224 @ 0x020a4224, 0x94 bytes, Thumb
 */

struct UnkStruct_020a43a0 {
    int unk_00;
    int unk_04;
};

typedef struct {
    int pad_00;
    int unk_04;
} UnkStruct_020a4370;

typedef struct {
    unsigned char pad_00[0xa1];
    unsigned char state;
    unsigned char pad_A2[0x6c];
    unsigned char unk_10E;
} StateStruct;

struct UnkStruct_020a42b8 {
    unsigned char pad_00[0xa1];
    unsigned char unk_A1;
};

extern struct UnkStruct_020a43a0 *func_020682e0(int);
extern void func_02068320(struct UnkStruct_020a43a0 *);
extern int func_020b65c4(void);
extern int func_020b5e10(void);
extern int func_020b6098(int, int);
extern void func_020a4e94(int, int);
extern int func_020a238c(void *);
extern int func_020a2120(void *, int);
extern int func_020984e8(void);
extern void func_02098fd0(int a, int b);

void func_020a43e0(void) {}

void func_020a43a0(int arg0)
{
    struct UnkStruct_020a43a0 *p = func_020682e0(0);
    if (p->unk_04 != 0) {
        return;
    }
    if ((((int) (func_02068320(p), p)), func_020b65c4()) == 6) {
        func_020b6098(func_020b5e10(), 2);
    } else {
        func_020b6098(func_020b5e10(), 0);
    }
    func_020a4e94(arg0, 0);
}

void func_020a439c(void) {}

void func_020a4370(int arg)
{
    UnkStruct_020a4370 *p = (UnkStruct_020a4370 *) func_020682e0(0);
    if (p->unk_04 == 0) {
        func_020b6098((((int) (func_02068320((struct UnkStruct_020a43a0 *) p), p)), func_020b5e10()), 2);
        func_020a4e94(arg, 0);
    }
}

void func_020a4368(int p0)
{
    *(unsigned char *) ((char *) (((int) (p0) + (161))) + (0)) = 0;
}

void func_020a42d4(StateStruct *self)
{
    switch (self->state) {
        case 0: {
            int r = func_020a238c(self);
            if (r == 1) {
                self->state = 3;
                break;
            }
            if (r == 3) {
                return;
            }
            self->state = 1;
            break;
        }
        case 1: {
            int r = func_020a2120(self, ((unsigned int) self->unk_10E << 24) >> 28);
            if (r == 1) {
                self->state = 3;
                break;
            }
            if (r == 0) {
                self->state = 2;
                break;
            }
            return;
        }
        case 2: {
            int r = func_020a2120(self, 2);
            if (r == 1) {
                self->state = 3;
                break;
            }
            if (r == 0) {
                self->state = 4;
                break;
            }
            return;
        }
        case 3:
            break;
        default:
            func_020a4e94((int) self, 0);
            break;
    }
}

void func_020a42b8(struct UnkStruct_020a42b8 *p)
{
    func_02098fd0(func_020984e8(), 2);
    p->unk_A1 = 0;
}

void func_020a4224(StateStruct *self)
{
    switch (self->state) {
        case 0: {
            int r = func_020a238c(self);
            if (r == 1) {
                self->state = 3;
                break;
            }
            if (r == 3) {
                return;
            }
            self->state = 1;
            break;
        }
        case 1: {
            int r = func_020a2120(self, ((unsigned int) self->unk_10E << 24) >> 28);
            if (r == 1) {
                self->state = 3;
                break;
            }
            if (r == 0) {
                self->state = 2;
                break;
            }
            return;
        }
        case 2: {
            int r = func_020a2120(self, 2);
            if (r == 1) {
                self->state = 3;
                break;
            }
            if (r == 0) {
                self->state = 4;
                break;
            }
            return;
        }
        case 3:
            break;
        default:
            func_020a4e94((int) self, 0);
            break;
    }
}
