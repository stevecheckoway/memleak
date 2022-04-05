#include <ruby.h>
#include <stdio.h>
#include <string.h>

static VALUE allocation_failure(VALUE self) {
  const size_t allocations = 200;
  const size_t page_size = getpagesize();
  char *p[allocations];
  
  for (size_t i = 0; i < allocations; ++i) {
    printf("Allocation %zu...", i);
    fflush(stdout);
    p[i] = ruby_xmalloc(1024 * 1024);
    memset(p[i], 0, 1024 * 1024); // Touch every page.
    puts("succeeded");
  }

  for (size_t i = 0; i < allocations; ++i)
    free(p[i]);
  return Qnil;
}

void Init_memleak(void) {
  VALUE mod = rb_define_module("MemLeak");
  rb_define_singleton_method(mod, "allocation_failure", allocation_failure, 0);
}
