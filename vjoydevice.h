#ifndef VJOYDEVICE_H
#define VJOYDEVICE_H

#include <windows.h>
#include "public.h"
#include "vJoyInterface.h"

class VJoyDevice {
public:
    explicit VJoyDevice(UINT id);
    ~VJoyDevice();

    bool isValid() const;
    bool setAxis(LONG value, UINT axis);
    bool setButton(bool pressed, UINT button);

private:
    UINT m_id;
    bool m_acquired;
};

#endif // VJOYDEVICE_H
