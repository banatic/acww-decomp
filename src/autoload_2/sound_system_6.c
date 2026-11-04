/* sound_system_6: 4 functions, module autoload_2
 * mwccarm 1.2/base -O4,p
 * func_020f1520 @ 0x020f1520, 0xfc bytes, ARM
 * func_020f13bc @ 0x020f13bc, 0x164 bytes, ARM
 * func_020f12cc @ 0x020f12cc, 0xf0 bytes, ARM
 * func_020f11d0 @ 0x020f11d0, 0xfc bytes, ARM
 */

#include "types.h"

struct UnkStruct_020f1520_2 {
    u8 pad_00[2];
    u16 flag;
};

typedef struct {
    u32 unk_00;
    struct UnkStruct_020f1520_2 sub;
    u8 pad_08[0x2c - 0x8];
    void *ptr;
    u8 pad_30[0x3c - 0x30];
    u8 sound[0x64 - 0x3c];
    u16 unk_64;
    u8 pad_66[0x6c - 0x66];
    s16 unk_6C;
    u16 unk_6E;
} UnkStruct_020f1520;

struct UnkStruct_020f13bc {
    u32 unk_00;
    u8 unk_04[2];
    unsigned short unk_06;
    u8 pad_08[8]; // 0x08..0x10
    u8 unk_10[2];
    unsigned short unk_12;
    u8 pad_14[8]; // 0x14..0x1c
    u8 unk_1C[2];
    unsigned short unk_1E;
    u8 pad_20[12]; // 0x20..0x2c
    void *unk_2C;  // 0x2c
    u8 pad_30[4];  // 0x30..0x34
    u8 unk_34[52]; // 0x34..0x68
    u32 unk_68;
};

typedef struct {
    unsigned char pad_00[0x38];
    void *h1;                   // 0x38
    unsigned char pad_3C[4];    // 0x3c-0x40
    void *h2;                   // 0x40
    unsigned char pad_44[0x2c]; // 0x44-0x70
    unsigned char unk_70;       // 0x70
} UnkStruct_020f12cc;

typedef struct {
    unsigned char pad_00[0x3a];
    unsigned short itemId;
} Handle;

extern int func_020f0d50(void *sub);
extern void func_020f0ddc(void *sub, int a);
extern void func_020f0d98(void *sub, int a, int b);
extern void NNS_SndPlayerSetTrackVolume(void *player, int track, int volume);
extern void func_020f1158(void *, int);
extern unsigned int NNS_SndArcStrmGetCurrentPlayingPos(void *);
extern void func_0210b634(void *a, int b, int c);
extern void NNS_SndPlayerSetPlayerVolume(int player, int volume);

void func_020f11d0(unsigned char *self, int volL, int volR);

void func_020f1520(UnkStruct_020f1520 *self)
{
    void *ptr;
    signed char c;
    s16 s;
    int vol;

    ptr = self->ptr;
    if (ptr == 0) {
        return;
    }
    c = *(signed char *) ((u8 *) ptr + 4);

    if (c >= 0x28 && c < 0x32) {
        if (self->sub.flag != 0) {
            vol = func_020f0d50(&self->sub);
            NNS_SndPlayerSetTrackVolume(self->sound, self->unk_64, vol);
        }
    }

    if (c == 1 || c == 3) {
        s = self->unk_6C;
        if (s > 0) {
            self->unk_6C = s - 1;
        } else if (s == 0) {
            func_020f0ddc(&self->sub, 0);
            func_020f0d98(&self->sub, 0x7f, 0x258);
            self->unk_6C = -1;
        }
        if (self->sub.flag == 0) {
            return;
        }
        vol = func_020f0d50(&self->sub);
        NNS_SndPlayerSetTrackVolume(self->sound, self->unk_64, vol);
        NNS_SndPlayerSetTrackVolume(self->sound, self->unk_6E, 0x7f - vol);
    }
}

void func_020f13bc(struct UnkStruct_020f13bc *self)
{
    if (self->unk_2C == 0) {
        return;
    }

    if (((signed char *) self->unk_2C)[4] == 50) {
        unsigned int pos = NNS_SndArcStrmGetCurrentPlayingPos(&self->unk_34);
        int secs = (self->unk_68 - pos) * 20 / 1000;
        if (pos != 0) {
            if (secs > 127) {
                func_020f11d0((unsigned char *) self, 0, 0);
            } else if (secs == 127) {
                func_020f0ddc(&self->unk_04, 0);
                func_020f0d98(&self->unk_04, 127, 160);
            }
        }

        if (self->unk_06 != 0) {
            int v = func_020f0d50(&self->unk_04);
            func_020f11d0((unsigned char *) self, v, v);
        }
    }

    if (((signed char *) self->unk_2C)[4] == 51) {
        if (self->unk_06 != 0) {
            int v = func_020f0d50(&self->unk_04);
            func_020f11d0((unsigned char *) self, v, v);
        }
    }

    if (self->unk_12 != 0) {
        int v1 = func_020f0d50(&self->unk_10);
        int v2 = func_020f0d50(&self->unk_1C);
        func_020f11d0((unsigned char *) self, v1, v2);
    } else if (self->unk_1E != 0) {
        int v = func_020f0d50(&self->unk_1C);
        func_020f1158(self, v);
    }
}

void func_020f12cc(UnkStruct_020f12cc *self, int p1)
{
    int v = (int) self->unk_70 - 0x80;
    if (v < -128) {
        v = -128;
    } else if (v > 127) {
        v = 127;
    }

    if (p1 == 0) {
        func_0210b634(&self->h1, 0xff, v);
        func_0210b634(&self->h2, 0xff, v);
        return;
    }

    {
        Handle *h = (Handle *) self->h1;
        unsigned int ok = (h != 0);
        if (!ok) {
            return;
        }
        switch (h->itemId) {
            case 0xb:
            case 0x92:
            case 0x93:
            case 0xb3:
                func_0210b634(&self->h1, 0xff, v);
                break;
            default:
                break;
        }
    }
}

void func_020f11d0(unsigned char *self, int volL, int volR)
{
    int half;

    if (volL > 0x7f) {
        volL = 0x7f;
    } else if (volL < 0) {
        volL = 0;
    }

    if (volR > 0x7f) {
        volR = 0x7f;
    } else if (volR < 0) {
        volR = 0;
    }

    half = volL >> 1;

    NNS_SndPlayerSetPlayerVolume(4, volL);
    NNS_SndPlayerSetPlayerVolume(7, volL);
    NNS_SndPlayerSetPlayerVolume(13, volL);
    NNS_SndPlayerSetPlayerVolume(9, volL);
    NNS_SndPlayerSetPlayerVolume(8, volR);
    NNS_SndPlayerSetPlayerVolume(11, volR);

    if (self[0x61] != 0) {
        return;
    }

    NNS_SndPlayerSetPlayerVolume(5, volR);
    NNS_SndPlayerSetPlayerVolume(6, volR);
    NNS_SndPlayerSetPlayerVolume(16, volR);
    NNS_SndPlayerSetPlayerVolume(17, volR);
    NNS_SndPlayerSetPlayerVolume(18, half);
    NNS_SndPlayerSetPlayerVolume(19, half);
    NNS_SndPlayerSetPlayerVolume(20, volR);

    return;
}
