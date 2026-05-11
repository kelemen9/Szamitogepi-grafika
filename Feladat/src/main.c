#include "app.h"

#include <stdio.h>

/**
 * Main function
 */
int main(int argc, char* argv[])
{
    App app;

    init_app(&app, 1000, 600);
    while (app.is_running) {
        handle_app_events(&app);
        update_app(&app);
        render_app(&app);
    }
    destroy_app(&app);
    
    if (argv[argc])
    {
        printf(" ");
    }

    return 0;
}
