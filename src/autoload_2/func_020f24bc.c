/* func_020f24bc @ 0x020f24bc, 0x44 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

typedef unsigned int uint32_t;
typedef unsigned char uint8_t;
typedef unsigned long long uint64_t;

struct UnkStruct_020f24bc;
extern uint64_t OS_GetTick(void);

struct UnkStruct_020f24bc {
    char pad_00[0x4d];
    uint8_t unk_4D;
    char pad_4E[6];
    uint32_t unk_54;
    uint64_t unk_58;
    uint8_t unk_60;
    uint8_t pad_61;
    uint8_t unk_62;
};

struct UnkStruct_020f24bc *func_020f24bc(struct UnkStruct_020f24bc *s)
{
    s->unk_54 = OS_GetTick();
    s->unk_58 = 0x00269ec35d588b65ULL;
    s->unk_4D = 0;
    s->unk_60 = 0;
    s->unk_62 = 0;
    return s;
}
