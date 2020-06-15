#ifndef FILESYS_PAGE_CACHE_H
#define FILESYS_PAGE_CACHE_H
#include "vm/vm.h"

struct page;
enum vm_type;

struct page_cache {};

void page_cache_init (void);
bool page_cache_initializer (struct page *page, enum vm_type type, void *kva);
#endif
