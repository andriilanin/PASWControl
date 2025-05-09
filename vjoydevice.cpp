#include "vjoydevice.h"
#include <windows.h>
#include "public.h"
#include "vJoyInterface.h"
#include <QDebug>

VJoyDevice::VJoyDevice(UINT id) : m_id(id), m_acquired(false) {
    if (!vJoyEnabled()) {
        qDebug() << "vJoy driver not enabled";
        return;
    }

    VjdStat status = GetVJDStatus(m_id);
    if (status != VJD_STAT_FREE && status != VJD_STAT_OWN) {
        qDebug() << "vJoy device not available";
        return;
    }

    m_acquired = AcquireVJD(m_id);
    if (m_acquired)
        qDebug() << "vJoy device" << m_id << "acquired";
    else
        qDebug() << "Failed to acquire vJoy device" << m_id;
}

VJoyDevice::~VJoyDevice() {
    if (m_acquired) {
        RelinquishVJD(m_id);
        qDebug() << "vJoy device" << m_id << "released";
    }
}

bool VJoyDevice::isValid() const {
    return m_acquired;
}

bool VJoyDevice::setAxis(LONG value, UINT axis) {
    return m_acquired && SetAxis(value, m_id, axis);
}

bool VJoyDevice::setButton(bool pressed, UINT button) {
    return m_acquired && SetBtn(pressed, m_id, button);
}
