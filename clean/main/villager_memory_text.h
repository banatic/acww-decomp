/* Two small text classes on the text base of text_label.h (the same four vtable entries: the
 * destructor, the deleting destructor, the capacity and the address of the characters):
 *
 * - a wide text of 10 16-bit characters (vtable data_020e18ec, 0x24 bytes), as long as the two
 *   texts of a villager's memory of a player (villager_memories.h); func_02081b24 builds one on
 *   its stack to convert the text at 0x3e to 8 bits;
 * - a label of 22 8-bit characters (vtable data_020e191c, 0x28 bytes): ten 16-bit characters
 *   as two bytes each, and room for an end code. The object func_02068644 constructs keeps one
 *   at 0x1e4c. */
#ifndef CLEAN_MAIN_VILLAGER_MEMORY_TEXT_H
#define CLEAN_MAIN_VILLAGER_MEMORY_TEXT_H

#include "text_label.h"
#include "types.h"

#define VILLAGER_MEMORY_WIDE_CAPACITY 10
#define VILLAGER_MEMORY_LABEL_CAPACITY 22

typedef struct VillagerMemoryWide {
    const TextVtable *vtable; /* data_020e18ec */
    u8 base_04[0xa];          /* the text base's */
    u16 text[VILLAGER_MEMORY_WIDE_CAPACITY];
} VillagerMemoryWide;

typedef struct VillagerMemoryLabel {
    const TextVtable *vtable; /* data_020e191c */
    u8 base_04[0xe];          /* the text base's */
    char text[VILLAGER_MEMORY_LABEL_CAPACITY];
} VillagerMemoryLabel;

int VillagerMemoryWide_Buffer(int text);
int VillagerMemoryWide_Capacity(void);
VillagerMemoryWide *VillagerMemoryWide_DestructDelete(VillagerMemoryWide *text);
void *VillagerMemoryWide_Destruct(void *text);
void *VillagerMemoryWide_Construct(void *text);
int VillagerMemoryLabel_Buffer(int label);
int VillagerMemoryLabel_Capacity(void);
void *VillagerMemoryLabel_DestructDelete(void *label);
void *VillagerMemoryLabel_Destruct(void *label);
void *VillagerMemoryLabel_Construct(void *label);

#endif
