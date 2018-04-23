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

#include <gtk/gtk.h>

#include <EssexEngineWindowDaemon/IRenderContext.h>

namespace EssexEngine{
namespace Drivers{
namespace GTK3{
    class GTK3RenderContext: public Daemons::Window::IRenderContext
    {
        public:
            GTK3RenderContext(int _height, int _width) {
                height = _height;
                width = _width;
            }
            ~GTK3RenderContext() {
            }
            
            int GetHeight() {
                return height;
            }
            int GetWidth() {
                return width;
            }
        private:
            int height;
            int width;
    };
}}};
