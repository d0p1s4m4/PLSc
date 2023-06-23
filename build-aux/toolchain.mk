ifneq (,$(findstring clang,$(CC)))
cc_clang_gcc := 1
else ifneq (,$(findstring gcc,$(CC)))
cc_clang_gcc := 1
else ifneq (,$(findstring tcc,$(CC)))
cc_tcc := 1
else ifneq (,$(findstring cl,$(CC)))
cc_msvc := 1
endif

ifneq (,$(findstring link,$(LD)))
ld_msvc := 1
endif
