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
//#include <gdk/gdk.h>

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
                window(
                    gtk_widget_get_parent_window(canvas.ToWeakPointer().Cast<GtkWidget>().Get())
                )
            {
                height = _height;
                width = _width;
            }
            ~GTK3RenderContext() {}
            
            void RenderToContext(WeakPointer<void> pixels) {
                //Build drawing context, and stage it in a unique pointer to clean up memory
                BaseUniquePointer<GdkDrawingContext> drawingContext = BaseUniquePointer<GdkDrawingContext>(
                    gdk_window_begin_draw_frame(window.Get(), gdk_window_get_visible_region(window.Get())),
                    [=] (GdkDrawingContext* ptr) {
                        gdk_window_end_draw_frame(window.Get(), ptr);
                    }
                );

                //We don't need to memory manage these, but I like our pointer stuff, so let's use WeakPointers
                WeakPointer<GdkPixbuf> pixbuf = WeakPointer<GdkPixbuf>(
                    gdk_pixbuf_new_from_data(
                        pixels.Cast<guchar>().Get(),
                        GDK_COLORSPACE_RGB,
                        true,
                        8,
                        height,
                        width,
                        width * 4,
                        NULL,
                        NULL
                    )
                );
                WeakPointer<cairo_t> cr = WeakPointer<cairo_t>(
                    gdk_drawing_context_get_cairo_context(drawingContext.Get())
                );

                gdk_cairo_set_source_pixbuf(cr.Get(), pixbuf.Get(), 0, 0);
                cairo_paint(cr.Get());
            }

            int GetHeight() {
                return height;
            }
            
            int GetWidth() {
                return width;
            }

            static void DeleteCanvas(GtkDrawingArea* ptr) {

            }
        private:
            BaseUniquePointer<GtkDrawingArea> canvas;
            WeakPointer<GdkWindow> window;

            int height;
            int width;
    };
}}};
