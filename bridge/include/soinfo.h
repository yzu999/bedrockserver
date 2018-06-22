
#pragma once
#include <elf.h>
#define SOINFO_NAME_LEN 128

struct link_map
{
  uintptr_t l_addr;
  char *l_name;
  uintptr_t l_ld;
  struct link_map *l_next;
  struct link_map *l_prev;
};

struct soinfo
{
  const char name[SOINFO_NAME_LEN];
  Elf32_Phdr *phdr;
  int phnum;
  unsigned entry;
  unsigned base;
  unsigned size;

  int unused; // DO NOT USE, maintained for compatibility.

  unsigned *dynamic;

  unsigned wrprotect_start;
  unsigned wrprotect_end;

  soinfo *next;
  unsigned flags;

  const char *strtab;
  Elf32_Sym *symtab;

  unsigned nbucket;
  unsigned nchain;
  unsigned *bucket;
  unsigned *chain;

  unsigned *plt_got;

  Elf32_Rel *plt_rel;
  unsigned plt_rel_count;

  Elf32_Rel *rel;
  unsigned rel_count;

  unsigned *preinit_array;
  unsigned preinit_array_count;

  unsigned *init_array;
  unsigned init_array_count;
  unsigned *fini_array;
  unsigned fini_array_count;

  void (*init_func)(void);
  void (*fini_func)(void);

#ifdef ANDROID_ARM_LINKER
  /* ARM EABI section used for stack unwinding. */
  unsigned *ARM_exidx;
  unsigned ARM_exidx_count;
#endif

  unsigned refcount;
  struct link_map linkmap;

  int constructors_called;

  Elf32_Addr gnu_relro_start;
  unsigned gnu_relro_len;
};