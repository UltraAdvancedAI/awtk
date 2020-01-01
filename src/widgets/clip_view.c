﻿/**
 * File:   clip_view.c
 * Author: AWTK Develop Team
 * Brief:  clip view
 *
 * Copyright (c) 2018 - 2020  Guangzhou ZHIYUAN Electronics Co.,Ltd.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * License file for more details.
 *
 */

/**
 * History:
 * ================================================================
 * 2019-12-12 Lou ZhiMing <louzhiming@zlg.cn> created
 *
 */

#include "tkc/mem.h"
#include "widgets/clip_view.h"
#include "base/widget_vtable.h"

static ret_t clip_view_on_paint_children(widget_t* widget, canvas_t* c) {
  rect_t r = {0};
  rect_t r_save = {0};
  rect_t r_vg_save = {0};
  clip_view_t* clip_view = CLIP_VIEW(widget);
  vgcanvas_t* vg = canvas_get_vgcanvas(c);
  return_value_if_fail(clip_view != NULL, RET_BAD_PARAMS);

  canvas_get_clip_rect(c, &r_save);
  r_vg_save = rect_init(vg->clip_rect.x, vg->clip_rect.y, vg->clip_rect.w, vg->clip_rect.h);

  r = rect_init(c->ox, c->oy, widget->w, widget->h);
  canvas_set_clip_rect(c, &r);
  vgcanvas_clip_rect(vg, r.x, r.y, r.w, r.h);

  widget_on_paint_children_default(widget, c);

  vgcanvas_clip_rect(vg, r_vg_save.x, r_vg_save.y, r_vg_save.w, r_vg_save.h);
  canvas_set_clip_rect(c, &r_save);

  return RET_OK;
}

TK_DECL_VTABLE(clip_view) = {.size = sizeof(clip_view_t),
                             .type = WIDGET_TYPE_VIEW,
                             .parent = TK_PARENT_VTABLE(widget),
                             .create = clip_view_create,
                             .on_paint_children = clip_view_on_paint_children};

widget_t* clip_view_create(widget_t* parent, xy_t x, xy_t y, wh_t w, wh_t h) {
  return widget_create(parent, TK_REF_VTABLE(clip_view), x, y, w, h);
}

widget_t* clip_view_cast(widget_t* widget) {
  return_value_if_fail(WIDGET_IS_INSTANCE_OF(widget, clip_view), NULL);

  return widget;
}
