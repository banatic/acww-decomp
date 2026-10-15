/* func_0204510c @ 0x0204510c, 0x274 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_0204510c {
    u8 f01 : 2;
    u8 fx : 2;
    u8 fy : 2;
    u8 f67 : 2;
    u8 fz : 5;
    u8 fw : 2;
    u8 f7 : 1;
    u16 unk_02;
    u16 unk_04;
    u16 unk_06;
};

struct Sbf {
    u8 z0 : 1;
    u8 a : 2;
    u8 b : 5;
    u8 c : 2;
    u8 d : 1;
    u8 e : 2;
    u8 f : 2;
    u8 g : 1;
};

struct Sraw {
    u8 raw0;
    u8 raw1;
    u16 primaryNotifyPair;
    u16 alternateNotifyPair;
    u16 tbl[3];
    u16 extra;
};

union UnkStruct_0204510c_2 {
    struct Sbf bf;
    struct Sraw m;
};

struct UnkStruct_0204510c_3 {
    u8 pad_00[8];
    int unk_08;
    u8 pad_0C[0x18];
};

extern struct UnkStruct_0204510c_3 data_021c7c48[];
extern void *data_020ccf94;

extern int func_02046024(int a, int *pair, u16 w, int b, int bits, int e, int f, int four, int g, int minus1);
extern int func_ov003_02221118(int a, u16 w, int *pair);
extern int func_0204482c(int a);
extern int func_02045380(union UnkStruct_0204510c_2 *packet, struct UnkStruct_0204510c *p, int a);
extern void func_02042a9c(union UnkStruct_0204510c_2 *packet);
extern void func_02073820(void *obj);
extern void func_020737f0(void *obj, void *buf, int length);
extern void func_02073770(void *obj, int a, int b);

void func_0204510c(struct UnkStruct_0204510c *p, int enabled, int actor)
{
    // Preserve ROM bitwise writes; every header bit is assigned below.
    unsigned int bits;
    int length;
    volatile u16 packedPosition;
    int primaryPair[2];
    int primaryNotifyPair[2];
    int alternatePair[2];
    int alternateNotifyPair[2];
    int defaultPair[2];
    union UnkStruct_0204510c_2 packet;
    int i;
    int tileX, tileZ;
    int kind;
    int tileId;
    void *object;
    struct UnkStruct_0204510c_3 *entry;

    length = 6;
    bits = packet.m.raw0;
    bits &= ~1u;
    packet.m.raw0 = bits;
    bits = packet.m.raw0;
    bits &= ~6u;
    bits |= ((u8) actor & 3) << 1;
    packet.m.raw0 = bits;
    bits = packet.m.raw0;
    bits &= ~0xf8u;
    bits |= (p->fz & 0x1f) << 3;
    packet.m.raw0 = bits;
    bits = packet.m.raw1;
    bits &= ~3u;
    bits |= (p->fx & 3);
    packet.m.raw1 = bits;
    bits = packet.m.raw1;
    bits &= ~4u;
    bits |= (enabled & 1) << 2;
    packet.m.raw1 = bits;
    bits = packet.m.raw1;
    bits &= ~0x60u;
    bits |= (p->fw & 3) << 5;
    packet.m.raw1 = bits;
    bits = packet.m.raw1;
    bits &= ~0x80u;
    bits |= (p->f7 & 1) << 7;
    packet.m.raw1 = bits;
    bits = packet.m.raw1;
    bits &= ~0x18u;
    bits |= (p->fy & 3) << 3;
    packet.m.raw1 = bits;
    packedPosition = p->unk_02;
    packet.m.primaryNotifyPair = packedPosition;
    packet.m.alternateNotifyPair = p->unk_06;
    for (i = 0; i < 3; i++) {
        packet.m.tbl[i] = 0xffff;
    }
    tileX = packet.m.primaryNotifyPair >> 8;
    tileZ = packet.m.primaryNotifyPair & 0xff;

    if (enabled != 0) {
        kind = packet.bf.b;
        switch (kind) {
            case 0x18:
                primaryPair[0] = tileX;
                primaryPair[1] = tileZ;
                func_02046024((u8) actor, primaryPair, packet.m.alternateNotifyPair, 0xfff1, kind, packet.bf.e, packet.bf.f, 4,
                              packet.bf.g, -1);
                primaryNotifyPair[0] = tileX;
                primaryNotifyPair[1] = tileZ;
                func_ov003_02221118(actor, packet.m.alternateNotifyPair, primaryNotifyPair);
                break;
            case 0x1a:
                alternatePair[0] = tileX;
                alternatePair[1] = tileZ;
                func_02046024((u8) actor, alternatePair, packet.m.alternateNotifyPair, 0xfff1, kind, packet.bf.e, packet.bf.f,
                              4, packet.bf.g, -1);
                if (func_0204482c(actor) == 0) {
                    alternateNotifyPair[0] = tileX;
                    alternateNotifyPair[1] = tileZ;
                    func_ov003_02221118(actor, packet.m.alternateNotifyPair, alternateNotifyPair);
                }
                break;
            default:
                // The original reads this input before materializing the pair.
                tileId = p->unk_04;
                defaultPair[0] = tileX;
                defaultPair[1] = tileZ;
                func_02046024((u8) actor, defaultPair, packet.m.alternateNotifyPair, tileId, kind, packet.bf.e, packet.bf.f, 4,
                              packet.bf.g, -1);
                if (func_02045380(&packet, p, actor) != 0) {
                    packet.bf.z0 = 1;
                    length = 0xe;
                }
                break;
            case 0xc:
            case 0xd:
            case 0xf:
            case 0x17:
                break;
        }
        if (func_0204482c(actor) != 0) {
            entry = &data_021c7c48[p->fx];
            entry->unk_08 = 2;
        } else {
            func_02042a9c(&packet);
        }
    } else {
        if (func_0204482c(actor) != 0) {
            entry = &data_021c7c48[p->fx];
            entry->unk_08 = 3;
        }
    }

    // All three operations use the same object even if the global changes.
    object = data_020ccf94;
    func_02073820(object);
    func_020737f0(object, &packet, length);
    func_02073770(object, 0x32, 4);
}
