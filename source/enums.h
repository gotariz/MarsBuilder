#ifndef ENUMS_H_INCLUDED
#define ENUMS_H_INCLUDED

enum UndoTypes {
    CREATION,
    MOVED,
    RESIZED,
};

enum Orientation {
    HORIZONTAL,
    VERTICAL,
};

enum BlockType {
    NONE                = 0x000000,
    HIGH_GRADE_WALL     = 0x000001,
    LOW_GRADE_WALL      = 0x000002,
    INTERIOR_WALL       = 0x000004,
    HIGH_GRADE_WINDOW   = 0x000008,
    LOW_GRADE_WINDOW    = 0x000010,
    HIGH_GRADE_DOOR     = 0x000020,
    LOW_GRADE_DOOR      = 0x000040,
    INTERIOR            = 0x000080,
    INTERIOR_DOOR       = 0x000100,
    ACCESSORY           = 0x000200,
};

enum ModuleType {
    M_INTERNAL_DOOR,
    M_INTERNAL_WALL,
    M_CORRIDOR,// high grade modules
    M_HIGH_GRADE_AIR_LOCK_DOOR,
    M_HIGH_GRADE_CONNTECTING_DOOR,
    M_HIGH_GRADE,
    M_HIGH_GRADE_DOOR,
    M_HIGH_GRADE_WINDOW,
    M_LOW_GRADE_WINDOW,// low grade modules
    M_LOW_GRADE_DOOR,
    M_LOW_GRADE,
    M_ACCESSORY_TABLE,
    M_ACCESSORY_BED,
    M_ACCESSORY_SHOWER,
    M_ACCESSORY_BATH,
    M_ACCESSORY_WARDROBE,
    M_ACCESSORY_SINK,
    M_ACCESSORY_COUNTER,
    M_ACCESSORY_STOVE,
    M_ACCESSORY_TOILET,
};

enum guiIDs {
    BTN_MH,
    BTN_ML,
    BTN_DH,
    BTN_DL,
    BTN_DAL,
    BTN_DC,
    BTN_DI,
    BTN_WI,
    BTN_WH,
    BTN_WL,
    BTN_C,
    BTN_R,
    BTN_M,
    BTN_ZI,
    BTN_ZO,
    BTN_UNDO,
    BTN_SAVE,
    BTN_OPEN,
    LBL_ZOOM,
    BTN_TABLE,
    BTN_BED,
    BTN_SHOWER,
    BTN_BATH,
    BTN_WARDROBE,
    BTN_SINK,
    BTN_COUNTER,
    BTN_STOVE,
    BTN_TOILET,
};

enum Anchor{
    TOP,
    BOTTOM,
    LEFT,
    RIGHT,
};

enum GUIState {
    IDLE,
    HOVER,
    ACTIVE,
    SELECTED,
    TOGGLED,
};

enum GUIEvent {
    TOGGLED_ON,
    TOGGLED_OFF,
    CLICKED,
    ENTERED,
    EXITED,
    DRAGGED_OFF,
    DRAGGED_ON,
};

enum MouseButton {
    MOUSE_LEFT = 0,
    MOUSE_MIDDLE = 1,
    MOUSE_RIGHT = 2
};

enum MouseState {
    PRESSED = 0,
    RELEASED = 1,
};

enum guiType {
    GUI_UNKNOWN,
    GUI_PANEL,
    GUI_BUTTON,
    GUI_LABEL,
};

enum DrawSpace {
    SCREEN,
    CANVAS
};


#endif // ENUMS_H_INCLUDED
