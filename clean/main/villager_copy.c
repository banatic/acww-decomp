/* A villager held inside another record (villager_copy.h). */
#include "villager_copy.h"

#include "clean.h"
#include "town_villager.h"

/* func_02079900: the villager itself. */
void *VillagerCopy_Villager(void *villager)
{
    return villager;
}
CLEAN_AS(func_02079900, VillagerCopy_Villager)

/* func_02079904: the villager destroyed. */
void *VillagerCopy_Destruct(void *villager)
{
    TownVillager_Destruct(villager);
    return villager;
}
CLEAN_AS(func_02079904, VillagerCopy_Destruct)

/* func_02079914: the villager built. */
void *VillagerCopy_Construct(void *villager)
{
    TownVillager_Construct(villager);
    return villager;
}
CLEAN_AS(func_02079914, VillagerCopy_Construct)
