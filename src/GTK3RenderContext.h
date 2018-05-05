/* 
 * Essex Engine
 * 
 * Copyright (C) 2017 Nathan Mentley - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the BSD license.
 *
 * You should have received a copy of the BSD license with
 * this file. If not, please visit: https://github.com/nathanmentley/EssexEngine
 */
#pragma once

#include <functional>

#include <cairo.h>
#include <gdk-pixbuf/gdk-pixbuf.h>
#include <gtk/gtk.h>

#include <EssexEngineCore/BaseUniquePointer.h>
#include <EssexEngineWindowDaemon/IRenderContext.h>

namespace EssexEngine{
namespace Drivers{
namespace GTK3{
    class GTK3RenderContext: public Daemons::Window::IRenderContext
    {
        public:
            GTK3RenderContext(WeakPointer<GtkDrawingArea> _canvas, int _height, int _width)
                :canvas(
                    BaseUniquePointer<GtkDrawingArea>(
                        _canvas,
                        GTK3RenderContext::DeleteCanvas
                    )
                ),
                cr(
                    BaseUniquePointer<cairo_t>(
                        gdk_cairo_create(gtk_widget_get_parent_window(canvas.ToWeakPointer().Cast<GtkWidget>().Get())),
                        GTK3RenderContext::DeleteCairo
                    )
                )
            {
                height = _height;
                width = _width;
            }
            ~GTK3RenderContext() {}
            
            void RenderToContext(WeakPointer<void> pixels) {
                GdkPixbuf* pixbuf = gdk_pixbuf_new_from_data(
                    pixels.Cast<guchar>().Get(),
                    GDK_COLORSPACE_RGB,
                    true,
                    8,
                    height,
                    width,
                    width * 4,
                    NULL,
                    NULL
                );

                
                gdk_cairo_set_source_pixbuf(cr.Get(), pixbuf, 0, 0);
                cairo_paint(cr.Get());

                g_object_unref(G_OBJECT(pixbuf));
                gtk_widget_queue_resize(canvas.ToWeakPointer().Cast<GtkWidget>().Get());
            }

            int GetHeight() {
                return height;
            }
            
            int GetWidth() {
                return width;
            }

            WeakPointer<GtkDrawingArea> GetCanvas() {
                return canvas.ToWeakPointer();
            }

            static void DeleteCairo(cairo_t* ptr) {
                cairo_destroy(ptr);
            }
            static void DeleteCanvas(GtkDrawingArea* ptr) {

            }
        private:
            BaseUniquePointer<GtkDrawingArea> canvas;
            BaseUniquePointer<cairo_t> cr;

            int height;
            int width;
    };
}}};
