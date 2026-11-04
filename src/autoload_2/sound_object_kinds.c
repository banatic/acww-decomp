/* sound_object_kinds: 15 functions, module autoload_2
 * mwccarm 1.2/base -O4,s
 * func_020f7bb0 @ 0x020f7bb0, 0x14 bytes, ARM
 * func_020f7b98 @ 0x020f7b98, 0x18 bytes, ARM
 * func_020f7b7c @ 0x020f7b7c, 0x1c bytes, ARM
 * func_020f7b64 @ 0x020f7b64, 0x18 bytes, ARM
 * func_020f78e8 @ 0x020f78e8, 0x27c bytes, ARM
 * func_020f78c4 @ 0x020f78c4, 0x24 bytes, ARM
 * func_020f7780 @ 0x020f7780, 0x144 bytes, ARM
 * func_020f7774 @ 0x020f7774, 0xc bytes, ARM
 * func_020f746c @ 0x020f746c, 0x308 bytes, ARM
 * func_020f7438 @ 0x020f7438, 0x34 bytes, ARM
 * func_020f72b8 @ 0x020f72b8, 0x180 bytes, ARM
 * func_020f726c @ 0x020f726c, 0x4c bytes, ARM
 * func_020f7218 @ 0x020f7218, 0x54 bytes, ARM
 * func_020f70ec @ 0x020f70ec, 0x12c bytes, ARM
 * func_020f70e8 @ 0x020f70e8, 0x4 bytes, ARM
 */

typedef struct UnkStruct_020f78e8 {
    int unk_00;
    int unk_04;
    int unk_08;
    signed char c;
    signed char d;
} UnkStruct_020f78e8;

typedef struct UnkStruct_020f7780 {
    char pad_00[8];
    char h;
    char pad_09[0xd - 8 - 1];
    signed char d;
} UnkStruct_020f7780;

typedef struct {
    int unk_00;
    void *unk_04;
    void *unk_08;
    char unk_0C;
    signed char d;
} UnkStruct_020f746c;

typedef struct {
    unsigned int pad_00;
    unsigned int unk_04;
    unsigned int unk_08;
} Snd;

struct UnkStruct_020f726c {
    unsigned char pad_00[4];
    unsigned char data[9];
    unsigned char d;
    unsigned char e;
    unsigned char unk_0F;
};

typedef struct {
    char pad_00[4];
    char unk_04[10];
    unsigned char unk_0E;
} UnkStruct_020f7218;

typedef struct UnkStruct_020f70ec {
    unsigned char pad_00[8];
    unsigned char unk_08[5];
    unsigned char unk_0D;
    unsigned char unk_0E;
    unsigned char unk_0F;
} UnkStruct_020f70ec;

extern int func_020f7bc4(void *receiver, int sequence, void *handle);
extern void func_020f7d4c(void *unused0);
extern void func_020f7c1c(UnkStruct_020f78e8 *obj, int arg);
extern void NNS_SndPlayerMoveVolume(int *slot, int a, int b);
extern int NNS_SndPlayerWriteVariable(int *slot, int a, int b);
extern void NNS_SndPlayerStopSeq(int *slot, int a);
extern void NNS_SndPlayerSetTrackVolume(int *slot, int a, int b);
extern char data_021fd1bc[];
extern int func_020f1d3c(void *address, int arg);
extern int NNS_SndArcPlayerStartSeq(void *address, unsigned short val);

unsigned int func_020f7bb0(unsigned int a)
{
    return (unsigned int) func_020f7bc4((void *) a, 0x4f0, (void *) (a + 4));
}

void func_020f7b98(char *self)
{
    func_020f7bc4(self, 0x4f1, self + 4);
}

void func_020f7b7c(char *r4)
{
    func_020f7d4c(r4);
    r4[0xd] = (char) 0xff;
}

void func_020f7b64(void *a)
{
    func_020f7bc4(a, 0x4f2, (char *) a + 8);
}

