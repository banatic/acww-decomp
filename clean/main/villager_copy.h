/* A villager (0x7ec bytes, as the town keeps eight of at data_021e5a2c) held inside another
 * record: the record at data_021ee418 holds one at its 0x14c (func_020900d8), which
 * func_0207c190 compares with the town's own villagers. */
#ifndef CLEAN_MAIN_VILLAGER_COPY_H
#define CLEAN_MAIN_VILLAGER_COPY_H

void *VillagerCopy_Villager(void *villager);
void *VillagerCopy_Destruct(void *villager);
void *VillagerCopy_Construct(void *villager);

#endif
