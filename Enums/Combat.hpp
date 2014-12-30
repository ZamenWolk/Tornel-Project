enum Controls
{
    NO_CONTROL,
    KEYBOARD, ///< Controlled by keyboard
    CONTROLLER, ///< Controlled by a gamepad
    AI, ///< Controlled by the AI
    ONLINE, ///< Actions received from online
    FROM_FILE, ///< Actions read from a file
};

enum CombatMenu
{
    MAIN, ///< Main part of the menu
    CHARACTER_CHOOSING, ///< Character choosing menu
    TARGET_CHOOSING, ///< Target choosing menu
    SPELL_CHOOSING, ///< Spell choosing menu
    ABILITY_CHOOSING, ///< Ability choosing menu
};