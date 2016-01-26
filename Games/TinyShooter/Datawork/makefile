CONV_MAP=tmx2c
CONV_SPRITE=png2c
CONV_BANK=png2tilefest
CONV_SFX=bin2c

MAP_FILES=$(wildcard tilemap_*.tmx)
SPRITE_FILES=$(wildcard sprite_*.png)
BANK_FILES=$(wildcard tilebank_*.png)
SFX_FILES=$(wildcard audiosamples_*.raw)

CONVERTED_MAP_FILES=$(MAP_FILES:.tmx=.cpp)
CONVERTED_SPRITE_FILES=$(SPRITE_FILES:.png=.cpp)
CONVERTED_BANK_FILES=$(BANK_FILES:.png=.cpp)
CONVERTED_SFX_FILES=$(SFX_FILES:.raw=.cpp)

ALL_CONVERTED_FILES=$(CONVERTED_MAP_FILES) $(CONVERTED_BANK_FILES) $(CONVERTED_SPRITE_FILES) $(CONVERTED_SFX_FILES)

build: $(ALL_CONVERTED_FILES)

%.cpp: %.tmx
	@echo Converting tilemap $^
	@$(CONV_MAP) $^ ../data/$(subst .tmx,,$^) $(subst .tmx,,$^) > /dev/null

sprite_%.cpp: sprite_%.png
	@echo Converting sprite $^
	@$(CONV_SPRITE) $^ ../data/$(subst .png,,$^) $(subst .png,,$^) > /dev/null

tilebank_%.cpp: tilebank_%.png
	@echo Converting tilebank $^ with tiles at 4x4 pixels
	@$(CONV_BANK) $^ ../data/$(subst .png,,$^) $(subst .png,,$^) 4 4 > /dev/null

audiosamples_%.cpp: audiosamples_%.raw
	@echo Converting audio samples $^
	@$(CONV_SFX) $^ ../data/$(subst .raw,,$^) $(subst .raw,,$^) > /dev/null
