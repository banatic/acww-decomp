/* The villagers' new day (villager_day.h). */
#include "villager_day.h"

#include "clean.h"
#include "npc_id.h"

extern unsigned int func_0208150c(unsigned int villager); /* the villager's NpcId, at 0x7a0 */
extern int func_0207f150(void *villager);                 /* 0-3, from three tests of the villager */
extern void func_0207d634(void *villager);
/* The address of the villager's entry `entry` (0x80 bytes each, from 0x000), or 0 when
 * func_02080808 refuses it. */
extern int func_020807c0(int villager, int entry);
extern int func_02081edc(void *memory); /* whether the entry is in use */
/* Each clears one of the entry's flags at 0x7c: 0x40, 0x80, 0x800, 0x1000, 0x2000, 0x4000 and
 * 0x20, in this order. */
extern void func_020819d0(unsigned short *memory);
extern void func_0208199c(void *memory);
extern void func_02081960(unsigned short *memory);
extern void func_02081924(unsigned short *memory);
extern void func_020818e8(unsigned short *memory);
extern void func_020818ac(unsigned short *memory);
extern void func_02081878(void *memory);
/* The villager and the date handed on, for each of the four players' records (data_021dc7bc). */
extern void func_02080fc0(int villager, int today);
extern void func_02080e5c(int villager, int today);

/* func_020790a8: for each villager whose NpcId is valid: func_0207d634 when func_0207f150 says
 * 3; the day's flags of each of its eight entries in use cleared; then func_02080fc0 and
 * func_02080e5c with the date.
 *
 * QUIRK: the entries are walked from what func_020807c0 gives for entry 0 even when it refuses
 * it (0), so func_02081edc is then asked about the addresses 0x000-0x380. */
void VillagerDay_Begin(u8 *villagers, const DateTime *today)
{
    for (int i = 0; i < VILLAGER_DAY_VILLAGERS; i++) {
        u8 *villager = villagers + i * VILLAGER_DAY_VILLAGER_SIZE;
        unsigned int npc = func_0208150c((unsigned int) (uintptr_t) villager);

        if (NpcId_IsValid((const NpcId *) (uintptr_t) npc) != 0) {
            uintptr_t memories;

            if (func_0207f150(villager) == 3) {
                func_0207d634(villager);
            }
            memories = (uintptr_t) (unsigned int) func_020807c0((int) (uintptr_t) villager, 0);
            for (int j = 0; j < VILLAGER_DAY_MEMORIES; j++) {
                unsigned short *memory = (unsigned short *) (memories + (uintptr_t) j * VILLAGER_DAY_MEMORY_SIZE);

                if (func_02081edc(memory) != 0) {
                    func_020819d0(memory);
                    func_0208199c(memory);
                    func_02081960(memory);
                    func_02081924(memory);
                    func_020818e8(memory);
                    func_020818ac(memory);
                    func_02081878(memory);
                }
            }
            func_02080fc0((int) (uintptr_t) villager, (int) (uintptr_t) today);
            func_02080e5c((int) (uintptr_t) villager, (int) (uintptr_t) today);
        }
    }
}
CLEAN_AS(func_020790a8, VillagerDay_Begin)