void func_020f78e8(UnkStruct_020f78e8 *obj, int key, int arg)
{
    unsigned int ok;

    switch (key) {
        case 1:
            ok = (unsigned int) (obj->unk_08 != 0);
            if (ok == 0) {
                func_020f7bc4((void *) obj, 0x4f2, (void *) (&obj->unk_08));
            }
            obj->d = (signed char) (obj->d + 1);
            if (obj->d == 3) {
                obj->d = 0;
            }
            switch (obj->d) {
                case 0:
                    func_020f7bc4((void *) obj, 0x4f6, (void *) (&obj->unk_04));
                    break;
                case 1:
                    NNS_SndArcPlayerStartSeq((void *) (&obj->unk_04), 0xf7);
                    break;
                case 2:
                    NNS_SndPlayerMoveVolume(&obj->unk_04, 0x28, 0xf);
                    break;
            }
            break;
        case 0x28:
            NNS_SndPlayerWriteVariable(&obj->unk_04, 1, 1);
            break;
        case 0x32:
            NNS_SndPlayerWriteVariable(&obj->unk_04, 0, 2);
            break;
        case 0x96:
            func_020f7bc4((void *) obj, 0x4f3, (void *) (&obj->unk_08));
            NNS_SndPlayerWriteVariable(&obj->unk_04, 0, 0);
            break;
        case 0xc8:
            func_020f7bc4((void *) obj, 0x4f4, (void *) (&obj->unk_08));
            NNS_SndPlayerWriteVariable(&obj->unk_04, 1, 2);
            break;
        case 0x12c:
            NNS_SndPlayerWriteVariable(&obj->unk_04, 0, 3);
            break;
        case 0x177:
            func_020f7bc4((void *) obj, 0x4f5, (void *) (&obj->unk_08));
            break;
        case 0x181:
            if (obj->d == 2) {
                NNS_SndPlayerStopSeq(&obj->unk_04, 0xf);
            }
            break;
    }

    switch (obj->d) {
        case 0:
            NNS_SndPlayerSetTrackVolume(&obj->unk_04, 0xfff, 0x7f);
            NNS_SndPlayerSetTrackVolume(&obj->unk_08, 0xfff, 0x7f);
            break;
        case 1:
            NNS_SndPlayerSetTrackVolume(&obj->unk_04, 0xfff, 0x64);
            NNS_SndPlayerSetTrackVolume(&obj->unk_08, 0xfff, 0);
            break;
        case 2:
            NNS_SndPlayerSetTrackVolume(&obj->unk_08, 0xfff, 0x64);
            break;
    }

    func_020f7c1c(obj, arg);
}

void func_020f78c4(void *self)
{
    NNS_SndArcPlayerStartSeq((char *) self + 4, 0xac);
    ((char *) self)[0xd] = 0;
}

void func_020f7780(UnkStruct_020f7780 *self, int msgId, void *p3)
{
    switch (msgId) {
        case 1:
            if (self->d == 0) {
                func_020f7bc4((void *) self, 0x4f7, &self->h);
            }
            break;
        case 0x78:
            if (self->d == 1) {
                func_020f7bc4((void *) self, 0x4f8, &self->h);
            }
            break;
        case 0xbe:
            if (self->d == 0) {
                func_020f7bc4((void *) self, 0x4f9, &self->h);
            }
            break;
        case 0xd2:
            if (self->d == 1) {
                func_020f7bc4((void *) self, 0x4fb, &self->h);
            }
            break;
        case 0x12c:
            if (self->d == 0) {
                func_020f7bc4((void *) self, 0x4fa, &self->h);
            }
            break;
        case 0x15d:
            self->d++;
            if (self->d == 2) {
                self->d = 0;
            }
            break;
    }
    func_020f7c1c((UnkStruct_020f78e8 *) self, (int) p3);
}

void func_020f7774(unsigned char *p)
{
    p[0xd] = 0;
}

void func_020f746c(UnkStruct_020f746c *p, int code, void *q)
{
    switch (code) {
        case 1:
            if (p->d == 0) {
                func_020f7bc4(p, 0x4fc, &p->unk_04);
            } else {
                func_020f7bc4(p, 0x4fd, &p->unk_04);
            }
            {
                unsigned int ok = (unsigned int) (p->unk_08 != 0);
                if (ok > 0) {
                    break;
                }
            }
            func_020f7bc4(p, 0x500, &p->unk_08);
            break;
        case 0x46:
            NNS_SndPlayerWriteVariable((int *) (&p->unk_08), 1, 1);
            break;
        case 0xd2:
            NNS_SndPlayerWriteVariable((int *) (&p->unk_08), 2, 1);
            break;
        case 0xdc:
            NNS_SndPlayerWriteVariable((int *) (&p->unk_08), 1, 0);
            break;
        case 0xe6:
            if (p->d == 0) {
                func_020f7bc4(p, 0x4fe, &p->unk_04);
            } else {
                func_020f7bc4(p, 0x4ff, &p->unk_04);
            }
            break;
        case 0xfd:
            if (p->d == 1) {
                NNS_SndPlayerWriteVariable((int *) (&p->unk_08), 2, 2);
            }
            break;
        case 0x102:
            if (p->d == 0) {
                NNS_SndPlayerWriteVariable((int *) (&p->unk_08), 2, 2);
            }
            break;
        case 0x118:
            NNS_SndPlayerWriteVariable((int *) (&p->unk_08), 1, 1);
            break;
        case 0x172:
            NNS_SndPlayerWriteVariable((int *) (&p->unk_08), 1, 0);
            NNS_SndPlayerWriteVariable((int *) (&p->unk_08), 2, 1);
            break;
        case 0x17f:
            if (p->d == 1) {
                NNS_SndPlayerWriteVariable((int *) (&p->unk_04), 0, 2);
            }
            break;
        case 0x186:
            if (p->d == 0) {
                NNS_SndPlayerWriteVariable((int *) (&p->unk_04), 0, 2);
            }
            break;
        case 0x195:
            if (p->d == 1) {
                NNS_SndPlayerWriteVariable((int *) (&p->unk_08), 2, 3);
            }
            break;
        case 0x1a9:
            if (p->d == 0) {
                NNS_SndPlayerWriteVariable((int *) (&p->unk_08), 2, 3);
            }
            break;
        case 0x1df:
            p->d = (signed char) (p->d + 1);
            if (p->d == 2) {
                p->d = 0;
            }
            break;
    }
    func_020f7c1c((UnkStruct_020f78e8 *) p, (int) q);
}

