#include "windows.h"
#include "simple_logger.h"
#include "label.h"
#include "gfc_vector.h"
#include "simple_json.h"
#include "gf2d_config.h"



windowsManager windowsmanager = { 0 };


void windows_manager_close()
{
	windows_manager_clear(); // clear all windows first
	if (windowsmanager.windows_list != NULL)
	{
		free(windowsmanager.windows_list);
	}
	slog("windows manager closed");
}


void windows_manager_init(Uint32 max_windows)
{
	windowsmanager.windows_list = gfc_allocate_array(sizeof(windows), max_windows);
	if (windowsmanager.windows_list == NULL) {
		slog("failed to allocate array in windows_list");
		return;
	}
	windowsmanager.max_windows = max_windows;
	atexit(windows_manager_close);
	slog("windows system initialzed successfully");
}

/**
 * @brief draws all active entities to the screen
 */
void windows_manager_draw_all()
{
	int i;
	for (i = 0; i < windowsmanager.max_windows; i++)
	{
		if (!windowsmanager.windows_list[i]._inuse)continue;
		windows_draw(&windowsmanager.windows_list[i]);
	}
}

/**
 * @brief runs any think function for all active entities
 */
void windows_manager_think_all();


/**
 * @brief free all active entities
 * @note for use in level transitions.
 */
void windows_manager_clear()
{
	int i;
	for (i = 0; i < windowsmanager.max_windows; i++)
	{
		if (!windowsmanager.windows_list[i]._inuse)continue;
		windows_free(&windowsmanager.windows_list[i]);
	}
}

/**
 * @brief get a new empty windows
 * @returns NULL on error, or a pointer to a blank windows
 */
windows* windows_new()
{
	int i;
	for (i = 0; i < windowsmanager.max_windows; i++)
	{
		if (!windowsmanager.windows_list[i]._inuse)
		{
			//GOT ONE!
			windowsmanager.windows_list[i]._inuse = 1;
			windowsmanager.windows_list[i].draw_scale.x = 1;
			windowsmanager.windows_list[i].draw_scale.y = 1;
			return &windowsmanager.windows_list[i];
		}
	}
	slog("out of windows");
	return NULL;
}
windows* windows_load(char* filename)
{
	int i;
	float x, y;
	windows* win;
	win = windows_new();
	SJson *json, *window, *labelList, *label;
	json=sj_load(filename);
	if (!json)
	{
		slog("failed to load json file (%s) for the world data", filename);
		free(win);
		return NULL;
	}
	window = sj_object_get_value(json, "window");
	if (!window)
	{
		slog("failed to find player object in %s player config", filename);
		free(window);
		sj_free(json);
		return NULL;
	}
	win->spritename = sj_get_string_value(sj_object_get_value(window, "sprite"));
	win->sprite = gf2d_sprite_load_image(win->spritename);

	win->frame = 1;
	sj_value_as_vector2d(sj_object_get_value(window, "scale"), &win->draw_scale);
	sj_get_float_value(sj_array_get_nth(sj_object_get_value(window, "position"), 0), &x);
	sj_get_float_value(sj_array_get_nth(sj_object_get_value(window, "position"), 1), &y);
	vector2d_set(win->position, x, y);

	labelList = sj_object_get_value(window, "labels");
	win->labelCount = sj_array_get_count(labelList);
	slog("label count: %i", win->labelCount);
	win->labelList = gfc_allocate_array(sizeof(Label), win->labelCount);
	if (win->labelList == NULL) {
		slog("failed to allocate array in label_list");
		return;
	}
	slog("windows label list initialized");
	for (i = 0; i < win->labelCount; i++)
	{
		label = sj_array_get_nth(labelList, i);
		win->labelList[i] = label_load(win->labelList[i],label);
	}
	
	return win;
}
/**
 * @brief draws the given windows
 * @param windows the windows to draw
 */
void windows_draw(windows* windows)
{
	int i;
	Vector2D drawPosition;
	if (windows == NULL)
	{
		slog("null pointer provided, nothing to do!");
		return;
	}
	if (windows->sprite == NULL) {
		slog("no sprite to draw");
		return;// nothing to draw
	}
	vector2d_add(drawPosition, windows->position, windows->draw_offset);
	/*gf2d_sprite_draw(
		windows->sprite,
		drawPosition,
		&windows->draw_scale,
		NULL,
		NULL,
		NULL,
		NULL,
		(Uint32)windows->frame);*/
	gf2d_sprite_draw_image(windows->sprite, drawPosition);
	for (i=0; i < windows->labelCount; i++)
	{
		label_draw(windows->labelList[i]);
	}
}

/**
 * @brief free the memory of an windows
 * @param windows the windows to free
 */
void windows_free(windows* windows)
{
	if (windows == NULL)
	{
		slog("null pointer provided, nothing to do!");
		return;
	}
	if (windows->sprite != NULL)
	{
		gf2d_sprite_free(windows->sprite);
	}
	memset(windows, 0, sizeof(windows));
}

void windows_update(windows* ent)
{
	if (!ent)return;
	//generic upkeep

	if (ent->update)
	{
		ent->update(ent);
	}
}

void windows_update_all()
{
	int i;
	for (i = 0; i < windowsmanager.max_windows; i++)
	{
		if (!windowsmanager.windows_list[i]._inuse)continue;
		windows_update(&windowsmanager.windows_list[i]);
	}
}

windowsManager* windows_manager_get()
{
	return &windowsmanager;
}