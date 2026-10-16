/* A villager held inside another record (villager_copy.h). */
#include "villager_copy.h"

#include "clean.h"

extern void *func_02081710(void *villager); /* a villager's destructor */
extern void *func_020817a8(void *villager); /* a villager's constructor */

/* func_02079900: the villager itself. */
void *VillagerCopy_Villager(void *villager)
{
    return villager;
}
CLEAN_AS(func_02079900, VillagerCopy_Villager)

/* func_02079904: the villager destroyed. */
void *VillagerCopy_Destruct(void *villager)
{
    func_02081710(villager);
    return villager;
}
CLEAN_AS(func_02079904, VillagerCopy_Destruct)

/* func_02079914: the villager built. */
void *VillagerCopy_Construct(void *villager)
{
    func_020817a8(villager);
    return villager;
}
CLEAN_AS(func_02079914, VillagerCopy_Construct)
