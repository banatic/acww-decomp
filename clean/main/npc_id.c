/* References to villagers (npc_id.h). */
#include "npc_id.h"

#include <assert.h>
#include <stddef.h>
#include <stdint.h>

#include "clean.h"

static_assert(sizeof(NpcIdHead) == 14, "NpcIdHead layout");
static_assert(offsetof(NpcId, personality) == 0x0e, "NpcId layout");
static_assert(offsetof(NpcId, number) == 0x0f, "NpcId layout");
static_assert(sizeof(NpcId) == 16, "NpcId layout");

/* For each personality, a kind (0, 0, 2, 1, 1, 1); 5 for none. */
extern const int data_020c7570[PERSONALITY_COUNT];
/* For each personality, the prefix of its resource names. */
extern const char *const data_020d72a4[PERSONALITY_COUNT];
extern const char data_020d72bc[]; /* "%s%s" */
/* The head a villager gets when none is given (NpcId_Set). */
extern const NpcIdHead data_021dc7aa;

extern void MI_CpuCopy8(const void *src, void *dst, u32 size);
extern void MI_CpuFill8(void *dst, u8 value, u32 size);
/* The villager's name ("st_npc_name") into `dst`; 0 for a number out of range. */
extern int func_0208249c(char *dst, int number);
/* sprintf */
extern int func_02064328(char *dst, const char *format, ...);
extern u32 func_02064294(const NpcIdHead *head);                 /* is it set */
extern void func_020642a8(const NpcIdHead *src, NpcIdHead *dst); /* copy */
extern void func_020642bc(NpcIdHead *dst, const NpcIdHead *src); /* assign */
extern void func_020642d0(NpcIdHead *dst, const NpcIdHead *src); /* copy */
extern void func_020642e0(NpcIdHead *head);                      /* clear */
extern void func_020642f8(NpcIdHead *head);                      /* destructor */
extern void func_020642fc(NpcIdHead *head);                      /* constructor */

/* func_02003618: the villager's name into `dst` when the reference is valid; whether it was
 * written. */
int NpcId_FormatName(const NpcId *npc, char *dst)
{
    if (NpcId_IsValid(npc) == 1) {
        return func_0208249c(dst, npc->number);
    }
    return 0;
}
CLEAN_AS(func_02003618, NpcId_FormatName)

/* func_0200363c */
int Npc_IsValidNumber(u32 number)
{
    return number < NPC_COUNT;
}
CLEAN_AS(func_0200363c, Npc_IsValidNumber)

/* func_02003648 */
int NpcId_Number(const NpcId *npc)
{
    return npc->number;
}
CLEAN_AS(func_02003648, NpcId_Number)

/* func_0200364c */
int NpcId_PersonalityKind(const NpcId *npc)
{
    return Personality_Kind(npc->personality);
}
CLEAN_AS(func_0200364c, NpcId_PersonalityKind)

/* func_02003658: the personality's kind, 5 for none. */
int Personality_Kind(u32 personality)
{
    if (personality < PERSONALITY_COUNT) {
        return data_020c7570[personality];
    }
    return 5;
}
CLEAN_AS(func_02003658, Personality_Kind)

/* func_0200366c: Personality_FormatResourceName with the villager's personality. */
int NpcId_FormatResourceName(const NpcId *npc, char *dst, int size, const char *name)
{
    return Personality_FormatResourceName(dst, size, name, NpcId_Personality(npc));
}
CLEAN_AS(func_0200366c, NpcId_FormatResourceName)

/* func_0200368c: `name` after the personality's prefix into `dst`, which is cleared first;
 * what sprintf returns.
 * REQUIRES: a personality below PERSONALITY_COUNT; the original reads past its table. */
int Personality_FormatResourceName(char *dst, int size, const char *name, int personality)
{
    MI_CpuFill8(dst, 0, (u32) size);
    return func_02064328(dst, data_020d72bc, data_020d72a4[personality], name);
}
CLEAN_AS(func_0200368c, Personality_FormatResourceName)

/* func_020036c0 */
u32 NpcId_PersonalityGroup(const NpcId *npc)
{
    return Personality_Group((u32) NpcId_Personality(npc));
}
CLEAN_AS(func_020036c0, NpcId_PersonalityGroup)

/* func_020036d4: 0 for the first three personalities, 1 for the last three, 2 for none. */
u32 Personality_Group(u32 personality)
{
    if (personality < 3) {
        return 0;
    }
    if (personality < 6) {
        return 1;
    }
    return 2;
}
CLEAN_AS(func_020036d4, Personality_Group)

/* func_020036e8 */
int NpcId_Personality(const NpcId *npc)
{
    return npc->personality;
}
CLEAN_AS(func_020036e8, NpcId_Personality)

/* func_020036ec: the villager, and its head copied from `head` or, without one, from the
 * game's default head. */
void NpcId_Set(NpcId *npc, u8 number, u8 personality, const NpcIdHead *head)
{
    npc->number = number;
    npc->personality = personality;
    if (head == NULL) {
        head = &data_021dc7aa;
    }
    func_020642d0(&npc->head, head);
}
CLEAN_AS(func_020036ec, NpcId_Set)

/* func_02003704: a set head and a villager number in range. */
int NpcId_IsValid(const NpcId *npc)
{
    return func_02064294(&npc->head) == 1 && Npc_IsValidNumber(npc->number) == 1;
}
CLEAN_AS(func_02003704, NpcId_IsValid)

/* func_02003728 */
void NpcId_Copy(NpcId *dst, const NpcId *src)
{
    MI_CpuCopy8(src, dst, sizeof(NpcId));
}
CLEAN_AS(func_02003728, NpcId_Copy)

/* func_02003738: no villager. */
void NpcId_Clear(NpcId *npc)
{
    func_020642e0(&npc->head);
    npc->number = NPC_NONE;
    npc->personality = PERSONALITY_NONE;
}
CLEAN_AS(func_02003738, NpcId_Clear)

/* func_02003750: the destructor; returns the reference's address. */
int NpcId_Destruct(NpcId *npc)
{
    func_020642f8(&npc->head);
    return (int) (intptr_t) npc;
}
CLEAN_AS(func_02003750, NpcId_Destruct)

/* func_02003760: the copy constructor. */
NpcId *NpcId_ConstructCopy(NpcId *npc, const NpcId *src)
{
    func_020642fc(&npc->head);
    NpcId_Assign(npc, src);
    return npc;
}
CLEAN_AS(func_02003760, NpcId_ConstructCopy)

/* func_02003780: the constructor; returns the reference's address. */
int NpcId_Construct(NpcId *npc)
{
    func_020642fc(&npc->head);
    return (int) (intptr_t) npc;
}
CLEAN_AS(func_02003780, NpcId_Construct)

/* func_02003790 */
void NpcId_CopyTo(const NpcId *src, NpcId *dst)
{
    func_020642a8(&src->head, &dst->head);
    dst->number = src->number;
    dst->personality = src->personality;
}
CLEAN_AS(func_02003790, NpcId_CopyTo)

/* func_020037ac: the assignment operator. */
void NpcId_Assign(NpcId *npc, const NpcId *src)
{
    func_020642bc(&npc->head, &src->head);
    npc->number = src->number;
    npc->personality = src->personality;
}
CLEAN_AS(func_020037ac, NpcId_Assign)
