CONV_MAP=tmx2c
CONV_SPRITE=png2c
CONV_BANK=png2tilefest

MAP_FILES=tilemap_spacebase.tmx tilemap_spacebase_background.tmx
SPRITE_FILES=sprite_player.png sprite_pb_01.png sprite_spacebase_boss_door.png
BANK_FILES=tilebank_spacebase.png

CONVERTED_MAP_FILES=$(MAP_FILES:.tmx=.cpp)
CONVERTED_SPRITE_FILES=$(SPRITE_FILES:.png=.cpp)
CONVERTED_BANK_FILES=$(BANK_FILES:.png=.cpp)

ALL_CONVERTED_FILES=$(CONVERTED_MAP_FILES) $(CONVERTED_SPRITE_FILES) $(CONVERTED_BANK_FILES)

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
