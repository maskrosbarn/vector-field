inline const int
    WINDOW_SIZE      = 1000,
    WINDOW_SIZE_HALF = WINDOW_SIZE / 2;

inline const int
    MOUSE_TEXT_OFFSET = 10;

// SDL window dimensions are measured in whole pixels, so an even window size
// avoids any slight graphical inaccuracies (I think?)
static_assert(WINDOW_SIZE % 2 == 0);

inline const int
    PLOT_AREA_INSET = 50,
    PLOT_AREA_SIZE  = WINDOW_SIZE - 2 * PLOT_AREA_INSET;

inline const int
    AXES_MAX_POSITION = WINDOW_SIZE - PLOT_AREA_INSET,
    AXES_MIN_POSITION = PLOT_AREA_INSET;