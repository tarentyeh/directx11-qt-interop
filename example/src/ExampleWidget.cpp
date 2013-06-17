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

// own
#include "ExampleWidget.h"
#include "Math.h"

    // qt
#include <QResizeEvent>

    // std
#include <iostream>
#include <sstream>

ExampleWidget::ExampleWidget(IRendererFactory* factory, QWidget* parent /* = NULL */, Qt::WFlags flags /* = 0 */)
    : Dx11Widget(factory, parent, flags)
{
    connect(m_renderThread, SIGNAL(fpsChanged(float, float)), this, SLOT(onFPSChanged(float, float)));
}

ExampleWidget::~ExampleWidget()
{
    if(m_renderThread)
        delete m_renderThread;

    if(m_interopState)
        delete m_interopState;
}

void ExampleWidget::mouseMoveEvent(QMouseEvent* e)
{
    if (m_leftMouseDown)
    {
        // orbit camera
        float dx = XMConvertToRadians(0.25f * static_cast<float>(e->pos().x() - m_prevMousePos.x()));
        float dy = XMConvertToRadians(0.25f * static_cast<float>(e->pos().y() - m_prevMousePos.y()));

        float theta = m_interopState->getTheta() + dx;
        float phi = m_interopState->getPhi() + dy;

        phi = Math::clamp(phi, 0.1f, Math::Pi - 0.1f);
        m_interopState->setTheta(theta);
        m_interopState->setPhi(phi);
    }

    if (m_rightMouseDown)
    {
        // change distance from camera
        float dx = 0.05f * static_cast<float>(e->pos().x() - m_prevMousePos.x());
        float dy = 0.05f * static_cast<float>(e->pos().y() - m_prevMousePos.y());

        float radius = m_interopState->getRadius() + dx - dy;

        radius = Math::clamp(radius, 5.0f, 20.0f);
        m_interopState->setRadius(radius);
    }

    m_prevMousePos = e->pos();
}

void ExampleWidget::onFPSChanged(float fps, float mspf)
{
    std::stringstream sstream;
    sstream << "fps: " << fps << "   millisecs/frame: " << mspf << "ms";
    QString message(sstream.str().c_str());

    emit updateStatusBar(message);
}