void func_020f7438(void *param1)
{
    func_020f7bc4(param1, 0x501, (void *) ((char *) param1 + 4));
    func_020f7bc4(param1, 0x502, (void *) ((char *) param1 + 8));
}

void func_020f72b8(Snd *p, int cmd, int arg)
{
    switch (cmd) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4: {
            unsigned int flag4;
            unsigned int flag8;

            flag4 = (p->unk_04 != 0) ? 1 : 0;
            if (flag4 == 0) {
                func_020f7bc4((void *) p, 0x501, (void *) (&p->unk_04));
            }

            flag8 = (p->unk_08 != 0) ? 1 : 0;
            if (flag8 == 0) {
                func_020f7bc4((void *) p, 0x502, (void *) (&p->unk_08));
            }

            NNS_SndPlayerWriteVariable((int *) (&p->unk_04), 0, 1);
            NNS_SndPlayerWriteVariable((int *) (&p->unk_08), 0, 1);
            break;
        }
        case 0x5a:
            NNS_SndPlayerWriteVariable((int *) (&p->unk_04), 0, 2);
            NNS_SndPlayerWriteVariable((int *) (&p->unk_08), 0, 2);
            break;
        case 0x8c:
            NNS_SndPlayerWriteVariable((int *) (&p->unk_04), 0, 3);
            break;
        case 0xe1:
            NNS_SndPlayerWriteVariable((int *) (&p->unk_04), 0, 4);
            break;
        case 0xeb:
            NNS_SndPlayerWriteVariable((int *) (&p->unk_04), 0, 5);
            break;
        case 0xf5:
            NNS_SndPlayerWriteVariable((int *) (&p->unk_08), 0, 3);
            break;
    }

    func_020f7c1c((UnkStruct_020f78e8 *) p, arg);
}

void func_020f726c(struct UnkStruct_020f726c *s)
{
    s->d = 0;
    s->e = (unsigned char) func_020f1d3c(data_021fd1bc, 3);
    s->unk_0F = 0;
    NNS_SndArcPlayerStartSeq(s->data, (unsigned short) (s->e + 0xad));
}

void func_020f7218(UnkStruct_020f7218 *p)
{
    int n = 3;
    int v;
    do {
        v = func_020f1d3c(((int *) data_021fd1bc), n);
    } while ((v & 0xff) == p->unk_0E);
    p->unk_0E = v & 0xff;
    NNS_SndArcPlayerStartSeq(&p->unk_04, (unsigned short) (p->unk_0E + 0xad));
}

void func_020f70ec(UnkStruct_020f70ec *self, int msg, void *arg)
{
    switch (msg) {
        case 10:
            switch (self->unk_0F) {
                case 0:
                    func_020f7bc4((void *) self, 0x503, (void *) self->unk_08);
                    break;
                case 1:
                    func_020f7bc4((void *) self, 0x505, (void *) self->unk_08);
                    break;
            }
            break;
        case 0x82:
            if (self->unk_0F == 0) {
                func_020f7bc4((void *) self, 0x504, (void *) self->unk_08);
            }
            break;
        case 0x96:
            if (self->unk_0F == 1) {
                func_020f7bc4((void *) self, 0x506, (void *) self->unk_08);
            }
            break;
        case 0x18f:
            self->unk_0D++;
            if (self->unk_0D == 7) {
                self->unk_0D = 0;
                func_020f7218((UnkStruct_020f7218 *) self);
            }
            self->unk_0F++;
            if (self->unk_0F == 3) {
                self->unk_0F = 0;
            }
            break;
    }
    func_020f7c1c((UnkStruct_020f78e8 *) self, (int) arg);
}

void func_020f70e8(void) {}
