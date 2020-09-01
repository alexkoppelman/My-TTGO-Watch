/****************************************************************************
 *   Aug 3 12:17:11 2020
 *   Copyright  2020  Dirk Brosswick
 *   Email: dirk.brosswick@googlemail.com
 ****************************************************************************/
 
/*
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */
#include "config.h"
#include <TTGO.h>

#include "music_app.h"
#include "music_app_main.h"

#include "gui/mainbar/app_tile/app_tile.h"
#include "gui/mainbar/main_tile/main_tile.h"
#include "gui/mainbar/mainbar.h"
#include "gui/statusbar.h"
#include "hardware/blectl.h"
<<<<<<< HEAD
#include "hardware/blectl.cpp"
=======
>>>>>>> 3cf933fff1a956402d254772973f7886e35e0d20

long music_milliseconds = 0;
time_t prevs_time;

lv_obj_t *music_app_main_tile = NULL;
lv_style_t music_app_main_style;

lv_style_t music_app_main_musicstyle;
// lv_obj_t *music_app_main_musiclabel = NULL;

//Second label

lv_obj_t *music_app_main_musiclabel2 = NULL;

lv_obj_t *music_app_main_start_btn = NULL;
lv_obj_t *music_app_main_stop_btn = NULL;
lv_obj_t *music_app_main_reset_btn = NULL;

// lv_task_t * _music_app_task;

LV_IMG_DECLARE(exit_32px);
LV_FONT_DECLARE(Ubuntu_72px);
LV_FONT_DECLARE(Ubuntu_32px);

static void exit_music_app_main_event_cb( lv_obj_t * obj, lv_event_t event );
static void start_music_app_main_event_cb( lv_obj_t * obj, lv_event_t event );
static void stop_music_app_main_event_cb( lv_obj_t * obj, lv_event_t event );
static void reset_music_app_main_event_cb( lv_obj_t * obj, lv_event_t event );

// void music_app_task( lv_task_t * task );

void music_app_main_setup( uint32_t tile_num ) {

    music_app_main_tile = mainbar_get_tile_obj( tile_num );
    lv_style_copy( &music_app_main_style, mainbar_get_style());

    lv_style_copy( &music_app_main_musicstyle, &music_app_main_style);
    lv_style_set_text_font( &music_app_main_musicstyle, LV_STATE_DEFAULT, &Ubuntu_32px);


    lv_obj_t * music_cont = mainbar_obj_create( music_app_main_tile );
    lv_obj_set_size( music_cont, LV_HOR_RES , LV_VER_RES / 2 );
    lv_obj_add_style( music_cont, LV_OBJ_PART_MAIN, &music_app_main_style );
    lv_obj_align( music_cont, music_app_main_tile, LV_ALIGN_CENTER, 0, 0 );

    // music_app_main_musiclabel = lv_label_create( music_cont , NULL);
    // lv_label_set_text(music_app_main_musiclabel, "00:00");
    // lv_obj_reset_style_list( music_app_main_musiclabel, LV_OBJ_PART_MAIN );
    // lv_obj_add_style( music_app_main_musiclabel, LV_OBJ_PART_MAIN, &music_app_main_musicstyle );
    // lv_obj_align(music_app_main_musiclabel, NULL, LV_ALIGN_CENTER, 0, 20);

    music_app_main_musiclabel2 = lv_label_create( music_cont , NULL);
    lv_label_set_text(music_app_main_musiclabel2, "Now Playing:");
    lv_obj_reset_style_list( music_app_main_musiclabel2, LV_OBJ_PART_MAIN );
    lv_obj_add_style( music_app_main_musiclabel2, LV_OBJ_PART_MAIN, &music_app_main_musicstyle );
    lv_obj_align(music_app_main_musiclabel2, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 0);

    music_app_main_start_btn = lv_btn_create(music_app_main_tile, NULL);  
    lv_obj_set_size(music_app_main_start_btn, 50, 50);
    lv_obj_add_style(music_app_main_start_btn, LV_IMGBTN_PART_MAIN, &music_app_main_style );
    lv_obj_align(music_app_main_start_btn, music_app_main_tile, LV_ALIGN_IN_BOTTOM_MID, 0, 0 );
    lv_obj_set_event_cb( music_app_main_start_btn, start_music_app_main_event_cb );

    lv_obj_t *music_app_main_start_btn_label = lv_label_create(music_app_main_start_btn, NULL);
    lv_label_set_text(music_app_main_start_btn_label, LV_SYMBOL_PLAY);



    music_app_main_stop_btn = lv_btn_create(music_app_main_tile, NULL);  
    lv_obj_set_size(music_app_main_stop_btn, 50, 50);
    lv_obj_add_style(music_app_main_stop_btn, LV_IMGBTN_PART_MAIN, &music_app_main_style );
    lv_obj_align(music_app_main_stop_btn, music_app_main_tile, LV_ALIGN_IN_BOTTOM_MID, 0, 0 );
    lv_obj_set_event_cb( music_app_main_stop_btn, stop_music_app_main_event_cb );
    lv_obj_set_hidden(music_app_main_stop_btn, true);

    lv_obj_t *music_app_main_stop_btn_label = lv_label_create(music_app_main_stop_btn, NULL);
    lv_label_set_text(music_app_main_stop_btn_label, LV_SYMBOL_STOP);



    music_app_main_reset_btn = lv_btn_create(music_app_main_tile, NULL);  
    lv_obj_set_size(music_app_main_reset_btn, 50, 50);
    lv_obj_add_style(music_app_main_reset_btn, LV_IMGBTN_PART_MAIN, &music_app_main_style );
    lv_obj_align(music_app_main_reset_btn, music_app_main_tile, LV_ALIGN_IN_BOTTOM_RIGHT,  -20, 0 );
    lv_obj_set_event_cb( music_app_main_reset_btn, reset_music_app_main_event_cb );

    lv_obj_t *music_app_main_reset_btn_label = lv_label_create(music_app_main_reset_btn, NULL);
    lv_label_set_text(music_app_main_reset_btn_label, LV_SYMBOL_EJECT);



    lv_obj_t * exit_btn = lv_imgbtn_create( music_app_main_tile, NULL);
    lv_imgbtn_set_src(exit_btn, LV_BTN_STATE_RELEASED, &exit_32px);
    lv_imgbtn_set_src(exit_btn, LV_BTN_STATE_PRESSED, &exit_32px);
    lv_imgbtn_set_src(exit_btn, LV_BTN_STATE_CHECKED_RELEASED, &exit_32px);
    lv_imgbtn_set_src(exit_btn, LV_BTN_STATE_CHECKED_PRESSED, &exit_32px);
    lv_obj_add_style(exit_btn, LV_IMGBTN_PART_MAIN, &music_app_main_style );
    lv_obj_align(exit_btn, music_app_main_tile, LV_ALIGN_IN_BOTTOM_LEFT, 10, -10 );
    lv_obj_set_event_cb( exit_btn, exit_music_app_main_event_cb );

}

