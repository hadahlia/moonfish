BUILD_DIR=build
#T3D_INST=$(shell realpath ../..)

include $(N64_INST)/include/n64.mk
include $(N64_INST)/include/t3d.mk #$(T3D_INST)/t3d.mk

N64_CFLAGS += -std=gnu2x

PROJECT_NAME=fishwizard

src = $(wildcard src/*.c) #main.c
#ovl = $(wildcard src/overlays/*.c)

pointer_src = src/overlays/pointer.c

assets_png =  $(wildcard assets/*.png assets/*/*.png) # $(wildcard assets/*/*.png)
assets_gltf = $(wildcard assets/*.glb assets/*/*.glb) #$(wildcard assets/*/*.glb)
# assets_conv = $(addprefix filesystem/,$(notdir $(assets_png:%.png=%.sprite))) \
# 			  $(addprefix filesystem/,$(notdir $(assets_gltf:%.glb=%.t3dm)))
assets_conv = $(addprefix filesystem/,$(subst assets/, ,$(assets_png:%.png=%.sprite))) \
			  $(addprefix filesystem/,$(subst assets/, ,$(assets_gltf:%.glb=%.t3dm)))


all: $(PROJECT_NAME).z64

MAIN_ELF_EXTERNS := $(BUILD_DIR)/$(PROJECT_NAME).externs
MAIN_ELF_SYMBOLS := $(BUILD_DIR)/$(PROJECT_NAME).msym

DSO_MODULES = pointer.dso #$(ovl:%.c=%.dso)
DSO_LIST = $(addprefix filesystem/, $(DSO_MODULES))

filesystem/%.sprite: assets/%.png #assets/*/%.png
	@mkdir -p $(dir $@)
	@echo "    [SPRITE] $@"
	$(N64_MKSPRITE) $(MKSPRITE_FLAGS) --verbose -o filesystem "$<"
	

filesystem/%.t3dm: assets/%.glb #assets/*/%.glb
	@mkdir -p $(dir $@)
	@echo "    [T3D-MODEL] $@"
	$(T3D_GLTF_TO_3D) "$<" $@
	$(N64_BINDIR)/mkasset -c 2 -o filesystem $@

# remove_empty: $(dir )
# 	rmdir filesystem/*

$(BUILD_DIR)/$(PROJECT_NAME).dfs: $(assets_conv) $(DSO_LIST)
$(BUILD_DIR)/$(PROJECT_NAME).elf: $(src:%.c=$(BUILD_DIR)/%.o) $(MAIN_ELF_EXTERNS)
$(MAIN_ELF_EXTERNS): $(DSO_LIST)

filesystem/pointer.dso: $(pointer_src:%.c=$(BUILD_DIR)/%.o)

#filesystem/%.dso: $(ovl:%.c=$(BUILD_DIR)/%.o)
# 	@mkdir -p $(dir $@)
# 	@echo "     [DSO] $@"
# 	$(N64_BINDIR)/n64dso  -c 1 -o filesystem $@
#echo "$<"
#$(ovl:%.c=$(BUILD_DIR)/%.o)
#$(addprefix $(BUILD_DIR),$(notdir $(ovl:%.c=%.o)))

$(PROJECT_NAME).z64: N64_ROM_TITLE="moon fish"
$(PROJECT_NAME).z64: $(BUILD_DIR)/$(PROJECT_NAME).dfs $(MAIN_ELF_SYMBOLS)

$(MAIN_ELF_SYMBOLS): $(BUILD_DIR)/$(PROJECT_NAME).elf



clean:
	rm -rf $(BUILD_DIR) *.z64
	rm -rf filesystem $(DSO_LIST)

build_lib:
	rm -rf $(BUILD_DIR) *.z64
	make -C $(T3D_INST)
	make all

-include $(wildcard $(BUILD_DIR)/*.d)

.PHONY: all clean