#ifndef CAMERA_H
#define CAMERA_H

#include "utils.h"

#define FALSE 0
#define TRUE 1

typedef struct Camera
{
    vec3 position;
    vec3 rotation;
    vec3 speed;

int is_preview_visible;

int is_guide_visible;



}Camera;



/*initialize, update, reset the position of the camera*/

void init_camera(Camera* camera);

void update_camera(Camera* camera, double time);

void reset_camera(Camera* camera);

/*Apply the camera settings to the view transformation*/

void set_view(Camera* camera); //const Camera

/*Set the horizontal and vertical rotation of the view angle*/

void rotate_camera(Camera* camera, double horizontal, double vertical);

/*Set the speed of forward and backward motion*/

void set_camera_speed(Camera* camera, double speed);

/*Set the speed of left and right side steps.*/

void set_camera_side_speed(Camera* camera, double speed);

/*Set the speed of lifting up and down motion*/
void set_camera_vertical_speed(Camera* camera, double speed);

/*Shows the guide/win/lose screen*/

void show_texture_preview();

void show_guide();


//void show_lose();

//void show_win();



#endif /* CAMERA_H */