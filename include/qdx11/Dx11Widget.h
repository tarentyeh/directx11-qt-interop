// Copyright (c) 2013, Hannes W�rfel <hannes.wuerfel@student.hpi.uni-potsdam.de>
// Computer Graphics Systems Group at the Hasso-Plattner-Institute, Germany
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//   * Redistributions of source code must retain the above copyright notice,
//     this list of conditions and the following disclaimer.
//   * Redistributions in binary form must reproduce the above copyright
//     notice, this list of conditions and the following disclaimer in the
//     documentation and/or other materials provided with the distribution.
//   * Neither the name of the Computer Graphics Systems Group at the
//     Hasso-Plattner-Institute (HPI), Germany nor the names of its
//     contributors may be used to endorse or promote products derived from
//     this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.

#ifndef DX11_WIDGET_H
#define DX11_WIDGET_H

// qt
#include <QWidget>
#include <QTimer>

// own
#include "BasicRenderer.h"
#include "IRendererFactory.h"

#include "Export.h"

namespace qdx11
{
    /**
    * @brief DirectX11 Context Widget.
    *
    * Subclass this widget if you want to handle Events,
    * implement a Camera Handler ...
    *  
    */
    class QDX11_API Dx11Widget : public QWidget
    {
	    Q_OBJECT
	    Q_DISABLE_COPY(Dx11Widget)

    public:
	    Dx11Widget(IRendererFactory* factory, QWidget* parent = NULL, Qt::WindowFlags flags = 0);
	    virtual ~Dx11Widget();

	    inline virtual QPaintEngine* paintEngine() const {return NULL;}

    protected:
	    virtual void paintEvent(QPaintEvent* e);
	    virtual void resizeEvent(QResizeEvent* e);
	    virtual void mousePressEvent(QMouseEvent* e);
	    virtual void mouseReleaseEvent(QMouseEvent* e);
	    virtual void mouseMoveEvent(QMouseEvent* e);
        virtual void wheelEvent(QWheelEvent* e);
        virtual void keyPressEvent(QKeyEvent* e);


    protected:
	    BasicRenderer* m_renderer;

	    QPoint m_prevMousePos;
	    bool m_leftMouseDown;
	    bool m_rightMouseDown;
    };
} // namespace qdx11

#endif // DX11_WIDGET_H