static void start_music_app_main_event_cb( lv_obj_t * obj, lv_event_t event ) {
    switch( event ) {
        case( LV_EVENT_CLICKED ):       // Send PLAY Message
                                        log_i("Play clicked");
<<<<<<< HEAD
                                        char* musicCommand = "play";
=======
                                        String musicCommand = "play";
>>>>>>> 3cf933fff1a956402d254772973f7886e35e0d20
                                        ble_send_command(musicCommand);              // Notify value.
                                        break;
    }
}

static void stop_music_app_main_event_cb( lv_obj_t * obj, lv_event_t event ) {
    switch( event ) {
        case( LV_EVENT_CLICKED ):       // create an task that runs every secound
                                        log_i("Pause clicked");
<<<<<<< HEAD
                                        char* musicCommand = "pause";
=======
                                        String musicCommand = "pause";
>>>>>>> 3cf933fff1a956402d254772973f7886e35e0d20
                                        ble_send_command(musicCommand); 
                                        break;
    }
}

static void reset_music_app_main_event_cb( lv_obj_t * obj, lv_event_t event ) {
    switch( event ) {
        case( LV_EVENT_CLICKED ):       // Send Pause command 
                                        log_i("Stop clicked");
<<<<<<< HEAD
                                        char* musicCommand = "stop";
=======
                                        String musicCommand = "stop";
>>>>>>> 3cf933fff1a956402d254772973f7886e35e0d20
                                        ble_send_command(musicCommand); 
                                        break;
    }
}


static void exit_music_app_main_event_cb( lv_obj_t * obj, lv_event_t event ) {
    switch( event ) {
        case( LV_EVENT_CLICKED ):       mainbar_jump_to_maintile( LV_ANIM_OFF );
                                        break;
    }
<<<<<<< HEAD
}

void ble_send_command(){
    log_i("Play clicked");

    char* jsonString = (char*)"{t:\"music\",n:\"play\"}";

    char *arr_ptr = &jsonString[0];

    pTxCharacteristic->setValue(jsonString); // Set value.
    pTxCharacteristic->notify();                // Notify value.
=======
>>>>>>> 3cf933fff1a956402d254772973f7886e35e0d20
}