/****************************************************************************
**
** Copyright (C) 2013 Research In Motion
** Contact: http://www.qt-project.org/legal
**
** This file is part of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
** $QT_END_LICENSE$
**
****************************************************************************/
#ifndef WINDOWGRABBER_H
#define WINDOWGRABBER_H

#include <QAbstractNativeEventFilter>
#include <QObject>
#include <QTimer>

#include <screen/screen.h>

QT_BEGIN_NAMESPACE

class WindowGrabber : public QObject, public QAbstractNativeEventFilter
{
    Q_OBJECT

public:
    explicit WindowGrabber(QObject *parent = 0);
    ~WindowGrabber();

    void setFrameRate(int frameRate);

    void setWindowId(const QByteArray &windowId);

    void start();
    void stop();

    void pause();
    void resume();

    bool nativeEventFilter(const QByteArray &eventType, void *message, long *result) Q_DECL_OVERRIDE;

    QByteArray windowGroupId() const;

signals:
    void frameGrabbed(const QImage &frame);

private slots:
    void grab();

private:
    void cleanup();
    void updateFrameSize();

    QTimer m_timer;

    QByteArray m_windowId;

    screen_window_t m_window;
    screen_context_t m_screenContext;
    screen_pixmap_t m_screenPixmap;
    screen_buffer_t m_screenPixmapBuffer;

    char* m_screenBuffer;

    int m_screenBufferWidth;
    int m_screenBufferHeight;
    int m_screenBufferStride;

    bool m_active : 1;
    bool m_screenContextInitialized : 1;
    bool m_screenPixmapInitialized : 1;
    bool m_screenPixmapBufferInitialized : 1;
};

QT_END_NAMESPACE

#endif
