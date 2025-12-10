typedef enum BaseClass {
    BC_Bard, 
    BC_Cleric, 
    BC_Druid, 
    BC_Fighter, 
    BC_Ranger, 
    BC_Rogue, 
    BC_Witch, 
    BC_Wizard,
} BaseClass;

typedef enum AncestoryHeritage {
    AH_Aiuvarin,
    AH_Ancient_Elf,
    AH_Ancient_Blooded_Dwarf,
    AH_Arctic_Elf,
    AH_Badlands_Orc,
    AH_Battle_Ready_Orc,
    AH_Cactus_Leshy,
    AH_Cavern_Elf,
    AH_Chameleon_Gnome,
    AH_Changeling,
    AH_Charhide_Goblin,
    AH_Death_Warden_Dwarf,
    AH_Deep_Orc,
    AH_Dromaar,
    AH_Fey_touched_Gnome,
    AH_Forge_Dwarf,
    AH_Fruit_Leshy,
    AH_Fungus_Leshy,
    AH_Gourd_Leshy,
    AH_Grave_Orc,
    AH_Gutsy_Halfling,
    AH_Hillock_Halfling,
    AH_Hold_Scarred_Orc,
    AH_Irongut_Goblin,
    AH_Jinxed_Halfling,
    AH_Leaf_Leshy,
    AH_Lotus_Leshy,
    AH_Nephilim,
    AH_Nomadic_Halfling,
    AH_Rainfall_Orc,
    AH_Razortooth_Goblin,
    AH_Rock_Dwarf,
    AH_Root_Leshy,
    AH_Seaweed_Leshy,
    AH_Seer_Elf,
    AH_Sensate_Gnome,
    AH_Skilled_Human,
    AH_Snow_Goblin,
    AH_Strong_Blooded_Dwarf,
    AH_Twilight_Halfling,
    AH_Umbral_Gnome,
    AH_Unbreakable_Goblin,
    AH_Versatile_Human,
    AH_Vine_Leshy,
    AH_Wellspring_Gnome,
    AH_Whisper_Elf,
    AH_Wildwood_Halfling,
    AH_Winter_Orc,
    AH_Woodland_Elf
} AncestoryHeritage;

typedef enum Feat {
    Feat_this,
} Feat;

typedef enum Background {
    BG_Acolyte, 
    BG_Acrobat, 
    BG_Animal_Whisperer, 
    BG_Artisan, 
    BG_Artist, 
    BG_Bandit, 
    BG_Barkeep, 
    BG_Barrister, 
    BG_Bounty_Hunter, 
    BG_Charlatan, 
    BG_Cook, 
    BG_Criminal, 
    BG_Cultist, 
    BG_Detective, 
    BG_Emissary, 
    BG_Entertainer, 
    BG_Farmhand, 
    BG_Field_Medic, 
    BG_Fortune_Teller, 
    BG_Gambler, 
    BG_Gladiator, 
    BG_Guard, 
    BG_Herbalist, 
    BG_Hermit, 
    BG_Hunter, 
    BG_Laborer, 
    BG_Martial_Disciple, 
    BG_Merchant, 
    BG_Miner, 
    BG_Noble, 
    BG_Nomad, 
    BG_Prisoner, 
    BG_Raised_by_Belief, 
    BG_Sailor, 
    BG_Scholar, 
    BG_Scout, 
    BG_Street_Urchin, 
    BG_Teacher, 
    BG_Tinker, 
    BG_Warrior,
} Background;

typedef enum StatusEffect {
    SE_blank,
} StatusEffect;

typedef struct Dice {
    u32 faces;
    u32 count;
} Dice;

typedef struct Attributes {
    u16 strength;
    u16 dexterity;
    u16 constitution;
    u16 intelligence;
    u16 wisdom;
    u16 charisma;
} Attributes;

typedef enum DamageType {
    DT_Bludgening,
    DT_Piercing,
} DamageType;

typedef enum Skill {
    Eating,
} Skill;

typedef enum SpellName {
    Spell_Arcane_Touch
} SpellName;

typedef union Action {
    struct {
        String8 name;
        String8 desc;
        SpellName name_type;
        Dice damage;
    } Spell;
} Action;


typedef struct Entity {
    AncestoryHeritage race;
    BaseClass base_class;
    Attributes attributes;
    u32 level;
    u32 movement_speed;
    i32 spellcaster_lvl;
} Entity;

typedef struct ArrayEntity {
    u32 len;
    u32 capacity;
    Entity *data;
} ArrayEntity;

void RollDice(Dice d);
void RollInitiative(Entity *e);
